#pragma once
#ifndef TX_H
#define TX_H

#include "Helper.h"
#include "TxIn.h"
#include "TxOut.h"

class Tx
{
private:
	cpp_int version;
	vector<TxIn> tx_ins;
	vector<TxOut> tx_outs;
	cpp_int locktime;
	bool testnet;
public:
	Tx();
	Tx(string input_stream, bool testnet = false);
	string id();
	string hash();
	string serialize();
};

#endif // !TX_H