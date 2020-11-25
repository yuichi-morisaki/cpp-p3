#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>

using namespace std;

vector<int> read_input();
int count_bulls(vector<int> a, vector<int> g);
int count_cows(vector<int> a, vector<int> g);
void play_game(vector<int> a);

int main()
try {
    cout << "Please enter a seed: ";
    int n;
    cin >> n;
    if (!cin)
        throw runtime_error("Invalid input for seed");
    mt19937 gen(n);
    uniform_int_distribution<> distrib(0, 9);

    while (true) {
        vector<int> answer;
        for (int i = 0; i < 4; ++i) {
            while (true) {
                int r = distrib(gen);
                bool duplicated = false;
                for (int a: answer) {
                    if (r == a)
                        duplicated = true;
                }
                if (!duplicated) {
                    answer.push_back(r);
                    break;
                }
            }
        }
        play_game(answer);
        cout << "Play again? (y/n): ";
        string resp;
        cin >> resp;
        if (resp == "n" || resp == "no")
            break;
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

int randint(int min, int max)
{
    mt19937 gen(1);
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void play_game(vector<int> answer)
{
    while (true) {
        vector<int> guess = read_input();
        int bulls = count_bulls(answer, guess);
        int cows = count_cows(answer, guess);
        if (bulls == 4) {
            cout << "4 Bulls! You WIN!!\n";
            break;
        }
        cout << bulls
             << ((bulls <= 1) ? " bull" : " bulls")
             << " and "
             << cows
             << ((cows <= 1) ? " cow" : " cows")
             << '\n';
    }
}

int count_bulls(vector<int> answer, vector<int> guess)
{
    int bulls = 0;
    for (int pos = 0; pos < 4; ++pos) {
        if (answer[pos] == guess[pos])
            ++bulls;
    }
    return bulls;
}

int count_cows(vector<int> answer, vector<int> guess)
{
    int cows = 0;
    for (int g_pos = 0; g_pos < 4; ++g_pos)
        for (int a_pos = 0; a_pos < 4; ++a_pos) {
            if (g_pos == a_pos)
                continue;
            if (guess[g_pos] == answer[a_pos]) {
                ++cows;
                break;
            }
        }
    return cows;
}

vector<int> read_input()
{
    vector<int> guessing_digits;
    cout << "Please guess four different digits: ";
    for (int i = 0; i < 4; ++i) {
        int digit;
        cin >> digit;
        if (!cin)
            throw runtime_error("Failed to read input as 'int'");
        if (!(0 <= digit && digit <= 9))
            throw runtime_error("Invalid input: not a digit");
        for (int already_guessed: guessing_digits)
            if (digit == already_guessed)
                throw runtime_error(
                    "Invalid input: duplicated input");
        guessing_digits.push_back(digit);
    }
    return guessing_digits;
}
