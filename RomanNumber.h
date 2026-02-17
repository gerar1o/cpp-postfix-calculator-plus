#pragma once
#include <string>
#include <exception>

class InvalidRomanNumberException : public std::exception {
    std::string msg;
public:
    InvalidRomanNumberException(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class RomanNumber {
private:
    int value;
    static int charValue(char c);

public:
    static const int maxValue = 4999;

    RomanNumber();
    RomanNumber(int v);
    RomanNumber(const std::string& s);

    static bool isValidRomanNumber(const std::string& s);

    operator int() const;
};
