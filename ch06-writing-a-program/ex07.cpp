/*  Bitwise logical expression
 *
 *      Expression:
 *          Sum
 *          Sum "|" Expression
 *      Sum:
 *          Product
 *          Product "^" Sum
 *      Product:
 *          Unary
 *          Unary "&" Product
 *      Unary:
 *          Primary
 *          "!" Primary
 *          "~" Primary
 *      Primary:
 *          Integer
 *          "(" Expression ")"
 */

#include <iostream>
#include <stdexcept>

using namespace std;


void error(string message);
int expression();

constexpr char INT = '8';
constexpr char QUIT = 'q';
constexpr char PRINT = ';';

class Token {
public:
    char kind;
    int value;
    Token(char k)
        : kind(k), value(0) { }
    Token(char k, int v)
        : kind(k), value(v) { }
};

class Token_stream {
public:
    Token_stream()
        : full(false), buffer(Token(QUIT)) { }
    void putback(Token t);
    Token get();
private:
    bool full;
    Token buffer;
};

Token_stream ts;

int main()
try {
    cout << "Enter an expression followed by ';'\n"
         << "To quit, enter 'q'\n";
    cout << ">> ";
    int result = 0;
    while (true) {
        Token t = ts.get();
        if (t.kind == QUIT)
            break;
        if (t.kind == PRINT)
            cout << result << "\n>> ";
        else {
            ts.putback(t);
            result = expression();
        }
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


int primary() {
    Token t = ts.get();
    if (t.kind == INT)
        return t.value;

    if (t.kind != '(')
        error("primary expected");
    int value = expression();
    t = ts.get();
    if (t.kind != ')')
        error("')' expected");
    return value;
}

int unary() {
    Token t = ts.get();
    int result;
    switch (t.kind) {
        case '!':
            result = primary();
            result = int(result == 0);
            break;
        case '~':
            result = primary();
            result = ~result;
            break;
        default:
            ts.putback(t);
            result = primary();
            break;
    }
    return result;
}

int product() {
    int result = unary();
    Token t = ts.get();
    if (t.kind == '&')
        result &= product();
    else
        ts.putback(t);
    return result;
}

int sum() {
    int result = product();
    Token t = ts.get();
    if (t.kind == '^')
        result ^= sum();
    else
        ts.putback(t);
    return result;
}

int expression() {
    int result = sum();
    Token t = ts.get();
    if (t.kind == '|')
        result |= expression();
    else
        ts.putback(t);
    return result;
}

void error(string message) {
    throw runtime_error(message);
}

void Token_stream::putback(Token t) {
    if (full)
        error("putback to full buffer");
    full = true;
    buffer = t;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    Token token = Token(QUIT);
    char c;
    cin >> c;
    switch (c) {
        case QUIT:
        case PRINT:
        case '!': case '~':
        case '&': case '^': case '|':
            token = Token(c);
            break;
        case '+': case '-':
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
            cin.putback(c);
            {
                int value;
                cin >> value;
                token = Token(INT, value);
            }
            break;
        default:
            error("Bad input");
    }
    return token;
}
