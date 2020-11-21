#include <iostream>

using namespace std;

int main()
{
    cout << "Enter the name of the person you want to write to: ";
    string first_name = "???";
    cin >> first_name;

    cout << "Enter the age of the recipient: ";
    int age = 0;
    cin >> age;
    if (age <= 0 || 110 <= age) {
        cerr << "you're kidding!\n";
        exit(1);
    }

    cout << "Enter the name of another friend: ";
    string friend_name = "???";
    cin >> friend_name;

    cout << "Enter 'm' or 'f' if the friend is male or female, respectively: ";
    char friend_sex = '0';
    cin >> friend_sex;

    cout << "----------------------------------------\n";
    cout << "Dear " << first_name << ",\n\n";
    cout << "    " << "How are you?" << " I'm fine. I miss you." << '\n';

    cout << "Have you seen " << friend_name << " lately?\n";

    cout << "If you see " << friend_name << ", please ask ";
    if (friend_sex == 'm')
        cout << "him";
    else if (friend_sex == 'f')
        cout << "her";
    else
        cout << "them";
    cout << " to call me.\n";

    cout << "I hear you just had a birthday"
         << " and you are " << age << " years old.\n";
    if (age < 12)
        cout << "Next year you will be " << age + 1 << ".\n";
    if (age == 17)
        cout << "Next year you will be able to vote.\n";
    if (age >= 70)
        cout << "I hope you are enjoying retirement.\n";

    cout << "\n\n" << "                    "
         << "Yours sincerely,\n";
    cout << "                               "
         << "Peter\n";

    cout << "----------------------------------------\n";
    return 0;
}
