// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "S256Field.h"
#include "S256Point.h"
using namespace std;

int main()
{
    S256Field num1 = S256Field(5, 7);
    S256Field num2 = S256Field(2, 7);
    
    S256Field res = num1 + num2;
    cout << num1.getNum() << " + " << num2.getNum() << " = ";

    res = num1 - num2;
    cout << num1.getNum() << " - " << num2.getNum() << " = ";

    res = num1 * num2;
    cout << num1.getNum() << " * " << num2.getNum() << " = ";

    res = num1 ^ 3;
    cout << num1.getNum() << " ^ 3" << " = ";

    res = num1 / num2;
    cout << num1.getNum() << " / " << num2.getNum() << " = ";

    int prime = 223;
    S256Field x = S256Field(47, prime);
    S256Field y = S256Field(71, prime);
    S256Field a = S256Field(0, prime);
    S256Field b = S256Field(7, prime);
    S256Point finitePoint = S256Point(x, y, a, b);
    //Point invalid = Point(200, 119, 0, 7);

}