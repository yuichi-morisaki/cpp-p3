#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    int i = 0;
    int j = 9;
/*
    // infinite-loop caused by logic error
    while (i < 10)
        ++j;
*/
    while (i < 10)
        ++i;

    if (j < i)
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
