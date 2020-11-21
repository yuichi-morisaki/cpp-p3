// Sort and output three integer values user input

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter three integers separated by space: ";
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    cin >> val1 >> val2 >> val3;

    if (val1 <= val2 && val1 <= val3) {
        cout << val1 << ", ";
        if (val2 <= val3)
            cout << val2 << ", " << val3 << '\n';
        else
            cout << val3 << ", " << val2 << '\n';
    } else if (val2 <= val3 && val2 <= val1) {
        cout << val2 << ", ";
        if (val3 <= val1)
            cout << val3 << ", " << val1 << '\n';
        else
            cout << val1 << ", " << val3 << '\n';
    } else {    // val3 <= val1 && val3 <= val2
        cout << val3 << ", ";
        if (val1 <= val2)
            cout << val1 << ", " << val2 << '\n';
        else
            cout << val2 << ", " << val1 << '\n';
    }

    return 0;
}
