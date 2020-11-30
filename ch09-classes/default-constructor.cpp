#include <stdexcept>
using namespace std;


enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};


class Year {
public:
    class Invalid {};
    Year();
    Year(int y);
    int year();
private:
    static constexpr int min {1800};
    static constexpr int max {2200};
    int y {min};
};

Year::Year()
{
}

Year::Year(int y)
    : y {y}
{
    if (y < min || max < y)
        throw runtime_error("Bad year");
}


class Date {
public:
    Date();
    Date(int y);
    Date(int y, Month m, int d);
private:
    Year y {};
    Month m {Month::jan};
    int d {1};
};


Date::Date()
{
}

Date::Date(int y)
    : y {y}
{
}

Date::Date(int y, Month m, int d)
    : y {y}, m {m}, d {d}
{
}

/*
// Instead of example code above,
const Date& default_date()
{
    static Date d {2001, Month::jan, 1};
    return d;
}

Date::Date()
    : y {default_date().year()},
    : m {default_date().month()},
    : d {default_date().day()}
{
}
*/


int main()
{
    Year y1 {};
    Year y2 {2020};

    Date d1 {};
    Date d2 {2020};
//    Date d3 {1600};     // Bad year
    Date d4 {2020, Month::nov, 30};

    return 0;
}
