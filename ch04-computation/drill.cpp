#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
/* drill 1~5
    double a = 0;
    double b = 0;
    while (cin >> a >> b) {
        if (a < b) {
            cout << "the smaller value is: " << a << '\n'
                 << "the larger value is: " << b << '\n';
            if (b - a < 1.0 / 100)
                cout << "the numbers are almost equal.\n";
        } else if (b < a) {
            cout << "the smaller value is: " << b << '\n'
                 << "the larger value is: " << a << '\n';
            if (a - b < 1.0 / 100)
                cout << "the numbers are almost equal.\n";
        } else {    // a == b
            cout << "the numbers are equal.\n";
        }
    }
*/
/* drill 6
    while (cin >> x) {
        cout << x;
        if (cnt == 0) {
            min_x = x;
            max_x = x;
            cout << ", the first input.";
        } else {
            if (x < min_x) {
                cout << ", the smallest so far.";
                min_x = x;
            }
            if (x > max_x) {
                cout << ", the largest so far.";
                max_x = x;
            }
        }
        cout << '\n';
        ++cnt;
    }
*/

    constexpr double cm_per_m = 100;
    constexpr double cm_per_in = 2.54;
    constexpr double cm_per_ft = 12 * 2.54;

    int cnt = 0;
    double len = 0;
    string unit = "";

    double len_max = 0;
    double len_min = 0;
    double len_sum = 0;

    vector<double> values;

    while (cin >> len >> unit) {
        bool valid = true;
        if (unit == "cm")
            ;
        else if (unit == "m")
            len *= cm_per_m;
        else if (unit == "in")
            len *= cm_per_in;
        else if (unit == "ft")
            len *= cm_per_ft;
        else
            valid = false;

        if (valid) {
            values.push_back(len);
            len_sum += len;
            if (cnt == 0) {
                len_max = len;
                len_min = len;
            } else {
                if (len > len_max) len_max = len;
                if (len < len_min) len_min = len;
            }
            ++cnt;
        } else {
            cout << "Invalid unit: '" << unit << "'\n";
        }
    }

    cout << "the number of values entered: " << cnt << '\n'
         << "the smallest length is " << len_min / 100.0 << "m\n"
         << "the largest length is " << len_max / 100.0 << "m\n"
         << "the sum of all values is " << len_sum / 100.0 << "m\n";

    sort(values.begin(), values.end());

    for (double v: values) cout << v << " ";
    cout << '\n';

    return 0;
}
