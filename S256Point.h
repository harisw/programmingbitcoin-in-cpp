#include "S256Field.h"

#pragma once
#ifndef POINT_H
#define POINT_H

class S256Point
{
private:
	S256Field  x;
	S256Field  y;
	S256Field  a;
	S256Field  b;
public:
	S256Point(S256Field x, S256Field y);
	S256Point(S256Field x, S256Field y, S256Field  a, S256Field  b);
	S256Point(int x, int y, S256Field  a, S256Field  b);
	bool operator==(const S256Point& operand);
	S256Point operator+(S256Point& operand);
	S256Point operator*(int  scalar);
	friend S256Point operator*(int lhs, S256Point& rhs);
	S256Field  getX();
	S256Field  getY();
};

#endif