#include "error.h"
#include <stdexcept>

void error(string s)
{
    throw runtime_error(s);
}


void error(string s1, string s2)
{
    error(s1 + ' ' + s2);
}
