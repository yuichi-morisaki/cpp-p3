#include <utilities.h>
#include <stdexcept>

using namespace std;

void error(string s)
{
    throw runtime_error(s);
}
