#ifndef JSON_LEXER_H
#define JSON_LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

// Token Types
enum class TokenType {
    LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,
    COLON, COMMA, STRING, NUMBER, BOOLEAN, NUL, END_OF_FILE, ERROR
};

// Token Structure
struct Token {
    TokenType type;
    string value;
    int line, column;

    Token(TokenType type, string value, int line, int column)
        : type(type), value(value), line(line), column(column) {}

    void print() const {  // Marked as const to avoid compilation error
        cout << "Token(" << value << ", Line: " << line << ", Column: " << column << ")\n";
    }
};

// Lexer Class
class Lexer {
private:
    string input;
    int pos = 0, line = 1, column = 0;
    char currentChar;

    void advance();
    void skipWhitespace();
    Token parseString();
    Token parseNumber();
    Token parseKeyword();

public:
    Lexer(const string& input);
    vector<Token> tokenize();
};

// Function prototype for reading files
string readFile(const string& filename);

#endif // JSON_LEXER_H

