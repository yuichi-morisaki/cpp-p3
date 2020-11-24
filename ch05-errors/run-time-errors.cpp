#include <iostream>
using namespace std;

int area(int length, int width)
{
    return length * width;
}

int framed_area(int x, int y)
{
    return area(x - 2, y - 2);
}

int main()
{
    int x = -1;
    int y = 2;
    int z = 4;

    int area1 = area(x, y);
    cout << "area1 is " << area1 << '\n';

    int area2 = framed_area(1, z);
    cout << "area2 is " << area2 << '\n';

    int area3 = framed_area(y, z);
    cout << "area3 is " << area3 << '\n';

    double ratio = double(area1) / area3;
    cout << "ratio is " << ratio << '\n';

    return 0;
}
