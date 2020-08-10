#include "FieldElement.h"
#include <iostream>
#include <cmath>
using namespace std;

FieldElement::FieldElement(int num, int prime)
{
	if(num >= prime || num < 0)
		throw("Number is not in field range 0 to %d", prime-1);
	this->num = num;
	this->prime = prime;
}

void FieldElement::print()
{
	cout << this->num << " in F" << this->prime << endl;
}

bool FieldElement::operator==(const FieldElement& operand)
{
	return this->prime == operand.prime && this->num == operand.num;
}

FieldElement FieldElement::operator+(const FieldElement& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num + operand.num) % this->prime;
	return FieldElement(result, this->prime);
}

FieldElement FieldElement::operator-(const FieldElement& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num - operand.num) % this->prime;
	return FieldElement(result, this->prime);
}

FieldElement FieldElement::operator*(const FieldElement& operand)
{
	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	int result = (this->num * operand.num) % this->prime;
	return FieldElement(result, this->prime);
}

FieldElement FieldElement::operator^(int exponent)
{
	exponent = exponent % (this->prime - 1);
	double result = (int)pow(this->num,exponent) % this->prime;
	return FieldElement(result, this->prime);
}

FieldElement FieldElement::operator/(const FieldElement& operand)
{

	if (this->prime != operand.prime)
		throw("Cannot add two numbers in different field");
	double result = (this->num * ((int)pow(operand.num, this->prime-2)%this->prime) ) % this->prime;
	return FieldElement(result, this->prime);
}

int FieldElement::getNum()
{
	return this->num;
}

int FieldElement::getPrime()
{
	return this->prime;
}

