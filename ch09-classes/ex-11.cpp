#include "chrono.h"
#include <iostream>

using namespace std;
using namespace Chrono;

int main()
{
    for (int y = 2021; y < 2030; ++y)
        cout << y << ": " << week_of_year(y) << '\n';

    Date d {2020, Month::Nov, 30};
    cout << d << '\n';
    d.add_day(1);
    cout << d << '\n';
    d.add_day(30);
    cout << d << '\n';
    d.add_day(1);
    cout << d << '\n';
    d.add_day(1);
    cout << d << '\n';

    Date d2 {2020, Month::Dec, 2};
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
    d2.add_day(1);
    cout << "Today: " << d2 << '\n';
    cout << "Next workday: " << next_workday(d2) << '\n';
}
