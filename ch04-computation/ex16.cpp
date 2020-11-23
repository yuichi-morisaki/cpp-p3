#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "Please enter a set of positive integers:\n";
    vector<int> integers;
    for (int i; cin >> i; )
        integers.push_back(i);

    sort(integers.begin(), integers.end());

    int mode = -1;
    int max_count = 0;
    for (int current: integers) {
        int cur_count = 0;
        for (int i: integers) {
            if (i > current)
                break;
            if (i == current)
                ++cur_count;
        }
        if (cur_count > max_count) {
            mode = current;
            max_count = cur_count;
        }
    }

    cout << "The mode of the sequence given is "
         << mode << '\n';

    return 0;
}
