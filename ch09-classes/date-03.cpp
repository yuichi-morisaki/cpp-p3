// simple Date with member functions
struct Date {
    int y;  // year
    int m;  // month in year
    int d;  // day of month
    Date(int y, int m, int d); // check for valid date and initialize
    void add_day(int n);        // increase the Date by n days
};

Date::Date(int y, int m, int d) : y {y}, m {m}, d {d} { }

void Date::add_day(int n)
{
    // ...
}


int main()
{
//    Date my_birthday;   // error:
                        // no matching function for call to 'Date::Date()'
    Date today {12, 24, 2007};      // is it valid?
    Date last {2000, 12, 31};       // OK (colloquial style)
    Date next_day = {2014, 2, 14};  // OK (slightly verbose)
    Date christmas = Date{1976, 12, 24};    // OK (verbose style)

    // use the dot member-access notation
    last.add_day(1);
//    add_day(2);     // error:
                    // 'add_day' was not declared in this scope

    // we cannot prevent these
    ++christmas.d;
    today.m = 14;

    // So, let's go to 'date-04.cpp'
}
