#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

string int_to_day(int);
int day_to_int(string);

int main()
try {
    vector<vector<int>> days(7);
    cout << "Please enter a sequence of pairs such as (Tuesday 23):\n";
    string day;
    int v;
    while (cin >> day >> v) {
        try {
            int idx = day_to_int(day);
            days[idx].push_back(v);
        }
        catch (exception& e) {
            cout << "Invalid input '" << day << "'\n";
        }
    }

    for (int i = 0; i < days.size(); ++i) {
        cout << int_to_day(i) << ": ";
        int sum = 0;
        for (int v: days[i]) {
            sum += v;
            cout << v << ' ';
        }
        cout << ", and sum == " << sum << '\n';
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

string int_to_day(int i)
{
    switch (i) {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        default:
            throw runtime_error("Invalid value for index of a day of the week");
    }
}

int day_to_int(string day)
{
    if (day == "Sunday" || day == "sunday" || day == "Sun")
        return 0;
    if (day == "Monday" || day == "monday" || day == "Mon")
        return 1;
    if (day == "Tuesday" || day == "tuesday" || day == "Tue")
        return 2;
    if (day == "Wednesday" || day == "wednesday" || day == "Wed")
        return 3;
    if (day == "Thursday" || day == "thursday" || day == "Thu")
        return 4;
    if (day == "Friday" || day == "friday" || day == "Fri")
        return 5;
    if (day == "Saturday" || day == "saturday" || day == "Sat")
        return 6;
    throw runtime_error("Invalid input for a day of the week");
}
