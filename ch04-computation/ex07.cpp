#include <iostream>
#include <vector>

using namespace std;

bool is_digit(string);
int c_to_i(char);
int s_to_i(string);

vector<string> digits
= {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    cout << "Please enter an expression >> ";
    string lval, rval;
    char op;
    while (cin >> lval >> rval >> op) {
        int ld, rd;
        if (is_digit(lval))
            ld = c_to_i(lval[0]);
        else if ((ld = s_to_i(lval)) == -1)
            cout << "Not a digit for lvalue: '" << lval << "'\n";

        if (is_digit(rval))
            rd = c_to_i(rval[0]);
        else if ((rd = s_to_i(rval)) == -1)
            cout << "Not a digit for rvalue: '" << rval << "'\n";

        if (ld != -1 && rd != -1) {
            switch (op) {
                case '+':
                    cout << "The sum of " << lval << " and " << rval << " is "
                         << ld + rd << '\n';
                    break;
                case '-':
                    cout << "The diff of " << lval << " and " << rval << " is "
                         << ld - rd << '\n';
                    break;
                case '*':
                    cout << "The prod of " << lval << " and " << rval << " is "
                         << ld * rd << '\n';
                    break;
                case '/':
                    if (rd == 0)
                        cout << "Can't divide by zero!\n";
                    else
                        cout << "The quot of " << lval << " and " << rval << " is "
                             << 1.0 * ld / rd << '\n';
                    break;
                default:
                    cout << "Sorry, I don't know an operator: '" << op << "'\n";
                    break;
            }
        }
        cout << ">> ";

    }

    return 0;
}

bool is_digit(string val)
{
    if (val.size() != 1)
        return false;
    char c = val[0];
    return '0' <= c && c <= '9';
}

int c_to_i(char c)
{
    return int(c) - int('0');
}

int s_to_i(string s)
{
    for (int i = 0; i < digits.size(); ++i)
        if (s == digits[i])
            return i;
    return -1;
}
