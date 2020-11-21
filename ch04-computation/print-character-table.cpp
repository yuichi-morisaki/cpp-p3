#include <iostream>

using namespace std;

int main()
{
    char c = 'a';
    while (c <= 'z') {
        cout << c << '\t' << int(c) << '\n';
        c = char(c + 1);
    }

    for (char u = 'A'; u <= 'Z'; u = char(u + 1)) {
        cout << u << '\t' << int(u) << '\n';
    }

    for (char d = '0'; d <= '9'; d = char(d + 1)) {
        cout << d << '\t' << int(d) << '\n';
    }

    return 0;
}
