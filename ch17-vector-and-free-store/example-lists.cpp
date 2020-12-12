#include <iostream>
#include <string>

using namespace std;


struct Link {
    string value;
    Link* prev;
    Link* succ;

    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value {v}, prev {p}, succ {s} {}
};

Link* insert(Link* p, Link* n) {    // insert n before p
    if (n == nullptr) return p;
    if (p == nullptr) return n;
    n->succ = p;
    if (p->prev)
        p->prev->succ = n;
    n->prev = p->prev;
    p->prev = n;

    return n;
}

Link* add(Link* p, Link* n) {
    // exercise 11
}

Link* erase(Link* p) {  // remove *p from list; return p's successor
    if (p == nullptr) return nullptr;
    if (p->succ)
        p->succ->prev = p->prev;
    if (p->prev)
        p->prev->succ = p->succ;
    return p->succ;
}

Link* find(Link* p, const string& s) {
    while (p) {
        if (p->value == s)
            return p;
        p = p->succ;
    }
    return nullptr;
}

Link* advance(Link* p, int n) {
    if (p == nullptr) return nullptr;
    if (n > 0) {
        while (n--) {
            if (p->succ == nullptr)
                return nullptr;
            p = p->succ;
        }
    }
    else if (n < 0) {
        while (n++) {
            if (p->prev == nullptr)
                return nullptr;
            p = p->prev;
        }
    }
    return p;
}

void print_all(Link* p) {
    cout << "{";
    while (p) {
        cout << p->value;
        if (p = p->succ)
            cout << ",";
    }
    cout << "}";
}

Link* make_list_v2() {
    Link* norse_gods = new Link {"Thor"};
    norse_gods = insert(norse_gods, new Link {"Odin"});
    norse_gods = insert(norse_gods, new Link {"Freia"});

    return norse_gods;
}

Link* make_list_v1() {
    Link* norse_gods = new Link {"Thor"};

    norse_gods = new Link {"Odin", nullptr, norse_gods};
    norse_gods->succ->prev = norse_gods;

    norse_gods = new Link {"Freia", nullptr, norse_gods};
    norse_gods->succ->prev = norse_gods;

    return norse_gods;
}

int main() {
    Link* norse_gods = new Link {"Thor"};
    norse_gods = insert(norse_gods, new Link {"Odin"});
    norse_gods = insert(norse_gods, new Link {"Zeus"});
    norse_gods = insert(norse_gods, new Link {"Freia"});

    Link* greek_gods = new Link {"Hera"};
    greek_gods = insert(greek_gods, new Link {"Athena"});
    greek_gods = insert(greek_gods, new Link {"Mars"});
    greek_gods = insert(greek_gods, new Link {"Poseidon"});

    Link* p = find(greek_gods, "Mars");
    if (p)
        p->value = "Ares";

    Link* p2 = find(norse_gods, "Zeus");
    if (p2) {
        if (p2 == norse_gods)
            norse_gods = p2->succ;
        erase(p2);
        greek_gods = insert(greek_gods, p2);
    }

    print_all(norse_gods);
    cout << "\n";

    print_all(greek_gods);
    cout << "\n";
}
