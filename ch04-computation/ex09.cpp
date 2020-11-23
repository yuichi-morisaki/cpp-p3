#include <iostream>

using namespace std;

int main()
{
    double total = 0;
    double current = 1;
    for (int square = 1; square < 64+1; ++square, current *= 2) {
        total += current;
        cout << square << '\t' << current << '\t' << total << '\n';
        if (total >= 1000 && total - current < 1000)
            cout << "*** You got 1,000 grains of rice! ***\n";
        if (total >= 1000000 && total - current < 1000000)
            cout << "*** You got 1,000,000 grains of rice! ***\n";
        if (total >= 1000000000 && total - current < 1000000000)
            cout << "*** You got 1,000,000,000 grains of rice! ***\n";
    }

    return 0;
}
