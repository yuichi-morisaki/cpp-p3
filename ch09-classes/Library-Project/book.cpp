#include "book.h"
#include <iostream>
#include <stdexcept>

using namespace std;


bool is_digits(string s)
{
    for (char c: s)
        if (!isdigit(c))
            return false;
    return s.size() > 0;
}


namespace Book_lib {

    ostream& operator<<(ostream& os, const Genre& g)
    {
        int idx = static_cast<int>(g);
        if (idx < 0 || genre_table.size() <= idx)
            throw runtime_error("Genre: out of range");

        return os << genre_table[idx];
    }


    Book::Book(string isbn,
               string title,
               string author,
               Genre genre,
               const Date& copyright_date)
        : isbn {isbn},
          title {title},
          author {author},
          genre {genre},
          copyright_date {copyright_date},
          checked_out {false}
    {
        string::size_type n1, n2, n3;
        n1 = isbn.find('-');
        if (n1 == string::npos)
            throw runtime_error("Bad ISBN");
        n2 = isbn.find('-', n1 + 1);
        if (n2 == string::npos)
            throw runtime_error("Bad ISBN");
        n3 = isbn.find('-', n2 + 1);
        if (n3 == string::npos)
            throw runtime_error("Bad ISBN");
        string s1 = isbn.substr(0, n1);
        string s2 = isbn.substr(n1 + 1, n2 - n1 - 1);
        string s3 = isbn.substr(n2 + 1, n3 - n2 - 1);
        string s4 = isbn.substr(n3 + 1);
        if (!is_digits(s1) || !is_digits(s2) || !is_digits(s3))
            throw runtime_error("Bad ISBN");
        if (s4.size() != 1 || (!isalpha(s4[0]) && !isdigit(s4[0])))
            throw runtime_error("Bad ISBN");

        int idx = static_cast<int>(genre);
        if (idx < 0 || genre_table.size() <= idx)
            throw runtime_error(
                    "Bad genre: out of range: " + to_string(idx));
    }


    string Book::get_isbn() const
    {
        return isbn;
    }


    string Book::get_title() const
    {
        return title;
    }


    string Book::get_author() const
    {
        return author;
    }


    Genre Book::get_genre() const
    {
        return genre;
    }


    Date Book::get_copyright_date() const
    {
        return copyright_date;
    }


    bool Book::is_checked_out() const
    {
        return checked_out;
    }


    void Book::check_in()
    {
        if (!checked_out)
            throw runtime_error("check_in(): already checked in");
        checked_out = false;
    }


    void Book::check_out()
    {
        if (checked_out)
            throw runtime_error("checked_out(): already checked out");
        checked_out = true;
    }


    void Book::set_genre(Genre g)
    {
        genre = g;
    }


    bool operator==(const Book& x, const Book& y)
    {
        return x.get_isbn() == y.get_isbn();
    }


    bool operator!=(const Book& x, const Book& y)
    {
        return !(x == y);
    }


    ostream& operator<<(ostream& os, const Book& b)
    {
        return os << "Title: " << b.get_title() << '\n'
                  << "Author: " << b.get_author() << '\n'
                  << "Genre: " << b.get_genre() << '\n'
                  << "ISBN: " << b.get_isbn();
    }

}   // end of namespace Book
