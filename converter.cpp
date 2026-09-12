#include <iostream>
#include <string>
#include <cctype>
#include <climits>
using namespace std;

// ---------- Validation helpers ----------

bool isValidBinary(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c != '0' && c != '1') return false;
    }
    return true;
}

bool isValidDecimal(const string &s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') start = 1;
    if (start == s.size()) return false; // just a sign, no digits
    for (size_t i = start; i < s.size(); i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

bool isValidHex(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isxdigit((unsigned char)c)) return false;
    }
    return true;
}

bool isValidOctal(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < '0' || c > '7') return false;
    }
    return true;
}

// ---------- Conversion helpers ----------

long long toDecimal(const string &s, int base) {
    return stoll(s, nullptr, base);
}

string decimalToBinary(long long n) {
    if (n == 0) return "0";
    bool negative = n < 0;
    unsigned long long num = negative ? -n : n;
    string result;
    while (num > 0) {
        result = char('0' + (num % 2)) + result;
        num /= 2;
    }
    return negative ? "-" + result : result;
}

string decimalToHex(long long n) {
    if (n == 0) return "0";
    bool negative = n < 0;
    unsigned long long num = negative ? -n : n;
    string digits = "0123456789ABCDEF";
    string result;
    while (num > 0) {
        result = digits[num % 16] + result;
        num /= 16;
    }
    return negative ? "-" + result : result;
}

string decimalToOctal(long long n) {
    if (n == 0) return "0";
    bool negative = n < 0;
    unsigned long long num = negative ? -n : n;
    string result;
    while (num > 0) {
        result = char('0' + (num % 8)) + result;
        num /= 8;
    }
    return negative ? "-" + result : result;
}

// ---------- Input helpers ----------

int askInputFormat() {
    int choice;
    while (true) {
        cout << "\nWhat format is your number in?\n";
        cout << "1. Binary\n2. Decimal\n3. Hexadecimal\n4. Octal\n";
        cout << "Enter choice (1-4): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Enter valid number\n";
            continue;
        }
        if (choice >= 1 && choice <= 4) return choice;
        cout << "Enter valid number\n";
    }
}

string askNumber(int format) {
    string input;
    while (true) {
        cout << "Enter the number: ";
        cin >> input;

        bool valid = false;
        if (format == 1) valid = isValidBinary(input);
        else if (format == 2) valid = isValidDecimal(input);
        else if (format == 3) valid = isValidHex(input);
        else if (format == 4) valid = isValidOctal(input);

        if (valid) return input;
        cout << "Enter valid number\n";
    }
}

int askOutputFormat() {
    int choice;
    while (true) {
        cout << "\nConvert it to which format?\n";
        cout << "1. Binary\n2. Decimal\n3. Hexadecimal\n4. Octal\n";
        cout << "Enter choice (1-4): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Enter valid number\n";
            continue;
        }
        if (choice >= 1 && choice <= 4) return choice;
        cout << "Enter valid number\n";
    }
}

// ---------- Main ----------

int main() {
    cout << "===== Number Base Converter =====\n";

    int inputFormat = askInputFormat();
    string number = askNumber(inputFormat);
    int outputFormat = askOutputFormat();

    int base = (inputFormat == 1) ? 2 : (inputFormat == 2) ? 10 : (inputFormat == 3) ? 16 : 8;
    long long decimalValue;

    try {
        decimalValue = toDecimal(number, base);
    } catch (...) {
        cout << "Enter valid number\n";
        return 1;
    }

    cout << "\nResult: ";
    if (outputFormat == 1) cout << decimalToBinary(decimalValue);
    else if (outputFormat == 2) cout << decimalValue;
    else if (outputFormat == 3) cout << decimalToHex(decimalValue);
    else cout << decimalToOctal(decimalValue);

    cout << "\n";
    return 0;
}