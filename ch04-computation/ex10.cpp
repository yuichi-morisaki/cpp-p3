#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<char> moves = {
        'r', 'p', 's', 'p', 's', 's', 'r', 'p', 'p', 'r',
        's', 'r', 'p', 'r', 's', 'r', 'p',
    };
    vector<int> steps = { 1, 2, 3, 5, 7, 11, 13, };

    int salt;
    cout << "Please enter any number: ";
    cin >> salt;
    int step = steps[salt % steps.size()];

    int idx = step % moves.size();
    cout << "Enter your move. [r/p/s] >> ";
    char m;
    while (cin >> m) {
        switch (m) {
            case 'r':
                switch (moves[idx]) {
                    case 'r':
                        cout << "Rock! -- We draw.\n";
                        break;
                    case 'p':
                        cout << "Paper! -- You lose.\n";
                        break;
                    case 's':
                        cout << "Scissors! -- You win.\n";
                        break;
                    default:
                        cout << "Error: invalid move in dataset at " << idx << '\n';
                        break;
                }
                break;
            case 'p':
                switch (moves[idx]) {
                    case 'r':
                        cout << "Rock! -- You win.\n";
                        break;
                    case 'p':
                        cout << "Paper! -- We draw.\n";
                        break;
                    case 's':
                        cout << "Scissors! -- You lose.\n";
                        break;
                    default:
                        cout << "Error: invalid move in dataset at " << idx << '\n';
                        break;
                }
                break;
            case 's':
                switch (moves[idx]) {
                    case 'r':
                        cout << "Rock! -- You lose.\n";
                        break;
                    case 'p':
                        cout << "Paper! -- You win.\n";
                        break;
                    case 's':
                        cout << "Scissors! -- We draw.\n";
                        break;
                    default:
                        cout << "Error: invalid move in dataset at " << idx << '\n';
                        break;
                }
                break;
            default:
                break;
        }
        idx = (idx + step) % moves.size();
        cout << "[r/p/s] >> ";
    }
    cout << '\n';

    return 0;
}
