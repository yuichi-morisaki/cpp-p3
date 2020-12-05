#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    cout << 1234.56789 << "\t\t(defaultfloat)\n"
         << fixed << 1234.56789 << "\t(fixed)\n"
         << scientific << 1234.56789 << "\t(scientific)\n\n";

    cout << 1234.56789 << '\n';
    cout << defaultfloat << 1234.56789 << "\n\n";

    cout << defaultfloat << 1234567.89 << '\t'
         << fixed << 1234567.89 << '\t'
         << scientific << 1234567.89 << "\n\n";

    cout << defaultfloat << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
    cout << defaultfloat << setprecision(5) << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
    cout << defaultfloat << setprecision(8) << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << "\n\n";
}
