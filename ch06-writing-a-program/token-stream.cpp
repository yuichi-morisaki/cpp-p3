#include <utilities.h>
#include <token-stream.h>
#include <iostream>

using namespace std;

Token::Token() { }

Token::Token(char c)
    : kind(c), value(0) { }

Token::Token(char c, double v)
    : kind(c), value(v) { }

Token_stream::Token_stream() { }

Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    Token t;
    char c;
    cin >> c;
    switch (c) {
        case ';':
        case 'q':
        case '(': case ')':
        case '+': case '-': case '*': case '/':
            t = Token {c};
            break;
        case '.':
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
            {
                cin.putback(c);
                double val;
                cin >> val;
                t = Token {'8', val};
                break;
            }
        default:
            error("Bad token");
    }
    return t;
}

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}
