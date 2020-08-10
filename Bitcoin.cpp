// Bitcoin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FieldElement.h"
using namespace std;

int main()
{
    FieldElement num1 = FieldElement(5, 7);
    FieldElement num2 = FieldElement(2, 7);
    
    FieldElement res = num1 + num2;
    cout << num1.getNum() << " + " << num2.getNum() << " = ";
    res.print();

    res = num1 - num2;
    cout << num1.getNum() << " - " << num2.getNum() << " = ";
    res.print();

    res = num1 * num2;
    cout << num1.getNum() << " * " << num2.getNum() << " = ";
    res.print();

    res = num1 ^ 3;
    cout << num1.getNum() << " ^ 3" << " = ";
    res.print();

    res = num1 / num2;
    cout << num1.getNum() << " / " << num2.getNum() << " = ";
    res.print();
    std::cout << "Hello World!\n";
}