//#pragma once
#ifndef HELPER_H
#define HELPER_H

#define BYTE_MULTIPLIER 2
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include "ripemd160.h"
#include "sha256.h"


using namespace std;
using namespace boost;
using boost::multiprecision::cpp_int;


//int SIGHASH_ALL = 1;
//int SIGHASH_NONE = 2;
//int SIGHASH_SINGLE = 3;
//string BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

inline cpp_int ipow(cpp_int base, cpp_int exp, cpp_int prime = 0)
{
	cpp_int result = 1;
	if (prime == 0) {
		for (;;)
		{
			if (exp & 1) {
				result *= base;
			}
			exp >>= 1;
			if (!exp)
				break;
			base *= base;
		}
	}
	else {
		exp = exp % (prime - 1);		//TO REDUCE BIG EXPONENT AND FORCE THE EXPONENT NOT TO BE NEGATIVE
		for (;;)
		{
			if (exp & 1) {
				result *= base;
				result %= prime;
			}
			exp >>= 1;
			if (!exp)
				break;
			base *= base;
			base %= prime;
		}
	}

	return result;
}

inline string dec_to_hex_byte(cpp_int num, int width = 0)
{
	stringstream stream;
	stream << setfill('0') << setw(width) << hex << num;
	
	return stream.str();
}

inline string reverse_byte(string inp)
{
	string result = "";

	for (int j = inp.size() - 1; j > 0; j -= 2) {
		result += inp[j - 1];
		result += inp[j];
	}
	return result;
}
inline string byte_to_little_endian(string inp)
{
	string result = "";

	for (int j = inp.size() - 1; j > 0; j -= 2) {
		result += inp[j - 1];
		result += inp[j];
	}
	return result;

}

inline cpp_int little_endian_to_int(string inp)
{
	string result = "";
	
	if (inp.substr(0, 2) == "0x")
		inp.erase(0, 2);
	
	for (int j = inp.size() - 1; j > 0; j -= 2) {
		result += inp[j - 1];
		result += inp[j];
	}
	return cpp_int("0x" + result);
}

inline string little_endian_to_byte(string inp)
{
	string result = "";

	for (int j = inp.size() - 1; j > 0; j -= 2) {
		result += inp[j - 1];
		result += inp[j];
	}
	return result;
}

inline string int_to_byte(string inp, int byte_size)
{
	string result = inp;
	int zero_pad = byte_size - (result.size()/2);

	result = string(zero_pad, '0').append(result);
	return result;
}

inline string encode_base58(string inp)
{
	string BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	int leading_zeros = 0;
	for (int j = 0; j < inp.length(); j++) {
		if (inp[j] == '0')
			leading_zeros++;
		else
			break;
	}
	cpp_int num("0x"+inp);
	string prefix(leading_zeros, '1');
	string result = "";

	while (num > 0) {
		cpp_int quotient = num / 58;
		int remainder = (int)(num % 58);
		
		result = BASE58_ALPHABET[remainder] + result;
		num = quotient;
	}
	return prefix + result;
}

inline string hash256(string inp)
{	
	return sha256::hash_hex(sha256::hash_hex(inp));
}

inline string decode_base58(string inp)
{
	cout << "inp : " << inp << endl;
	string BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	cpp_int num = 0;
	for (int j = 0; j < inp.length(); j++) {
		num *= 58;
		num += BASE58_ALPHABET.find(inp[j]);
	}
	string combined = dec_to_hex_byte(num, 25);

	//string checksum = combined.substr(combined.size() - 4*BYTE_MULTIPLIER);
	//string hash_result = hash256(combined.substr(0, combined.size() - 4*BYTE_MULTIPLIER));
	//string temp_result = hash_result.substr(0, 4*BYTE_MULTIPLIER);
	

	//if ( temp_result != checksum) {
	//	cout << "Bad Address Checksum :: " << endl;
	//	throw("Bad Address");
	//}
	return combined.substr(1*BYTE_MULTIPLIER, combined.size() - 4*BYTE_MULTIPLIER);
	
}

inline string uint8_to_hex_string(const uint8_t* v, const size_t s) {
	std::stringstream ss;

	ss << std::hex << std::setfill('0');

	for (int i = 0; i < s; i++) {
		ss << std::hex << std::setw(2) << static_cast<int>(v[i]);
	}

	return ss.str();
}

inline string hash160(string inp)
{
	//boost::uint8_t sha256digest[cryptlite::sha256::HASH_SIZE];
	//cryptlite::sha256::hash(inp, sha256digest);
	//string hash_res = lexical_cast<string>(lexical_cast<int>(sha256digest));

	inp = sha256::hash_hex(inp);
	unsigned char* val = new unsigned char[inp.length() + 1];
	strcpy((char*)val, inp.c_str());

	unsigned char* hash = new unsigned char[sizeof(val) + 25];

	ripemd160(val, sizeof(val), hash);
	string result = uint8_to_hex_string(hash, sizeof(hash));
	return result;
}

inline string base58_checksum(string inp)
{
	string hash_result = hash256(inp);

	string result = inp + hash_result.substr(0, 8);
	return encode_base58(result);
}


inline string encode_varint(cpp_int inp)
{
	if (inp < 0xfd)
		return dec_to_hex_byte(inp);
	else if (inp < 0x10000)
		return "fd" + byte_to_little_endian(dec_to_hex_byte(inp, 2));
	else if (inp < 0x100000000)
		return "fe" + byte_to_little_endian(dec_to_hex_byte(inp, 4));
	else if (inp < cpp_int("0x10000000000000000"))
		return "ff" + byte_to_little_endian(dec_to_hex_byte(inp, 8));
	
	throw("Integer too large");
}

inline cpp_int read_varint(string &inp_stream)
{ 

	string first_byte = inp_stream.substr(0, 2);
	inp_stream.erase(0, 2);
	string result = "0x";
	if (first_byte == "fd") {
		result += inp_stream.substr(0, 4);
		inp_stream.erase(0, 4);
		return little_endian_to_int(result);
	}
	else if (first_byte == "fe") {
		result += inp_stream.substr(0, 8);
		inp_stream.erase(0, 8);
		return little_endian_to_int(result);
	}
	else if (first_byte == "fe") {
		result += inp_stream.substr(0, 16);
		inp_stream.erase(0, 16);
		return little_endian_to_int(result);
	}
	else {
		return cpp_int(result + first_byte);
	}
}

inline bool is_integer(string inp)
{
	try
	{
		lexical_cast<cpp_int>("0x" + inp);
		return true;
	}
	catch (bad_lexical_cast&)
	{
		return false;
		// if it throws, it's not a number.
	}
}
#endif // !HELPER_H