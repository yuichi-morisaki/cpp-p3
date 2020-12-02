#include "chrono2.h"
#include <iostream>

using namespace std;


int main()
try {
    Date d0 {};
    cout << d0 << '\n';
    Date d {15000};
    cout << d << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
