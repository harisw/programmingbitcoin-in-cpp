#include "Signature.h"

Signature::Signature(cpp_int inp_r, cpp_int inp_s)
{
	this->r = inp_r;
	this->s = inp_s;
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
	string rbin = int_to_byte(dec_to_hex(this->r), 32);
	rbin.erase(0, min(rbin.find_first_not_of('0'), rbin.size() - 1));		//REMOVE LEADING ZEROS
	if (stoi(rbin.substr(0, 2)) > 80)
		rbin = "00" + rbin;
	result = to_string((rbin.length()/2)) + rbin;

	string sbin = int_to_byte(dec_to_hex(this->r), 32);
	sbin.erase(0, min(sbin.find_first_not_of('0'), sbin.size() - 1));		//REMOVE LEADING ZEROS
	if (stoi(sbin.substr(0, 2)) > 80)
		sbin = "00" + sbin;
	result = result + to_string((sbin.length() / 2)) + sbin;

	result = "30" + to_string((result.length() / 2)) + result;
	return result;
}
