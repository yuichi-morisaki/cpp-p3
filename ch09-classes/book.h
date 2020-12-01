#include "chrono.h"
#include <vector>

using namespace Chrono;


namespace Book_lib {

    enum class Genre {
        fiction,
        nonfiction,
        periodical,
        biography,
        children,
    };


    const vector<string> genre_table = {
        "fiction",
        "non-fiction",
        "periodical",
        "biography",
        "children",
    };


    ostream& operator<<(ostream& os, const Genre& g);


    class Book {
    public:
        Book(string isbn,
             string title,
             string author,
             Genre genre,
             const Date& copyright_date);

        string get_isbn() const;
        string get_title() const;
        string get_author() const;
        Genre get_genre() const;
        Date get_copyright_date() const;
        bool is_checked_out() const;

        void check_in();
        void check_out();
        void set_genre(Genre g);
    private:
        string isbn;
        string title;
        string author;
        Genre genre;
        Date copyright_date;
        bool checked_out;
    };


    bool operator==(const Book& x, const Book& y);
    bool operator!=(const Book& x, const Book& y);
    ostream& operator<<(ostream& os, const Book& b);

}   // end of namespace Book
