#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> disliked = {
        "Broccoli",
        "Eggplant",
    };

    for (string temp; cin >> temp; ) {
        bool found = false;
        for (string word: disliked)
            if (temp == word)
                found = true;
        if (found)
            cout << "BLEEP!\n";
        else
            cout << temp << '\n';
    }

    return 0;
}
