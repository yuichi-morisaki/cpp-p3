#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

char* as_bytes(int i)
{
    void* addr = &i;
    return static_cast<char*>(addr);
}

int main()
{
    cout << "Please enter input file name\n";
    string iname;
    cin >> iname;
    ifstream ifs {iname, ios_base::binary};
    if (!ifs)
        error("can't open input file ", iname);

    cout << "Please enter output file name\n";
    string oname;
    cin >> oname;
    ofstream ofs {oname, ios_base::binary};
    if (!ofs)
        error("can't open output file ", oname);

    vector<int> v;

    for (int x; ifs.read(as_bytes(x), sizeof(int)); )
        v.push_back(x);

    // ... do something with v ...

    for (int x: v)
        ofs.write(as_bytes(x), sizeof(int));

    return 0;
}
