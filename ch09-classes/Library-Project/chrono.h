#include <iostream>

using namespace std;


namespace Chrono {

    enum class Day {
        Sun, Mon, Tue, Wed, Thu, Fri, Sat
    };


    enum class Month {
        Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    };


    class Date {
    public:
        class Invalid {};   // to throw as exception

        Date();     // default constructor
        Date(int y, Month m, int d);

        int day() const;
        Month month() const;
        int year() const;

        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
    };


    bool is_date(int y, Month m, int d);    // true for valid date
    bool leapyear(int y);      // true if y is a leap year

    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);

    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(istream& is, Date& dd);

    Day day_of_week(const Date& d);     // day of week of d
    Date next_sunday(const Date& d);    // next Sunday after d
    Date next_weekday(const Date& d);   // next weekday after d

}   // end of namespace Chrono
