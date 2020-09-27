#pragma comment(lib, "urlmon.lib")

#pragma once
#include "Script.h"

#ifndef TX_IN_H
#define TX_IN_H

#include <urlmon.h>
#include <WinInet.h>

class Tx;

class TxIn
{
private:
	static wstring testnet_url;
	static wstring mainnet_url;
public:
	string prev_tx;
	cpp_int prev_index;
	Script script_sig;
	cpp_int sequence;
	TxIn(string &inp_stream);
	TxIn(string inp_prev_tx, cpp_int inp_prev_index, Script inp_script_sig = Script(), cpp_int inp_sequence = 0xffffffff);
	void print();
	string serialize();
	Tx fetch_tx(bool testnet = false);
	cpp_int value(bool testnet = false);
	Script script_pubkey(bool testnet = false);
};

#include "Tx.h"

#endif // !TX_IN_H
