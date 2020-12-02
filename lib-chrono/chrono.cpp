#include "chrono.h"

namespace Chrono {

    // ============================================================
    //  'Day' in the week

    // ------------------------------------------------------------
    //  Helper functions for class 'Day'

    Day Day_from_int(int i)
    {
        if (i < DAY_MIN || DAY_MAX < i)
            throw runtime_error(
                    "Day_from_int(): out of bound: "
                    + to_string(i));

        return static_cast<Day>(i);
    }

    int int_from_Day(const Day& d)
    {
        int i = static_cast<int>(d);
        if (i < DAY_MIN || DAY_MAX < i)
            throw runtime_error(
                    "int_from_Day(): out of bound: "
                    + to_string(i));

        return i;
    }

    ostream& operator<<(ostream& os, const Day& d)
    {
        int idx = int_from_Day(d);
        return os << DAYS[idx];
    }

    // ============================================================
    //  'Month'

    // ------------------------------------------------------------
    //  Helper functions for class 'Month'

    Month Month_from_int(int i)
    {
        if (i < MONTH_MIN || MONTH_MAX < i)
            throw runtime_error(
                    "Month_from_int(): out of bound: "
                    + to_string(i));

        return static_cast<Month>(i);
    }

    int int_from_Month(const Month& m)
    {
        int i = static_cast<int>(m);
        if (i < MONTH_MIN || MONTH_MAX < i)
            throw runtime_error(
                    "int_from_Month(): out of bound: "
                    + to_string(i));

        return i;
    }

    ostream& operator<<(ostream& os, const Month& m)
    {
        int idx = int_from_Month(m);
        return os << MONTHS[idx];
    }

    // ============================================================
    //  'Date'

    Date::Date()
    {
    }

    Date::Date(int y, Month m, int d)
    {
        days = days_from_origin(y, m, d);
    }

    vector<int> Date::getter() const
    {
        vector<int> ymd;
        long int rest = days;

        int year = 1970;
        while (true) {
            int d_in_y = leapyear(year) ? 366 : 365;
            if (rest < d_in_y)
                break;
            rest -= d_in_y;
            ++year;
        }
        ymd.push_back(year);

        Month month = Month::Jan;
        while (true) {
            int d_in_m = days_in_month(year, month);
            if (rest < d_in_m)
                break;
            rest -= d_in_m;
            month = Month_from_int(int_from_Month(month) + 1);
        }
        ymd.push_back(int_from_Month(month));

        int day = 1;
        while (rest > 0) {
            --rest;
            ++day;
        }
        ymd.push_back(day);

        return ymd;
    }

    int Date::year() const
    {
        vector<int> ymd_vec = getter();
        return ymd_vec[0];
    }

    Month Date::month() const
    {
        vector<int> ymd_vec = getter();
        return Month_from_int(ymd_vec[1]);
    }

    int Date::day() const
    {
        vector<int> ymd_vec = getter();
        return ymd_vec[2];
    }


    void Date::add_year(int num_of_years)
    {
        if (num_of_years == 0) return;

        vector<int> ymd = getter();
        int year = ymd[0];
        Month month = Month_from_int(ymd[1]);
        int day = ymd[2];

        // beware of leap year
        year += num_of_years;
        if (year < 1970)
            throw runtime_error(
                    "Date::add_year: before origin");

        if (month == Month::Feb && day == 29 &&
                !leapyear(year)) {
            month = Month::Mar;
            day = 1;
        }

        days = days_from_origin(year, month, day);
    }

    void Date::add_month(int num_of_months)
    {
        if (num_of_months == 0) return;

        vector<int> ymd = getter();
        int year = ymd[0];
        Month month = Month_from_int(ymd[1]);
        int day = ymd[2];

        bool neg = num_of_months < 0 ? true : false;
        if (neg) num_of_months *= -1;
        int num_of_years = num_of_months / 12;
        num_of_months %= 12;
        if (neg) {
            if (num_of_months) {
                num_of_months = 12 - num_of_months;
                ++num_of_years;
            }
            num_of_years *= -1;
        }

        int i = int_from_Month(month) + num_of_months;
        if (i > 12) {
            i -= 12;
            ++year;
        }
        year += num_of_years;
        Month new_month = Month_from_int(i);
        int d_in_m = days_in_month(year, new_month);
        if (day > d_in_m) {
            new_month = Month_from_int(
                    int_from_Month(new_month) + 1);
            day = 1;
        }

        days = days_from_origin(year, new_month, day);
    }

    void Date::add_day(int num_of_days)
    {
        days += num_of_days;

        if (days < 0)
            throw runtime_error(
                    "Date::add_day(): negative value");
    }

    // ------------------------------------------------------------
    //  Helper functions for class 'Date'

    ostream& operator<<(ostream& os, const Date& date)
    {
        return os << '(' << date.year()
                  << ',' << int_from_Month(date.month())
                  << ',' << date.day() << ')';
    }

    istream& operator>>(istream& is, Date& date)
    {
        int year, month, day;
        char c1, c2, c3, c4;
        is >> c1 >> year
           >> c2 >> month
           >> c3 >> day >> c4;

        if (!is) return is;
        if (c1 != '(' || c2 != ',' || c3 != ',' || c4 != ')') {
            is.clear(ios_base::failbit);
            return is;
        }

        date = Date(year, Month_from_int(month), day);

        return is;
    }

    bool operator==(const Date& x, const Date& y)
    {
        return x.year() == y.year()
            && x.month() == y.month()
            && x.day() == y.day();
    }

    bool operator!=(const Date& x, const Date& y)
    {
        return !(x == y);
    }

    long int days_from_origin(int year, Month month, int day)
    {
        if (year < 1970)
            throw runtime_error(
                    "days_from_origin(): before origin");
        if (day <= 0 || days_in_month(year, month) < day)
            throw runtime_error(
                    "days_from_origin(): day - out of bound");

        long int offset = (day - 1);
        while (month != Month::Jan) {
            month = Month_from_int(int_from_Month(month) - 1);
            offset += days_in_month(year, month);
        }
        for (int y = 1970; y < year; ++y) {
            offset += (leapyear(y) ? 366 : 365);
        }

        return offset;
    }

    bool leapyear(int year)
    {
        if (year % 4 != 0)      return false;
        if (year % 400 == 0)    return true;
        if (year % 100 == 0)    return false;
        return true;
    }

    int days_in_month(int year, Month month)
    {
        switch (month) {
            case Month::Feb:
                if (leapyear(year))
                    return 29;
                return 28;
            case Month::Apr:
            case Month::Jun:
            case Month::Sep:
            case Month::Nov:
                return 30;
            default:
                return 31;
        }
        throw runtime_error(
                "days_in_month(): never reached here");
    }


    Day day_of_week(const Date& date)
    {
        int year = date.year();
        Month month = date.month();
        int day = date.day();
        long int days = days_from_origin(year, month, day);
        return Day_from_int((days + 4) % 7);
    }

    Date next_sunday(const Date& date)
    {
        Day day = day_of_week(date);
        int offset = 7 - int_from_Day(day);
        Date result = date;
        result.add_day(offset);
        return result;
    }

    Date next_weekday(const Date& date)
    {
        Day day = day_of_week(date);
        int offset;
        switch (day) {
            case Day::Sun:
            case Day::Mon:
            case Day::Tue:
            case Day::Wed:
            case Day::Thu:
                offset = 1;
                break;
            default:
                offset = 8 - int_from_Day(day);
                break;
        }
        Date result = date;
        result.add_day(offset);
        return result;
    }

    int week_of_year(int year)
    {
        if (!leapyear(year))
            return 53;
        Date first_day {year, Month::Jan, 1};
        Day day = day_of_week(first_day);
        if (day == Day::Sat)
            return 54;
        else
            return 53;
    }

}   // end of namespace Chrono
