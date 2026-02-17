#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

#include "BigInteger.h"
#include "RomanNumber.h"

using namespace std;

bool isOperator(const string& t) {
    return t == "+" || t == "-" || t == "*";
}

BigInteger toBigInt(const string& t) {
    if (RomanNumber::isValidRomanNumber(t)) {
        RomanNumber r(t);
        return BigInteger((long long)(int)r);
    }
    return BigInteger(t);
}

int main() {
    cout << "Postfix Calculator (Roman + BigInteger)\n";
    cout << "Enter input file name: ";

    string filename;
    getline(cin, filename);

    ifstream fin(filename);
    if (!fin) {
        cout << "Could not open file.\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        stack<BigInteger> st;
        stringstream ss(line);
        string token;

        cout << "\nExpression: " << line << endl;

        try {
            while (ss >> token) {
                if (!isOperator(token)) {
                    st.push(toBigInt(token));
                }
                else {
                    if (st.size() < 2)
                        throw runtime_error("Not enough operands");

                    BigInteger b = st.top(); st.pop();
                    BigInteger a = st.top(); st.pop();

                    if (token == "+") st.push(a + b);
                    else if (token == "-") st.push(a - b);
                    else if (token == "*") st.push(a * b);
                }
            }

            if (st.size() == 1) {
                cout << "Result = " << st.top() << endl;
            }
            else {
                cout << "Result = (error)\n";
            }
        }
        catch (const exception& e) {
            cout << "Error during evaluation: " << e.what() << endl;
        }


        cout << "Result = " << st.top() << endl;
    }

    cout << "\nDone.\n";
    return 0;
}
