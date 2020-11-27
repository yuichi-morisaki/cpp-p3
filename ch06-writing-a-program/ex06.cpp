#include <iostream>
#include <stdexcept>

using namespace std;

void error(string message);
bool is_valid_sentence();

int main()
try {
    cout << ">> ";
    while (true) {
        char c;
        cin >> c;
        if (c == 'q')
            break;
        cin.putback(c);

        bool valid = is_valid_sentence();
        if (valid)
            cout << "OK.\n\n>> ";
        else {
            cout << "Not OK.\n\n>> ";
            string w;
            while (true) {
                cin >> w;
                if (w == ".") break;
            }
        }
    }

    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}


string is_conj_or_next();
string is_noun_or_next();
string is_verb_or_next();

bool is_valid_sentence() {
    string w;
    cin >> w;
    if (w != "the")
        for (int i = w.size() - 1; i >= 0; --i)
            cin.putback(w[i]);
    w = is_noun_or_next();
    if (w != "") {
        cerr << "Noun expected, but we got '" << w << "'\n";
        return false;
    }
    w = is_verb_or_next();
    if (w != "") {
        cerr << "Verb expected, but we got '" << w << "'\n";
        return false;
    }
    w = is_conj_or_next();
    if (w == ".")
        return true;
    if (w != "") {
        cerr << "Conjunction expected, but we got '" << w << "'\n";
        return false;
    }
    return is_valid_sentence();
}

string is_conj_or_next() {
    string w;
    cin >> w;
    if (w == "and" || w == "or" || w == "but")
        return "";
    return w;
}

string is_noun_or_next() {
    string w;
    cin >> w;
    if (w == "birds" || w == "fish" || w == "C++")
        return "";
    return w;
}

string is_verb_or_next() {
    string w;
    cin >> w;
    if (w == "rules" || w == "fly" || w == "swim")
        return "";
    return w;
}

void error(string message) {
    throw runtime_error(message);
}
