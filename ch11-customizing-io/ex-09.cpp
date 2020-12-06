/*
    Split the binary I/O program from section 11.3.2 into two:
    one program that converts an ordinary text file into binary
    and one program that reads binary and converts it to text.
    Test these programs by comparing a text file with what you
    get by converting it to binary and back.
*/

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

char* as_bytes(char& c)
{
    void* addr = &c;
    return static_cast<char*>(addr);
}


int main()
try {
    string bin_fname {"ex-09.bin"};

    // program 1. txt => bin
    {
        string txt_fname {"ex-09.cpp"};
        ifstream ifs {txt_fname};
        if (!ifs)
            error("can't open input file ", txt_fname);

        ofstream ofs {bin_fname, ios_base::binary};
        if (!ofs)
            error("can't open output file ", bin_fname);

        vector<char> v;

        for (char c; ifs.get(c); ) {
            v.push_back(c);
        }

        for (char c: v)
            ofs.write(as_bytes(c), sizeof(char));
    }

    // program 2. bin => txt;
    {
        ifstream ifs {bin_fname, ios_base::binary};
        if (!ifs)
            error("can't open input file ", bin_fname);

        string txt_fname {"ex-09-out.txt"};
        ofstream ofs {txt_fname};
        if (!ifs)
            error("can't open output file ", txt_fname);

        vector<char> v;

        for (char c; ifs.read(as_bytes(c), sizeof(char)); )
            v.push_back(c);

        for (char c: v)
            ofs.put(c);
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
