#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string message);

constexpr char BULL = 'b';
constexpr char COW = 'c';
constexpr char NONE = ' ';

class Answer {
public:
    Answer()
        : initialized(false) { }
    void init(char c1, char c2, char c3, char c4);
    char guess(char c, int pos);
private:
    bool initialized;
    vector<char> vec;
};


int main()
try {
    Answer answer = Answer();
    answer.init('a', 'c', 'e', 'z');

    while (true) {
        cout << "Please guess four different chars: ";
        char c;
        int bulls = 0;
        int cows = 0;
        for (int i = 0; i < 4 && cin >> c; ++i) {
            char res = answer.guess(c, i);
            if (res == BULL) ++bulls;
            if (res == COW) ++cows;
        }
        cout << bulls << ((bulls <= 1) ? " bull" : " bulls")
             << " and "
             << cows << ((cows <= 1) ? " cow" : " cows")
             << '\n';
        if (bulls == 4) {
            cout << "YOU WIN!!\n";
            break;
        }
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

char Answer::guess(char c, int pos) {
    for (int i = 0; i < vec.size(); ++i) {
        if (c == vec[i]) {
            if (i == pos)
                return BULL;
            else
                return COW;
        }
    }
    return NONE;
}


void Answer::init(char c1, char c2, char c3, char c4) {
    if (initialized)
        return;
    if (c1 == c2 || c1 == c3 || c1 == c4
            || c2 == c3 || c2 == c4 || c3 == c4)
        error("duplicated char in answer");
    vec.push_back(c1);
    vec.push_back(c2);
    vec.push_back(c3);
    vec.push_back(c4);
    initialized = true;
    return;
}

void error(string message) {
    throw runtime_error(message);
}
