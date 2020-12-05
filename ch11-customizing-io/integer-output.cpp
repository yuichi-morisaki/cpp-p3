#include <iostream>
using namespace std;

int main()
{
    cout << 1234 << "\t(decimal)\n"
         << hex << 1234 << "\t(hexadecimal)\n"
         << oct << 1234 << "\t(octal)\n\n";

    cout << dec << 1234 << '\t'
         << hex << 1234 << '\t'
         << oct << 1234 << '\n';
    cout << 1234 << "\n\n";

    cout << dec << 1984 << '\t'
         << hex << 1984 << '\t'
         << oct << 1984 << '\n';
    cout << dec << 36 << '\t'
         << hex << 36 << '\t'
         << oct << 36 << "\n\n";

    cout << dec << 1234 << '\t'
         << hex << 1234 << '\t'
         << oct << 1234 << '\n';
    cout << showbase;
    cout << dec << 1234 << '\t'
         << hex << 1234 << '\t'
         << oct << 1234 << "\n\n";

    cout << noshowbase;
    cout << dec << 1234 << '\t'
         << hex << 1234 << '\t'
         << oct << 1234 << '\n';
    cout << dec;
    cout << 1234 << '\t'
         << 0x4d2 << '\t'
         << 02322 << "\n\n";
}
