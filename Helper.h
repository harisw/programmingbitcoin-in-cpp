#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
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

inline string dec_to_hex(cpp_int num)
{
	stringstream stream;
	stream << hex << num;
	string result(stream.str());
	return result;
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
#endif // !HELPER_H