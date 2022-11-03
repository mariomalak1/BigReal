//    cout << "fractionPart : " << fractionPart << endl;
//    cout << "floatPart : " << subString(fractionPart, 2, fractionPart.length() - 1) << endl;
//this->floatPart.setNumber(floatPart.getNumber().erase(0,1));

#include "BigReal.h"

// user defined function to cut the string from I want that help me in BigReal
// function that takes string that I want to cut from it and the first index and last index
// return new string that is sub string from the param I pass it
string subString(string str, int index1, int index2){
    string newString;
    cout << "str.length() : " << str.length() << "  " << "index1 : "  << index1 << "  " << "index2 : " << index2 << endl;
    if(index1 >= 0 and index2 >= 0 and index2 < str.length() and index1 < str.length() and index1 <= index2){
        for (int i = index1; i <= index2; ++i) {
            newString += str[i];
        }
        return newString;
    }
    return newString;
}

void BigReal::addFloatParts(BigReal &real1, BigReal &real2, BigReal &answer) {
    int lenFrac1 = real1.floatPart.size();
    int lenFrac2 = real2.floatPart.size();
    BigDecimalInt floatNumber;

    floatNumber = real1.floatPart + real2.floatPart;

    if(lenFrac1 > lenFrac2){
        if (floatNumber.size() > lenFrac1){
            BigDecimalInt reminder(to_string(floatNumber.getNumber()[0]));
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size()));
            answer.floatPart = reminderFloatPart;
        }else{
            answer.floatPart = floatNumber;
        }
    }
    else if (lenFrac2 > lenFrac1){
        if (floatNumber.size() > lenFrac2){
            BigDecimalInt reminder(to_string(floatNumber.getNumber()[0]));
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size()));
            answer.floatPart = reminderFloatPart;
        }else{
            answer.floatPart = floatNumber;
        }
    }
    else{
        if (floatNumber.size() > lenFrac1){
            BigDecimalInt reminder(to_string(floatNumber.getNumber()[0]));
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size()));
            answer.floatPart = reminderFloatPart;
        }
        else if (floatNumber.size() > lenFrac2){
            BigDecimalInt reminder(to_string(floatNumber.getNumber()[0]));
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size()));
            answer.floatPart = reminderFloatPart;
        }
        else{
            answer.floatPart = floatNumber;
        }
    }
}

BigReal::BigReal(double realNumber) {
    this->decimalPart.setNumber(to_string(int (realNumber)));
    string fractionPart = to_string(realNumber - int(realNumber));
    cout << "fractionPart : " << fractionPart << endl;
    cout << "floatPart : " << subString(fractionPart, 2, fractionPart.length() - 1) << endl;
    this->floatPart.setNumber(subString(fractionPart, 2, fractionPart.length() - 1));

    if (realNumber < 0){
        this->Sign = '-';
    }else{
        this->Sign = '+';
    }
}

BigReal BigReal::operator+(BigReal &other) {
    BigReal result;

    result.decimalPart = this->decimalPart + other.decimalPart;
    addFloatParts(*this, other, result);

    cout << this->decimalPart << "." << this->floatPart << " + " << other.decimalPart << "." << other.floatPart << " = ";
    cout << result.decimalPart << "." << result.floatPart << endl;

    return result;
}