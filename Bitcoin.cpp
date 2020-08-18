// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "S256Point.h"
#include <boost/lexical_cast.hpp>
using namespace boost;

int main()
{
    S256Field num1 = S256Field(190, 223);
    S256Field num2 = S256Field(7, 223);
    
    S256Field res = num1 + num2;
    cout << num1.getNum() << " + " << num2.getNum() << " = " << res.getNum() << endl;

    res = num1 - num2;
    cout << num1.getNum() << " - " << num2.getNum() << " = " << res.getNum() << endl;

    res = num1 * num2;
    cout << num1.getNum() << " * " << num2.getNum() << " = " << res.getNum() << endl;

    res = num1 ^ 32;
    cout << num1.getNum() << " ^ 32" << " = " << res.getNum() << endl;

    res = num1 / num2;
    cout << num1.getNum() << " / " << num2.getNum() << " = " << res.getNum() << endl;

    //int prime = 223;
    //S256Field x = S256Field(47, prime);
    //S256Field y = S256Field(71, prime);
    //S256Field a = S256Field(0, prime);
    //S256Field b = S256Field(7, prime);
    //S256Point finitePoint = S256Point(x, y, a, b);
    //finitePoint = finitePoint*20;
    
    
    /*string genX = "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
    string genY = "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";*/
    

    //cout << "Point : (" << finitePoint.getX().getNum() << " , " << finitePoint.getX().getNum() << ")" << endl;

}