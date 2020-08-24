#pragma once
#ifndef HELPER_H
#define HELPER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
#include "SHA256.h"
#include "ripemd160.h"
using namespace std;
using namespace boost;
using boost::multiprecision::cpp_int;


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

//inline string dec_to_hex(cpp_int num, int width)
//{
//	stringstream stream;
//	stream << hex << num;
//	string result(stream.str());
//	return result;
//}

inline string dec_to_hex_byte(cpp_int num, int width = 0)
{
	stringstream stream;
	stream << setfill('0') << setw(width) << hex << num;
	
	return stream.str();
}

inline string int_to_byte(string inp, int byte_size)
{
	string result = inp;
	int zero_pad = byte_size - (result.size()/2);

	result = string(zero_pad, '0').append(result);
	return result;
}

inline string reverse_endian(string val)
{
	string result = "";
	int pos = 0;

	for (int j = val.size() - 1; j > 0; j -= 2) {
		result += val[j - 1];
		result += val[j];
		pos += 2;
	}
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
	return sha256(sha256(inp));
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
	inp = sha256(inp);
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
	cout << "INP : " << inp << endl;
	cout << "HASH256: " << hash_result << endl;
	string result = inp + hash_result.substr(0, 8);
	return encode_base58(result);
}
#endif // !HELPER_H