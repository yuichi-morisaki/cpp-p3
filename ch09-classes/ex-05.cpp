#include "book.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;


int main()
try {
    Date date {2020, Month::Dec, 1};
/* Bad ISBN examples
    Book b2 {"12c-456-789-x", "C++", "Stroustrup", date};
    Book b3 {"123-45f-789-x", "C++", "Stroustrup", date};
    Book b4 {"123-456-78z-x", "C++", "Stroustrup", date};
    Book b5 {"123--789-x", "C++", "Stroustrup", date};
    Book b7 {"123-456-789-32", "C++", "Stroustrup", date};
*/
    Book b6 {"123-456-789-3", "C++", "Stroustrup", date};
    Book b1 {"123-456-789-x", "C++", "Stroustrup", date};

    cout << ((b1.is_checked_out()) ? "out" : "in") << '\n';
    b1.check_out();
//    b1.check_out();
    cout << ((b1.is_checked_out()) ? "out" : "in") << '\n';

    cout << "ISBN: " << b1.get_isbn() << '\n'
         << "Title: " << b1.get_title() << '\n'
         << "Author: " << b1.get_author() << '\n'
         << "Copyright Date: " << b1.get_copyright_date() << '\n';

    cout << ((b1.is_checked_out()) ? "out" : "in") << '\n';
    b1.check_in();
//    b1.check_in();
    cout << ((b1.is_checked_out()) ? "out" : "in") << '\n';

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
