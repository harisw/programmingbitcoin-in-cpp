#include "TxIn.h"
#include "TxOut.h"

#pragma once
#ifndef TX_H
#define TX_H

#include "Helper.h"

class TxIn;
class TxOut;

class Tx
{
public:
	cpp_int version;
	vector<TxIn> tx_ins;
	vector<TxOut> tx_outs;
	cpp_int locktime;
	bool testnet;

	Tx();
	Tx(string input_stream, bool testnet = false);
	string id();
	cpp_int hash();
	string serialize();
	cpp_int fee();
	bool verify();
	bool verify_input(int input_index);
	string sig_hash(int input_index);
};

#endif // !TX_H