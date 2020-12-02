#include "chrono.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Chrono;

int main()
{
    for (int i = MONTH_MIN - 1; i <= MONTH_MAX + 1; ++i) {
        try {
            Month m = Month_from_int(i);
            cout << i << ": " << m << '\n';
        }
        catch (exception& e) {
            cerr << "exception: " << e.what() << '\n';
        }
    }

    for (int m = MONTH_MIN - 1; m <= MONTH_MAX + 1; ++m) {
        try {
            int i = int_from_Month(Month(m));
            cout << Month(m) << ": " << i << '\n';
        }
        catch (exception& e) {
            cerr << "exception: " << e.what() << '\n';
        }
    }

    cout << "Month_from_int(1) ";
    if (Month_from_int(1) == Month::Jan)
        cout << "== ";
    else
        cout << "!= ";
    cout << "Month::Jan\n";

    cout << "Month_from_int(12) ";
    if (Month_from_int(12) != Month::Jan)
        cout << "!= ";
    else
        cout << "== ";
    cout << "Month::Jan\n";

    return 0;
}
