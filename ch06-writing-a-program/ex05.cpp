/* English Grammar
 *
 *  Sentence:
 *      Noun Verb
 *      Sentence Conjunction Sentence
 *  Conjunction:
 *      "and"
 *      "or"
 *      "but"
 *  Noun:
 *      "birds"
 *      "fish"
 *      "C++"
 *  Verb:
 *      "rules"
 *      "fly"
 *      "swim"
 */

/*  Sentence:
 *      Noun Verb
 *      Sentence Conjunction Sentence
 *  Conjunction:
 *      "and"
 *      "or"
 *      "but"
 *  Noun:
 *      Articled
 *      Nonarticled
 *  Articled:
 *      "the" Nonarticled
 *  Nonarticled:
 *      "birds"
 *      "fish"
 *      "C++"
 *  Verb:
 *      "rules"
 *      "fly"
 *      "swim"
 */

#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s) {
    throw runtime_error(s);
}

class Token {
public:
    char kind;
    string word;
    Token()
        : kind(' '), word("") { }
    Token(char k, string w)
        : kind(k), word(w) { }
};

class Token_stream {
public:
    Token get();
    void putback(Token);
    Token_stream()
        : full(false), buffer() { }
private:
    bool full;
    Token buffer;
};

void Token_stream::putback(Token t) {
    if (full)
        error("putback(): full buffer");
    full = true;
    buffer = t;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    Token token;
    string word;
    cin >> word;
    if (word == "and" || word == "or" || word == "but")
        token = Token('c', word);
    else if (word == "the" || word == "The")
        token = Token('a', word);
    else if (word == "birds" || word == "fish" || word == "C++")
        token = Token('n', word);
    else if (word == "rules" || word == "fly" || word == "swim")
        token = Token('v', word);
    else if (word == ".")
        token = Token('.', word);
    else
        error("Unknown word: '" + word + "'");

    return token;
}

Token_stream ts;

bool verb() {
    Token t = ts.get();
    if (t.kind == 'v')
        return true;
    ts.putback(t);
    return false;
}

bool non_articled() {
    Token t = ts.get();
    if (t.kind == 'n')
        return true;
    ts.putback(t);
    return false;
}

bool articled() {
    Token t = ts.get();
    if (t.kind == 'a') {
        if (non_articled())
            return true;
        t = ts.get();
        error("Non-articled noun is expected: '" + t.word + "'");
    }
    ts.putback(t);
    return false;
}

bool noun() {
    return non_articled() || articled();
}

bool conj() {
    Token t = ts.get();
    if (t.kind == 'c')
        return true;
    ts.putback(t);
    return false;
}

bool sentence() {
    if (!noun()) {
        Token t = ts.get();
        error("Noun is expected: '" + t.word + "'");
    }
    if (!verb()) {
        Token t = ts.get();
        error("Verb is expected: '" + t.word + "'");
    }
    if (conj())
        return sentence();
    else {
        Token t = ts.get();
        if (t.kind != '.')
            error("Unexpected word: '" + t.word + "'");
        return true;
    }
}

int main()
try {
    cout << ">> ";
    bool result = sentence();
    if (result)
        cout << "This is a valid sentence.\n";

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
