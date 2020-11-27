#include <iostream>
#include <vector>

using namespace std;

class Name_value {
public:
    Name_value(string n, int v)
        : _name(n), _value(v) { }
    string name();
    int value();
private:
    string _name;
    int _value;
};

string Name_value::name() {
    return _name;
}

int Name_value::value() {
    return _value;
}

int main()
{
    vector<Name_value> table;
    string name;
    int value;

    while (cin >> name >> value) {
        if (name == "NoName" && value == 0)
            break;
        bool duplicated = false;
        for (Name_value person: table) {
            if (name == person.name()) {
                duplicated = true;
                break;
            }
        }
        if (duplicated)
            cout << "Duplicated name: " << name << '\n';
        else
            table.push_back(Name_value(name, value));
    }

    for (Name_value person: table)
        cout << "(" << person.name() << ", "
             << person.value() << ")\n";

    return 0;
}
