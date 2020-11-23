#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "Please enter a sequence of string:\n";
    vector<string> words;
    for (string w; cin >> w; )
        words.push_back(w);

    sort(words.begin(), words.end());

    cout << "The min of the sequence is '"
         << words[0] << "'\n";
    cout << "The max of the sequence is '"
         << words[words.size() - 1] << "'\n";

    string mode = "";
    int max_count = 0;
    for (string current: words) {
        int cur_count = 0;
        for (string w: words) {
            if (w > current)
                break;
            if (w == current)
                ++cur_count;
        }
        if (cur_count > max_count) {
            mode = current;
            max_count = cur_count;
        }
    }
    cout << "The mode of the sequence is '"
         << mode << '\n';

    return 0;
}
