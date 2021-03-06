#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}


class Date {
    public:
        Date(int yy, int mm, int dd);
        void add_day(int n);
        int year() const { return y; }
        int month() const { return m; }
        int day() const { return d; }
    private:
        int y, m, d;
};

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() << ')';
}

Date::Date(int yy, int mm, int dd)
    : y {yy}, m {mm}, d {dd}
{
    if (m <= 0 || 12 < m)
        error("Bad month");
    if (d <= 0)
        error("Bad day");
    int days_of_month = 31;
    switch (m) {
        case 2:
            days_of_month = 28;     // ignore leapyears
            break;
        case 4: case 6: case 9: case 11:
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
            case 2:
                days_of_month = 28;
                break;
            case 4: case 6: case 9: case 11:
                days_of_month = 30;
                break;
            default:
                break;
        }
        if (d == days_of_month) {
            d = 1;
            if (m == 12) {
                m = 1;
                ++y;
            } else {
                ++m;
            }
        } else {
            ++d;
        }

        --n;
    }
}


int main()
try {
    // Date today {1999, 0, 10};
    // Date today {1999, 13, 10};
    // Date today {1999, 2, 0};
    // Date today {1999, 2, 29};

    // Date today {1978, 6, 25};
    // Date today {2007, 9, 30};
    // Date today {2001, 2, 28};
    Date today {1999, 12, 31};
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
