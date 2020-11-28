
/*
    calculator08buggy.cpp
*/

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string s) { throw runtime_error(s); }
void error(string s1, string s2) { throw runtime_error(s1 + s2); }

// ----------------------------------------------------------------------------

struct Token {
    char kind;
    double value;
    string name;
    Token(char ch) :kind(ch), value(0) { }
    Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch, string n) :kind(ch), name(n) { }
};

class Token_stream {
    bool full;
    Token buffer;
public:
    Token_stream() :full(0), buffer(0) { }

    Token get();
    void unget(Token t) { buffer = t; full = true; }

    void ignore(char);
};

const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char root = 'r';
const char expt = 'p';

Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    if (cin.get(ch) && ch == '\n')
        return Token(print);
    else
        cin.unget();
    cin >> ch;
    switch (ch) {
        case '(': case ')': case ',':
        case '+': case '-': case '*': case '/': case '%':
        case print:
        case '=':
        case '#':   // let
            return Token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                cin.unget();
                double val;
                cin >> val;
                return Token(number, val);
            }
        default:
            if (isalpha(ch)) {
                string s;
                s += ch;
                while (cin.get(ch)
                        && (isalpha(ch) || isdigit(ch)))
                    s += ch;
                cin.unget();
                if (s == "quit")
                    return Token(quit);
                if (s == "sqrt")
                    return Token(root);
                if (s == "pow")
                    return Token(expt);
                return Token(name, s);
            }
            error("Bad token");
            return Token(0);    // for muting compile warning
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin.get(ch))
        if (ch == c || ch == '\n')
            return;
}

// ----------------------------------------------------------------------------

struct Variable {
    string name;
    double value;
    Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return names[i].value;
    error("get: undefined name ", s);
    return 0;   // for muting compile warning
}

void set_value(string s, double d)
{
    for (int i = 0; i <= names.size(); ++i) // TODO
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool is_declared(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return true;
    return false;
}

// ----------------------------------------------------------------------------

Token_stream ts;

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return d;
        }
        case '-':
            return -primary();
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        case root:
        {
            t = ts.get();
            if (t.kind != '(')
                error("'(' expected");
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            if (d < 0)
                error("sqrt of negative");
            return sqrt(d);
        }
        case expt:
        {
            t = ts.get();
            if (t.kind != '(')
                error("'(' expected");
            double base = expression();
            t = ts.get();
            if (t.kind != ',')
                error("',' expected");
            double dexp = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            int iexp = int(dexp);
            if (iexp != dexp)
                error("2nd arg of pow() must be int");
            return pow(base, iexp);
        }
        default:
            error("primary expected");
            return 0;   // for muting compile warning
    }
}

double term()
{
    double left = primary();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0)
                    error("divide by zero");
                left /= d;
                break;
            }
            case '%':
            {
                double d = primary();
                if (d == 0)
                    error("modulo: divide by zero");
                left = fmod(left, d);
                break;
            }
            default:
                ts.unget(t);
                return left;
        }
    }
}

double expression()
{
    double left = term();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.unget(t);
                return left;
        }
    }
}

// ----------------------------------------------------------------------------

double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string name = t.name;
    if (is_declared(name))
        error(name, " declared twice");

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of ", name);

    double d = expression();

    names.push_back(Variable(name, d));
    return d;
}

// ----------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    default:
        ts.unget(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

// ----------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

void calculate()
{
    while (true) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.unget(t);
            double d = statement();
            cout << result << d << endl;
        }
        catch (runtime_error& e) {
            cerr << "E: " << e.what() << endl;
            clean_up_mess();
        }
    }
}

// ----------------------------------------------------------------------------

double define_variable(string name, double value)
{
    if (is_declared(name))
        error(name, " already declared");
    names.push_back(Variable(name, value));
    return value;
}

// ----------------------------------------------------------------------------

int main()

try {
    define_variable("k", 1000);

    calculate();

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >> c && c != ';')
        ;
    return 1;
}
catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';')
        ;
    return 2;
}

// ----------------------------------------------------------------------------
