#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}

double str_to_double(string s)
{
    istringstream iss {s};
    double d;
    iss >> d;
    if (!iss)
        error("double format error: ", s);
    return d;
}


struct Temperature {
    double temp;
    char unit;
};

void my_code(string label, Temperature temp)
{
    ostringstream oss;
    oss << left << setw(8) << label << ":"
        << fixed << setprecision(5) << temp.temp << temp.unit;
    /* Instead of
    someobject.display(Point(100, 100), oss.str().c_str());
    */
    cout << oss.str() << '\n';
}


int main()
try {
    Temperature t {12.3456789, 'c'};
    my_code("Temp", t);

    double d1 = str_to_double("12.4");
    double d2 = str_to_double("1.34e-3");
    double d3 = str_to_double("twelve point three");

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
