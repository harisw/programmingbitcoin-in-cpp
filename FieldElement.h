#pragma once
#ifndef FIELD_H
#define FIELD_H


class FieldElement
{
private:
	int num;
	int prime;
public:
	FieldElement(int num, int prime);
	void print();
	bool operator==(const FieldElement& operand);
	FieldElement operator+(const FieldElement& operand);
	FieldElement operator-(const FieldElement& operand);
	FieldElement operator*(const FieldElement& operand);
	FieldElement operator^(int exponent);
	FieldElement operator/(const FieldElement& operand);
	int getNum();
	int getPrime();
};

#endif // !FIELD_H