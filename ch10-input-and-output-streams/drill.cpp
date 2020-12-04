#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}

void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}

struct Point {
    double x;
    double y;
};

struct Invalid_Point {};

bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point& a, const Point& b)
{
    return !(a == b);
}

istream& operator>>(istream& is, Point& p)
{
    char c1;
    if (is >> c1 && c1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    if (is.eof())
        return is;

    char c2, c3;
    double x, y;
    is >> x >> c2 >> y >> c3;
    if (!is || c2 != ',' || c3 != ')')
        throw Invalid_Point {};

    p.x = x;
    p.y = y;

    return is;
}

ostream& operator<<(ostream& os, const Point& p)
{
    return os << '(' << p.x << ',' << p.y << ')';
}


Point get_point()
{
    while (true) {
        cout << "Enter a point: ";
        Point p;
        try {
            cin >> p;
            if (cin)
                return p;

            if (cin.fail()) {
                cin.clear();
                cout << "Invalid format. Enter ')': ";
                cin.ignore(numeric_limits<streamsize>::max(), ')');
            }
        }
        catch (Invalid_Point& p) {
            if (cin.eof())
                error("Bad input - EOF");

            cin.clear();
            cout << "Something wrong was detected."
                 << "Enter '}': ";
            cin.ignore(numeric_limits<streamsize>::max(), '}');
        }
        cout << "An example for valid point: '(x, y)'\n";
    }
}


int main()
try {
    vector<Point> original_points;
    for (int i = 0; i < 7; i++) {
        Point p = get_point();
        original_points.push_back(p);
    }

    string fname = "mydata.txt";
    ofstream ofs {fname};
    if (!ofs)
        error("can't open output file ", fname);
    for (Point p: original_points)
        ofs << p << '\n';
    ofs.close();

    ifstream ifs {fname};
    if (!ifs)
        error("can't open input file ", fname);
    vector<Point> processed_points;

    try {
        for (Point p; ifs >> p && !ifs.eof(); )
            processed_points.push_back(p);
    }
    catch (Invalid_Point& e) {
        error("Failed to read into Point");
    }

/*
    // test 1
    processed_points.pop_back();
    // test 2
    processed_points[2].x = 7;
    processed_points[6].y = 1;
*/

    cout << "---- original points ----\n";
    for (Point p: original_points)
        cout << p << '\n';
    cout << "---- processed points ----\n";
    for (Point p: processed_points)
        cout << p << '\n';

    cout << "----\n";
    if (original_points.size() != processed_points.size())
        cout << "Different sizes\n";
    else {
        vector<int> diff_idx;
        for (int i = 0; i < original_points.size(); ++i)
            if (original_points[i] != processed_points[i])
                diff_idx.push_back(i);
        for (int idx: diff_idx)
            cout << '#' << idx << ": " << original_points[idx]
                 << " != " << processed_points[idx] << '\n';
        if (diff_idx.size() == 0)
            cout << "They have the same points\n";
    }

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
