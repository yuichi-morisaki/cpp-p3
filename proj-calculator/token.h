#include <iostream>
#include <queue>

using namespace std;


const string kw_quit {"quit"};
const string kw_let {"let"};
const string kw_const {"const"};
const string kw_set {"set"};

const string fn_sqrt {"sqrt"};
const string fn_pow {"pow"};

constexpr char PRINT {';'};

constexpr char QUIT {'Q'};
constexpr char LET {'L'};
constexpr char CONST {'C'};
constexpr char SET {'S'};
constexpr char NAME {'A'};
constexpr char NUMBER {'8'};
constexpr char EMPTY {' '};
constexpr char MATH_SQRT {'s'};
constexpr char MATH_POW {'p'};


struct Token {
    Token(char kind);
    Token(double value);
    Token(string name);

    char kind;
    double value;
    string name;
};


class Token_stream {
    public:
        Token_stream(istream& is);

        bool is_empty();
        Token get();
        void putback(Token t);
        void ignore(char t_kind);

    private:
        istream& is;
        queue<Token> que;
        bool full {false};
        Token buf;
};
