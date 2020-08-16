#include "S256Field.h"
#include <iostream>
using namespace std;

cpp_int ipow(cpp_int base, cpp_int exp, cpp_int prime = 0);
S256Field::S256Field()
{
}

S256Field::S256Field(cpp_int num)
{
	cpp_int s256_prime = ipow(2, 256) - ipow(2, 32) - 977;
	this->num = num;
	this->prime = s256_prime;

	if (num >= this->prime || num < 0) {
		throw("Number is not in field range 0 to prime number");
	}
}

S256Field::S256Field(cpp_int num, cpp_int prime)
{
	if (num >= prime || num < 0) {
		cerr << "Number is not in field range 0 to " << prime << endl;
		return;
	}
	this->num = num;
	this->prime = prime;
}

bool S256Field::operator==(cpp_int operand)
{
	return this->num == operand;
}

bool S256Field::operator!=(cpp_int operand)
{
	return this->num != operand;
}

bool S256Field::operator==(const S256Field& operand)
{
	return this->prime == operand.prime && this->num == operand.num;
}

bool S256Field::operator!=(const S256Field& operand)
{
	return !(this->prime == operand.prime && this->num == operand.num);
}

S256Field S256Field::operator+(const S256Field& operand)
{
	if ( this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	cpp_int result = (this->num + operand.num) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator-(const S256Field& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	cpp_int result = (this->num - operand.num) % this->prime;
	if (result < 0)
		result = (result + this->prime) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator*(const S256Field& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	cpp_int result = (this->num * operand.num) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator*(cpp_int operand)
{
	if (operand >= this->prime || operand < 0) {
		throw("Number is not in field range 0 to %d", this->prime);
	}

	cpp_int result = (this->num * operand) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator^(cpp_int exponent)
{
	exponent = exponent % (this->prime - 1);
	cpp_int result = ipow(this->num, exponent, this->prime);
	return S256Field(result, this->prime);
}

S256Field S256Field::operator/(const S256Field& operand)
{

	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	cpp_int exp = this->prime - 2;
	cpp_int temp = ipow(operand.num, exp, this->prime);

 	cpp_int result = (this->num * temp) % this->prime;
	
	return S256Field(result, this->prime);
}

cpp_int S256Field::getNum()
{
	return this->num;
}

cpp_int S256Field::getPrime()
{
	return this->prime;
}

S256Field operator*(cpp_int lhs, const S256Field& rhs)
{
	if (lhs >= rhs.prime || lhs < 0) {
		throw("Number is not in field range 0 to %d", rhs.prime);
	}

	cpp_int result = (rhs.num * lhs) % rhs.prime;
	return S256Field(result, rhs.prime);
}

//S256Field operator^(cpp_int lhs, const S256Field& rhs)
//{
//	lhs = lhs % (rhs.prime - 1);
//	double result = (int)pow(rhs.num, lhs) % rhs.prime;
//	return S256Field(result, rhs.prime);
//}

cpp_int ipow(cpp_int base, cpp_int exp, cpp_int prime)
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