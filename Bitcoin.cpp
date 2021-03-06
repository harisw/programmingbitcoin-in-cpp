// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
//#include "S256Point.h"
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
    string hash_res = hash256("Programming Bitcoin");
    cout << "hash256 : " << hash_res << endl;

    cpp_int z("0x"+hash_res);
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
    
    string hash_res = "af9875";
    cout << "sha256 : " << hash_res << endl;
    cpp_int z("0x" + hash_res);
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
    Script script_pubkey, script_sig, result;

    //P2PK PAGE 115
    string z = "0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d";
    string sec = "04887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34";
    string sig = "3045022000eff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c022100c7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab601";
    script_pubkey = Script({ sec, string("0xac") });
    vector<string> temp = { sig };
    script_sig = Script(temp);
    result = script_sig + script_pubkey;
    cout << "P2PK TEST : " << result.evaluate(z) << endl << endl;


    //Exercise 3
    vector<string> first_script = { 
        string("76"), string("76"), string("95"), string("93"), string("56"), string("87") };
    vector<string> second_script = { string("52") };
    script_pubkey = Script(first_script);
    script_sig = Script(second_script);
    result = script_sig + script_pubkey;
    cout << "RESULT : " << result.evaluate(string("0")) << endl;

    
}

void transaction_creation_validation_test()
{
    //TRANSACTION CREATION PAGE 140
    string prev_tx = "0d6fe5213c0b3291f208cba8bfb59b7476dffacc4e5cb66f6eb20a080843a299";
    cpp_int prev_index = 13;
    vector<TxIn> tx_ins;
    TxIn tx_in = TxIn(prev_tx, prev_index);
    tx_ins.push_back(tx_in);

    vector<TxOut> tx_outs;
    cpp_int change_amount = lexical_cast<cpp_int>(0.33 * 100000000);
    string change_h160 = decode_base58("mzx5YhAH9kNHtcN481u6WkjeHjYtVeKVh2");

    Script change_script = Op::p2pkh_script(change_h160);
    TxOut change_output = TxOut(change_amount, change_script);
    tx_outs.push_back(change_output);

    cpp_int target_amount = lexical_cast<cpp_int>(0.1 * 100000000);
    string target_h160 = decode_base58("mnrVtF8DWjMu839VW3rBfgYaAfKk8983Xf");
    Script target_script = Op::p2pkh_script(target_h160);
    TxOut target_output = TxOut(target_amount, target_script);
    tx_outs.push_back(target_output);

    Tx tx_obj = Tx(1, tx_ins, tx_outs, 0, true);
    tx_obj.print();
}

void transaction_signing_test()
{
    string stream = "0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600";
    Tx transaction = Tx(stream);
    cpp_int z = cpp_int("0x"+transaction.sig_hash(0));
    PrivateKey priv_key = PrivateKey(8675309);
    
    string der = priv_key.sign(z).der();
    string sig = der + to_string(SIGHASH_ALL);
    string sec = priv_key.pub_key.sec();
    
    Script script_sig = Script({ sig, sec });
    transaction.tx_ins[0].script_sig = script_sig;
    cout << "RESULT : " << transaction.serialize() << endl;
}

void transaction_creation_on_testnet()
{
    cpp_int secret = cpp_int("0x" +reverse_byte(hash256("This is my secret")));
    PrivateKey priv_key = PrivateKey(secret);
    cout << "Address : " << priv_key.pub_key.address(true);
}

int main()
{
    //ecc_test();
    //serialization_test();
    //transaction_test();
    script_test();
    //transaction_creation_validation_test();
    //transaction_signing_test();
    //transaction_creation_on_testnet();

}