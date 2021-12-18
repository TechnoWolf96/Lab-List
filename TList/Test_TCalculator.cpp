#include "TCalculatorList.h"
#include <iostream>
#include <cmath>
using namespace std;

void TestTCalculatorList()
{
    TCalculatorList a("5+24/2*4^(2+1)/3.2");
    cout << "Postfix: " << a.GetPostfix() << endl;
    cout << "Result Postfix: " << a.CalculatePostfix() << endl;
    cout << "Result: " << a.Calculate() << endl;
    cout << "Real Result: " << (5 + 24 / 2 * pow(4, 2 + 1) / 3.2);
}


int main()
{
    setlocale(LC_ALL, "eng");
    TestTCalculatorList();

    cout << endl;
    system("pause");
    return 0;
}