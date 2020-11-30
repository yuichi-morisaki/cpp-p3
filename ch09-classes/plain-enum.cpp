// #include <iostream>
using namespace std;

enum Month {    // cf: 'enum class Month {}'
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

/*
enum Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};
*/
enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

void do_something() {}
void do_something_else() {}
void my_code(Month m)
{
    if (m == 17) do_something();
    // error if 'enum class Day' is defined, but
    // warning if 'enum Day' is defined
    if (m == Day::monday) do_something_else();
}

int main()
{
    Month m = feb;  // OK
    Month m2 = Month::feb;  // also OK
//    m = 7;  // invalid conversion from int to Month
    int n = m;  // OK: we can assign a Month to an int
    Month mm = Month(7);    // OK, but unchecked

    // Given iostream,
//    Month m3 = dec; // error: reference to dec is ambiguous

    return 0;
}
