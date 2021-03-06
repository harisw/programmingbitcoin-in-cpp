#pragma once

#ifndef S256F_H
#define S256F_H
#include "Helper.h"

class S256Field
{
private:
	cpp_int num;
	cpp_int prime;
public:
	S256Field();
	S256Field(cpp_int num);
	S256Field(cpp_int num, cpp_int prime);
	bool operator==(cpp_int rhs);
	bool operator!=(cpp_int rhs);
	bool operator==(const S256Field& other);
	bool operator!=(const S256Field& other);
	S256Field operator+(const S256Field& other);
	S256Field operator-(const S256Field& other);

	S256Field operator*(const S256Field& other);
	S256Field operator*(cpp_int rhs);
	friend S256Field operator*(cpp_int lhs, const S256Field& other);
	
	S256Field pow(cpp_int exponent);
	//friend S256Field operator^(cpp_int lhs, const S256Field& other);
	S256Field operator/(const S256Field& other);
	cpp_int sqrt();
	cpp_int getNum();
	cpp_int getPrime();
};
#endif // !S256F_H