#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <memory>
#include <vector>
#include "json_ast.h"
#include "json_lexer.h"

using namespace std;

class Parser {
public:
    explicit Parser(const vector<Token>& tokens); // Constructor declaration
    shared_ptr<ASTNode> parse(); // Method declaration

private:
    vector<Token> tokens;
    size_t currentIndex;

    shared_ptr<ASTNode> parseValue();
    shared_ptr<ASTObject> parseObject();
    shared_ptr<ASTArray> parseArray();
    shared_ptr<ASTValue> parsePrimitive();

    Token peek();
    Token advance();
    bool match(TokenType type);
    void error(const string& message);
};

#endif // JSON_PARSER_H

