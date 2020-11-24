#include <string>
using namespace std;

int area(int length, int width);

int main()
{
    // 'arena' was not declared in this scope; did you mean 'area'?
    int x0 = arena(7);

    // too few arguments to function 'int area(int, int)'
    int x1 = area(7);

    // invalid conversion from 'const char*' to 'int'
    int x2 = area("seven", 2);

    // conversion from 'int' to non-scalar type 'std::string'...
    string s = area(2, 7);

    return 0;
}

int area(int length, int width)
{
    return length * width;
}
