#include "error.h"
#include "token.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;


double expression(Token_stream& ts);


double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
        case number:
            return t.value;
        case '+':
            return primary(ts);
        case '-':
            return -primary(ts);
        case '(':
        {
            double val = expression(ts);
            t = ts.get();
            if (t.kind != ')')
                error("')' expected");
            return val;
        }
        default:
            error("primary expected");
            return 0;
    }
}


double term(Token_stream& ts)
{
    double left = primary(ts);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= primary(ts);
                break;
            case '/':
            {
                double denom = primary(ts);
                if (denom == 0)
                    error("divide by zero");
                left /= denom;
                break;
            }
            case '%':
            {
                double denom = primary(ts);
                if (denom == 0)
                    error("modulo: divide by zero");
                left = fmod(left, denom);
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}


double expression(Token_stream& ts)
{
    double left = term(ts);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term(ts);
                break;
            case '-':
                left -= term(ts);
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}


void clean_up_mess(Token_stream& ts)
{
    ts.ignore();
}


const string prompt = "> ";
const string result = "= ";


void calculate(Token_stream& ts)
{
    while (true) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.putback(t);
            double val = expression(ts);
            cout << result << val << '\n';
        }
        catch (runtime_error& e) {
            cerr << "E: " << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}


int main()
try {
    Token_stream ts = Token_stream(cin);
    calculate(ts);

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
