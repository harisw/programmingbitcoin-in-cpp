// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "S256Point.h"
#include "PrivateKey.h"

int main()
{

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


    cout << PrivateKey(5000).pub_key.address(false, true) << endl;
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