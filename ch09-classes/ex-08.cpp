#include "library.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main()
try {
    string name {"James"};
    string number {"1234567"};
    Patron p1 {name, number};

    cout << "Name: " << p1.get_name() << '\n'
         << "Number: " << p1.get_number() << '\n'
         << "Fee: " << p1.get_fee() << '\n';

    if (has_fee(p1))
        cout << p1.get_name() << " owe some fee\n";
    else
        cout << p1.get_name() << " doesn't owe any fee\n";

//    p1.set_fee(-234);   // exception
    p1.set_fee(2500);

    cout << "Name: " << p1.get_name() << '\n'
         << "Number: " << p1.get_number() << '\n'
         << "Fee: " << p1.get_fee() << '\n';

    if (has_fee(p1))
        cout << p1.get_name() << " owe some fee\n";
    else
        cout << p1.get_name() << " doesn't owe any fee\n";

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
