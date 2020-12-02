#include "chrono.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;

int main()
{
    for (int i = DAY_MIN - 1; i <= DAY_MAX + 1; ++i) {
        try {
            Day d = Day_from_int(i);
            cout << i << ": " << d << '\n';
        }
        catch (exception& e) {
            cerr << "exception: " << e.what() << '\n';
        }
    }

    for (int d = DAY_MIN - 1; d <= DAY_MAX + 1; ++d) {
        try {
            int i = int_from_Day(Day(d));
            cout << Day(d) << ": " << i << '\n';
        }
        catch (exception& e) {
            cerr << "exception: " << e.what() << '\n';
        }
    }

    cout << "Day_from_int(0) ";
    if (Day_from_int(0) == Day::Sun)
        cout << "== ";
    else
        cout << "!= ";
    cout << "Day::Sun\n";

    cout << "Day_from_int(0) ";
    if (Day_from_int(0) != Day::Mon)
        cout << "!= ";
    else
        cout << "== ";
    cout << "Day::Mon\n";

    return 0;
}
