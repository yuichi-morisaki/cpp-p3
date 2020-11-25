#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    vector<int> numbers = {1, 2, 3, 4};
    while (true) {
        cout << "Please guess four different digits: ";
        vector<int> guess;
        for (int i = 0; i < 4; ++i) {
            int g;
            cin >> g;
            if (!cin)
                throw runtime_error("Failed to read input as int");
            if (!(0 <= g && g <= 9))
                throw runtime_error("Invalid input: not a digit");
            for (int n: guess)
                if (g == n)
                    throw runtime_error("Invalid input: duplicated digits");
            guess.push_back(g);
        }

        int bulls = 0;
        int cows = 0;
        for (int pos = 0; pos < 4; ++pos) {
            if (numbers[pos] == guess[pos]) {
                ++bulls;
                continue;
            }
            for (int n: numbers) {
                if (n == guess[pos]) {
                    ++cows;
                    break;
                }
            }
        }
        if (bulls == 4) {
            cout << "4 bulls -- You win!\n";
            break;
        }
        cout << bulls << ((bulls <= 1) ? " bull" : " bulls") << " and "
             << cows << ((cows <= 1) ? " cow" : " cows") << '\n';
    }

    return 0;
}
catch (exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Fatal: Unknown error occurred.\n";
    return 2;
}
