#pragma once
#ifndef S256F_H
#define S256F_H

class S256Field
{
private:
	int num;
	int prime;
public:
	S256Field();
	S256Field(int num, int prime);
	bool operator==(int rhs);
	bool operator!=(int rhs);
	bool operator==(const S256Field& rhs);
	bool operator!=(const S256Field& rhs);
	S256Field operator+(const S256Field& rhs);
	S256Field operator-(const S256Field& rhs);

	S256Field operator*(const S256Field& rhs);
	S256Field operator*(int rhs);
	friend S256Field operator*(int lhs, const S256Field& rhs);
	
	S256Field operator^(int exponent);
	friend S256Field operator^(int lhs, const S256Field& rhs);
	S256Field operator/(const S256Field& rhs);
	int getNum();
	int getPrime();
};
#endif // !S256F_H