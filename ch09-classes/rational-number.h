#include <iostream>

using namespace std;


class Rational {
    public:
        Rational();
        Rational(int num, int den);

        int numer() const { return numerator; }
        int denom() const { return denominator; }
        double to_double() const;

    private:
        int numerator;
        int denominator;
};


ostream& operator<<(ostream& os, const Rational& a);

bool operator==(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);

Rational operator+(const Rational& a);
Rational operator-(const Rational& a);

Rational operator+(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);


int greatest_common_divisor(int a, int b);
