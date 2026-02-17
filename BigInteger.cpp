#include "BigInteger.h"
#include <cctype>
#include <stdexcept>

using namespace std;

BigInteger::BigInteger() : digits(1, 0), negative(false) {}

BigInteger::BigInteger(long long value) {
    negative = (value < 0);
    if (value < 0) value = -value;
    if (value == 0) digits.push_back(0);
    while (value > 0) {
        digits.push_back(value % 10);
        value /= 10;
    }
}

BigInteger::BigInteger(const string& s) {
    negative = false;
    digits.clear();

    int start = 0;
    if (s[0] == '-') {
        negative = true;
        start = 1;
    }

    for (int i = s.size() - 1; i >= start; --i) {
        if (!isdigit(s[i]))
            throw invalid_argument("Invalid BigInteger");
        digits.push_back(s[i] - '0');
    }
    normalize();
}

void BigInteger::normalize() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
    if (digits.size() == 1 && digits[0] == 0)
        negative = false;
}

static int absCompare(const BigInteger& a, const BigInteger& b) {
    if (a.digits.size() != b.digits.size())
        return (a.digits.size() < b.digits.size()) ? -1 : 1;
    for (int i = a.digits.size() - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i])
            return (a.digits[i] < b.digits[i]) ? -1 : 1;
    }
    return 0;
}

BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    BigInteger r;
    r.digits.clear();
    int carry = 0;
    size_t n = max(a.digits.size(), b.digits.size());

    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        r.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return r;
}

BigInteger operator-(const BigInteger& a, const BigInteger& b) {
    if (absCompare(a, b) < 0)
        throw runtime_error("Negative BigInteger result");

    BigInteger r;
    r.digits.clear();
    int borrow = 0;

    for (size_t i = 0; i < a.digits.size(); ++i) {
        int diff = a.digits[i] - borrow - (i < b.digits.size() ? b.digits[i] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else borrow = 0;
        r.digits.push_back(diff);
    }
    r.normalize();
    return r;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    BigInteger r;
    r.digits.assign(a.digits.size() + b.digits.size(), 0);

    for (size_t i = 0; i < a.digits.size(); ++i)
        for (size_t j = 0; j < b.digits.size(); ++j)
            r.digits[i + j] += a.digits[i] * b.digits[j];

    int carry = 0;
    for (size_t i = 0; i < r.digits.size(); ++i) {
        int val = r.digits[i] + carry;
        r.digits[i] = val % 10;
        carry = val / 10;
    }

    r.normalize();
    return r;
}

ostream& operator<<(ostream& os, const BigInteger& n) {
    if (n.negative) os << "-";
    for (int i = n.digits.size() - 1; i >= 0; --i)
        os << n.digits[i];
    return os;
}
