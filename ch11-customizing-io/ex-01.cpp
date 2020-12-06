#include <fstream>
#include <locale>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

int main()
{
    string ifname {"ex-01.cpp"};
    ifstream ifs {ifname};
    if (!ifs)
        error("can't open input file ", ifname);

    string ofname {"ex-01-out.txt"};
    ofstream ofs {ofname};
    if (!ofs)
        error("can't open output file ", ofname);

    for (string line; getline(ifs, line); ) {
        for (char& c: line)
            c = toupper(c);
        ofs << line << '\n';
        if (!ofs.good())
            error("something wrong with output file ", ofname);
    }

    if (ifs.eof())
        return 0;

    error("something wrong with input file ", ifname);
}
