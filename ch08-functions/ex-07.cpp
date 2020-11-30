#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<string>
copy_name(const vector<string>& name)
{
    vector<string> res;
    for (string n: name)
        res.push_back(n);
    return res;
}

int main()
{
    vector<string> name;
    while (name.size() < 5) {
        cout << "Enter a name: ";
        string n;
        cin >> n;
        name.push_back(n);
    }

    vector<double> age;
    for (string n: name) {
        cout << "How old is " << n << "? ";
        double a;
        cin >> a;
        age.push_back(a);
    }

    for (int i = 0; i < name.size(); ++i) {
        cout << "(" << name[i] << ", " << age[i] << ")\n";
    }

    vector<string> orig = copy_name(name);
    sort(name.begin(), name.end());

    for (int i = 0; i < name.size(); ++ i) {
        cout << "(" << name[i] << ", ";
        for (int j = 0; j < orig.size(); ++j) {
            if (name[i] != orig[j])
                continue;
            cout << age[j] << ")\n";
            break;
        }
    }

    return 0;
}
