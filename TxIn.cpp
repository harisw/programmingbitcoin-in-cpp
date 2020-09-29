#include "TxIn.h"

wstring TxIn::testnet_url = L"http://testnet.programmingbitcoin.com/tx/";
wstring TxIn::mainnet_url = L"http://mainnet.programmingbitcoin.com/tx/";

TxIn::TxIn(string inp_prev_tx, cpp_int inp_prev_index, Script inp_script_sig, cpp_int inp_sequence)
{
	this->prev_tx = inp_prev_tx;
	this->prev_index = inp_prev_index;
	this->script_sig = inp_script_sig;
	this->sequence = inp_sequence;

}


TxIn::TxIn(string &inp_stream)
{
	this->prev_tx = little_endian_to_byte(inp_stream.substr(0, 32*BYTE_MULTIPLIER));
	inp_stream.erase(0, 32 * BYTE_MULTIPLIER);

	this->prev_index = little_endian_to_int(inp_stream.substr(0, 4*BYTE_MULTIPLIER));
	inp_stream.erase(0, 4 * BYTE_MULTIPLIER);

	this->script_sig = Script(inp_stream);
	this->sequence = little_endian_to_int(inp_stream.substr(0, 4 * BYTE_MULTIPLIER));
	inp_stream.erase(0, 4 * BYTE_MULTIPLIER);
}

string TxIn::serialize()
{
	string  result;

	result = reverse_byte(this->prev_tx);


	result += reverse_byte(dec_to_hex_byte(this->prev_index, 4 * BYTE_MULTIPLIER));

	result += this->script_sig.serialize();

	result += dec_to_hex_byte(this->sequence, 4 * BYTE_MULTIPLIER);

	return result;
}

void TxIn::print()
{
	cout << this->prev_tx << "  :  " << this->prev_index << endl;
}

Tx TxIn::fetch_tx(bool testnet)
{
	string tx_id = this->prev_tx;
	IStream* stream;
	wstring temp_url = testnet ? this->testnet_url : this->mainnet_url;

	string tx_url = tx_id + ".hex";
	temp_url += wstring(tx_url.cbegin(), tx_url.cend());
	LPCWSTR url = temp_url.c_str();

	HRESULT result = URLOpenBlockingStream(0, url, &stream, 0, 0);
	if (result != 0)
	{
		throw("Http Fetching Error");
	}
	char buffer[500];
	unsigned long bytesRead;
	stringstream ss;
	stream->Read(buffer, 500, &bytesRead);
	while (bytesRead > 0U)
	{
		ss.write(buffer, (long long)bytesRead);
		stream->Read(buffer, 500, &bytesRead);
	}
	stream->Release();
	string raw = ss.str();
	Tx result_tx;
	cout << "FETCHER " << endl;
	try
	{
		algorithm::trim(raw);
		string result;

		if (raw.substr(4*BYTE_MULTIPLIER, 2) == "00") {
			result = raw.substr(0, 4) + raw.substr(6);
			result_tx = Tx(result, testnet);

			string locktime = string(result.rbegin(), result.rend());
			result_tx.locktime = little_endian_to_int(locktime.substr(4));
		}
		else {
			result_tx = Tx(raw, testnet);
		}

		if (result_tx.id() != tx_id)
			throw("Tx ID is not the same!");
	}
	catch (int e)
	{
		cout << "Exception occured, Exception " << e << endl;
	}
	return result_tx;
}

cpp_int TxIn::value(bool testnet)
{
	Tx prev_transaction = this->fetch_tx(testnet);

	return prev_transaction.tx_outs[this->prev_index.convert_to<int>()].amount;
}

Script TxIn::script_pubkey(bool testnet)
{
	Tx prev_transaction = this->fetch_tx(testnet);
	return prev_transaction.tx_outs.at((int)this->prev_index).script_pubkey;
}
