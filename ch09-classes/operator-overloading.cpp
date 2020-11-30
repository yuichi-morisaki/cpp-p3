#include <iostream>
#include <vector>
using namespace std;

enum class Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

Month operator++(Month& m)
{
    m = (m == Month::Dec) ?
        Month::Jan : Month(int(m) + 1);
    return m;
}

vector<string> month_tbl = {
    "",
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[int(m)];
}

int main()
{
    Month m = Month::Sep;
    ++m;
    cout << m << ' ';
    ++m;
    cout << m << ' ';
    ++m;
    cout << m << ' ';
    ++m;
    cout << m << '\n';
}
