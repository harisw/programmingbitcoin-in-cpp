#pragma once

#ifndef SIGNATURE_H
#define SIGNATURE_H
#include "Helper.h"

class Signature
{
private:
	cpp_int r;
	cpp_int s;
public:
	Signature(cpp_int inp_r, cpp_int inp_s);
	Signature(string signature_bin);
	cpp_int getR();
	cpp_int getS();
	string der();
};

#endif