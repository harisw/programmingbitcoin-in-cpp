// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "S256Point.h"
#include "PrivateKey.h"
#include "Tx.h"
S256Point genPoint = S256Point(cpp_int{ "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" },
    cpp_int{ "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8" });

string prefix = "<<<<<<<<<<";
string suffix = ">>>>>>>>>>";
void ecc_test()
{

    cout << prefix << "  ELLIPTIC CURVE CRYPTOGRAPHY  " << suffix << endl << endl;
    cout << "Generator Point : " << endl;

    cout << "x = " << genPoint.getX().getNum() << endl;
    cout << "y = " << genPoint.getY().getNum() << endl;
    cout << "prime = " << genPoint.getY().getPrime() << endl;
    S256Point multiplied = 13 * genPoint;
    cout << "Scalar multiplication (13 * genPoint) = (" << multiplied.getX().getNum() << ",  " << multiplied.getY().getNum() << ")" << endl;


    cout << "Private Key(5003) : " << endl;
    PrivateKey priv_key = PrivateKey(5003);
    cpp_int z("0x"+sha256("Learning bitcoin"));
    cout << "z : " << z << endl;
    Signature example_sign = priv_key.sign(z);
    cout << "Signature DER : " << example_sign.der() << endl;
    cout << "Verification : " << priv_key.pub_key.verify(z, example_sign) << endl;
    cout << endl << endl << endl;
}

void serialization_test()
{
    cout << prefix << "  SERIALIZATION  " << suffix << endl << endl;

    cout << "Private Key(5003) : " << endl;
    PrivateKey priv_key = PrivateKey(5003);
    cpp_int z("0x" + sha256("Learning bitcoin"));
    cout << "z : " << z << endl;
    Signature example_sign = priv_key.sign(z);
    cout << "SEC Compressed : " << priv_key.pub_key.sec(true) << endl;
    cout << "SEC Uncompressed : " << priv_key.pub_key.sec(false) << endl;
    cout << "Signature DER : " << example_sign.der() << endl;
    cout << "Address : " << endl;
    cout << "Compressed Testnet :  " << priv_key.pub_key.address(true, true) << endl;
    cout << "Uncompressed Testnet :  " << priv_key.pub_key.address(false, true) << endl;
    cout << "Compressed Mainnet :  " << priv_key.pub_key.address(true, false) << endl;
    cout << "Uncompressed Mainnet :  " << priv_key.pub_key.address(false, false) << endl << endl << endl;
    
    cout << "Private Key WIF: " << endl;
    cout << "Compressed Testnet :  " << priv_key.wif(true, true) << endl;
    cout << "Uncompressed Testnet :  " << priv_key.wif(false, true) << endl;
    cout << "Compressed Mainnet :  " << priv_key.wif(true, false) << endl;
    cout << "Uncompressed Mainnet :  " << priv_key.wif(false, false) << endl << endl << endl;

}

void transaction_test()
{
    cout << prefix << "  TRANSACTION  " << suffix << endl << endl;
    string hex_trans = "010000000456919960ac691763688d3d3bcea9ad6ecaf875df5339e148a1fc61c6ed7a069e010000006a47304402204585bcdef85e6b1c6af5c2669d4830ff86e42dd205c0e089bc2a821657e951c002201024a10366077f87d6bce1f7100ad8cfa8a064b39d4e8fe4ea13a7b71aa8180f012102f0da57e85eec2934a82a585ea337ce2f4998b50ae699dd79f5880e253dafafb7feffffffeb8f51f4038dc17e6313cf831d4f02281c2a468bde0fafd37f1bf882729e7fd3000000006a47304402207899531a52d59a6de200179928ca900254a36b8dff8bb75f5f5d71b1cdc26125022008b422690b8461cb52c3cc30330b23d574351872b7c361e9aae3649071c1a7160121035d5c93d9ac96881f19ba1f686f15f009ded7c62efe85a872e6a19b43c15a2937feffffff567bf40595119d1bb8a3037c356efd56170b64cbcc160fb028fa10704b45d775000000006a47304402204c7c7818424c7f7911da6cddc59655a70af1cb5eaf17c69dadbfc74ffa0b662f02207599e08bc8023693ad4e9527dc42c34210f7a7d1d1ddfc8492b654a11e7620a0012102158b46fbdff65d0172b7989aec8850aa0dae49abfb84c81ae6e5b251a58ace5cfeffffffd63a5e6c16e620f86f375925b21cabaf736c779f88fd04dcad51d26690f7f345010000006a47304402200633ea0d3314bea0d95b3cd8dadb2ef79ea8331ffe1e61f762c0f6daea0fabde022029f23b3e9c30f080446150b23852028751635dcee2be669c2a1686a4b5edf304012103ffd6f4a67e94aba353a00882e563ff2722eb4cff0ad6006e86ee20dfe7520d55feffffff0251430f00000000001976a914ab0c0b2e98b1ab6dbf67d4750b0a56244948a87988ac005a6202000000001976a9143c82d7df364eb6c75be8c80df2b3eda8db57397088ac46430600";
    Tx trans = Tx(hex_trans);
    cout << "First input (prev_tx) : " << trans.tx_ins.front().prev_tx << endl;
    cout << "Last output (amount) : " << trans.tx_outs.back().amount << endl;
    //cout << "Tx Fee : " << trans.fee() << endl;
}

void script_test()
{
    //Exercise 3
    vector<string> first_script = { 
        string("76"), string("76"), string("95"), string("93"), string("56"), string("87") };
    vector<string> second_script = { string("52") };
    Script script_pubkey = Script(first_script);
    Script script_sig = Script(second_script);
    Script result = script_sig + script_pubkey;
    cout << "RESULT : " << result.evaluate(string("0")) << endl;

    //Exercise 4
    //first_script = {
    //    string("76"), string("76"), string("95"), string("93"), string("56"), string("87") };
    //second_script = { string("52") };
    //Script script_pubkey = Script(first_script);
    //Script script_sig = Script(second_script);
    //Script result = script_sig + script_pubkey;
    //cout << "RESULT : " << result.evaluate(string("0")) << endl;
}

int main()
{
    /*ecc_test();
    serialization_test();*/
    //transaction_test();
    script_test();
    //cpp_int x("0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798");

}