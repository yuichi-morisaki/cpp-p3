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
    void sort();
    int size() const;
    string name_at(int) const;
    double age_at(int) const;
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

int Name_pairs::size() const
{
    return name.size();
}

string Name_pairs::name_at(int n) const
{
    if (n < 0 || size() <= n)
        error("name_at(): out of range");
    return name[n];
}

double Name_pairs::age_at(int n) const
{
    if (n < 0 || size() <= n)
        error("age_at(): out of range");
    return age[n];
}

ostream& operator<<(ostream& os, const Name_pairs& np)
{
    for (int i = 0; i < np.size(); ++i)
        os << '(' << np.name_at(i)
           << ',' << np.age_at(i)
           << ")\n";
    return os;
}


int main()
try {
    Name_pairs np {};
    np.read_names();
    np.read_ages();
    cout << "\n-----\n";
    cout << np;
    np.sort();
    cout << "-----\n";
    cout << np;

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
