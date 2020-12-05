#include <iostream>
using namespace std;

int main()
{
    int birth_year;
    birth_year = 1984;

    cout << showbase;
    cout << dec << birth_year << "\t(decimal)\n"
         << hex << birth_year << "\t(hexadecimal)\n"
         << oct << birth_year << "\t(octal)\n";

    int current_year = 2020;
    int age = current_year - birth_year;

    cout << dec << age << '\n';

    cout << "Enter an integer in decimal: ";
    int nd;
    cin >> dec >> nd;
    cout << "Enter an integer in hexadecimal: ";
    int nh;
    cin >> hex >> nh;
    cout << "Enter an integer in octal: ";
    int no;
    cin >> oct >> no;

    cout << showbase;
    cout << dec
         << nd << '\t' << nh << '\t' << no << '\n'
         << hex
         << nd << '\t' << nh << '\t' << no << '\n'
         << oct
         << nd << '\t' << nh << '\t' << no << '\n';

    double d = 1234567.89;
    cout << defaultfloat << d << '\n'
         << fixed << d << '\n'
         << scientific << d << '\n';

    /*
     *  See field.cpp for drill #10.
     */

    return 0;
}
