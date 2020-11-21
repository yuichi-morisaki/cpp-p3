// How much coins do you have?

#include <iostream>

using namespace std;

int main()
{
    cout << "How many pennies do you have? ";
    int penny = 0;
    cin >> penny;

    cout << "How many nickels do you have? ";
    int nickel = 0;
    cin >> nickel;

    cout << "How many dimes do you have? ";
    int dime = 0;
    cin >> dime;

    cout << "How many quarters do you have? ";
    int quarter = 0;
    cin >> quarter;

    cout << "How many half dollars do you have? ";
    int half_dollar = 0;
    cin >> half_dollar;

    cout << "How many one-dollar coins do you have? ";
    int one_dollar = 0;
    cin >> one_dollar;

    cout << "You have " << penny;
    if (penny == 1)
        cout << " penny.\n";
    else
        cout << " pennies.\n";

    cout << "You have " << nickel;
    if (nickel == 1)
        cout << " nickel.\n";
    else
        cout << " nickels.\n";

    cout << "You have " << dime;
    if (dime == 1)
        cout << " dime.\n";
    else
        cout << " dimes.\n";

    cout << "You have " << quarter;
    if (quarter == 1)
        cout << " quarter.\n";
    else
        cout << " quarters.\n";

    cout << "You have " << half_dollar;
    if (half_dollar == 1)
        cout << " half dollar.\n";
    else
        cout << " half dollars.\n";

    cout << "You have " << one_dollar;
    if (one_dollar == 1)
        cout << " one-dollar coin.\n";
    else
        cout << " one-dollar coins.\n";

    double total = (penny * 1 + nickel * 5 + dime * 10
        + quarter * 25 + half_dollar * 50 + one_dollar * 100) / 100.0;
    cout << "The value of all of your coins is $" << total << ".\n";

    return 0;
}
