#include <iostream>
#include <stdexcept>

using namespace std;

int main()
try {
/*
    // 'success' was not declared in this scope
    cout << success << '\n';
*/
    cout << "success" << '\n';

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
