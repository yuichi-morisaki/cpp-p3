// convert from yen, kroner, pounds, and yuan to dollars

#include <iostream>

using namespace std;

int main()
{
    constexpr double dollars_per_yen = 0.0096;
    constexpr double dollars_per_kroner = 0.11;
    constexpr double dollars_per_pound = 1.33;
    constexpr double dollars_per_yuan = 0.15;

    double amount = 1;
    char unit = ' ';
    cout << "How much money do you have? (followed by a unit: y, k, p, or u)\n";
    cin >> amount >> unit;

    switch (unit) {
        case 'y':
            cout << amount << "yen == $" << dollars_per_yen * amount << "\n";
            break;
        case 'k':
            cout << amount << "kroner == $" << dollars_per_kroner * amount << "\n";
            break;
        case 'p':
            cout << amount << "pounds == $" << dollars_per_pound * amount << "\n";
            break;
        case 'u':
            cout << amount << "yuan == $" << dollars_per_yuan * amount << "\n";
            break;
        default:
            cout << "Sorry, I don't know a unit called '" << unit << "'\n";
            break;
    }

    return 0;
}
