#include "TxOut.h"

TxOut::TxOut()
{
}

TxOut::TxOut(string input_stream)
{
	string remainder;
	this->amount = little_endian_to_int(input_stream.substr(0, 16));
	remainder = input_stream.substr(16);

	this->script_pubkey = Script(remainder);
}

string TxOut::serialize()
{
	string result = "";
	result = byte_to_little_endian(dec_to_hex_byte(this->amount, 8));

	result += this->script_pubkey.serialize();

	return result;
}
