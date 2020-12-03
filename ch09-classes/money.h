#include <iostream>

using namespace std;

constexpr double d_to_y = 104.46;
constexpr double y_to_d = 0.0096;

class Money {
    public:
        Money(double amount, char currency);

        long int dollar() const;
        long int cent() const;
        long int yen() const;
        char kind() const { return currency; }

    private:
        long int amount;
        char currency;
};


ostream& operator<<(ostream& os, const Money& m);
istream& operator>>(istream& is, Money& m);

Money operator+(const Money& a, const Money& b);
