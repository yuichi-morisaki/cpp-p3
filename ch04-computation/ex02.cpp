#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> temps;
    for (double temp; cin >> temp; )
        temps.push_back(temp);

    double sum = 0;
    for (double x: temps) sum += x;
    cout << "Average temperature: " << sum / temps.size() << '\n';

    sort(temps.begin(), temps.end());
    int mid_index = temps.size() / 2;
    double median = (temps.size() % 2) ?
        temps[mid_index] : (temps[mid_index - 1] + temps[mid_index]) / 2;
    cout << "Median temperature: " << median << '\n';

    return 0;
}
