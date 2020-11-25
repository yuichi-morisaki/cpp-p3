#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    int i = 0;
    while (i < 10)
/*
        // 'j' was not declared in this scope
        ++j;
*/
        ++i;
/*
    // 'j' was not declared in this scope
    if (j < i)
*/
    int j = 9;
    if (j < i)
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
