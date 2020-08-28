#pragma once
#ifndef TX_IN_H
#define TX_IN_H
#include "Helper.h"
#include "Script.h"

class TxIn
{
private:
	string prev_tx;
	cpp_int prev_index;
	Script script_sig;
	cpp_int sequence;
public:
	TxIn(string inp);
	TxIn(string inp_prev_tx, cpp_int inp_prev_index, string inp_script_sig = "", cpp_int inp_sequence = 0xffffffff);
	string serialize();
};


#endif // !TX_IN_H
