// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "S256Point.h"
#include "PrivateKey.h"

S256Point genPoint = S256Point(cpp_int{ "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" },
    cpp_int{ "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8" });

string prefix = "<<<<<<<<<<";
string suffix = ">>>>>>>>>>";
void ecc_test()
{

    cout << prefix << " ELLIPTIC CURVE CRYPTOGRAPHY " << suffix << endl << endl;
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
    cout << prefix << " SERIALIZATION " << suffix << endl << endl;

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

int main()
{
    ecc_test();
    serialization_test();
    //cpp_int x("0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798");    

    /*a 32-bit hexadecimal number*/
    //cpp_int x("0x175e3");
    //cpp_int x(1234567891011121314);
    //cout << x << endl;
    //string bytearr = int_to_byte(x, 32);

    //cout << bytearr << endl;

    //string reversed_byte = reverse_endian(bytearr);
    //
    //cout << reversed_byte << endl;

    Signature example = Signature(cpp_int{ "0x37206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6" },
            cpp_int{ "0x8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec" });
    cout << "DER : " << example.der() << endl;
    PrivateKey priv_key = PrivateKey(5003);
    //cout << "SEC : " << priv_key.pub_key.sec(false) << endl << endl;
    /*cout << "Private Key X : " << dec_to_hex_byte(priv_key.pub_key.getX().getNum()) << endl;
    cout << "Private Key Y : " << dec_to_hex_byte(priv_key.pub_key.getY().getNum()) << endl<<endl;*/
    cout << "Address : " << priv_key.pub_key.address(true, true) << endl;
    cout << "Address : " << priv_key.wif(true, true) << endl;
    //cout << PrivateKey(5000).pub_key.address(false, true) << endl;
    //S256Field num1 = S256Field(190, 223);
    //S256Field num2 = S256Field(7, 223);
    //
    //S256Field res = num1 + num2;
    //cout << num1.getNum() << " + " << num2.getNum() << " = " << res.getNum() << endl;

    //res = num1 - num2;
    //cout << num1.getNum() << " - " << num2.getNum() << " = " << res.getNum() << endl;

    //res = num1 * num2;
    //cout << num1.getNum() << " * " << num2.getNum() << " = " << res.getNum() << endl;

    //res = num1 ^ 32;
    //cout << num1.getNum() << " ^ 32" << " = " << res.getNum() << endl;

    //res = num1 / num2;
    //cout << num1.getNum() << " / " << num2.getNum() << " = " << res.getNum() << endl;

    //int prime = 223;
    //S256Field x = S256Field(47, prime);
    //S256Field y = S256Field(71, prime);
    //S256Field a = S256Field(0, prime);
    //S256Field b = S256Field(7, prime);
    //S256Point finitePoint = S256Point(x, y, a, b);
    //finitePoint = finitePoint*20;    

    //cout << "Point : (" << finitePoint.getX().getNum() << " , " << finitePoint.getX().getNum() << ")" << endl;

}