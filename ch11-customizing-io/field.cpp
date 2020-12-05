#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cout << 123456
         << '|' << setw(4) << 123456
         << '|' << setw(8) << 123456
         << '|' << 123456
         << '|' << "\n\n";

    cout << 12345
         << '|' << setw(4) << 12345
         << '|' << setw(8) << 12345
         << '|' << 12345
         << '|' << '\n';
    cout << 1234.5
         << '|' << setw(4) << 1234.5
         << '|' << setw(8) << 1234.5
         << '|' << 1234.5
         << '|' << '\n';
    cout << "asdfg"
         << '|' << setw(4) << "asdfg"
         << '|' << setw(8) << "asdfg"
         << '|' << "asdfg"
         << '|' << "\n\n";

    vector<string> last_names {
        "Ichiro", "Jiro", "Hanako",
    };
    vector<string> first_names {
        "Yamada", "Suzuki", "Tanaka",
    };
    vector<string> telephones {
        "03-1245-6789", "06-5432-9876", "092-1345-8765",
    };
    vector<string> emails {
        "y.1ro@foo.com", "suzujiro@bar.com", "hanako@baz.com",
    };

    cout << "+------------+------------+----------------+--------------------+\n"
         << "| " << left << setw(11) << "Last name"
         << "| " << left << setw(11) << "First name"
         << "| " << left << setw(15) << "Telephone"
         << "| " << left << setw(19) << "Email Address"
         << "|\n"
         << "+------------+------------+----------------+--------------------+\n";
    for (int i = 0; i < last_names.size(); ++i)
        cout << "| " << left << setw(11) << last_names[i]
             << "| " << left << setw(11) << first_names[i]
             << "| " << left << setw(15) << telephones[i]
             << "| " << left << setw(19) << emails[i]
             << "|\n";
    cout << "+------------+------------+----------------+--------------------+\n\n";
}
