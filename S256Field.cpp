#include "S256Field.h"

S256Field::S256Field()
{
}

S256Field::S256Field(cpp_int num)
{
	cpp_int s256_prime("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");

	this->num = num;
	this->prime = s256_prime;

	if (num >= this->prime || num < 0) {
		throw("Number is not in field range 0 to prime number");
	}
}

S256Field::S256Field(cpp_int num, cpp_int prime)
{
	if (num >= prime || num < 0) {
		throw("Number is not in field range 0 to prime number");
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

S256Field S256Field::pow(cpp_int exponent)
{
	exponent = exponent % (this->prime - 1);
	cpp_int result = ipow(this->num, exponent, this->prime);
	return S256Field(result, this->prime);
}

S256Field S256Field::operator/(const S256Field& operand)
{

	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");

	cpp_int denominator = ipow(operand.num, (this->prime - 2), this->prime);

 	cpp_int result = (this->num * denominator) % this->prime;
	
	return S256Field(result, this->prime);
}

cpp_int S256Field::sqrt()
{
	cpp_int exponent = (this->prime + 1) / 4;

	return this->pow(exponent).getNum();
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