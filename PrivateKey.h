#pragma once
#ifndef PRIVKEY_H
#define PRIVKEY_H

#include "S256Point.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class PrivateKey
{
public:
	PrivateKey();
	PrivateKey(cpp_int inp_secret);
	Signature sign(cpp_int z);
	cpp_int random_int();
	string wif(bool compressed = true, bool testnet = false);
private:
	cpp_int secret;
	S256Point pub_key;
};

#endif // !1