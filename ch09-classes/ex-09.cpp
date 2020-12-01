#include "library.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main()
try {
    Date d {2020, Month::Dec, 1};
    Book b1 {"1-2-3-x", "Unix", "D.R.", Genre::biography, d};
    Book b2 {"4-5-6-y", "C", "K.T.", Genre::children, d};
    Book b3 {"7-8-9-z", "C++", "S.S.", Genre::fiction, d};
    b2.check_out();
    vector<Book> books = {b1, b2, b3};

    Library lib {};
    vector<Result> vr1 = lib.add_books(books);
    for (int i = 0; i < vr1.size(); ++i) {
        if (vr1[i].success)
            cout << books[i].get_isbn() << ": " << "OK\n";
        else
            cout << books[i].get_isbn() << ": "
                 << "NG - " << vr1[i].reason << '\n';
    }

    Patron p1 {"Alice", "1234"};
    Patron p2 {"Bob", "5678"};
    Patron p3 {"Chris", "9036"};
    vector<Patron> patrons = {p1, p2, p3};
    patrons.push_back(p1);
    vector<Result> vr2 = lib.add_patrons(patrons);
    for (int i = 0; i < vr2.size(); ++i) {
        if (vr2[i].success)
            cout << patrons[i].get_name() << ": " << "OK\n";
        else
            cout << patrons[i].get_name() << ": "
                 << "NG - " << vr2[i].reason << '\n';
    }

    vector<Result> vr3 = lib.checkout(p1, books);
    for (int i = 0; i < vr3.size(); ++i) {
        if (vr3[i].success)
            cout << books[i].get_isbn() << ": OK\n";
        else
            cout << books[i].get_isbn()
                 << ": NG - " << vr3[i].reason << '\n';
    }

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
