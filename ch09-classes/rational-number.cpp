#include "rational-number.h"


Rational::Rational()
    : numerator {0}, denominator {1}
{
}

Rational::Rational(int num, int den)
    : numerator {num}, denominator {den}
{
    if (den == 0)
        throw runtime_error("Rational: denominator is zero");
    int sign = (num * den < 0) ? -1 : 1;
    num = abs(num);
    den = abs(den);
    int g = greatest_common_divisor(num, den);
    numerator = sign * num / g;
    denominator = den / g;
}


double Rational::to_double() const
{
    return 1.0 * numerator / denominator;
}


ostream& operator<<(ostream& os, const Rational& a)
{
    return os << a.numer() << '/' << a.denom();
}

bool operator==(const Rational& a, const Rational& b)
{
    return a.numer() == b.numer() && a.denom() == b.denom();
}

bool operator!=(const Rational& a, const Rational& b)
{
    return !(a == b);
}

bool operator<(const Rational& a, const Rational& b)
{
    int g = greatest_common_divisor(a.denom(), b.denom());
    int lterm = b.denom() / g * a.numer();
    int rterm = a.denom() / g * b.numer();
    return lterm < rterm;
}


Rational operator+(const Rational& a)
{
    Rational r = a;
    return r;
}

Rational operator-(const Rational& a)
{
    Rational r {-1 * a.numer(), a.denom()};
    return r;
}


Rational operator+(const Rational& a, const Rational& b)
{
    int g = greatest_common_divisor(a.denom(), b.denom());
    int den = a.denom() / g * b.denom();
    int lnum = b.denom() / g * a.numer();
    int rnum = a.denom() / g * b.numer();
    return Rational {lnum + rnum, den};
}


Rational operator-(const Rational& a, const Rational& b)
{
    return a + (- b);
}


Rational operator*(const Rational& a, const Rational& b)
{
    return Rational {a.numer() * b.numer(), a.denom() * b.denom()};
}


Rational operator/(const Rational& a, const Rational& b)
{
    if (b.numer() == 0)
        throw runtime_error("divide by zero");

    return a * Rational {b.denom(), b.numer()};
}


int greatest_common_divisor(int a, int b)
{
    if (b == 0) return a;
    return greatest_common_divisor(b, a % b);
}
