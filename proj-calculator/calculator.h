#include "token.h"
#include <string>
#include <vector>

using namespace std;


const string prompt = "> ";
const string result = "= ";


struct Variable {
    string name;
    double value;
    bool constant;
};


class Symbol_table {
    public:
        Symbol_table() {};

        double get(string var_name);
        void set(string var_name, double var_val);
        bool is_declared(string var_name);
        double declare(
                string var_name, double var_val, bool constant);

    private:
        vector<Variable> var_table;
};


void calculate(Token_stream& ts);

double expression(Token_stream& ts);
