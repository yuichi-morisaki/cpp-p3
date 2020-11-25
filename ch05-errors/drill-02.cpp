#include <iostream>
#include <stdexcept>

using namespace std;

int main()
try {
/*
    // missing terminating " character
    cout << "Success!\n;
*/
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
