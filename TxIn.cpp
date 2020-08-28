#include "TxIn.h"

TxIn::TxIn(string inp_prev_tx, cpp_int inp_prev_index, string inp_script_sig, cpp_int inp_sequence)
{
	this->prev_tx = inp_prev_tx;
	this->prev_index = inp_prev_index;
	this->script_sig = inp_script_sig == "" ? Script() : inp_script_sig;
	this->sequence = inp_sequence;

}

TxIn::TxIn(string inp)
{
	string rest_inp;
	this->prev_tx = inp.substr(0, 64);
	rest_inp = inp.substr(64);

	this->prev_index = cpp_int("0x"+rest_inp.substr(0, 8));
	rest_inp = inp.substr(8);

	this->script_sig = Script(rest_inp);
	this->sequence = cpp_int(rest_inp);
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
