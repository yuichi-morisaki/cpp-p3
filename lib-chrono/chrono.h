#include <iostream>
#include <vector>

using namespace std;


namespace Chrono {

    // ============================================================
    //  'Day' in the week

    enum class Day {
        Sun, Mon, Tue, Wed, Thu, Fri, Sat
    };

    // ------------------------------------------------------------
    //  Helper functions for class 'Day'

    constexpr int DAY_MIN {0};
    constexpr int DAY_MAX {6};

    const vector<string> DAYS {
        "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat."
    };

    Day Day_from_int(int i);
    int int_from_Day(const Day& d);

    ostream& operator<<(ostream& os, const Day& d);

    // ============================================================
    //  'Month'

    enum class Month {
        Jan=1, Feb, Mar, Apr, May, Jun,
        Jul, Aug, Sep, Oct, Nov, Dec
    };

    // ------------------------------------------------------------
    //  Helper functions for class 'Month'

    constexpr int MONTH_MIN {1};
    constexpr int MONTH_MAX {12};

    const vector<string> MONTHS {
        "",
        "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
        "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
    };

    Month Month_from_int(int i);
    int int_from_Month(const Month& m);

    ostream& operator<<(ostream& os, const Month& m);

    // ============================================================
    //  'Date'

    class Date {
        public:
            Date();
            Date(int y, Month m, int d);

            int year() const;
            Month month() const;
            int day() const;

            void add_year(int num_of_years);
            void add_month(int num_of_months);
            void add_day(int num_of_days);

        private:
            long int days {0};  // from Jan. 1st, 1970
            vector<int> getter() const;
    };

    // ------------------------------------------------------------
    //  Helper functions for class 'Date'

    ostream& operator<<(ostream& os, const Date& date);
    istream& operator>>(istream& is, Date& date);

    bool operator==(const Date& x, const Date& y);
    bool operator!=(const Date& x, const Date& y);

    long int days_from_origin(int year, Month month, int day);

    bool leapyear(int year);
    int days_in_month(int year, Month month);

    Day day_of_week(const Date& date);
    Date next_sunday(const Date& date);
    Date next_weekday(const Date& date);
    int week_of_year(int year);

    // ============================================================

}   // END of namespace Chrono
