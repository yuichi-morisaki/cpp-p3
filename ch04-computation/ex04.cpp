#include <iostream>

using namespace std;

int main()
{
    cout << "Please think of any number between 1 to 100.\n";

    int inf = 0;
    int sup = 100;
    int guess = (inf + sup) / 2;
    int chance = 7;

    while (chance) {
        cout << "Is the number you are thinking of less than " << guess << "? (y/n):";
        char answer;
        cin >> answer;
        if (answer == 'y') {
            sup = guess;
        } else if (answer == 'n') {
            inf = guess;
        } else {
            cout << "Please answer 'y' or 'n'\n";
        }
        guess = (inf + sup) / 2;
        --chance;
    }

    cout << "The number you are thinking of is " << guess << ", right?\n";

    return 0;
}
