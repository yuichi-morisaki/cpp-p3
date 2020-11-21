// determin an integer user input is odd or even

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter an integer: ";
    int n = 0;
    cin >> n;

    cout << "The value " << n << " is an ";
    if (n % 2 == 0)
        cout << "even ";
    else
        cout << "odd ";
    cout << "number.\n";

    return 0;
}
