#pragma once
#ifndef S256F_H
#define S256F_H

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;
using namespace std;

class S256Field
{
private:
	cpp_int num;
	cpp_int prime;
public:
	S256Field();
	S256Field(cpp_int num, cpp_int prime);
	bool operator==(cpp_int rhs);
	bool operator!=(cpp_int rhs);
	bool operator==(const S256Field& rhs);
	bool operator!=(const S256Field& rhs);
	S256Field operator+(const S256Field& rhs);
	S256Field operator-(const S256Field& rhs);

	S256Field operator*(const S256Field& rhs);
	S256Field operator*(cpp_int rhs);
	friend S256Field operator*(cpp_int lhs, const S256Field& rhs);
	
	S256Field operator^(cpp_int exponent);
	//friend S256Field operator^(cpp_int lhs, const S256Field& rhs);
	S256Field operator/(const S256Field& rhs);
	cpp_int getNum();
	cpp_int getPrime();
};
#endif // !S256F_H