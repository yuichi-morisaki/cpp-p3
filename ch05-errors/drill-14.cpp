#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    vector<char> v(5);
    // we should use
    for (int i = 0; i < v.size(); ++i) ;
    // instead of below;
/*
    // this is good for getting desired output
    // because the body is for-loop is empty,
    // but there is an out-of-range error.
    for (int i = 0; i <= v.size(); ++i) ;
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
