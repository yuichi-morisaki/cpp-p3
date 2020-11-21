// convert from miles to kilometers

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a distance [miles] to convert to [km]: ";
    double d = 0;
    cin >> d;
    cout << d << " miles is " << d * 1.609 << " kilometers.\n";

    return 0;
}
