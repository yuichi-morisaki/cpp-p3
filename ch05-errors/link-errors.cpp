int area(int length, int width);

int main()
{
    // Error when linking;
    // undefined reference to 'area(int, int)'
    int x = area(2, 3);

    return 0;
}
