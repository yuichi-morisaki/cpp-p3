#include "book.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;


int main()
try {
    Date date {2020, Month::Dec, 1};
    Book b1 {"123-456-789-x", "C++", "Stroustrup", date};
    Book b2 {"123-456-789-x", "C", "K & R", date};
    Book b3 {"123-456-789-0", "C++", "Stroustrup", date};

    cout << "b1" << '\n' << b1 << '\n';
    cout << "b2" << '\n' << b2 << '\n';
    cout << "b3" << '\n' << b3 << '\n';

    cout << "b1 "
         << ((b1 == b2) ? "==" : "!=")
         << " b2\n";
    cout << "b1 "
         << ((b1 != b3) ? "!=" : "==")
         << " b3\n";

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
