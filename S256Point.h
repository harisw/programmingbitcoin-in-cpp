#pragma once
#ifndef POINT_H
#define POINT_H

#include "S256Field.h"
#include "Signature.h"

class S256Point
{
private:
	S256Field  x;
	S256Field  y;
	S256Field  a;
	S256Field  b;
public:
	S256Point();
	S256Point(S256Field x, S256Field y);
	S256Point(S256Field x, S256Field y, S256Field  a, S256Field  b);
	S256Point(cpp_int x, cpp_int y);
	bool operator==(const S256Point& operand);
	S256Point operator+(S256Point& operand);
	S256Point operator*(cpp_int  scalar);
	friend S256Point operator*(cpp_int lhs, S256Point& rhs);
	S256Field  getX();
	S256Field  getY();
	S256Field  getA();
	S256Field  getB();
	bool verify(cpp_int z, Signature sig);
	string sec(bool compressed = true);
};

#endif