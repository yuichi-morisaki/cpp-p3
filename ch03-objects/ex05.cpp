// Some operations on two floating-point values

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter two numbers separated by space: ";
    double val1 = 0.0;
    double val2 = 0.0;
    cin >> val1 >> val2;

    if (val1 == val2) {
        cout << "That's the same value twice.\n";
    } else {
        if (val1 < val2)
            cout << "The smaller is " << val1
                 << " and the larger is " << val2 << '\n';
        else
            cout << "The smaller is " << val2
                 << " and the larger is " << val1 << '\n';
    }

    cout << val1 << " + " << val2 << " = " << val1 + val2 << '\n';
    cout << val1 << " - " << val2 << " = " << val1 - val2 << '\n';
    cout << val1 << " * " << val2 << " = " << val1 * val2 << '\n';
    cout << val1 << " / " << val2 << " = " << val1 / val2 << '\n';

    return 0;
}
