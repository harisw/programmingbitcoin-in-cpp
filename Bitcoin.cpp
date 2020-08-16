// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "S256Field.h"
#include "S256Point.h"
using namespace std;

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

    int prime = 223;
    S256Field x = S256Field(47, prime);
    S256Field y = S256Field(71, prime);
    S256Field a = S256Field(0, prime);
    S256Field b = S256Field(7, prime);
    S256Point finitePoint = S256Point(x, y, a, b);
    finitePoint = finitePoint*19;

}