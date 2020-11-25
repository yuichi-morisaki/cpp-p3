#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    int x = 2;
/*
    // Floating point exception (core dumped)
    double d = 5 / (x - 2);     // divides by zero
*/
    double d = 5.0 / x + 2;
    if (d == 2 * x + 0.5)
        cout << "Success!\n";

    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
}
