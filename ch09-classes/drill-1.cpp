#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}


struct Date {
    int y;
    int m;
    int d;
};


ostream& operator<<(ostream& os, const Date& dd)
{
    return os << '(' << dd.y
              << ',' << dd.m
              << ',' << dd.d << ')';
}

void init_day(Date& dd, int y, int m, int d)
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

    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_one_day(Date& dd)
{
    int days_of_month = 31;
    switch (dd.m) {
        case 2:
            days_of_month = 28;
            break;
        case 4: case 6: case 9: case 11:
            days_of_month = 30;
            break;
        default:
            break;
    }

    if (dd.d == days_of_month) {
        dd.d = 1;
        if (dd.m == 12) {
            dd.m = 1;
            ++dd.y;
        } else {
            ++dd.m;
        }
    } else {
        ++dd.d;
    }
}

void add_day(Date& dd, int n)
{
    while (n > 0) {
        add_one_day(dd);
        --n;
    }
}


int main()
try {
    Date today;
    init_day(today, 1978, 6, 25);
    init_day(today, 1999, 12, 31);
    init_day(today, 2001, 2, 28);
    init_day(today, 2007, 9, 30);
    // init_day(today, 1999, 0, 10);
    // init_day(today, 1999, 13, 10);
    // init_day(today, 1999, 9, 0);
    // init_day(today, 1999, 9, 31);

    Date tomorrow = today;
    add_day(tomorrow, 1);
    cout << "Today:\t  " << today << '\n'
         << "Tomorrow: " << tomorrow << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
