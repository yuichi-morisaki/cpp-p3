
class Date {
public:
    Date(int year, int month, int day);
    int day() const;    // can't modify the object
    void add_day(int n);
private:
    int y;
    int m;
    int d;
};

Date::Date(int year, int month, int day)
    : y {year}, m {month}, d {day}
{
}

int Date::day() const
{
    return d;
}

void Date::add_day(int n)
{
    d += n;
}


void some_function(
    Date& d,
    const Date& start_of_term)
{
    int a = d.day();
    int b = start_of_term.day();
    d.add_day(3);
//    start_of_term.add_day(3);   // error
}


int main()
{
    Date d {2000, 1, 1};
    some_function(d, d);
}
