#pragma once

#include "Script.h"

#ifndef TX_OUT_H
#define TX_OUT_H
#include "Helper.h"

class TxOut
{

public:
	cpp_int amount;
	Script script_pubkey;
	TxOut();
	TxOut(string &input_stream);
	TxOut(cpp_int inp_amount, Script inp_script);
	string serialize();
	void print();
};

#endif // !TX_OUT_H