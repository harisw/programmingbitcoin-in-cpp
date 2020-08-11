#include "S256Field.h"
#include <iostream>
using namespace std;

S256Field::S256Field()
{
}

S256Field::S256Field(int num, int prime)
{
	if (num >= prime || num < 0) {
		cerr << "Number is not in field range 0 to " << prime << endl;
		return;
	}
	this->num = num;
	this->prime = prime;
}

bool S256Field::operator==(int operand)
{
	return this->num == operand;
}

bool S256Field::operator!=(int operand)
{
	return this->num != operand;
}

bool S256Field::operator==(const S256Field& operand)
{
	return this->prime == operand.prime && this->num == operand.num;
}

bool S256Field::operator!=(const S256Field& operand)
{
	return this->prime != operand.prime && this->num != operand.num;;
}

S256Field S256Field::operator+(const S256Field& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num + operand.num) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator-(const S256Field& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num - operand.num) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator*(const S256Field& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num * operand.num) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator*(int operand)
{
	if (operand >= this->prime || operand < 0) {
		throw("Number is not in field range 0 to %d", this->prime);
	}

	int result = (this->num * operand) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator^(int exponent)
{
	exponent = exponent % (this->prime - 1);
	double result = (int)pow(this->num, exponent) % this->prime;
	return S256Field(result, this->prime);
}

S256Field S256Field::operator/(const S256Field& operand)
{

	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	double result = (this->num * ((int)pow(operand.num, this->prime - 2) % this->prime)) % this->prime;
	return S256Field(result, this->prime);
}

int S256Field::getNum()
{
	return this->num;
}

int S256Field::getPrime()
{
	return this->prime;
}

S256Field operator*(int lhs, const S256Field& rhs)
{
	if (lhs >= rhs.prime || lhs < 0) {
		throw("Number is not in field range 0 to %d", rhs.prime);
	}

	int result = (rhs.num * lhs) % rhs.prime;
	return S256Field(result, rhs.prime);
}

S256Field operator^(int lhs, const S256Field& rhs)
{
	lhs = lhs % (rhs.prime - 1);
	double result = (int)pow(rhs.num, lhs) % rhs.prime;
	return S256Field(result, rhs.prime);
}
