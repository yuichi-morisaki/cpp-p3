#include "library.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
try {
    // Date
    Date d1 {2020, Month::Dec, 1};

    // Books
    Book b1 {"1-2-3-x", "Unix", "D.R.", Genre::biography, d1};
    Book b2 {"4-5-6-y", "C", "K.T.", Genre::children, d1};
    Book b3 {"7-8-9-z", "C++", "B.S.", Genre::fiction, d1};
    Book b4 = b1;
    b1.check_out();
    b2.check_out();
    vector<Book> books = {b1, b2, b3, b4};

    Patron p1 {"John", "1234"};
    Patron p2 {"Amy", "2345"};
    Patron p3 {"Mark", "3456"};
    Patron p4 {"Jessica", "4567"};
    p1.set_fee(100);
    p4.set_fee(200);
    vector<Patron> patrons = {p1, p2, p3, p4};

    Library lib {};
    lib.add_books(books);
    lib.add_patrons(patrons);

    Book b5 {"1-4-7-p", "Python", "G.R.", Genre::nonfiction, d1};
    vector<Book> target_books = {b5};
//    lib.checkout_books(p3, target_books);   // Book not found

    target_books = {b1, b3};
//    lib.checkout_books(p1, target_books);   // Patron with fee
//    lib.checkout_books(p2, target_books);   // OK
    target_books.push_back(b2);
    lib.checkout_books(p2, target_books);   // Book not found

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
