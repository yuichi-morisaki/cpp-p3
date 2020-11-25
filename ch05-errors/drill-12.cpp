#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    string s = "ape";
/*
    // could not convert 'std::operator+' from 'string' to 'bool'
    if (s+"fool")
*/
    if ((s+"fool").size())
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
