// simple Date
struct Date {
    int y;  // year
    int m;  // month in year
    int d;  // day of month
};

// ----------------------------------------------------------------------------
//  helper functions
// ----------------------------------------------------------------------------

void init_day(Date& dd, int y, int m, int d)
{
    // check that (y, m, d) is a valid date
    // if it is, use it to initialize dd
}

void add_day(Date& dd, int n)
{
    // increase dd by n days
}

// ----------------------------------------------------------------------------

int main()
{
    Date x;
    init_day(x, 11, 30, 2020);  // oops! (no day 2020 in year 11)
    add_day(x, 1);

    // assume we have defined the output operator << for a Date
    Date today;
        // ...
    cout << today << '\n';  // use today, but is it initialized?
        // ...
    init_day(today, 2020, 11, 30);
        // ...
    Date tomorrow;
    // someone might do this way instead of using add_day()
    tomorrow.m = today.m;
    tomorrow.d = today.d + 1;
    cout << tomorrow << '\n';   // use tomorrow, but is it a valid date?

    // So, let's go to 'date-03.cpp'
}
