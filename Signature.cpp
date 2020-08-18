#include "Signature.h"

Signature::Signature(cpp_int inp_r, cpp_int inp_s)
{
	this->r = inp_r;
	this->s = inp_s;
}

cpp_int Signature::getR()
{
	return this->r;
}

cpp_int Signature::getS()
{
	return this->s;
}
