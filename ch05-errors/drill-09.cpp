#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    string s = "ape";
/*
    // 'boo' was not declared in this scope; did you mean 'bool'?
    boo c = "fool" < s;
    // 'c' was not defined in this scope
    if (c)
*/
/*
    // logic error
    bool c = "fool" < s;
*/
    bool c = "fool" > s;
    if (c)
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
