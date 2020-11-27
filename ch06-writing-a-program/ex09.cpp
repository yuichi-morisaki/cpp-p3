#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string message) {
    throw runtime_error(message);
}

class Digit {
public:
    int digit;
    int scale;
    Digit(int d)
        : digit(d), scale(1) { }
};


int main()
try {
    string input;
    cin >> input;
    int len = input.size();
    if (len > 4)
        error("Too many character");
    for (int i = len - 1; i >= 0; --i)
        cin.putback(input[i]);

    vector<Digit> integer;
    char c;
    while (cin >> c) {
        switch (c) {
            case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9': case '0':
                if (len != 1 && c == '0' && integer.size() == 0)
                    error("Invalid integer: starts with zero");
                for (int i = 0; i < integer.size(); ++i)
                    integer[i].scale *= 10;
                {
                    int d = c - '0';
                    integer.push_back(Digit(d));
                    cout << d;
                }
                break;
            default:
                error("a digit expected");
                break;
        }
        if (integer.size() == len)
            break;
    }
    cout << " is ";
    bool rightmost = true;
    for (Digit d: integer) {
        if (d.digit == 0)
            continue;
        if (rightmost)
            rightmost = false;
        else
            cout << " and ";
        cout << d.digit << ' ';
        switch (d.scale) {
            case 1:
                cout << "one";
                break;
            case 10:
                cout << "ten";
                break;
            case 100:
                cout << "hundred";
                break;
            case 1000:
                cout << "thousand";
                break;
            default:
                error("Too many digits");
        }
        if (d.digit > 1)
            cout << "s";
    }
    if (rightmost)
        cout << "zero";
    cout << ".\n";

    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}
