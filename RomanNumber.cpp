#include "RomanNumber.h"
#include <cctype>

int RomanNumber::charValue(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0;
    }
}

RomanNumber::RomanNumber() : value(1) {}

RomanNumber::RomanNumber(int v) {
    if (v <= 0 || v > maxValue)
        throw InvalidRomanNumberException("Invalid integer for RomanNumber");
    value = v;
}

bool RomanNumber::isValidRomanNumber(const std::string& s) {
    int prev = 1000000;
    int total = 0;

    for (char c : s) {
        c = toupper(c);
        int v = charValue(c);
        if (v == 0 || v > prev) return false;
        prev = v;
        total += v;
        if (total > maxValue) return false;
    }
    return total > 0;
}

RomanNumber::RomanNumber(const std::string& s) {
    if (!isValidRomanNumber(s))
        throw InvalidRomanNumberException("Invalid Roman numeral");
    value = 0;
    for (char c : s)
        value += charValue(toupper(c));
}

RomanNumber::operator int() const {
    return value;
}
