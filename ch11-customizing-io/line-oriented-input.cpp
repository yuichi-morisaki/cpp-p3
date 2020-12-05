#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

// default: word-oriented
void read_a_word(istream& is)
{
    string name;
    is >> name;
    cout << name << '\n';
}

// line-oriented version
void read_a_line(istream& is)
{
    string name;
    getline(is, name);
    cout << name << '\n';
}

int main()
{
    string s = "Dennis Ritchie";
    istringstream iss {s};
    read_a_word(iss);   // Dennis

    iss = istringstream {s};
    read_a_line(iss);   // Dennis Ritchie

    s = "go left until you see a picture on the wall to your right\n";
    s += "remove the picture and open the door behind it. take the bag from there";

    iss = istringstream {s};
    string command;
    getline(iss, command);

    stringstream ss {command};
    vector<string> words;
    for (string s1; ss >> s1; )
        words.push_back(s1);

    for (string s2: words)
        cout << s2 << '\n';
}
