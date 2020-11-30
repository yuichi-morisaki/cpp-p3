#include <iostream>
#include <vector>
using namespace std;

double maxv(const vector<double>& vec)
{
    if (vec.size() == 0)
        throw runtime_error("Empty vector");
    double m = vec[0];
    for (double v: vec) {
        if (v > m) {
            m = v;
        }
    }
    return m;
}

int main()
{
    vector<double> v0;
    vector<double> v1 = {1};
    vector<double> v2 = {1, 3, 2, 9, 4, 8, 7};

    cout << maxv(v2) << '\n';
    cout << maxv(v1) << '\n';
    cout << maxv(v0) << '\n';

    return 0;
}
