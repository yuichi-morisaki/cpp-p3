#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}


enum class Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};


class Date {
    public:
        Date(int yy, Month mm, int dd);
        void add_day(int n);
        int year() const { return y; }
        Month month() const { return m; }
        int day() const { return d; }
    private:
        int y;
        Month m;
        int d;
};

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << int(d.month())
              << ',' << d.day() << ')';
}

Date::Date(int yy, Month mm, int dd)
    : y {yy}, m {mm}, d {dd}
{
    if (m < Month::Jan || Month::Dec < m)
        error("Bad month");
    if (d <= 0)
        error("Bad day");
    int days_of_month = 31;
    switch (m) {
        case Month::Feb:
            days_of_month = 28;     // ignore leapyears
            break;
        case Month::Apr:
        case Month::Jun:
        case Month::Sep:
        case Month::Nov:
            days_of_month = 30;
            break;
        default:
            break;
    }
    if (days_of_month < d)
        error("Bad day");
}

void Date::add_day(int n)
{
    while (n > 0) {
        int days_of_month = 31;
        switch (m) {
            case Month::Feb:
                days_of_month = 28;
                break;
            case Month::Apr:
            case Month::Jun:
            case Month::Sep:
            case Month::Nov:
                days_of_month = 30;
                break;
            default:
                break;
        }
        if (d == days_of_month) {
            d = 1;
            if (m == Month::Dec) {
                m = Month::Jan;
                ++y;
            } else {
                m = Month(int(m) + 1);
            }
        } else {
            ++d;
        }

        --n;
    }
}


int main()
try {
/*  // 0 or 13 is a wrong-type argument
    Date today {1999, 0, 10};
    Date today {1999, 13, 10};
*/
    // Date today {1999, Month::Feb, 0};
    // Date today {1999, Month::Feb, 29};

    // Date today {1978, Month::Jun, 25};
    // Date today {2007, Month::Sep, 30};
    // Date today {2001, Month::Feb, 28};
    Date today {1999, Month::Dec, 31};

    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << "Today:\t  " << today << '\n';
    cout << "Tomorrow: " << tomorrow << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
