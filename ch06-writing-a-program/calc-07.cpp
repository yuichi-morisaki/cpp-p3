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
        Token t = ts.get();
        if (t.kind == 'q')
            break;
        if (t.kind == ';')
            cout << "=" << val << '\n';
        else
            ts.putback(t);
        val = expression();
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
    while (t.kind == '+' || t.kind == '-') {
        if (t.kind == '+')
            left += term();
        else
            left -= term();
        t = ts.get();
    }
    ts.putback(t);
    return left;
}


double term()
{
    double left = primary();
    Token t = ts.get();
    while (t.kind == '*' || t.kind == '/') {
        if (t.kind == '*') {
            left *= primary();
        } else {
            double d = primary();
            if (d == 0)
                error("divide by zero");
            left /= d;
        }
        t = ts.get();
    }
    ts.putback(t);
    return left;
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
