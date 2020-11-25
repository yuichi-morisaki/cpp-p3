#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    int x = 2000;
    char c = x;
/*
    // using a result of narrowing cast
    if (c == 2000)
*/
    // 2000 % 256 = 208
    // 208 > 127, and 208 - 256 = -48
    if (c == -48)
        cout << "Success!\n";

    // or
    if (c == char(2000))
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
