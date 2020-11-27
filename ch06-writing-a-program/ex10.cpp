#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s) {
    throw runtime_error(s);
}

int factorial(int n) {
    if (n < 0)
        error("factorial: n must not be negative");
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int permutation(int a, int b) {
    if (a < b)
        error("permutation: a must not be less than b");
    int num = 1;
    for (int i = a; i > a - b; --i)
        num *= i;
    int den = 1;
    for (int i = b; i > 0; --i)
        den *= i;
    return num / den;
}

int combination(int a, int b) {
    if (a < b)
        error("combination: a must not be less than b");
    return permutation(a, b) / factorial(b);
}

int main()
try {
    cout << "Enter two numbers for 'a' and 'b' (a >= b): ";
    int a, b;
    cin >> a >> b;
    if (!cin)
        error("Failed to read input");
    cout << "Whether do you want permutation or combination?"
         << " [p/c]: ";
    char c;
    cin >> c;

    switch (c) {
        case 'p':
            cout << permutation(a, b) << '\n';
            break;
        case 'c':
            cout << combination(a, b) << '\n';
            break;
        default:
            error("Sorry, only permutation or combination");
    }

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
