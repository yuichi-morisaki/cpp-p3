#include <iostream>
using namespace std;

int main()
{
    char c;
    cin >> c;
    cout << "c is " << c << '\n';
    cin.unget();
    char d;
    cin >> d;
    cout << "d is " << d << '\n';
}
