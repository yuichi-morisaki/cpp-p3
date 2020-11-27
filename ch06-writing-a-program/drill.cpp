#include <iostream>
#include <stdexcept>

using namespace std;

constexpr char QUIT = 'x';
constexpr char PRINT = '=';

void error(string s) {
    throw runtime_error(s);
}


//------------------------------------------------------------------------------

class Token{
    public:
        char kind;        // what kind of token
        double value;     // for numbers: a value 
        Token()
            :kind('8'), value(0) { }
        Token(char ch)    // make a Token from a char
            :kind(ch), value(0) { }
        Token(char ch, double val)     // make a Token from a char and a double
            :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
    public:
        Token_stream();   // make a Token_stream that reads from cin
        Token get();      // get a Token (get() is defined elsewhere)
        void putback(Token t);    // put a Token back
    private:
        bool full;        // is there a Token in the buffer?
        Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    Token result;
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        case PRINT:
        case QUIT:
        case '(': case ')': case '+': case '-': case '*': case '/':
            result = Token(ch);
            break;
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '9':
            {
                cin.putback(ch);         // put digit back into the input stream
                double val;
                cin >> val;              // read a floating-point number
                result = Token('8', val);
                break;
            }
        default:
            error("Bad token");
    }
    return result;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    double result = 0;
    switch (t.kind) {
        case '(':    // handle '(' expression ')'
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                result = d;
                break;
            }
        case '8':            // we use '8' to represent a number
            result = t.value;
            break;
        default:
            error("primary expected");
    }
    return result;
}

//------------------------------------------------------------------------------
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                {
                    double d = primary();
                    if (d == 0) error("divide by zero");
                    left /= d;
                    t = ts.get();
                    break;
                }
            default:
                ts.putback(t);     // put t back into the token stream
                return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term();    // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();    // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
try {
    cout << "Welcome to our simple calculator.\n"
         << "Please enter expressions using floating-point numbers.\n"
         << "We can handle four operators: + - * / and parentheses ( )\n"
         << "Use the command '=' to print, 'x' to exit.\n";
    cout << ">> ";

    double val = 0;
    while (cin) {
        Token t = ts.get();

        if (t.kind == QUIT) break;
        if (t.kind == PRINT)
            cout << val << "\n>> ";
        else {
            ts.putback(t);
            val = expression();
        }
    }

    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
}

//------------------------------------------------------------------------------
