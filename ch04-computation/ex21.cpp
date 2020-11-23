#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> names;
    vector<int> scores;

    string name;
    int score;
    while (cin >> name >> score) {
        if (name == "NoName" && score == 0)
            break;
        bool duplicated = false;
        for (string registered: names) {
            if (name == registered) {
                duplicated = true;
            }
        }
        if (duplicated) {
            cout << "Duplicated name: " << name << '\n';
            break;
        } else {
            names.push_back(name);
            scores.push_back(score);
        }
    }

    cout << "Please enter a score: ";
    int key_score;
    cin >> key_score;
    bool found = false;
    for (int i = 0; i < names.size(); ++i) {
        if (scores[i] == key_score) {
            cout << names[i] << '\n';
            found = true;
        }
    }
    if (!found)
        cout << "score not found\n";

    return 0;
}
