// two operands calculator

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter an operator followed by two operands: ";
    string operation = "";
    double operand1 = 0.0;
    double operand2 = 0.0;
    cin >> operation >> operand1 >> operand2;

    if (operation == "+" || operation == "plus")
        cout << operand1 + operand2 << '\n';
    else if (operation == "-" || operation == "minus")
        cout << operand1 - operand2 << '\n';
    else if (operation == "*" || operation == "mul")
        cout << operand1 * operand2 << '\n';
    else if (operation == "/" || operation == "div")
        cout << operand1 / operand2 << '\n';
    else
        cout << "not an operation I know: " << operation << '\n';

    return 0;
}
