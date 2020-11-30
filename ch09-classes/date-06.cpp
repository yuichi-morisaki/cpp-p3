#include <iostream>
#include <vector>
using namespace std;

// ------------------------------------------------------------------

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

vector<string> month_tbl = {
    "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
    "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
};

ostream& operator<<(ostream& os, Month m)
{
    int idx = int(m) - int(Month::jan);
    return os << month_tbl[idx];
}

// ------------------------------------------------------------------

class Year {
public:
    class Invalid {};
    Year(int x);
    int year();
private:
    static constexpr int min = 1800;
    static constexpr int max = 2200;
    int y;
};

Year::Year(int x)
    : y {x}
{
    if (x < min || max < x)
        throw Invalid {};
}

int Year::year()
{
    return y;
}

ostream& operator<<(ostream& os, Year y)
{
    return os << y.year();
}

// ------------------------------------------------------------------

class Date {
public:
    class Invalid {};
    Date();     // default constructor
    Date(Year y, Month m, int d);
    void add_day(int n);
    int year();
    int month();
    int day();
private:
    Year y;
    Month m;
    int d;
    bool is_valid();
};

Date::Date()
    : y {2001}, m {Month::jan}, d {1}
{
}

Date::Date(Year y, Month m, int d)
    : y {y}, m {m}, d {d}
{
    if (!is_valid())
        throw Invalid {};
}

void Date::add_day(int n)
{
    // TODO
}

int Date::year()
{
    return y.year();
}

int Date::month()
{
    return int(m);
}

int Date::day()
{
    return d;
}

bool Date::is_valid()
{
    // TODO

    return true;
}

ostream& operator<<(ostream& os, Date d)
{
    return os << d.year() << '/'
              << d.month() << '/'
              << d.day();
}

// ------------------------------------------------------------------

int main()
{
    Date holiday {1978, Month::jul, 4};     // initialization
    // cout << "holiday = " << holiday << '\n';
    Date d2 = holiday;
    // cout << "d2 = " << d2 << '\n';
    Date d3 = Date {1978, Month::jul, 4};
    // cout << "d3 = " << d3 << '\n';
    holiday = Date {1978, Month::dec, 24};  // assignment
    // cout << "holiday = " << holiday << '\n';
    d3 = holiday;
    // cout << "d3 = " << d3 << '\n';

/*
    Date d0;                // no initializer
    Date d1 {};             // empty initializer
    Date d2 {1998};         // too few arguments
    Date d3 {1, 2, 3, 4};   // too mamy arguments
    Date d4 {1, "jan", 2};  // wrong argument type
*/
    Date d5 {1, Month::jan, 2};     // OK
    Date d6 {d5};                   // OK

    return 0;
}
