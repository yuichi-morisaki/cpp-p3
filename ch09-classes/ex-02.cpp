#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}


class Name_pairs {
public:
    Name_pairs();
    void read_names();
    void read_ages();
    void print();
    void sort();
private:
    vector<string> name;
    vector<double> age;
};

Name_pairs::Name_pairs()
    : name {}, age {}
{
}

void Name_pairs::read_names()
    // reads a series of names
{
    cout << "Enter a series of names:\n"
         << "(separated by white space and "
         << "ended by 'NoName')\n";
    string s;
    while (cin >> s) {
        if (s == "NoName")
            break;
        name.push_back(s);
    }
    return;
}

void Name_pairs::read_ages()
    // prompts the user for an age for each name
{
    cout << "Enter an age for the name printed\n";
    for (string s: name) {
        cout << s << ": ";
        double a;
        cin >> a;
        if (!cin)
            error("Failed to read an age");
        age.push_back(a);
    }
    return;
}

void Name_pairs::print()
    // prints out the (name[i], age[i]) pairs,
    // one per line in the order determined by the name vector
{
    for (int i = 0; i < name.size(); ++i) {
        cout << '(' << name[i]
             << ',' << age[i]
             << ")\n";
    }
    return;
}

void Name_pairs::sort()
    // sorts the name vector in alphabetical order
    // and reorganizes the age vector to match
{
    vector<double> cp_age;
    vector<string> cp_name;
    for (string s: name)
        cp_name.push_back(s);
    std::sort(name.begin(), name.end());
    for (string s: name) {
        for (int i = 0; i < cp_name.size(); i++) {
            if (s == cp_name[i]) {
                cp_age.push_back(age[i]);
                break;
            }
        }
    }
    age = cp_age;
    return;
}


int main()
try {
    Name_pairs np {};
    np.read_names();
    np.read_ages();
    cout << "\n-----\n";
    np.print();
    np.sort();
    cout << "-----\n";
    np.print();

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
