// FCAI – Object-Oriented Programming – 2022 - Assignment 2
// Program Name: BigReal
// Last Modification Date: 5/11/2022
// Author1 : Mario Malak Alabd, ID: 20210313, Section : 5
// Author2 : Kirolos Osama Adib, ID: , Section : 5
// Author3 : Ehab Ashraf, ID: , Section : 5
/*
description: In this problem we developed new class Big Real.
that can hold unlimited real values and performs arithmetic operations on them.
such as: +, -, <, and >.
 */

#ifndef BIGREALV3_BIGREAL_H
#define BIGREALV3_BIGREAL_H
#include "BigDecimalIntClass.h"


class BigReal {
private:
    BigDecimalInt decimalPart;
    BigDecimalInt floatPart;
    char Sign;
    void addFloatParts(BigReal &real1, BigReal &real2, BigReal &answer);
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    bool   checkValidInput(string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal &anotherReal);
    bool operator> (BigReal &anotherReal);
    bool operator== (BigReal &anotherReal);
    int size();
    int sign();
    friend ostream& operator << (ostream& out, BigReal& num);
    friend istream& operator >> (istream& in, BigReal& num);
};


#endif //BIGREALV3_BIGREAL_H
