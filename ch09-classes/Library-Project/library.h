#include "book.h"
#include <string>
#include <vector>

using namespace std;
using namespace Book_lib;


class Patron {
public:
    Patron(string name, string number);

    string get_name() const;
    string get_number() const;
    double get_fee() const;

    void set_fee(double fee);

private:
    string user_name;
    string card_number;
    double library_fee;
};


bool owe_fee(const Patron& patron);


bool operator==(const Patron& x, const Patron& y);
bool operator!=(const Patron& x, const Patron& y);

// ------------------------------------------------------------------

class Library {
public:
    Library();

    void add_books(const vector<Book>& books);
    void add_patrons(const vector<Patron>& patrons);
    void checkout_books(const Patron& patron,
                        const vector<Book>& books);
    vector<Patron> get_patrons_with_fee() const;

private:
    struct Transaction {
        Transaction(Book b, Patron p, Date d);
        Book book;
        Patron patron;
        Date date;
    };

    vector<Book> books_in_lib;
    vector<Patron> patrons_in_lib;
    vector<Transaction> transactions;
};


