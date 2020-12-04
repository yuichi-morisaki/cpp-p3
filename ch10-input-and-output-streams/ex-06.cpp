#include <iostream>
#include <stdexcept>
using namespace std;

void error(string s) { throw runtime_error(s); }
void error(string s, char c) {
    throw runtime_error(s + to_string(c));
}


string to_roman(int n, char x, char v, char i)
{
    if (n < 0 || 9 < n)
        error("to_roman: out of range");

    string r;
    if (n == 9) {
        r += i;
        r += x;
    }
    else if (n == 4) {
        r += i;
        r += v;
    }
    else {
        if (n >= 5)
            r += v;
        for (int j = 0; j < n % 5; ++j)
            r += i;
    }
    return r;
}


string int_to_roman(int n)
{
    if (n == 0)
        return "";

    string r;
    if (n < 0) {
        r += '-';
        n = -n;
    }

    for (int j = 0; j < n / 1000; ++j)
        r += 'M';
    n %= 1000;
    r += to_roman(n / 100, 'M', 'D', 'C');
    n %= 100;
    r += to_roman(n / 10, 'C', 'L', 'X');
    n %= 10;
    r += to_roman(n, 'X', 'V', 'I');

    return r;
}


struct Parse_result {
    int num;
    string rest;
};

Parse_result from_roman(string s, char x, char v, char i)
{
    if (s.size() == 0)
        return Parse_result {0, s};
    if (s[0] != v && s[0] != i)
        return Parse_result {0, s};

    if (s.size() >= 2 && s[0] == i && s[1] == x)
        return Parse_result {9, s.substr(2)};
    if (s.size() >= 2 && s[0] == i && s[1] == v)
        return Parse_result {4, s.substr(2)};

    int idx = 0;
    int num_v = 0;
    if (s[0] == v) {
        ++idx;
        num_v = 5;
    }
    int num_i = 0;
    while (idx < s.size()) {
        if (s[idx] == i) {
            ++num_i;
            if (num_i > 3)
                error("Unexpected character: ", i);
            ++idx;
            continue;
        }
        if (s[idx] == v || s[idx] == x)
            error("Unexpected character: ", s[idx]);
        break;
    }
    return Parse_result {num_v + num_i, s.substr(idx)};
}

int roman_to_int(string s)
{
    if (s.size() == 0)
        return 0;
    int num = 0;
    int sign = 1;
    int idx = 0;
    if (s[0] == '-') {
        sign = -1;
        ++idx;
    }
    while (idx < s.size()) {
        if (s[idx] == 'M') {
            num += 1000;
            ++idx;
            continue;
        }
        break;
    }
    Parse_result r = from_roman(s.substr(idx), 'M', 'D', 'C');
    num += (100 * r.num);
    r = from_roman(r.rest, 'C', 'L', 'X');
    num += (10 * r.num);
    r = from_roman(r.rest, 'X', 'V', 'I');
    num += r.num;
    if (r.rest.size() > 0)
        error("Incomplete parsing, left: " + r.rest);

    return sign * num;
}


class Roman_int {
    public:
        Roman_int();
        Roman_int(int n);
        Roman_int(string s);
        int as_int() const { return num; }
    private:
        int num;
};

Roman_int::Roman_int()
    : num {0}
{
}

Roman_int::Roman_int(int n)
    : num {n}
{
}

Roman_int::Roman_int(string s)
    : num {0}
{
    num = roman_to_int(s);
}


ostream& operator<<(ostream& os, const Roman_int& r)
{
    string s = int_to_roman(r.as_int());
    return os << s;
}

istream& operator>>(istream& is, Roman_int& r)
{
    string s;
    is >> s;
    int n = roman_to_int(s);
    r = Roman_int {n};

    return is;
}


int main()
try {
    Roman_int r;
    cout << "Enter a roman numeral: ";
    cin >> r;
    cout << "Roman: " << r << " equals " << r.as_int() << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
