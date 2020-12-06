#include "calculator.h"
#include "error.h"
#include <cmath>


// ================================================================
//  Symbol_table

// Global variable
Symbol_table sym_table;


double Symbol_table::get(string var_name)
{
    bool found = false;
    double val;

    for (const Variable& v: var_table)
        if (v.name == var_name) {
            found = true;
            val = v.value;
            break;
        }

    if (!found)
        error("get: undefined name ", var_name);

    return val;
}


void Symbol_table::set(string var_name, double var_val)
{
    bool found = false;

    for (Variable& v: var_table)
        if (v.name == var_name) {
            if (v.constant)
                error("set: can't change const variable");
            v.value = var_val;
            found = true;
        }

    if (!found)
        error("set: undefined name ", var_name);
}


bool Symbol_table::is_declared(string var_name)
{
    bool found = false;

    for (const Variable& v: var_table)
        if (v.name == var_name) {
            found = true;
            break;
        }

    return found;
}


double Symbol_table::declare(
        string var_name, double var_val, bool constant)
{
    if (is_declared(var_name))
        error(var_name, " declared twice");

    var_table.push_back(
            Variable {var_name, var_val, constant});

    return var_val;
}

// ================================================================

double parse_fn_sqrt(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected in fn sqrt()");

    double val = expression(ts);
    if (val < 0)
        error("arg of fn sqrt() must not be negative");

    Token t2 = ts.get();
    if (t2.kind != ')')
        error("')' expected in fn sqrt()");

    return sqrt(val);
}


double parse_fn_pow(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != '(')
        error("'(' expected in fn pow()");

    double base = expression(ts);

    Token t2 = ts.get();
    if (t.kind != ',')
        error("',' expected in fn pow()");

    double d_exp = expression(ts);
    int i_exp = static_cast<int>(d_exp);
    if (i_exp != d_exp)
        error("2nd arg of fn pow() must be integer");

    Token t3 = ts.get();
    if (t.kind != ')')
        error("')' expected in fn pow()");

    return pow(base, i_exp);
}


double parse_group(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != '(')
        error("primary expected");

    double val = expression(ts);

    Token t2 = ts.get();
    if (t.kind != ')')
        error("')' expected");

    return val;
}


double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
        case NUMBER:
            return t.value;
        case NAME:
            return sym_table.get(t.name);
        case '+':
            return primary(ts);
        case '-':
            return - primary(ts);
        case MATH_SQRT:
            return parse_fn_sqrt(ts);
        case MATH_POW:
            return parse_fn_pow(ts);
        default:
            return parse_group(ts);
    }
}


double term(Token_stream& ts)
{
    double val = primary(ts);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                val *= primary(ts);
                break;
            case '/':
                {
                    double denom = primary(ts);
                    if (denom == 0)
                        error("divide by zero");
                    val /= denom;
                    break;
                }
            case '%':
                {
                    double denom = primary(ts);
                    if (denom == 0)
                        error("module zero");
                    val = fmod(val, denom);
                    break;
                }
            default:
                ts.putback(t);
                return val;
        }
    }
}


double expression(Token_stream& ts)
{
    double val = term(ts);

    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                val += term(ts);
                break;
            case '-':
                val -= term(ts);
                break;
            default:
                ts.putback(t);
                return val;
        }
    }
}

// ----------------------------------------------------------------

double declaration(Token_stream& ts, bool constant)
{
    Token t = ts.get();
    if (t.kind != NAME)
        error("name expected in declaration");
    string n = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("'=' expected in declaration of ", n);

    double rval = expression(ts);

    sym_table.declare(n, rval, constant);
    return rval;
}


double statement(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
        case LET:
            return declaration(ts, false);
        case CONST:
            return declaration(ts, true);
        case SET:
            {
                Token t2 = ts.get();
                if (t2.kind != NAME)
                    error("set: name expected");
                double rval = expression(ts);
                sym_table.set(t2.name, rval);
                return rval;
            }
        default:
            ts.putback(t);
            return expression(ts);
    }
}


void clean_up_mess(Token_stream& ts)
{
    ts.ignore(PRINT);
}

// ----------------------------------------------------------------

void calculate(Token_stream& ts)
{
    double val;
    bool has_val {false};

    while (true) {
        try {
            if (has_val) {
                cout << result << val << '\n';
                has_val = false;
            }
            cout << prompt;
            while (true) {
                Token t = ts.get();
                if (t.kind == QUIT)
                    return;
                if (t.kind == PRINT)
                    continue;
                ts.putback(t);
                break;
            }
            val = statement(ts);
            has_val = true;
        }
        catch (runtime_error& e) {
            cerr << "E: " << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}
