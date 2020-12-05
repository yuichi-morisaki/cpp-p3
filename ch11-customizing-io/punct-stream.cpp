#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Punct_stream {
    public:
        Punct_stream(istream& is)
            : source {is}, sensitive {true} {}

        void whitespace(const string& s) { white = s; }
        void add_white(char c) { white += c; }
        bool is_whitespace(char c);
        void case_sensitive(bool b) { sensitive = b; }
        bool is_case_sensitive() { return sensitive; }

        Punct_stream& operator>>(string& s);
        operator bool();

    private:
        istream& source;
        istringstream buffer;
        string white;
        bool sensitive;
};

bool Punct_stream::is_whitespace(char c)
{
    for (char w: white)
        if (c == w) return true;
    return false;
}

Punct_stream& Punct_stream::operator>>(string& s)
{
    while (!(buffer >> s)) {
        if (buffer.bad() || !source.good())
            return *this;

        buffer.clear();
        string line;
        getline(source, line);

        for (char& c: line)
            if (is_whitespace(c))
                c = ' ';
            else if (!sensitive)
                c = tolower(c);

        buffer.str(line);   // put string into stream
    }
    return *this;
}


Punct_stream::operator bool()
{
    return !(source.fail() || source.bad())
        && buffer.good();
}



int main()
{
    string input_source;
    input_source =
        "There are only two kinds of languages: "
        "languages that peple complain about, "
        "and languages that people don't use.";
    istringstream iss {input_source};

    Punct_stream ps {iss};  // or 'cin' instead of 'iss'
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
    ps.case_sensitive(false);

    vector<string> vs;
    for (string word; ps >> word; )
        vs.push_back(word);

    sort(vs.begin(), vs.end());

    for (int i = 0; i < vs.size(); ++i)
        if (i == 0 || vs[i] != vs[i-1])
            cout << vs[i] << '\n';

    return 0;
}
