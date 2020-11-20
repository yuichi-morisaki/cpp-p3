#include <iostream>

using namespace std;

int main()
{
    cout << "Please enter your first name and age:\n";
    string first_name = "???";
    double age = 0;
    cin >> first_name;
    cin >> age;
    cout << "Hello, " << first_name << " (age " << age * 12 << "months)\n";

    return 0;
}
