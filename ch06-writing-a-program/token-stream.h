class Token {
    public:
        Token();
        Token(char c);
        Token(char c, double v);
        char kind;
        double value;
};

class Token_stream {
    public:
        Token_stream();
        Token get();
        void putback(Token t);
    private:
        bool full {false};
        Token buffer;
};
