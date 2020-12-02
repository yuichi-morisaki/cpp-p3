#include "chrono.h"
#include <cmath>


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
        for ( ; n > 0; --n) {
            int days_in_month;
            switch (m) {
                case Month::Feb:
                    if (leapyear(y))
                        days_in_month = 29;
                    else
                        days_in_month = 28;
                    break;
                case Month::Apr:
                case Month::Jun:
                case Month::Sep:
                case Month::Nov:
                    days_in_month = 30;
                    break;
                default:
                    days_in_month = 31;
                    break;
            }
            if (d == days_in_month) {
                if (m == Month::Dec) {
                    ++y;
                    m = Month::Jan;
                    d = 1;
                }
                else {
                    m = static_cast<Month>(
                            static_cast<int>(m) + 1);
                    d = 1;
                }
            }
            else {
                ++d;
            }
        }
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
        if (y % 4 != 0) return false;
        if (y % 400 == 0) return true;
        if (y % 100 == 0) return false;
        return true;
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


    Day day_of_1st_jan(int year, int base_year, Day base_day)
    {
        if (year == base_year)
            return base_day;

        int n = static_cast<int>(base_day);
        if (year > base_year) {
            if (leapyear(base_year))
                n = (n + 2) % 7;
            else
                n = (n + 1) % 7;
            base_day = static_cast<Day>(n);
            return day_of_1st_jan(year, base_year + 1, base_day);
        }
        else {
            if (leapyear(base_year - 1))
                n = (n + 5) % 7;    // decrement twice
            else
                n = (n + 6) % 7;    // decrement once
            base_day = static_cast<Day>(n);
            return day_of_1st_jan(year, base_year - 1, base_day);
        }
    }


    Day day_of_the_week(const Date& d)
    {
        int year = d.year();
        Day d0 = day_of_1st_jan(year, 2021, Day::Fri);

        int offset = 0;
        int month = static_cast<int>(d.month());
        if (month > 1) offset += 31;
        if (month > 2) {
            offset += 28;
            if (leapyear(year)) offset += 1;
        }
        if (month > 3) offset += 31;
        if (month > 4) offset += 30;
        if (month > 5) offset += 31;
        if (month > 6) offset += 30;
        if (month > 7) offset += 31;
        if (month > 8) offset += 31;
        if (month > 9) offset += 30;
        if (month > 10) offset += 31;
        if (month > 11) offset += 30;
        offset += (d.day() - 1);

        return static_cast<Day>(
                (static_cast<int>(d0) + offset) % 7);
    }


    Date next_workday(const Date& d)
    {
        Day wd = day_of_the_week(d);
        Date result = d;
        switch (wd) {
            case Day::Sun:
            case Day::Mon:
            case Day::Tue:
            case Day::Wed:
            case Day::Thu:
                result.add_day(1);
                break;
            case Day::Fri:
                result.add_day(3);
                break;
            case Day::Sat:
                result.add_day(2);
                break;
            default:
                throw runtime_error("next_workday(): Invalid day");
        }
        return result;
    }


    int week_of_year(int y)
    {
        /*  Case: 'y' is not a leap year
                365 == the_days_in_the_first_week
                     + (7 days * 51 weeks)
                     + the_days_in_the_final_week,
                where   1 <= the_days_in_the_first_week <= 7
                  and   1 <= the_days_in_the_final_week <= 7
        */
        if (!leapyear(y))
            return 53;

        /*  Case: 'y' is a leap year
                If 1st, Jan. is not Sat.,
                then it's the same of the case above.
                If not,
                366 = 1 + (7 days * 52 weeks) + 1
        */
        Day d = day_of_1st_jan(y, 2021, Day::Fri);
        if (d != Day::Sat)
            return 53;
        else
            return 54;
    }

}   // end of namespace Chrono
