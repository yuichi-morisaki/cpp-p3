#include "book.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;
using namespace Book_lib;


int main()
try {
    Date date {2020, Month::Dec, 1};
    Book b1 {
        "123-456-789-x", "C++", "Stroustrup",
            Genre::nonfiction, date
    };

    cout << b1 << '\n';

    b1.set_genre(Genre::children);

    cout << b1 << '\n';

/*
    // An exception occurred - Genre out of range
    Book b2 {
        "1-2-3-4", "Python", "who?", Genre(10), date
    };
    cout << b2 << '\n';
*/

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
