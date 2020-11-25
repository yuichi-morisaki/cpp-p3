#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    vector<char> v(5);
/*
    // infinite loop
    for (int i = 0; 0 < v.size(); ++i) ;
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
