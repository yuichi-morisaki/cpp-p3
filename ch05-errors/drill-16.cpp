#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
/*
    // 'then' was not declared in this scope
    if (true) then
*/
    if (true)
        cout << "Success!\n";
    else
        cout << "Fail!\n";

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
