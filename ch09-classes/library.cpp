#include "library.h"
#include <stdexcept>

using namespace std;


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


bool has_fee(const Patron& p)
{
    double fee = p.get_fee();
    return fee > 0;
}


bool operator==(const Patron& x, const Patron& y)
{
    return x.get_number() == y.get_number();
}


bool operator!=(const Patron& x, const Patron& y)
{
    return !(x == y);
}


Library::Library()
    : books {}, patrons {}, transactions {}
{
}


vector<Result>
Library::add_books(vector<Book>& vec)
{
    vector<Result> res;
    for (Book book: vec) {
        Result r;
        r.success = true;
        r.reason = "";
        if (book.is_checked_out()) {
            r.success = false;
            r.reason = "Cannot add a book checked-out";
        } else {
            books.push_back(book);
        }
        res.push_back(r);
    }
    return res;
}


vector<Result>
Library::add_patrons(vector<Patron>& vec)
{
    vector<Result> res;
    for (Patron p: vec) {
        Result r;
        r.success = true;
        r.reason = "";
        for (Patron patron: patrons) {
            if (p.get_number() == patron.get_number()) {
                r.success = false;
                r.reason = "Already added";
                break;
            }
        }
        if (r.success)
            patrons.push_back(p);
        res.push_back(r);
    }
    return res;
}


vector<Result>
Library::checkout(const Patron& p, vector<Book>& vec)
{
    bool patron_found = false;
    for (Patron patron: patrons) {
        if (p == patron) {
            patron_found = true;
            break;
        }
    }
    if (!patron_found)
        throw runtime_error(
                "Unregisterd patron: " + p.get_name());

    vector<Result> res;
    for (Book book: vec) {
        Result r;
        r.success = true;
        r.reason = "";
        bool book_found = false;
        for (Book book_in_lib: books) {
            if (book == book_in_lib) {
                book_found = true;
                if (book_in_lib.is_checked_out()) {
                    r.success = false;
                    r.reason = "already checked out";
                }
                else {
                    r.success = true;
                    r.reason = "";
                    break;
                }
            }
        }
        if (!book_found) {
            r.success = "false";
            r.reason = "not found";
        }
        res.push_back(r);
    }
    return res;
}
