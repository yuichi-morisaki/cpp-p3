#include <iostream>
#include <stdexcept>

using namespace std;

int area(int length, int width)
{
    return length * width;
}

constexpr int frame_width = 2;
int framed_area(int x, int y)
{
    return area(x - frame_width, y - frame_width);
}

int main()
{
    int x = -1;
    int y = 2;
    int z = 4;

    /* Error handling
    if (x <= 0) throw runtime_error("non-positive x");
    if (y <= 0) throw runtime_error("non-positive y");
    // or
    if (x <= 0 || y <= 0)
        throw runtime_error("non-positive area() argument");
    */
    int area1 = area(x, y);
    cout << "area1 is " << area1 << '\n';

    int area2 = framed_area(1, z);
    cout << "area2 is " << area2 << '\n';

    if (y <= frame_width || z <= frame_width)
        throw runtime_error("non-positive area() argument called by framed_area()");
    int area3 = framed_area(y, z);
    cout << "area3 is " << area3 << '\n';

    double ratio = double(area1) / area3;
    cout << "ratio is " << ratio << '\n';

    return 0;
}
