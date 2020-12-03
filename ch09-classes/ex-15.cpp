#include "money.h"
#include <stdexcept>

using namespace std;


int main()
{
    try {
        Money {0, 'p'};
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
    }
    try {
        Money {1000000000000000000, 'd'};
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << '\n';
    }
    Money d1 {1.0, 'd'};
    Money y1 {100.0, 'y'};
    cout << "d1 == " << d1 << '\n';
    cout << "y1 == " << y1 << '\n';
    cout << "d1 == Y" << d1.yen() << '\n';
    cout << "y1 == $" << y1.dollar() << '.' << y1.cent() << '\n';

    Money d2 {2.5, 'd'};
    Money y2 {250.0, 'y'};
    cout << "d2 == " << d2 << '\n';
    cout << "y2 == " << y2 << '\n';

    cout << "d1 + d2 == " << d1 + d2 << '\n';
    cout << "y1 + y2 == " << y1 + y2 << '\n';
    cout << "d1 + y1 == " << d1 + y1 << '\n';
    cout << "d2 + y2 == " << d2 + y2 << '\n';

    Money m1 {0, 'd'};
    cout << "Enter like 'd2.5': ";
    cin >> m1;
    cout << "m1 == " << m1 << '\n';
    Money m2 {0, 'y'};
    cout << "Enter like 'y100': ";
    cin >> m2;
    cout << "m2 == " << m2 << '\n';

    return 0;
}
