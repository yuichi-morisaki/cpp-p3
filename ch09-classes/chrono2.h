#include <iostream>
#include <vector>

using namespace std;


namespace Chrono {

    enum class Day {
        Sun, Mon, Tue, Wed, Thu, Fri, Sat
    };

    const vector<string> Day_Table = {
        "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat."
    };

    ostream& operator<<(ostream& os, const Day& day);

    Day int_to_Day(int n);

    // ----------------------------------------------------------

    enum class Month {
        Jan=1, Feb, Mar, Apr, May, Jun,
        Jul, Aug, Sep, Oct, Nov, Dec
    };

    const vector<string> Month_Table = {
        "",
        "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
        "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
    };

    ostream& operator<<(ostream& os, const Month& month);

    Month int_to_Month(int n);

    // ----------------------------------------------------------

    class Date {
    public:
        Date();
        Date(long int n);

        int year() const;
        Month month() const;
        int day() const;

        void sync();
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        long int days {0};
        bool synced {false};
        int _year {1970};
        int _month {1};
        int _day {1};
    };


    ostream& operator<<(ostream& os, const Date& d);

    bool leapyear(int year);
}
