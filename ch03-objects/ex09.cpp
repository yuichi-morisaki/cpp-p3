// convert spelled-out numbers into digits (0, 1, 2, 3, and 4)

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a spelled-out number between zero and four: ";
    string number = "";
    cin >> number;

    if (number == "zero")
        cout << 0 << '\n';
    else if (number == "one")
        cout << 1 << '\n';
    else if (number == "two")
        cout << 2 << '\n';
    else if (number == "three")
        cout << 3 << '\n';
    else if (number == "four")
        cout << 4 << '\n';
    else
        cout << "not a number I know\n";

    return 0;
}
