#include "S256Point.h"
#include <cmath>
#include <iostream>
using namespace std;

S256Point::S256Point(S256Field x, S256Field y, S256Field a, S256Field b)
{
	this->x = x;
	this->y = y;
	this->a = a;
	this->b = b;

	if ((y^2) != ( (x^3) + a * x + b) )
		throw("S256Point (%d, %d) is not on the curve!", x, y);
}

S256Point::S256Point(int x, int y, S256Field a, S256Field b)
{
	this->x = S256Field(x, a.getPrime());
	this->y = S256Field(y, a.getPrime());
	this->a = a;
	this->b = b;
}

bool S256Point::operator==(const S256Point& operand)
{
	return this->x == operand.x && this->y == operand.y
		&& this->a == operand.a && this->b == operand.b;
}

S256Point S256Point::operator+(S256Point& operand)
{
 	if (this->a != operand.a || this->b != operand.b)
		throw("S256Point is not on the same curve!");

	//case 0 if one of the point at infinity
	if (this->x == NULL)
		return operand;
	if (&operand.x == NULL)
		return *this;

	//Case 1: self.x == other.x, self.y != other.y
	//Result is point at infinity
	if (this->x == operand.x && this->y != operand.y)
		return S256Point(NULL, NULL, this->a, this->b);

	/*Case 2: self.x ≠ other.x
	Formula(x3, y3) == (x1, y1) + (x2, y2)
	s = (y2 - y1) / (x2 - x1)
	x3 = s * *2 - x1 - x2
	y3 = s * (x1 - x3) - y1*/
	if (this->x != operand.x) {
		S256Field slope = (operand.y - this->y) / (operand.x - this->x);
		S256Field x3 = (slope^2) - this->x - operand.x;
		S256Field y3 = slope * (this->x - x3) - this->y;
		return S256Point(x3, y3, this->a, this->b);
	}

	/*Case 4: if we are tangent to the vertical line,
	we return the point at infinity
	note instead of figuring out what 0 is for each type
	we just use 0 * self.x*/
	if (*this == operand && this->y == 0)
		return S256Point(NULL, NULL, this->a, this->b);

	/*Case 3: self == other
	Formula(x3, y3) = (x1, y1) + (x1, y1)
	s = (3 * x1 * *2 + a) / (2 * y1)
	x3 = s * *2 - 2 * x1
	y3 = s * (x1 - x3) - y1*/
	if (*this == operand) {
		S256Field temp = (this->x ^ 2);
		cout << temp.getNum();
		S256Field temp1 = (2 * this->y);
		cout << temp1.getNum();
		S256Field temp2 = (3 * temp)+this->a;
		cout << temp2.getNum();
		
		S256Field slope = temp2 / temp1;
		S256Field x3 = (slope ^ 2) - 2 * this->x;
		temp = this->x - x3;
		temp = slope * (temp);
		S256Field y3 = temp - this->y;
		return S256Point(x3, y3, this->a, this->b);
	}
}

S256Point S256Point::operator*(int scalar)
{
	S256Point result = S256Point(NULL, NULL, this->a, this->b);
	for (int j = 1; j <= scalar; j++) {
		result = result + * this;
	}
	return result;
}

S256Field S256Point::getX()
{
	return this->x;
}

S256Field S256Point::getY()
{
	return this->y;
}

S256Point operator*(int lhs, S256Point& rhs)
{
	S256Point result = S256Point(NULL, NULL, rhs.a, rhs.b);
	for (int j = 1; j <= lhs; j++) {
		result = result + rhs;
	}
	return result;
}
