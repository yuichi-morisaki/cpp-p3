#include "chrono.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;

int main()
{
    // ------------------------------------------------------------
    //  leapyear()

    vector<int> years {1994, 1996, 2000, 2100};
    for (int year: years) {
        bool leap = leapyear(year);
        if (leap)
            cout << year << " is a leap year\n";
        else
            cout << year << " is NOT a leap year\n";
    }

    // ------------------------------------------------------------
    //  days_in_month()

    int year = 2000;
    while (year < 2002) {
        cout << "---- Year " << year << " ----\n";
        for (int i = 1; i <= 12; ++i) {
            Month month = Month_from_int(i);
            int days = days_in_month(year, month);
            cout << days << "days in " << month << '\n';
        }
        ++year;
    }

    // ------------------------------------------------------------
    //  days_from_origin()

    cout << "---- Days from the origin ----\n";
    try {
        days_from_origin(1969, Month::Dec, 31);
    }
    catch (exception& e) {
        cerr << "exception" << e.what() << '\n';
    }
    try {
        days_from_origin(1970, Month::Dec, 0);
    }
    catch (exception& e) {
        cerr << "exception" << e.what() << '\n';
    }
    try {
        days_from_origin(1970, Month::Dec, 32);
    }
    catch (exception& e) {
        cerr << "exception" << e.what() << '\n';
    }

    cout << "\n";
    cout << "1970/01/01 => "
         << days_from_origin(1970, Month::Jan, 1) << '\n';
    cout << "1970/01/02 => "
         << days_from_origin(1970, Month::Jan, 2) << '\n';
    cout << "1970/02/01 => "
         << days_from_origin(1970, Month::Feb, 1) << '\n';
    cout << "1971/01/01 => "
         << days_from_origin(1971, Month::Jan, 1) << '\n';
    cout << "1972/01/01 => "
         << days_from_origin(1972, Month::Jan, 1) << '\n';
    cout << "1973/01/01 => "
         << days_from_origin(1973, Month::Jan, 1) << '\n';

    // ------------------------------------------------------------

    cout << "\n";
    Date d0 {};
    cout << "d0: " << d0 << '\n';
    Date d1 {2020, Month::Dec, 24};
    cout << "d1: " << d1 << '\n';
    d1.add_day(1);
    cout << "+1d: " << d1 << '\n';
    d1.add_day(7);
    cout << "+7d: " << d1 << '\n';
    d1.add_day(-8);
    cout << "-8d: " << d1 << '\n';
    d1.add_month(1);
    cout << "+1m: " << d1 << '\n';
    d1.add_month(-3);
    cout << "-3m: " << d1 << '\n';

    Date d2 {2020, Month::Feb, 29};
    cout << "d2: " << d2 << '\n';
    d2.add_year(1);
    cout << "+1y: " << d2 << '\n';
    d2.add_year(-1);
    d2.add_day(-1);
    cout << "-1y-1d: " << d2 << '\n';
    d2.add_year(-1);
    cout << "-1y: " << d2 << '\n';
    d2.add_year(+1);
    d2.add_day(-1);
    cout << "+1y-1d: " << d2 << '\n';
    d2.add_year(20);
    cout << "+20y: " << d2 << '\n';
    d2.add_year(60);
    cout << "+60y: " << d2 << '\n';

    cout << "----\n";
    cout << "Enter a date '(y,m,d)': ";
    Date ld, rd;
    cin >> ld;
    cout << "Enter another date: ";
    cin >> rd;
    if (ld == rd)
        cout << ld << " == " << rd << '\n';
    else
        cout << ld << " != " << rd << '\n';

    cout << ld << " is " << day_of_week(ld) << '\n';
    cout << rd << " is " << day_of_week(rd) << '\n';

    vector<int> vd = {2, 3, 4, 5, 6, 7, 8};
    for (int d: vd) {
        Date date {2020, Month::Dec, d};
        cout << date << " is " << day_of_week(date)
             << ", Sun: " << next_sunday(date)
             << ", Weekday: " << next_weekday(date)
             << "\n";
    }

    for (int year = 2020; year < 2030; ++year)
        cout << "Year " << year << " has "
             << week_of_year(year) << " weeks.\n";

    return 0;
}
