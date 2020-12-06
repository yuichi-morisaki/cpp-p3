// multi_input.cpp
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Number {
    int value;
    int base;
};

int main()
{
    cout << "Enter a series of integer.\n"
         << "Decimal, hexadecimal (0x...) or octal (0....):\n";

    vector<Number> v;

    int n;
    char c;
    while (cin) {
        if (cin >> c && c == '0') {
            if (cin >> c && (c == 'x' || c == 'X')) {
                cin >> hex >> n;
                v.push_back(Number {n, 16});
            }
            else if (cin && '0' < c && c < '8') {
                cin.unget();
                cin >> oct >> n;
                v.push_back(Number {n, 8});
            }
            else if (cin) {
                throw runtime_error("unexpected char");
            }
        }
        else if (cin && isdigit(c)) {
            cin.unget();
            cin >> dec >> n;
            v.push_back(Number {n, 10});
        }
        else if (cin) {
            break;
        }
    }
    if (!cin.eof() && (cin.fail() || cin.bad()))
        throw runtime_error("bad input");

    cout << showbase;
    for (const Number& n: v)
        if (n.base == 10)
            cout << dec << setw(8) << n.value
                 << " decimal\tconverts to "
                 << dec << setw(8) << n.value << " decimal\n";
        else if (n.base == 16)
            cout << hex << setw(8) << n.value
                 << " hexadecimal\tconverts to "
                 << dec << setw(8) << n.value << " decimal\n";
        else if (n.base == 8)
            cout << oct << setw(8) << n.value
                 << " octal\t\tconverts to "
                 << dec << setw(8) << n.value << " decimal\n";
        else
            throw runtime_error("Invalid base");
}
