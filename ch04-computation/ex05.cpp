#include <iostream>

using namespace std;

int main()
{
    cout << "Please enter an expression like '35.6 24.1 +' >> ";
    double lval, rval;
    char op;
    while (cin >> lval >> rval >> op) {
        switch (op) {
            case '+':
                cout << "The sum of " << lval << " and " << rval << " is "
                     << lval + rval << '\n';
                break;
            case '-':
                cout << "The diff of " << lval << " and " << rval << " is "
                     << lval - rval << '\n';
                break;
            case '*':
                cout << "The prod of " << lval << " and " << rval << " is "
                     << lval * rval << '\n';
                break;
            case '/':
                if (rval == 0)
                    cout << "Can't divide by zero!\n";
                else
                    cout << "The quot of " << lval << " and " << rval << " is "
                         << lval / rval << '\n';
                break;
            default:
                cout << "Sorry, I don't know such an operator: '" << op << "'\n";
                break;
        }
        cout << ">> ";
    }

    return 0;
}
