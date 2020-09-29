#include "Signature.h"

Signature::Signature(cpp_int inp_r, cpp_int inp_s)
{
	this->r = inp_r;
	this->s = inp_s;
}

Signature::Signature(string signature_bin)
{
	string ori_bin = signature_bin;
	string compound = signature_bin.substr(0, 1 * BYTE_MULTIPLIER);
	signature_bin.erase(0, 1 * BYTE_MULTIPLIER);

	if (compound != "30")
		throw("Bad Signature!");
	

	cpp_int length("0x" + signature_bin.substr(0, 1*BYTE_MULTIPLIER));
	signature_bin.erase(0, 1 * BYTE_MULTIPLIER);

	if (length + 2 != signature_bin.length / BYTE_MULTIPLIER)
		throw("Bad Signature Length!");

	string marker = signature_bin.substr(0, 1 * BYTE_MULTIPLIER);
	signature_bin.erase(0, 1 * BYTE_MULTIPLIER);
}

cpp_int Signature::getR()
{
	return this->r;
}

cpp_int Signature::getS()
{
	return this->s;
}

string Signature::der()
{
	string result = "";
	cpp_int first_byte;
	string rbin = dec_to_hex_byte(this->r, 32);
	rbin.erase(0, min(rbin.find_first_not_of('0'), rbin.size() - 1));
	first_byte = cpp_int("0x"+rbin.substr(0, 2));
	if (first_byte & 0x80)
		rbin = "00" + rbin;
	rbin = "02" + to_string((rbin.length() / 2)) + rbin;
	result = rbin;

	string sbin = dec_to_hex_byte(this->s, 32);
	sbin.erase(0, min(sbin.find_first_not_of('0'), sbin.size() - 1));
	first_byte = cpp_int("0x" + sbin.substr(0, 2));
	if (first_byte & 0x80)
		sbin = "00" + sbin;

	sbin = "02" + to_string((sbin.length() / 2)) + sbin;
	
	result = result + sbin;
	result = "30" + to_string((result.length() / 2)) + result;
	return result;
}
