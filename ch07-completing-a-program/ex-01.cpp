#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// ----------------------------------------------------------------------------

void error(string s)
{
    throw runtime_error(s);
}


void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}

// ----------------------------------------------------------------------------

struct Token
{
    public:
        char kind;
        double value;
        string name;

        Token(char c)
            : kind {c}, value {0} { }
        Token(char c, double v)
            : kind {c}, value {v} { }
        Token(char c, string n)
            : kind {c}, name {n} { }
};


const Token dummy_token = Token(0);

// ----------------------------------------------------------------------------

class Token_stream
{
    public:
        Token_stream()
            : full {false}, buffer {dummy_token} { }

        Token get();
        void putback(Token);
        void ignore();

    private:
        bool full;
        Token buffer;
};


Token_stream ts;

// ----------------------------------------------------------------------------

const string key_quit = "quit";
constexpr char print = ';';
constexpr char let = '#';

constexpr char quit = 'Q';
constexpr char number = '8';
constexpr char name = 'a';

constexpr char math_sqrt = 'r';
constexpr char math_pow = 'p';


Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char c;
    while (cin.get(c))
    {
        if (isspace(c) && c != '\n')
            continue;

        switch (c)
        {
            case print:
            case '\n':
                return Token(print);
            case let:
                return Token(let);
            case '(': case ')':
            case ',':
            case '+': case '-': case '*': case '/': case '%':
            case '=':
                return Token(c);
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                cin.putback(c);
                double val;
                cin >> val;
                return Token(number, val);
            }
            default:
                if (isalpha(c) || c == '_')
                {
                    string s;
                    s += c;
                    while (cin.get(c)
                            && (isalpha(c) || isdigit(c) || c == '_'))
                        s += c;
                    cin.putback(c);

                    if (s == key_quit)
                        return Token(quit);
                    if (s == "sqrt")
                        return Token(math_sqrt);
                    if (s == "pow")
                        return Token(math_pow);

                    return Token(name, s);
                }
                else
                {
                    error("Bad token");
                }
        }
    }
    return dummy_token;     // to mute compiler warning
}


void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into full buffer");

    buffer = t;
    full = true;
}


void Token_stream::ignore()
    // ignore input characters until ';' or '\n', that is 'print'
{
    if (full && buffer.kind == print)
    {
        full = false;
        return;
    }

    full = false;

    char c;
    while (cin.get(c))
    {
        if (c == print || c == '\n')
            return;
    }
}

// ----------------------------------------------------------------------------

class Variable
{
    public:
        string name;
        double value;

        Variable(string n, double v)
            : name {n}, value {v} { }
};

// ----------------------------------------------------------------------------

vector<Variable> var_table;


double get_value(string name)
{
    for (const Variable& var: var_table)
    {
        if (var.name == name)
            return var.value;
    }

    error("get: undefined name ", name);
    return 0;   // to mute compiler warning
}


void set_value(string name, double val)
{
    for (Variable& var: var_table)
    {
        if (var.name == name)
        {
            var.value = val;
            return;
        }
    }

    error("set: undefined name ", name);
}


bool is_declared(string name)
{
    for (const Variable& var: var_table)
    {
        if (var.name == name)
            return true;
    }

    return false;
}


double define_var(string name, double val)
{
    if (is_declared(name))
        error(name, " declared twice");

    var_table.push_back(Variable(name, val));

    return val;
}

// ----------------------------------------------------------------------------

double expression();

double parse_sqrt();
double parse_pow();


double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        case '+':
            return primary();
        case '-':
            return -primary();
        case '(':
        {
            double val = expression();
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return val;
        }
        case math_sqrt:
            return parse_sqrt();
        case math_pow:
            return parse_pow();
        default:
            error("primary expected");
            return 0;   // to mute compiler warning
    }
}


double term()
{
    double left = primary();
    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double denom = primary();
                if (denom == 0)
                    error("divide by zero");
                left /= denom;
                break;
            }
            case '%':
            {
                double denom = primary();
                if (denom == 0)
                    error("module: divide by zero");
                left = fmod(left, denom);
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}


double expression()
{
    double left = term();
    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}


// ----------------------------------------------------------------------------

double parse_sqrt()
{
    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected");

    double val = expression();

    t = ts.get();
    if (t.kind != ')')
        error("')' expected");

    if (val < 0)
        error("sqrt of negative value");

    return sqrt(val);
}


double parse_pow()
{
    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected");

    double base = expression();

    t = ts.get();
    if (t.kind != ',')
        error("',' expected");

    double dexp = expression();
    int iexp = int(dexp);
    if (dexp != iexp)
        error("2nd arg of pow() must be integer");

    t = ts.get();
    if (t.kind != ')')
        error("')' expected");

    return pow(base, iexp);
}

// ----------------------------------------------------------------------------

double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string name = t.name;

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", name);

    double val = expression();

    return define_var(name, val);
}

// ----------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case let:
            return declaration();
        default:
            ts.putback(t);
            return expression();
    }
}

// ----------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore();
}

// ----------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

void calculate()
{
    while (true)
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.putback(t);
            double val = statement();
            cout << result << val << '\n';
        }
        catch (runtime_error& e)
        {
            cerr << "E: " << e.what() << '\n';
            clean_up_mess();
        }
    }
}

// ----------------------------------------------------------------------------

int main()
try
{
    define_var("pi", 3.1415926535);

    calculate();

    return 0;
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "exception\n";
    return 2;
}

// ----------------------------------------------------------------------------
