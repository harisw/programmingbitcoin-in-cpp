#include "TxIn.h"

TxIn::TxIn(string inp_prev_tx, cpp_int inp_prev_index, string inp_script_sig, cpp_int inp_sequence)
{
	this->prev_tx = inp_prev_tx;
	this->prev_index = inp_prev_index;
	this->script_sig = inp_script_sig == "" ? Script() : inp_script_sig;
	this->sequence = inp_sequence;

}

TxIn::TxIn(string &inp_stream)
{
	this->prev_tx = inp_stream.substr(0, 64);
	inp_stream.erase(0, 64);

	this->prev_index = cpp_int("0x"+inp_stream.substr(0, 8));
	inp_stream.erase(0, 8);

	this->script_sig = Script(inp_stream);
	this->sequence = cpp_int("0x"+inp_stream);
}

string TxIn::serialize()
{
	string  result;

	result = string(this->prev_tx.rbegin(), this->prev_tx.rend());

	result += byte_to_little_endian(dec_to_hex_byte(this->prev_index, 4));

	result += this->script_sig.serialize();

	result += byte_to_little_endian(dec_to_hex_byte(this->sequence, 4));

	return string();
}
