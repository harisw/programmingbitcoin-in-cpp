#pragma once
#ifndef TX_OUT_H
#define TX_OUT_H
#include "Helper.h"
#include "Script.h"

class TxOut
{
//private:
//	cpp_int amount;
//	Script script_pubkey;
public:
	cpp_int amount;
	Script script_pubkey;
	TxOut();
	TxOut(string &input_stream);
	string serialize();
	void print();
};

#endif // !TX_OUT_H