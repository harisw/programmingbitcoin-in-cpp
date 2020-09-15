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

Tx::Tx(cpp_int inp_version, vector<TxIn> inp_tx_ins, vector<TxOut> inp_tx_outs, cpp_int inp_locktime, bool inp_testnet)
{
	this->version = inp_version;
	this->tx_ins = inp_tx_ins;
	this->tx_outs = inp_tx_outs;
	this->locktime = inp_locktime;
	this->testnet = inp_testnet;
}

string Tx::id()
{
	stringstream stream;
	stream << hex << this->hash();
	return stream.str();
}

cpp_int Tx::hash()
{
	string hash_result = hash256(this->serialize());
	hash_result = string(hash_result.rbegin(), hash_result.rend());
	return cpp_int("0x"+hash_result);
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
	
	result += byte_to_little_endian(dec_to_hex_byte(this->locktime, 4));
	return result;
}

cpp_int Tx::fee()
{
	cpp_int input_sum = 0;
	cpp_int output_sum = 0;

	vector<TxIn>::iterator it_in;
	for (it_in = this->tx_ins.begin(); it_in != this->tx_ins.end(); it_in++) {
		input_sum += it_in->value(this->testnet);
	}

	vector<TxOut>::iterator it_out;
	for (it_out = this->tx_outs.begin(); it_out != this->tx_outs.end(); it_out++) {
		output_sum += it_out->amount;
	}
	return input_sum - output_sum;
}

bool Tx::verify()
{
	if (this->fee() < 0)
		return false;

	for (int j = 0; j < this->tx_ins.size(); j++) {
		if (!this->verify_input(j))
			return false;
	}
	return true;
}

string Tx::sig_hash(int input_index)
{
	int SIGHASH_ALL = 1;

	string s = byte_to_little_endian(dec_to_hex_byte(this->version, 4));

	s += encode_varint(this->tx_ins.size());
	vector<TxIn>::iterator it_in;
	int index = 0;
	for (it_in = this->tx_ins.begin(); it_in != this->tx_ins.end(); it_in++) {
		if (index == input_index) {
			s += TxIn(it_in->prev_tx, it_in->prev_index, it_in->script_pubkey(testnet), it_in->sequence).serialize();
		}
		else {
			s += TxIn(it_in->prev_tx, it_in->prev_index, Script(), it_in->sequence).serialize();
		}
		index++;
	}

	s += encode_varint(this->tx_outs.size());
	vector<TxOut>::iterator it_out;
	index = 0;
	for (it_out = this->tx_outs.begin(); it_out != this->tx_outs.end(); it_out++) {
			s += it_out->serialize();
	}
	
	s += byte_to_little_endian(dec_to_hex_byte(this->locktime, 4));
	s += byte_to_little_endian(dec_to_hex_byte(SIGHASH_ALL, 4));
	string h256 = hash256(s);
	return h256;
}

bool Tx::verify_input(int input_index)
{
	TxIn curr_tx = this->tx_ins[input_index];
	Script script_pubkey = curr_tx.script_pubkey(this->testnet);
	string z = this->sig_hash(input_index);
	Script script_combined = curr_tx.script_sig + script_pubkey;
	return script_combined.evaluate(z);
}