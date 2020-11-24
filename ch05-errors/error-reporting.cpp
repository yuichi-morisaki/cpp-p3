#include <iostream>
#include <stdexcept>

using namespace std;

char ask_user(string question)
{
    cout << question << "? (yes or no)\n";
    string answer = " ";
    cin >> answer;
    if (answer == "y" || answer == "yes") return 'y';
    if (answer == "n" || answer == "no") return 'n';
    return 'b';
}

int area(int length, int width)
{
    if (length <= 0 || width <= 0) return -1;
    return length * width;
}

int framed_area(int x, int y)
{
    constexpr int frame_width = 2;
    return area(x - frame_width, y - frame_width);
}

int main()
{
    cout << "Please enter three integers for x, y, and z: ";
    int x, y, z;
    cin >> x >> y >> z;

    int area1 = area(x, y);
    if (area1 <= 0)
        throw runtime_error("non-positive area: area1");
    int area2 = framed_area(1, z);
    if (area2 == -1)
        cout << "non-positive area2\n";
        // throw runtime_error("non-positive area: area2");
    int area3 = framed_area(y, z);
    if (area3 == -1)
        throw runtime_error("non-positive area: area3");
    double ratio = double(area1) / area3;

    cout << "area1 == " << area1
         << ", area2 == " << area2
         << ", area3 == " << area3
         << ", and ratio == " << ratio << '\n';

    return 0;
}
