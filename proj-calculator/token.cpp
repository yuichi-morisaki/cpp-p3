#include "token.h"
#include "error.h"
#include <sstream>


// ================================================================
//  Token

Token::Token(char kind)
    : kind {kind}, value {0}
{
}

Token::Token(double value)
    : kind {NUMBER}, value {value}
{
}

Token::Token(string name)
    : kind {NAME}, value {0}, name {name}
{
}

// ================================================================
//  Token_stream

Token get_token(istringstream&);


Token_stream::Token_stream(istream& is)
    : is {is}, buf {Token {EMPTY}}
{
}


Token Token_stream::get()
{
    if (full) {
        full = false;
        return buf;
    }

    while (que.empty()) {
        string line;
        if (getline(is, line)) {
            istringstream iss {line};
            while (true) {
                Token t = get_token(iss);
                if (t.kind == EMPTY)
                    break;
                que.push(t);
            }
        }
        else
            error("can't get any more token");
    }

    Token t = que.front();
    que.pop();
    return t;
}


void Token_stream::putback(Token t)
{
    if (full)
        error("putback to full buffer");

    buf = t;
    full = true;
}


void Token_stream::ignore(char t_kind)
{
    if (full && buf.kind == t_kind) {
        full = false;
        return;
    }

    full = false;
    while (!que.empty()) {
        Token t = que.front();
        que.pop();
        if (t.kind == t_kind)
            return;
    }
}

// ----------------------------------------------------------------

string parse_name(istringstream&);

Token name_to_token(const string&);


Token get_token(istringstream& iss)
{
    char c;
    if (iss >> c) {
        switch (c) {
            case PRINT:
            case '(': case ')': case ',':
            case '+': case '-': case '*': case '/': case '%':
            case '=':
                return Token {c};
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                iss.unget();
                {
                    double val;
                    iss >> val;
                    return Token {val};
                }
            default:
                iss.unget();
                {
                    string name = parse_name(iss);
                    Token t = name_to_token(name);
                    return t;
                }
        }
    }
    if (!iss.eof() && (iss.fail() || iss.bad()))
        error("failed to get token");
    return Token {EMPTY};
}


string parse_name(istringstream& iss)
{
    string name;
    char c;

    if (iss.get(c)) {
        if (isalpha(c) || c == '_')
            name += c;
        else
            error("unexpected character for name[0]: ", c);
    }
    else
        error("failed to get character for name[0]");

    while (iss.get(c)) {
        if (isalnum(c) || c == '_')
            name += c;
        else if (isspace(c))
            break;
        else
            error("unexpected character for name: ", c);
    }
    if (!iss.eof() && (iss.fail() || iss.bad()))
        error("failed to get character for name");

    return name;
}


Token name_to_token(const string& name)
{
    if (name == kw_quit)
        return Token {QUIT};
    if (name == kw_let)
        return Token {LET};
    if (name == kw_const)
        return Token {CONST};
    if (name == kw_set)
        return Token {SET};
    if (name == fn_sqrt)
        return Token {MATH_SQRT};
    if (name == fn_pow)
        return Token {MATH_POW};

    return Token {name};
}

// ================================================================
