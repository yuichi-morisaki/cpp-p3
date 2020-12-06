#include "error.h"
#include <sstream>


void error(string s)
{
    throw runtime_error(s);
}


void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}


void error(string s, char c)
{
    ostringstream oss;
    oss << s << " '" << c << "' (" << int(c) << ")";
    throw runtime_error(oss.str());
}
