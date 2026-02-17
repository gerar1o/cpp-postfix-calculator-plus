#pragma once
#include <iostream>
#include <vector>
#include <string>

class BigInteger {
public:
    std::vector<int> digits;   // least-significant digit first
    bool negative;

    BigInteger();
    BigInteger(long long value);
    BigInteger(const std::string& s);

    void normalize();

    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& n);
};
