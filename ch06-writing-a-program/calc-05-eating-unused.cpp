#include <token-stream.h>
#include <utilities.h>
#include <iostream>

using namespace std;

double expression();
double term();
double primary();

Token_stream ts;

int main()
try {
    double val = 0;
    while (cin) {
        val = expression();
        cout << "=" << val << '\n';
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


double expression()
{
    double left = term();
    Token t = ts.get();
    switch (t.kind) {
        case '+':
            return left + expression();
        case '-':
            return left - expression();
        default:
            return left;
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    switch (t.kind) {
        case '*':
            return left * term();
        case '/':
            return left / term();
        default:
            return left;
    }
}

double primary()
{
    Token t = ts.get();
    double result;
    switch (t.kind) {
        case '(':
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')')
                    error("')' expected");
                result = d;
                break;
            }
        case '8':
            result = t.value;
            break;
        default:
            error("primary expected");
    }
    return result;
}
