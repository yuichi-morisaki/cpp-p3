#include <iostream>
using namespace std;

int main()
{
    for (string s; cin >> s; ) {
        for (const char& c: s) {
            cout << c << ':';
            if (isspace(c)) cout << "space.";
            if (isalpha(c)) cout << "alpha.";
            if (isdigit(c)) cout << "digit.";
            if (isxdigit(c)) cout << "Xdigit.";
            if (isupper(c)) cout << "UPPER.";
            if (islower(c)) cout << "lower.";
            if (isalnum(c)) cout << "alnum.";
            if (iscntrl(c)) cout << "cntrl.";
            if (ispunct(c)) cout << "punct.";
            if (isprint(c)) cout << "print.";
            if (isgraph(c)) cout << "graph.";
            cout << '\n';
        }
        cout << '\n';
    }
    if (!cin.eof() && (cin.fail() || cin.bad()))
        throw runtime_error("cin is not good");

    return 0;
}
