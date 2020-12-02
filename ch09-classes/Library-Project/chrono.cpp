#include "chrono.h"


namespace Chrono {

    const Date& default_date()
    {
        static Date d {2001, Month::Jan, 1};
        return d;
    }


    Date::Date()
        : y {default_date().year()},
          m {default_date().month()},
          d {default_date().day()}
    {
    }


    Date::Date(int yy, Month mm, int dd)
        : y {yy}, m {mm}, d {dd}
    {
        if (!is_date(yy, mm, dd))
            throw Invalid {};
    }


    int Date::day() const
    {
        return d;
    }


    Month Date::month() const
    {
        return m;
    }


    int Date::year() const
    {
        return y;
    }


    void Date::add_day(int n)
    {
        // TODO
    }


    void Date::add_month(int n)
    {
        // TODO
    }


    void Date::add_year(int n)
    {
        // beware of leap year
        if (m == Month::Feb && d == 29 && !leapyear(y + n)) {
            m = Month::Mar;
            d = 1;
        }
        y += n;
    }


    bool is_date(int y, Month m, int d)
    {
        // assume that y is valid

        if (m < Month::Jan || Month::Dec < m)
            return false;

        if (d <= 0)
            return false;

        int days_in_month = 31;     // default
        switch (m) {
        case Month::Feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::Apr:
        case Month::Jun:
        case Month::Sep:
        case Month::Nov:
            days_in_month = 30;
            break;
        default:
            break;
        }
        if (days_in_month < d)
            return false;

        return true;
    }


    bool leapyear(int y)
    {
        // TODO
    }


    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year()
            && a.month() == b.month()
            && a.day() == b.day();
    }


    bool operator!=(const Date& a, const Date& b)
    {
        return !(a == b);
    }


    ostream& operator<<(ostream& os, const Date& d)
    {
        return os << '(' << d.year()
                  << ',' << int(d.month())
                  << ',' << d.day() << ')';
    }


    istream& operator>>(istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;

        if (!is)
            return is;

        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
            is.clear(ios_base::failbit);    // set the fail bit
            return is;
        }

        dd = Date(y, Month(m), d);

        return is;
    }


    Day day_of_week(const Date& d)
    {
        // TODO
    }


    Date next_sunday(const Date& d)
    {
        // TODO
    }


    Date next_weekday(const Date& d)
    {
        // TODO
    }

}   // end of namespace Chrono
