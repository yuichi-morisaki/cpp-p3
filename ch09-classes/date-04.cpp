#include <iostream>
using namespace std;

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

void f(int x, int y)
{
    try {
        Date dxy {2004, x, y};
        cout << dxy.month() << "/" << dxy.day() << '\n';
//        cout << dxy << '\n';
        dxy.add_day(2);
    }
    catch (Date::Invalid) {
        throw runtime_error("invalid date");
    }
}

int main()
{
    Date birthday {1970, 12, 30};
/*
    birthday.m = 14;    // error:
                        // 'int Date::m' is private
*/
    cout << birthday.month() << '\n';

    f(12, 31);
    f(31, 12);

    return 0;

    // To improve more, let's go to date-05.cpp
}


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

