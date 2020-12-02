#include "chrono2.h"


namespace Chrono {

    ostream& operator<<(ostream& os, const Day& day)
    {
        int idx = static_cast<int>(day);
        if (idx < 0 || Day_Table.size() <= idx)
            throw runtime_error("Day: out of bound");
        return os << Day_Table[idx];
    }

    Day int_to_Day(int n)
    {
        if (n < 0 || Day_Table.size() <= n)
            throw runtime_error("Day: out of bound");
        return static_cast<Day>(n);
    }

    // ----------------------------------------------------------

    ostream& operator<<(ostream& os, const Month& month)
    {
        int idx = static_cast<int>(month);
        if (idx <= 0 || Month_Table.size() <= idx)
            throw runtime_error("Month: out of bound");
        return os << Month_Table[idx];
    }

    Month int_to_Month(int n)
    {
        if (n < 0 || Month_Table.size() <= n)
            throw runtime_error("Month: out of bound");
        return static_cast<Month>(n);
    }

    // ----------------------------------------------------------

    Date::Date()
    {
    }

    Date::Date(long int n)
        : days {n}
    {
        if (n < 0)
            throw runtime_error("Date: init with negative value");
    }

    void Date::sync()
    {
        long int rest = days;

        int year = 1970;
        while (true) {
            int days_in_year = leapyear(year) ? 366 : 365;
            if (rest < days_in_year)
                break;
            rest -= days_in_year;
            ++year;
        }
        _year = year;

        int month = 1;
        while (true) {
            int days_in_month;
            switch (month) {
                case 2:
                    days_in_month = leapyear(year) ? 29 : 28;
                    break;
                case 4: case 6: case 9: case 11:
                    days_in_month = 30;
                    break;
                default:
                    days_in_month = 31;
                    break;
            }
            if (rest < days_in_month)
                break;
            rest -= days_in_month;
            ++month;
        }
        _month = month;

        int day = 1;
        while (rest > 0) {
            --rest;
            ++day;
        }
        _day = day;

        synced = true;
    }

    int Date::year() const
    {
        if (!synced) sync();
        return _year;
    }

    Month Date::month() const
    {
        if (!synced) sync();
        return int_to_Month(_month);
    }

    int Date::day() const
    {
        if (!synced) sync();
        return _day;
    }


    void Date::add_day(int n)
    {
        days += n;
        if (days < 0)
            throw runtime_error("Invalid: days negative value");
        synced = false;
    }

    void Date::add_month(int n)
        // TODO: check if offset exceed the limit of int
    {
        if (!synced) sync();
        int offset = 0;
        if (n > 0) {
            while (n > 0) {
                int days_in_month;
                switch (_month) {
                    case 2:
                        days_in_month = leapyear(_year) ? 29 : 28;
                        break;
                    case 4: case 6: case 9: case 11:
                        days_in_month = 30;
                        break;
                    default:
                        days_in_month = 31;
                        break;
                }
                offset += days_in_month;
                --n;
                if (_month == 12) {
                    _month = 1;
                    ++_year;
                }
                else {
                    ++_month;
                }
            }
        } else if (n < 0) {
            while (n < 0) {
                int days_in_month;
                switch (_month - 1) {   // previous month
                    case 2:
                        days_in_month = leapyear(_year) ? 29 : 28;
                        break;
                    case 4: case 6: case 9: case 11:
                        days_in_month = 30;
                        break;
                    default:
                        days_in_month = 31;
                        break;
                }
                offset -= days_in_month;
                ++n;
                if (_month == 1) {
                    _month = 12;
                    --_year;
                }
                else {
                    --_month;
                }
            }
        } else {
            ;   // do nothing
        }
        add_day(offset);
    }

    void Date::add_year(int n)
        // TODO: check if 12*n exceed the limit of int
    {
        add_month(12 * n);
    }


    ostream& operator<<(ostream& os, const Date& d)
    {
        return os << '(' << d.year()
                  << ',' << static_cast<int>(d.month())
                  << ',' << d.day() << ')';
    }

    bool leapyear(int year)
    {
        if (year % 4 != 0)
            return false;
        if (year % 400 == 0)
            return true;
        if (year % 100 == 0)
            return false;
        return true;
    }
}
