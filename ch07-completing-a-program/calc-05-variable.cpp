/*
 *  Simple calculator
 *
 *  This program implements a basic expression calculator.
 *  Input from cin; output to cout.
 *  The grammar for input is:
 *
 *      Calculation:
 *          Statement
 *          Print
 *          Quit
 *          Calculation Statement
 *      Statement:
 *          Declaration
 *          Assignment
 *          Expression
 *      Declaration:
 *          "let" Name "=" Expression
 *      Assignment:
 *          TODO
 *      Name:
 *          TODO
 *      Expression:
 *          Term
 *          Expression + Term
 *          Expression - Term
 *      Term:
 *          Primary
 *          Term * Primary
 *          Term / Primary
 *          Term % Primary
 *      Primary
 *          Number
 *          ( Expression )
 *          - Primary
 *          + Primary
 *      Number:
 *          floating-point-literal
 *
 *  Input comes from cin through the Token_stream called ts.
 */
 
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

constexpr char QUIT = 'q';
constexpr char PRINT = ';';
constexpr char NUMBER = '8';
constexpr char DUMMY = ' ';
const string PROMPT = "> ";
const string RESULT = "=";

constexpr char NAME = 'a';
constexpr char LET = 'L';
const string DECL_KEY = "let";

void calculate();
double expression();
double define_name(string n, double v);

void error(string msg) {
    throw runtime_error(msg);
}

void error(string s1, string s2) {
    throw runtime_error(s1 + s2);
}

class Variable {
public:
    string name;
    double value;
    Variable(string n, double v)
        : name(n), value(v) { }
};

class Token {
public:
    char kind;
    double value;
    string name;
    Token(char c)
        : kind(c), value(0) { }
    Token(char c, double v)
        : kind(c), value(v) { }
    Token(char c, string n)
        : kind {c}, name {n} { }
};

class Token_stream {
public:
    void putback(Token t);
    Token get();
    void ignore(char c);
    Token_stream()
        : full(false), buffer(Token {DUMMY}) { }
private:
    bool full;
    Token buffer;
};

vector<Variable> var_table;
Token_stream ts;

int main()
try {
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    calculate();

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


double get_value(string s) {
    for (const Variable& v: var_table) {
        if (v.name == s)
            return v.value;
    }
    error("get: undefined variable ", s);
    return 0;   // Never reach here: for muting compiler warning
}

void set_value(string s, double d) {
    for (Variable& v: var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}

void clean_up_mess() {
    ts.ignore(PRINT);
}

bool is_declared(string var) {
    for (const Variable& v: var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val) {
    if (is_declared(var))
        error(var, " declared twice");
    var_table.push_back(Variable {var, val});
    return val;
}

double declaration() {
    Token t = ts.get();
    if (t.kind != NAME)
        error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("'=' missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement() {
    Token t = ts.get();
    switch (t.kind) {
        case LET:
            return declaration();
        default:
            ts.putback(t);
            return expression();
    }
}

void calculate() {
    while (cin) {
        try {
            cout << PROMPT;
            Token t = ts.get();
            while (t.kind == PRINT)
                t = ts.get();
            if (t.kind == QUIT)
                break;
            ts.putback(t);
            cout << RESULT << statement() << '\n';
        }
        catch (exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
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
        case NUMBER:
            val = t.value;
            break;
        case '-':
            val = primary();
            val *= -1;
            break;
        case '+':
            val = primary();
            break;
        case NAME:
            val = get_value(t.name);
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
            case '%':
                {
                    double d = primary();
                    if (d == 0)
                        error("%: idvide by zero");
                    val = fmod(val, d);
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
        case '%':
        case '=':
            t = Token {c};
            break;
        case '.':
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
            cin.putback(c);
            {
                double val;
                cin >> val;
                t = Token {NUMBER, val};
            }
            break;
        default:
            if (isalpha(c)) {
                string s;
                s += c;
                while (cin.get(c) &&
                        (isalpha(c) || isdigit(c)))
                    s += c;
                cin.putback(c);
                if (s == DECL_KEY)
                    t = Token {LET};
                else
                    t = Token {NAME, s};
            } else {
                error("Bad token");
            }
            break;
    }
    return t;
}

void Token_stream::ignore(char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }

    full = false;
    char ch;
    while (cin >> ch)
        if (ch == c)
            return;
}
