#pragma once
#ifndef TX_FETCHER_H
#define TX_FETCHER_H

#include "Helper.h"
class Tx;

class TxFetcher
{

private:
	string testnet_url = "http://testnet.programmingbitcoin.com";
	string mainnet_url = "http://mainnet.programmingbitcoin.com";
	vector<cpp_int> cache;
public:
	cpp_int fetch(string tx_id, bool testnet = false, bool fresh = false);
};

#endif // !TX_FETCHER_H