#include "library.h"

// ==================================================================

Patron::Patron(string name, string number)
    : user_name {name}, card_number {number}, library_fee {0}
{
}


string Patron::get_name() const
{
    return user_name;
}


string Patron::get_number() const
{
    return card_number;
}


double Patron::get_fee() const
{
    return library_fee;
}


void Patron::set_fee(double fee)
{
    if (fee < 0)
        throw runtime_error("set_fee(): negative value");

    library_fee = fee;
}

// ------------------------------------------------------------------

bool owe_fee(const Patron& patron)
{
    return patron.get_fee() > 0;
}


bool operator==(const Patron& x, const Patron& y)
{
    return x.get_number() == y.get_number();
}


bool operator!=(const Patron& x, const Patron& y)
{
    return !(x == y);
}


// ==================================================================

Library::Library()
    : books_in_lib {}, patrons_in_lib {}, transactions {}
{
}


void Library::add_books(const vector<Book>& books)
{
    for (const Book& book: books) {
        books_in_lib.push_back(book);
    }
}


void Library::add_patrons(const vector<Patron>& patrons)
{
    for (const Patron& patron: patrons) {
        for (const Patron& lib_patron: patrons_in_lib) {
            if (patron == lib_patron)
                throw runtime_error("Patron already added");
        }
        patrons_in_lib.push_back(patron);
    }
}


void Library::checkout_books(const Patron& patron,
                             const vector<Book>& books)
{
    // check user existence
    bool patron_exist = false;
    for (const Patron& lib_patron: patrons_in_lib) {
        if (patron == lib_patron) {
            patron_exist = true;
            break;
        }
    }
    if (!patron_exist)
        throw runtime_error("Patron not found");

    // check that user has no fee
    for (const Patron& fee_patron: get_patrons_with_fee()) {
        if (patron == fee_patron)
            throw runtime_error(
                    "Patron with fee cannot checkout books");
    }

    // check book existence
    for (const Book& book: books) {
        bool book_exist = false;
        for (Book& lib_book: books_in_lib) {
            if (book == lib_book
                    && !lib_book.is_checked_out()) {
                book_exist = true;
                lib_book.check_out();
                break;
            }
        }
        if (!book_exist)
            throw runtime_error("Book not found");
    }

    // create Transaction and set to the vector
    Date today {2020, Month::Dec, 2};
    for (const Book& book: books) {
        Transaction ts {book, patron, today};
        transactions.push_back(ts);
    }
}


vector<Patron> Library::get_patrons_with_fee() const
{
    vector<Patron> patrons;
    for (const Patron& patron: patrons_in_lib) {
        if (owe_fee(patron))
            patrons.push_back(patron);
    }
    return patrons;
}


Library::Transaction::Transaction(
        Book book, Patron patron, Date date)
    : book {book}, patron {patron}, date {date}
{
}
