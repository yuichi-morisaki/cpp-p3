#include "rational-number.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main()
try {
    Rational r0 {};
    Rational r1 {3, 6};
    Rational r2 {2, 6};

    cout << "default r is " << r0 << '\n';

    cout << r1 << " + " << r2 << " == " << r1 + r2 << '\n';
    cout << r1 << " - " << r2 << " == " << r1 - r2 << '\n';
    cout << r1 << " * " << r2 << " == " << r1 * r2 << '\n';
    cout << r1 << " / " << r2 << " == " << r1 / r2 << '\n';

    cout << r1 << ((r1 == r2) ? " == " : " != ") << r2 << '\n';
    cout << r1 << ((r1 < r2) ? " < " : " >= ") << r2 << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
