#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <cmath>
using boost::multiprecision::cpp_int;
using namespace std;

//cpp_int ipow(cpp_int base, cpp_int exp, cpp_int prime = 0);


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
#endif // !HELPER_H