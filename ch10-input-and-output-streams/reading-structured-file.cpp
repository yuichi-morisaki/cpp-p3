#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string s);
void error(string s, int i);
void error(string s1, string s2);
void end_of_loop(istream& is, char term, const string& message);


vector<string> month_input_tbl = {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(string s)
{
    for (int i = 0; i < 12; ++i)
        if (month_input_tbl[i] == s)
            return i;
    return -1;
}

vector<string> month_print_tbl = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

string int_to_month(int i)
{
    if (i < 0 || 12 <= i)
        error("bad month index");
    return month_print_tbl[i];
}


constexpr int not_a_reading = -7777;
constexpr int not_a_month = -1;

struct Day {
    vector<double> hour {vector<double>(24, not_a_reading)};
};

struct Month {
    int month {not_a_month};
    vector<Day> day {32};   // waste day[0] for simplicity
};

struct Year {
    int year;
    vector<Month> month {12};   // [0:11] January is 0
};

struct Reading {
    int day;
    int hour;
    double temperature;
};


constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

bool is_valid(const Reading& r)
{
    if (r.day < 1 || 31 < r.day)
        return false;
    if (r.hour < 0 || 23 < r.hour)
        return false;
    if (r.temperature < implausible_min
            || implausible_max < r.temperature)
        return false;

    return true;
}


istream& operator>>(istream& is, Reading& r)
{
    char ch1;
    if (is >> ch1 && ch1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    char ch2;
    int day;
    int hour;
    double temp;
    is >> day >> hour >> temp >> ch2;
    if (!is || ch2 != ')')
        error("bad reading");

    r.day = day;
    r.hour = hour;
    r.temperature = temp;
    return is;
}

istream& operator>>(istream& is, Month& m)
{
    char ch = 0;
    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string month_marker;
    string month;
    is >> month_marker >> month;
    if (!is || month_marker != "month")
        error("bad start of month");
    m.month = month_to_int(month);

    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r; ) {
        if (is_valid(r)) {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;
            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else {
            ++invalids;
        }
    }

    if (invalids)
        error("invalid readings in month", invalids);
    if (duplicates)
        error("duplicate readings in month", duplicates);

    end_of_loop(is, '}', "bad end of month");
    return is;
}

istream& operator>>(istream& is, Year& y)
{
    char ch;
    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string year_marker;
    int year;
    is >> year_marker >> year;
    if (!is || year_marker != "year")
        error("bad start of year");
    y.year = year;

/* -------------------------------------------------------
    for (Month m; is >> m; )
        y.month[m.month] = m;
---------------------------------------------------------- */
    while (true) {
        Month m;
        if (!(is >> m))
            break;
        y.month[m.month] = m;
    }
    end_of_loop(is, '}', "bad end of year");
    return is;
}


// for exercise
void print_year(ostream& os, const Year& y);


int main()
try {
/*
    cout << "Please enter input file name\n";
    string iname;
    cin >> iname;
*/
    string iname = "structured-data.txt";
    ifstream is {iname};
    if (!is)
        error("can't open input file ", iname);

    is.exceptions(is.exceptions()|ios_base::badbit);

/*
    cout << "Please enter output file name\n";
    string oname;
    cin >> oname;
*/
    string oname = "structured-data-out.txt";
    ofstream os {oname};
    if (!os)
        error("can't open output file ", oname);

    vector<Year> ys;
    while (true) {
        Year y;
        if (!(is >> y))
            break;
        ys.push_back(y);
    }
    cout << "read " << ys.size() << " years of readings=n";

    for (Year& y : ys)
        print_year(os, y);

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}


void error(string s)
{
    throw runtime_error(s);
}

void error(string s, int i)
{
    throw runtime_error(s + to_string(i));
}

void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.fail()) {
        is.clear();
        char c;
        if (is >> c && c == term)
            return;
        error(message);
    }
}
