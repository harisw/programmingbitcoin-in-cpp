#pragma once
#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "Helper.h"
//#include <boost/multiprecision/cpp_int.hpp>
//using boost::multiprecision::cpp_int;
//using namespace std;

class Signature
{
private:
	cpp_int r;
	cpp_int s;
public:
	Signature(cpp_int inp_r, cpp_int inp_s);
	cpp_int getR();
	cpp_int getS();
};

#endif