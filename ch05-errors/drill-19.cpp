#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
/*
    // missing template arguments before 'v'
    vector v(5);
*/
    vector<int> v(5);
/*
    // out-of-range error
    for (int i = 0; i <= v.size(); ++i) ;
*/
    for (int i = 0; i < v.size(); ++i) ;
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
