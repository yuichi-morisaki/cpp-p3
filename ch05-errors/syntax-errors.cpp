int area(int length, int width);

int main()
{
    // expected ')' before ';' token
    int s1 = area(7;

    // too few arguments to function 'int area(int, int)'
    int s2 = area(7)

    // 'Int' was not declared in this scope; did you mean 'int'?
    Int s3 = area(7);

    // missing terminating ' character
    int s4 = area('7);

    return 0;
}

int area(int length, int width)
{
    return length * width;
}
