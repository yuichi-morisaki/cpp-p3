#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    string s = "ape";
/*
    // logic error
    if (s == "fool")
*/
    if (s != "fool")
/*
        // no match for ‘operator<’
        cout < "Success!\n";
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
