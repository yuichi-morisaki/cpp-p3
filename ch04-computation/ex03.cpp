#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> distances;
    for (double d; cin >> d; )
        distances.push_back(d);

    if (distances.size()) {
        double sum = 0;
        double min_d = distances[0];
        double max_d = distances[0];

        for (double d: distances) {
            sum += d;
            if (d < min_d) min_d = d;
            if (d > max_d) max_d = d;
        }
        cout << "The total distance is " << sum << '\n'
             << "The smallest distance is " << min_d << '\n'
             << "The greatest distance is " << max_d << '\n'
             << "The mean distance is " << sum / distances.size() << '\n';
    } else {
        cout << "There is no input of distance.\n";
    }

    return 0;
}
