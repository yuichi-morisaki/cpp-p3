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


bool has_fee(const Patron& p);

bool operator==(const Patron& x, const Patron& y);
bool operator!=(const Patron& x, const Patron& y);


struct Result {
    bool success;
    string reason;
};


struct Transaction {
    Book book;
    Patron patron;
    Date date;
};


class Library {
public:
    Library();
    vector<Result> add_books(vector<Book>& vec);
    vector<Result> add_patrons(vector<Patron>& vec);
    vector<Result> checkout(
        const Patron& p, vector<Book>& vec);
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
};
