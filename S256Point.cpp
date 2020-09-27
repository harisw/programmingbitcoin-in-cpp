#include "S256Point.h"
#define S256_A 0
#define S256_B 7

S256Point::S256Point()
{
}

S256Point::S256Point(S256Field x, S256Field y)
{
	this->x = x;
	this->y = y;
	this->a = S256Field(S256_A);
	this->b = S256Field(S256_B);

	if (x == 0 && y == 0)
		return;
	if ((this->y.pow(2)) != ((this->x.pow(3)) + (this->a*x) + this->b))
		throw("S256Point (%d, %d) is not on the curve!", x, y);
}

S256Point::S256Point(cpp_int x, cpp_int y)
{
	this->x = S256Field(x);
	this->y = S256Field(y);
	this->a = S256Field(S256_A);
	this->b = S256Field(S256_B);

	if (x == 0 && y == 0)
		return;

	if ((this->y.pow(2)) != ((this->x.pow(3)) + (this->a * x) + this->b))
		throw("S256Point (%d, %d) is not on the curve!", x, y);
}

S256Point::S256Point(S256Field x, S256Field y, S256Field a, S256Field b)
{
	this->x = x;
	this->y = y;
	this->a = a;
	this->b = b;

	if (x == 0 && y == 0)
		return;

	if ((this->y.pow(2)) != ((this->x.pow(3)) + (this->a * x) + this->b))
		throw("S256Point (%d, %d) is not on the curve!", x, y);
}

bool S256Point::operator==(const S256Point& other)
{
	return this->x == other.x && this->y == other.y
		&& this->a == other.a && this->b == other.b;
}

bool S256Point::operator!=(const S256Point& other)
{
	return !(*this == other);
}

S256Point S256Point::operator*(cpp_int scalar)
{
	S256Point result = S256Point((cpp_int)0, (cpp_int)0, this->a, this->b);
	S256Point current = *this;
	while (scalar) {
		if (scalar & 1)
			result = result + current;
		current = current + current;
		scalar >>= 1;
	}
	return result;
}

S256Point S256Point::operator+(S256Point& other)
{
 	if (this->a != other.a || this->b != other.b)
		throw("S256Point is not on the same curve!");

	//case 0 if one of the point at infinity
	if (this->x == NULL)
		return other;
	if (&other.x == NULL)
		return *this;

	//Case 1: self.x == other.x, self.y != other.y
	//Result is point at infinity
	if (this->x == other.x && this->y != other.y)
		return S256Point((cpp_int)0, (cpp_int)0, this->a, this->b);

	/*Case 2: self.x ≠ other.x
	Formula(x3, y3) == (x1, y1) + (x2, y2)
	s = (y2 - y1) / (x2 - x1)
	x3 = s * *2 - x1 - x2
	y3 = s * (x1 - x3) - y1*/
	if (this->x != other.x) {
		S256Field slope = (other.y - this->y) / (other.x - this->x);
		S256Field x3 = ((slope.pow(2)) - this->x) - other.x;
		S256Field y3 = (slope * (this->x - x3)) - this->y;
		return S256Point(x3, y3, this->a, this->b);
	}

	/*Case 4: if we are tangent to the vertical line,
	we return the point at infinity
	note instead of figuring out what 0 is for each type
	we just use 0 * self.x*/
	if (*this == other && this->y == 0)
		return S256Point((cpp_int)0, (cpp_int)0, this->a, this->b);

	/*Case 3: self == other
	Formula(x3, y3) = (x1, y1) + (x1, y1)
	s = (3 * x1 * *2 + a) / (2 * y1)
	x3 = s * *2 - 2 * x1
	y3 = s * (x1 - x3) - y1*/
	if (*this == other) {
		S256Field slope = ((3*(this->x.pow(2)))+this->a) / (2 * this->y);
		S256Field x3 = (slope.pow(2)) - 2 * this->x;
		S256Field y3 = (slope*(this->x - x3)) - this->y;
		return S256Point(x3, y3, this->a, this->b);
	}
}



S256Field S256Point::getX()
{
	return this->x;
}

S256Field S256Point::getY()
{
	return this->y;
}

S256Field S256Point::getA()
{
	return this->a;
}

S256Field S256Point::getB()
{
	return this->b;
}

bool S256Point::verify(cpp_int z, Signature sig)
{
	S256Point genPoint = S256Point(cpp_int{ "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" },
		cpp_int{ "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8" });

	cpp_int N{ "0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141" };

	cpp_int s_inv = ipow(sig.getS(), N - 2, N);
	cpp_int u = (z * s_inv) % N;
	cpp_int v = (sig.getR() * s_inv) % N;
	S256Point lh = (u * genPoint);
	S256Point rh = (v * *this);
	S256Point total =  lh + rh;
	return total.x.getNum() == sig.getR();
}

string S256Point::sec(bool compressed)
{
	string result = "";
	if (compressed) {
		if (this->y.getNum() % 2 == 0)
			result += "02";
		else
			result += "03";

		return result + dec_to_hex_byte(this->x.getNum(), 32);
	}
	else {
		result += "04";
		return result + dec_to_hex_byte(this->x.getNum(), 32) + dec_to_hex_byte(this->y.getNum(), 32);
	}
}

S256Point S256Point::parse(string sec_bin)
{
	cpp_int P("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");

	if (sec_bin.substr(0, 2) == "04") {
		cpp_int parsed_x(sec_bin.substr(2, 32));
		cpp_int parsed_y(sec_bin.substr(32, 32));
		return S256Point(parsed_x, parsed_y);
	}

	bool is_even = sec_bin.substr(0, 2) == "02";
	cpp_int parsed_x(sec_bin.substr(2));

	S256Field finite_x = S256Field(parsed_x);
	S256Field alpha = finite_x.pow(3) + S256Field(S256_B);
	S256Field beta = alpha.sqrt();
		
	S256Field even_beta;
	S256Field odd_beta;
	if (beta.getNum() % 2 == 0) {
		even_beta = beta;
		odd_beta = S256Field(P - beta.getNum());
	}
	else {
		even_beta = S256Field(P - beta.getNum());
		odd_beta = beta;
	}
		
	if(is_even)
		return S256Point(finite_x, even_beta);
	else
		return S256Point(finite_x, odd_beta);
}

string S256Point::address(bool compressed, bool testnet)
{
	string hash160_result = hash160(sec(compressed));
	string prefix;
	if (testnet)
		prefix = "6f";
	else
		prefix = "00";
	return base58_checksum(prefix + hash160_result);
}

S256Point operator*(cpp_int lhs, S256Point& rhs)
{
	S256Point result = S256Point((cpp_int)0, (cpp_int)0, rhs.a, rhs.b);
	S256Point current = rhs;
	while (lhs) {
		if (lhs & 1)
			result = result + current;
		current = current + current;
		lhs >>= 1;
	}
	return result;
}
