// convert from yen, kroner, and pounds to dollars

#include <iostream>

using namespace std;

int main()
{
    constexpr double dollars_per_yen = 0.0096;
    constexpr double dollars_per_kroner = 0.11;
    constexpr double dollars_per_pound = 1.33;

    double amount = 1;
    char unit = ' ';
    cout << "How much money do you have? (followed by a unit: y, k, or p)\n";
    cin >> amount >> unit;

    if (unit == 'y')
        cout << amount << "yen == $" << dollars_per_yen * amount << "\n";
    else if (unit == 'k')
        cout << amount << "kroner == $" << dollars_per_kroner * amount << "\n";
    else if (unit == 'p')
        cout << amount << "pounds == $" << dollars_per_pound * amount << "\n";
    else
        cout << "Sorry, I don't know a unit called '" << unit << "'\n";

    return 0;
}
