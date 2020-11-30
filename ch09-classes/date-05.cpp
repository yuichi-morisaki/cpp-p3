#include <iostream>
using namespace std;

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month int_to_month(int x)
{
    if (x < int(Month::jan) || int(Month::dec) < x)
        throw runtime_error("bad month");
    return Month(x);
}

enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

class Date {
public:
    class Invalid {};   // to be used as exception
    Date(int y, int m, int d);
    void add_day(int n);
    int year();
    int month();
    int day();
private:
    int y;  // year
    int m;  // month in year
    int d;  // day of month
    bool is_valid();    // return true if date is valid
};


int main()
{
    Month m = Month::feb;
/*
    Month m2 = feb; // error: 'feb' was not declared
    m = 7;  // error: cannot convert 'int' to 'Month'
    int n = m;  // cannot convert 'Month' to 'int'
*/
    Month mm = Month(7);    // OK: convert 'int' to 'Month'
    mm = int_to_month(7);
    Month mm2 = Month(13);  // but, unchecked
//    mm2 = int_to_month(13);   // error: bad month


    return 0;

    // To improve more, let's go to date-06.cpp
}


// ==================================================================
// Implementation

bool Date::is_valid()
{
    if (m < 1 || 12 < m) return false;
    // ...
    return true;
}

Date::Date(int y, int m, int d)
    : y{y}, m{m}, d{d}
{
    if (!is_valid())
        throw Invalid{};
}

void Date::add_day(int n)
{
    // ...
}

int Date::year()
{
    return y;
}

int Date::month()
{
    return m;
}

int Date::day()
{
    return d;
}

