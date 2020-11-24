// This doesn't solve the error occurred in main()
double area(double x, double y)
{
    return x * y;
}

// This also doesn't solve the error occurred in main()
int area(int x, int y, char unit)
{
    return x * y;
}

// This solves the undefined-reference error occurred in main()
int area(int x, int y)
{
    return x * y;
}
