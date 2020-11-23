#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> spelled_digits = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
    };

    cout << "Please enter a digit >> ";
    string input;
    while (cin >> input) {
        char c = input[0];
        if (input.size() == 1 && '0' <= c && c <= '9') {
            int d = int(c) - int('0');
            cout << spelled_digits[d] << '\n';
        } else {
            int idx = -1;
            for (int i = 0; i < spelled_digits.size(); ++i) {
                if (input == spelled_digits[i]) {
                    idx = i;
                    break;
                }
            }
            if (idx == -1)
                cout << "Not a digit: '" << input << "'\n";
            else
                cout << idx << '\n';
        }
        cout << ">> ";
    }

    return 0;
}
