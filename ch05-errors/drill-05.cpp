#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
/*
    // conversion from 'int' to non-scalar type 'std::string' requested
    string res = 7;
*/
    string res = "7";
    vector<int> v(10);
/*
    // cannot convert 'std::string' to 'int' in assignment
    v[5] = res;
*/
    v[5] = stoi(res);   // or change int to string in defining vector above
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
