#include <iostream>
#include <stdexcept>

using namespace std;


void skip_to_int()
{
    if (cin.fail()) {
        cin.clear();
        char c;
        while (true) {
            c = cin.get();
            if (!cin)
                throw runtime_error("no input");
            if (isdigit(c) || c == '-')
                break;
        }
        cin.unget();
        return;
    }
}

int get_int()
{
    int n = 0;
    while (true) {
        if (cin >> n)
            return n;
        if (cin.bad())
            throw runtime_error("cin is bad");
        if (cin.eof())
            throw runtime_error("no input");
        cout << "Sorry, that was not a number;"
             << " please try again\n";
        skip_to_int();
    }
}

int get_int(int low, int high,
            const string& greeting, const string& sorry)
{
    cout << greeting << ": [" << low << ":" << high << "]\n";
    while (true) {
        int n = get_int();
        if (low <= n && n <= high)
            return n;
        cout << sorry << ": [" << low << ":" << high << "]\n";
    }
}


int main()
try {
    int strength = get_int(
            1, 10,
            "enter strength",
            "Not in range, try again");
    cout << "strength: " << strength << '\n';

    int altitude = get_int(
            0, 50000,
            "Please enter altitude in feet",
            "Not in range, please try again");
    cout << "altitude: " << altitude << "f above sea level\n";

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
