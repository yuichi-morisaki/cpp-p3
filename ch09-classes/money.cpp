#include "money.h"
#include <cmath>
#include <limits>


Money::Money(double value, char c)
    : amount {0}, currency {c}
{
    if (currency != 'd' && currency != 'y')
        throw runtime_error("Unknown currency");
    if (currency == 'd') {
        if (value > numeric_limits<double>::max() / 100)
            throw runtime_error("value exceeds limit");
        value *= 100;   // in cent
    }
    if (value > numeric_limits<long int>::max() / 1000
            || value < numeric_limits<long int>::min() / 1000)
        throw runtime_error("value exceeds limit");

    amount = value * 1000;  // in milli-cent or milli-yen
}


long int Money::dollar() const
{
    double amt_in_d = 0;
    switch (currency) {
        case 'd':
            amt_in_d = amount / 1000.0 / 100.0;
            break;
        case 'y':
            amt_in_d = amount / 1000.0 * y_to_d;
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    return static_cast<long int>(amt_in_d);
}


long int Money::cent() const
{
    double amt_in_d = 0;
    switch (currency) {
        case 'd':
            amt_in_d = amount / 1000.0 / 100.0 - dollar();
            break;
        case 'y':
            amt_in_d = amount / 1000.0 * y_to_d - dollar();
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    return round(amt_in_d * 100);
}


long int Money::yen() const
{
    double amt_in_y = 0;
    switch (currency) {
        case 'd':
            amt_in_y = amount / 1000.0 / 100.0 * d_to_y;
            break;
        case 'y':
            amt_in_y = amount / 1000.0;
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    return round(amt_in_y);
}


ostream& operator<<(ostream& os, const Money& m)
{
    switch (m.kind()) {
        case 'd':
            os << '$' << m.dollar() << '.' << m.cent();
            break;
        case 'y':
            os << 'Y' << m.yen();
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    return os;
}

istream& operator>>(istream& is, Money& m)
{
    char currency;
    double amount;
    is >> currency >> amount;

    if (!is)
        return is;
    if (currency != 'd' && currency != 'y') {
        is.clear(ios_base::failbit);
        return is;
    }

    m = Money {amount, currency};

    return is;
}


Money operator+(const Money& a, const Money& b)
{
    if (a.kind() == b.kind()) {
        long int left;
        long int right;
        double amt;
        switch (a.kind()) {
            case 'd':
                left = a.dollar() * 100 + a.cent();
                right = b.dollar() * 100 + b.cent();
                amt = (left + right) / 100.0;
                return Money {amt, a.kind()};
            case 'y':
                left = a.yen();
                right = b.yen();
                amt = left + right;
                return Money {amt, a.kind()};
            default:
                throw runtime_error("Unknown currency");
        }
    }
    double lamt = 0;
    switch (a.kind()) {
        case 'd':
            lamt = (a.dollar() * 100 + a.cent()) / 100.0;
            break;
        case 'y':
            lamt = a.yen() * y_to_d;
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    double ramt = 0;
    switch (b.kind()) {
        case 'd':
            ramt = (b.dollar() * 100 + b.cent()) / 100.0;
            break;
        case 'y':
            ramt = b.yen() * y_to_d;
            break;
        default:
            throw runtime_error("Unknown currency");
    }
    return Money {lamt + ramt, 'd'};
}
