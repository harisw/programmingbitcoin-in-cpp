#include "Tx.h"

Tx::Tx()
{
}

Tx::Tx(string input_stream, bool testnet)
{
	this->version = little_endian_to_int(input_stream.substr(0, 8));
	input_stream.erase(0, 8);

	cpp_int num_inputs = read_varint(input_stream);
	for (cpp_int j = 0; j < num_inputs; j++) {
		this->tx_ins.push_back(TxIn(input_stream));
	}

	cpp_int num_outputs = read_varint(input_stream);
	for (cpp_int j = 0; j < num_outputs; j++) {
		this->tx_outs.push_back(TxOut(input_stream));
	}

	this->locktime = little_endian_to_int(input_stream);
}

string Tx::id()
{
	stringstream stream;
	stream << hex << this->hash();
	return stream.str();
}

string Tx::hash()
{
	string hash_result = hash256(this->serialize());

	return string(hash_result.rbegin(), hash_result.rend());
}

string Tx::serialize()
{
	string result = "";

	result = byte_to_little_endian(dec_to_hex_byte(this->version, 4));

	result += encode_varint(this->tx_ins.size());
	vector<TxIn>::iterator it_in;
	for (it_in = this->tx_ins.begin(); it_in != this->tx_ins.end(); it_in++) {
		result += it_in->serialize();
	}

	result += encode_varint(this->tx_outs.size());
	vector<TxOut>::iterator it_out;
	for (it_out = this->tx_outs.begin(); it_out != this->tx_outs.end(); it_out++) {
		result += it_out->serialize();
	}

	return result;
}
