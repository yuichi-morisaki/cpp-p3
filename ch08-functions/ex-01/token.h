#include <iostream>
using namespace std;


class Token {
    public:
        char kind;
        double value;
        Token(char c)
            : kind {c}, value {0} { }
        Token(char c, double v)
            : kind {c}, value {v} { }
};

const Token dummy_token {' ', 0};

const string key_quit = "quit";
constexpr char print = ';';

constexpr char quit = 'Q';
constexpr char number = '8';


class Token_stream {
    public:
        Token_stream(istream& is)
            : in_stream {is},
              full {false},
              buffer {dummy_token}
            { }
        Token get();
        void putback(Token);
        void ignore();
    private:
        istream& in_stream;
        bool full;
        Token buffer;
};
