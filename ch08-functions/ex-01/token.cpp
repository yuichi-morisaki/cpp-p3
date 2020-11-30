#include "token.h"
#include "error.h"


Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char c;
    while (cin.get(c)) {
        if (isspace(c) && c != '\n') continue;
        switch (c) {
            case print:
            case '\n':
                return Token(print);
            case '(': case ')':
            case '+': case '-': case '*': case '/': case '%':
                return Token(c);
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                in_stream.putback(c);
                double val;
                in_stream >> val;
                return Token(number, val);
            }
            default:
                if (isalpha(c)) {
                    string s;
                    s += c;
                    while (cin.get(c) &&
                            (isalpha(c) || isdigit(c)))
                        s += c;
                    in_stream.putback(c);
                    if (s == key_quit)
                        return Token(quit);
                }
                error("Bad Token");
        }
    }
    return dummy_token;
}


void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into full buffer");

    full = true;
    buffer = t;
}


void Token_stream::ignore()
{
    if (full && buffer.kind == print) {
        full = false;
        return;
    }

    full = false;
    char c;
    while (cin.get(c)) {
        if (c == print || c == '\n')
            return;
    }
}
