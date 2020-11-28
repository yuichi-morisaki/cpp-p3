#include <iostream>
#include <stdexcept>

using namespace std;

constexpr char QUIT = 'q';
constexpr char PRINT = ';';
constexpr char INT = '8';
constexpr char DUMMY = ' ';

void error(string msg) {
    throw runtime_error(msg);
}

double expression();

class Token {
public:
    char kind;
    double value;
    Token(char c)
        : kind(c), value(0) { }
    Token(char c, double v)
        : kind(c), value(v) { }
};

class Token_stream {
public:
    void putback(Token t);
    Token get();
    Token_stream()
        : full(false), buffer(Token {DUMMY}) { }
private:
    bool full;
    Token buffer;
};

Token_stream ts;

int main()
try {
    while (cin) {
        cout << "> ";
        Token t = ts.get();
        while (t.kind == PRINT)
            t = ts.get();
        if (t.kind == QUIT)
            break;
        ts.putback(t);
        cout << "=" << expression() << '\n';
    }

    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}


double primary() {
    double val;
    Token t = ts.get();
    switch (t.kind) {
        case '(':
            val = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            break;
        case INT:
            val = t.value;
            break;
        default:
            error("primary expected");
    }
    return val;
}

double term() {
    double val = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                val *= primary();
                t = ts.get();
                break;
            case '/':
                {
                    double d = primary();
                    if (d == 0)
                        error("divide by zero");
                    val /= d;
                }
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return val;
        }
    }
}

double expression() {
    double val = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '+':
                val += term();
                t = ts.get();
                break;
            case '-':
                val -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return val;
        }
    }
}


void Token_stream::putback(Token t) {
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    Token t = Token {DUMMY};
    char c;
    cin >> c;
    switch (c) {
        case QUIT:
        case PRINT:
        case '(': case ')':
        case '+': case '-': case '*': case '/':
            t = Token {c};
            break;
        case '.':
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
            cin.putback(c);
            {
                double val;
                cin >> val;
                t = Token {INT, val};
            }
            break;
        default:
            error("Bad token");
    }
    return t;
}
