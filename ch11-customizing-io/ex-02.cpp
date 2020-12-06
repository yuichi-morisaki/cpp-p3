#include <fstream>
#include <iostream>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

int main()
{
    string ifname;
    cout << "Enter input file name: ";
    cin >> ifname;
    ifstream ifs {ifname};
    if (!ifs)
        error("can't open input file ", ifname);

    string word;
    cout << "Enter a word to be searched for: ";
    cin >> word;
    if (word.size() == 0)
        throw runtime_error("empty word!");

    for (string line; getline(ifs, line); ) {
        string::size_type n = line.find(word[0]);
        while (n != string::npos) {
            if (line.substr(n, word.size()) == word) {
                cout << line << '\n';
                break;
            }
            n = line.find(word[0], n + 1);
        }
    }
    if (ifs.eof())
        return 0;

    error("something wrong with input file ", ifname);
}
