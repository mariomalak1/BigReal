#include "BigReal.h"

// user defined function to cut the string from I want that help me in BigReal
// function that takes string that I want to cut from it and the first index and last index
// return new string that is sub string from the param I pass it
string subString(string str, int index1, int index2){
    string newString;
    if(index1 >= 0 and index2 >= 0 and index2 < str.length() and index1 < str.length() and index1 <= index2){
        for (int i = index1; i <= index2; ++i) {
            newString += str[i];
        }
        return newString;
    }
    return newString;
}

bool BigReal::checkValidInput(string realNumber)
{
//    regex validInput("[+\-]?[0-9][.][0-9]");
//    regex validInput("([+|-]?[0-9]+(.)?[0-9])|([+|-]?[0-9](.)?[0-9]+)|([+|-]?[0-9]+(.)?[0-9]+)");
    regex validInput("([+|-]?[0-9]+(.)?[0-9])|([0-9]*(.)[0-9]+)|([+|-]?[0-9]+(.)?[0-9]+)");
    regex secondValidInput("[-+]?[0-9]+");
    return (regex_match(realNumber, validInput) || (regex_match(realNumber, secondValidInput)));
}

// constructor that take double number
BigReal::BigReal(double realNumber) {
    if (realNumber < 0){
        realNumber *= -1;
        this->Sign = '-';
    }
    else{
        this->Sign = '+';
    }
    this->decimalPart.setNumber(to_string(int (realNumber)));
    string fractionPart = to_string(realNumber - int(realNumber));

    if (stod(fractionPart) == 0){
        this->floatPart.setNumber("0");
    }else {
        fractionPart.erase(0,2);
        this->floatPart.setNumber(fractionPart);
    }
    removeZeroes(*this);
}

// constructor that take string
BigReal:: BigReal(string realNumber){
    // first check validation
    string number = "";
    bool validNumber = checkValidInput(realNumber);
    if (validNumber) {
        number = realNumber;
        if (number[0] == '+') {
            number.erase(0, 1);
            Sign = '+';
        } else if (number[0] == '-') {
            number.erase(0, 1);
            Sign = '-';
        } else {
            Sign = '+';
        }
        string decimal = "", fraction = "";
        while (number[0] != '.') {
            decimal += number[0];
            number.erase(number.begin());
        }
        number.erase(number.begin());
        fraction = number;
        BigDecimalInt dec(decimal);
        BigDecimalInt frac(fraction);
        decimalPart = dec;
        floatPart = frac;
        removeZeroes(*this);
    } else {
        cerr << "Invalid Number" << "\n";
        exit(1);
    }
}

// function to add float parts between two big real objects, and if it has reminder add it in the decimal part in the result
void BigReal::addFloatParts(BigReal &real1, BigReal &real2, BigReal &answer) {
    int lenFrac1 = real1.floatPart.size();
    int lenFrac2 = real2.floatPart.size();
    BigDecimalInt floatNumber;

    floatNumber = real1.floatPart + real2.floatPart;

    if(lenFrac1 > lenFrac2){
        if (floatNumber.size() > lenFrac1){
            BigDecimalInt reminder("1");
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size() - 1));
            answer.floatPart = reminderFloatPart;
        }else{
            answer.floatPart = floatNumber;
        }
    }
    else if (lenFrac2 > lenFrac1){
        if (floatNumber.size() > lenFrac2){
            BigDecimalInt reminder("1");
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size() - 1));
            answer.floatPart = reminderFloatPart;
        }else{
            answer.floatPart = floatNumber;
        }
    }
    else{
        if (floatNumber.size() > lenFrac1){
            BigDecimalInt reminder("1");
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size() - 1));

            answer.floatPart = reminderFloatPart;
        }
        else if (floatNumber.size() > lenFrac2){
            BigDecimalInt reminder("1");
            answer.decimalPart = answer.decimalPart + reminder;
            BigDecimalInt reminderFloatPart(subString(floatNumber.getNumber(), 1, floatNumber.size() - 1));
            answer.floatPart = reminderFloatPart;
        }
        else{
            answer.floatPart = floatNumber;
        }
    }
}

// overloading + operator to add two big real objects
BigReal BigReal::operator+(BigReal& other) {
    // object to hold the operations and return it at the end
    BigReal result, otherCopy = other, thisCopy = *this;

    // check that two objects is in same sign as + sign
    if(otherCopy.Sign == '+' and thisCopy.Sign == '+') {
        result.decimalPart = thisCopy.decimalPart + otherCopy.decimalPart;
        addFloatParts(thisCopy, otherCopy, result);
    }

    // check that the second object is negative and the second is positive or negative
    else if(otherCopy.Sign == '-'){
        if (thisCopy.Sign == '+'){
            // obj1 - (+obj2)
            otherCopy.Sign = '+';
            result = (thisCopy - otherCopy);
        }
        else{
            // (-obj1) + (-obj2) = -result
            result.Sign = '-';
            result.decimalPart = otherCopy.decimalPart + thisCopy.decimalPart;
            addFloatParts(otherCopy, thisCopy, result);
        }
    }
    // check that the first object is negative and the second is positive
    else if(thisCopy.Sign == '-'){
        thisCopy.Sign = '+';
        result = (otherCopy - thisCopy);
    }
    return result;
}

// Copy constructor
BigReal::BigReal(const BigReal &other){
    this->decimalPart = other.decimalPart;
    this->floatPart = other.floatPart;
    this->Sign = other.Sign;
}


// move constructor
BigReal &BigReal::operator=(BigReal &&other) {
    this->decimalPart = other.decimalPart;
    this->Sign = other.Sign;
    this->floatPart = other.floatPart;
    return *this;
}

// overloaded bitwise operator << to print the object of the BigReal Class
ostream &operator<<(ostream &out, BigReal num) {
    if (num.Sign == '-'){
        out << "-";
    }
    out << num.decimalPart << "." << num.floatPart;
    return out;
}

// function to make subtraction in float parts in the two BigReal objects
void BigReal::subtractFloatParts(BigReal &real1, BigReal &real2, BigReal &answer) {
    BigDecimalInt floatNumber, zero("0"), decimalOne("1");
    BigReal ZeroBigReal(0);

    // to fill the two float parts with zeroes to make them equal in length of number
    if (real1.floatPart.getNumber().length() < real2.floatPart.getNumber().length()){
        real1.floatPart.setNumber(completeWithZeroes(real1.floatPart.getNumber(), real2.floatPart.getNumber().length()));
    }else if (real1.floatPart.getNumber().length() > real2.floatPart.getNumber().length()){
        real2.floatPart.setNumber(completeWithZeroes(real2.floatPart.getNumber(), real1.floatPart.getNumber().length()));
    }

    // check if the second fraction is bigger than the first, then it will make the second - the first and the decimal part in answer will be minus one
    if (real2.floatPart > real1.floatPart){
        if (answer < ZeroBigReal){
            answer.decimalPart = answer.decimalPart + decimalOne;
            string NumberOne = "1";
            NumberOne = completeWithZeroes(NumberOne, real1.floatPart.getNumber().length() + 1);
            BigDecimalInt one(NumberOne);
            real1.floatPart = real1.floatPart + NumberOne;
            cout << real1 << "  " << real2 << endl;
            floatNumber = real1.floatPart - real2.floatPart;
            if (floatNumber.getNumber().length() < NumberOne.length()) {
                floatNumber.setNumber("0" + floatNumber.getNumber());
            }
            answer.floatPart = floatNumber;
        }else if (answer > ZeroBigReal){
            answer.decimalPart = answer.decimalPart - decimalOne;
            string NumberOne = "1";
            NumberOne = completeWithZeroes(NumberOne, real1.floatPart.getNumber().length() + 1);
            BigDecimalInt one(NumberOne);
            real1.floatPart = real1.floatPart + NumberOne;
            floatNumber = real1.floatPart - real2.floatPart;
            if (floatNumber.getNumber().length() < NumberOne.length()) {
                floatNumber.setNumber("0" + floatNumber.getNumber());
            }
            answer.floatPart = floatNumber;
        }else{
            answer.Sign = '-';
            subtractFloatParts(real2, real1, answer);
        }
    }

    // if the first float part is bigger than the second it will make simple subtraction
    else if (real2.floatPart < real1.floatPart){
        floatNumber = real1.floatPart - real2.floatPart;
        if (floatNumber.getNumber().length() < real1.floatPart.getNumber().length()){
            floatNumber.setNumber("0" + floatNumber.getNumber());
        }
        answer.floatPart = floatNumber;
    }

    // if the two float parts are equal, so it will make answer float part equal zero
    else{
        answer.floatPart = zero;
    }

    // to remove the last zeroes numbers in the float part
}

BigReal BigReal::operator-(BigReal &other) {
    BigReal result, otherCopy = other, thisCopy = *this;
    BigDecimalInt zero("0");

    if(otherCopy.Sign == '+' and thisCopy.Sign == '+') {
        if (otherCopy.decimalPart > thisCopy.decimalPart){
            result = otherCopy - thisCopy;
            result.Sign = '-';
        }else{
            result.decimalPart = thisCopy.decimalPart - otherCopy.decimalPart;
            subtractFloatParts(thisCopy, otherCopy, result);
        }
    }

    // check that the second object is negative and the second is positive or negative
    else if(otherCopy.Sign == '-'){
        if (thisCopy.Sign == '+'){
            otherCopy.Sign = '+';
            result = (*this + otherCopy);
        }
        else{
            otherCopy.Sign = '+';
            result = (*this + otherCopy);
        }
    }

    // check that the first object is negative and the second is positive
    else if(thisCopy.Sign == '-'){
        otherCopy.Sign = thisCopy.Sign = '+';
        result.Sign = '-';
        result.decimalPart = thisCopy.decimalPart + otherCopy.decimalPart;
        addFloatParts(*this, otherCopy, result);
    }

    return result;
}

BigReal &BigReal::operator=(BigReal &other) {
    this->decimalPart = other.decimalPart;
    this->Sign = other.Sign;
    this->floatPart = other.floatPart;
    return *this;
}

// function that take string and length of another string to complete this string till it is as the second string with zeroes
string BigReal::completeWithZeroes(string str, int len) {
    for (int i = str.length(); i < len; ++i) {
        str += "0";
    }
    return str;
}

// logic operator
bool BigReal:: operator< (BigReal anotherReal){
    if(decimalPart < anotherReal.decimalPart){
        return true;
    }
    else if (decimalPart == anotherReal.decimalPart){
        if(floatPart < anotherReal.floatPart ){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }

}

// logic operator
bool BigReal::operator> (BigReal anotherReal) {
    if (decimalPart < anotherReal.decimalPart) {
        return false;
    } else if (decimalPart == anotherReal.decimalPart) {
        if (floatPart > anotherReal.floatPart) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

BigReal::BigReal(BigDecimalInt bigInteger) {
    BigDecimalInt zero("0");
    this->decimalPart = bigInteger.getNumber();
    this->floatPart = zero;
    this->Sign = bigInteger.sign();
}

// function to remove last zeroes digits from float part, and the first zeroes in decimal part
void BigReal::removeZeroes(BigReal &number) {
    string stringFloatNumber = number.floatPart.getNumber();
    string stringDecimalNumber = number.decimalPart.getNumber();
    if (stringFloatNumber.length() > 1) {
        while (!((int) stringFloatNumber[stringFloatNumber.length() - 1] - 48)) {
            stringFloatNumber.erase(stringFloatNumber.length() - 1, 1);
            if ((int) stringFloatNumber[stringFloatNumber.length() - 1] - 48) {
                break;
            }
        }
    }
    if (stringDecimalNumber.length() > 1){
        while(! ( (int) stringDecimalNumber[0] - 48)){
            stringDecimalNumber.erase(0,1);
            if (( (int) stringDecimalNumber[0] - 48)){
                break;
            }
        }
    }
    number.floatPart.setNumber(stringFloatNumber);
    number.decimalPart.setNumber(stringDecimalNumber);
}

// Move constructor
BigReal::BigReal (BigReal&& other){
    decimalPart = other.decimalPart;
    floatPart = other.floatPart;
    Sign=other.Sign;
}

int BigReal:: size(){
    return decimalPart.size() + floatPart.size();
}

int BigReal::sign(){
    return decimalPart.sign();
}

bool BigReal::operator==(BigReal anotherReal) {
    if (decimalPart == anotherReal.decimalPart && floatPart == anotherReal.floatPart){
        return true ;
    }
    else{
        return false;
    }
}

istream &operator>>(istream &in, BigReal& num) {
    string number, decimal, fraction;
    getline(cin, number);
    if (BigReal::checkValidInput(number)) {
        int i = 0;
        if (number[i] == '-'){
            i++;
            num.Sign = '-';
        }else{
            num.Sign = '+';
        }

        // to loop on number and store it in decimal part till it reach to . decimal pint
        for (; i < number.length(); ++i) {
            if (number[i] == '.') {
                break;
            } else {
                decimal += number[i];
            }
        }
        // to avoid . decimal point
        i++;

        // to loop on the remaining part of the number and store it in fraction part
        for (; i < number.length(); ++i) {
            fraction += number[i];
        }

        num.decimalPart.setNumber(decimal);
        if (fraction != ""){
            num.floatPart.setNumber(fraction);
        }else{
            num.floatPart.setNumber("0");
        }
    }
    else{
        cerr << "invalid Big Real Input" << endl;
        exit(1);
    }
    return in;
}
