#include <iostream>
#include "BigReal.h"
using namespace std;

int main() {
    BigReal num1("-484.989898"), num2(1.09000000000), num3("2184.1485480000"), num4("484.5"), num5(num4), num;
    BigReal num8("441.55");
    cout << "enter Big Real : ";
    cin >> num1;
    cout << num1 << endl;
    cout << num5 << endl;
    cout << num2 << endl;
    cout << num4 << endl;
    cout << num1 + num2 << endl;
    cout << num1 - num2 << endl;
    cout << (num3 > num2) << endl;
    cout << (num1 < num3) << endl;
    num1 = num2 = num3;
    cout << num1 << "  " << num2 << "  " << num3 << endl;
    cout << (num1 == num2) << endl;
    cout << num1 + num2 << endl;
    cout << num1 - num2 << endl;
    return 0;
}
