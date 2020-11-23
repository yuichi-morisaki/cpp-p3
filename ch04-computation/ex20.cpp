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

    cout << "Whose score do you need? ";
    string target;
    cin >> target;
    bool found = false;
    for (int i = 0; i < names.size(); ++i) {
        if (names[i] == target) {
            cout << scores[i] << '\n';
            found = true;
            break;
        }
    }
    if (!found)
        cout << "name not found\n";

    return 0;
}
