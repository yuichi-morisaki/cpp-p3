// simple Date
struct Date {
    int y;  // year
    int m;  // month in year
    int d;  // day of month
};

int main()
{
    Date today; // a Date variable
    // set today to November 30, 2020
    today.y = 2020;
    today.m = 30;
    today.d = 11;

    // this doesn't make sense
    Date x;
    x.y = -3;
    x.m = 13;
    x.d = 32;

    // how about this?
    Date y;
    y.y = 2000;
    y.m = 2;
    y.d = 29;

    // So, let's go to 'date-02.cpp'
}
