#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    string s = "Success!\n";
/*
    // output is "Succes"
    for (int i = 0; i < 6; ++i)
*/
    for (int i = 0; i < 9; ++i)
        cout << s[i];

    // we can use s.size() instead of 9
    for (int i = 0; i < s.size(); ++i)
        cout << s[i];

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
