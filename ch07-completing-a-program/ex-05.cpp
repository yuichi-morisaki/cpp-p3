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
            : buffer {} { }

        Token get();
        void putback(Token);
        void ignore();

    private:
        vector<Token> buffer;
};


Token_stream ts;

// ----------------------------------------------------------------------------

const string key_quit = "quit";
const string key_let = "let";
const string key_const = "const";
constexpr char print = ';';
constexpr char let = '#';
constexpr char constant = 'C';

constexpr char quit = 'Q';
constexpr char number = '8';
constexpr char name = 'a';

constexpr char math_sqrt = 'r';
constexpr char math_pow = 'p';


Token Token_stream::get()
{
    if (!buffer.empty())
    {
        Token t = buffer.back();
        buffer.pop_back();
        return t;
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
                    if (s == key_let)
                        return Token(let);
                    if (s == key_const)
                        return Token(constant);
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
    buffer.push_back(t);
}


void Token_stream::ignore()
    // ignore input characters until ';' or '\n', that is 'print'
{
    while (!buffer.empty())
    {
        Token t = buffer.back();
        buffer.pop_back();
        if (t.kind == print)
            return;
    }

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
        bool constant;

        Variable(string n, double v, bool c)
            : name {n}, value {v}, constant {c} { }
};

// ----------------------------------------------------------------------------

class Symbol_table
{
    public:
        vector<Variable> var_table;

        Symbol_table()
            : var_table {} { }

        double get(string var_name);
        void set(string var_name, double var_value);
        bool is_declared(string var_name);
        double declare(
            string var_name, double var_value, bool is_constant);
};

// ----------------------------------------------------------------------------

double Symbol_table::get(string n)
{
    for (const Variable& var: var_table)
    {
        if (var.name == n)
            return var.value;
    }
    error("get: undefined name ", n);
    return 0;   // to mute compiler warning
}

void Symbol_table::set(string n, double v)
{
    for (Variable& var: var_table)
    {
        if (var.name == n)
        {
            if (var.constant)
                error("set: cannot change a const");
            var.value = v;
            return;
        }
    }
    error("set: undefined name ", n);
}

bool Symbol_table::is_declared(string n)
{
    for (const Variable& var: var_table)
    {
        if (var.name == n)
            return true;
    }
    return false;
}

double Symbol_table::declare(string n, double v, bool is_constant)
{
    if (is_declared(n))
        error(n, " declared twice");

    var_table.push_back(
            Variable(n, v, is_constant));

    return v;
}


Symbol_table sym_table;

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
            return sym_table.get(t.name);
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

double declaration(bool is_constant)
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string name = t.name;

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", name);

    double val = expression();

    return sym_table.declare(name, val, is_constant);
}

// ----------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case let:
            return declaration(false);
        case constant:
            return declaration(true);
        case name:
        {
            Token t2 = ts.get();
            if (t2.kind == '=')
            {
                double rval = expression();
                sym_table.set(t.name, rval);
                return rval;
            }
            else
            {
                ts.putback(t2);
                ts.putback(t);
                return expression();
            }
        }
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
    cout << "\nWelcome to The Simple Calculator!\n"
         << "'+' '-' '*' '/' '%' "
         << "'sqrt' and 'pow' are available.\n"
         << "You can use 'let' to define a variable "
         << " and 'const' for constant.\n"
         << "'pi' and 'e' are already defined.\n"
         << "To stop the calculator, enter 'quit' "
         << "and print for ';' in the middle of a line.\n"
         << "Enter expression following the prompt '>'\n";

    sym_table.declare("pi", 3.1415926535, true);
    sym_table.declare("e", 2.7182818284, true);

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
