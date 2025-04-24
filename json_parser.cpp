#include <iostream>
#include <vector>
#include <memory>
#include "json_lexer.h"
#include "json_ast.h"

using namespace std;

// JSON Parser
class Parser {
private:
    vector<Token> tokens;
    int index = 0;
    bool hasError = false; // Track if any syntax error occurred

    Token currentToken() {
        return (index < tokens.size()) ? tokens[index] : Token(TokenType::END_OF_FILE, "EOF", -1, -1);
    }

    void advance() {
        if (index < tokens.size()) index++;
    }

    void error(const string& message) {
        Token t = currentToken();
        cerr << "Syntax Error: " << message << " at Line " << t.line << ", Column " << t.column << endl;
        hasError = true; // Mark error occurred
        advance();       // Attempt recovery
    }

    shared_ptr<ASTNode> parseValue() {
        Token t = currentToken();

        if (t.type == TokenType::LEFT_BRACE) {
            return parseObject();
        } else if (t.type == TokenType::LEFT_BRACKET) {
            return parseArray();
        } else if (t.type == TokenType::STRING || t.type == TokenType::NUMBER ||
                   t.type == TokenType::BOOLEAN || t.type == TokenType::NUL) {
            advance();
            return make_shared<ASTValue>(t.value);
        }

        error("Invalid JSON value");
        return nullptr;
    }

    shared_ptr<ASTNode> parseObject() {
        advance(); // Consume '{'
        auto obj = make_shared<ASTObject>();

        while (currentToken().type != TokenType::RIGHT_BRACE && currentToken().type != TokenType::END_OF_FILE) {
            if (currentToken().type != TokenType::STRING) {
                error("Expected a string key in object");
                break;
            }

            string key = currentToken().value;
            advance(); // Consume key

            if (currentToken().type != TokenType::COLON) {
                error("Expected ':' after key in object");
                break;
            }
            advance(); // Consume ':'

            auto value = parseValue();
            if (value) {
                obj->properties.emplace_back(key, value);
            }

            if (currentToken().type == TokenType::COMMA) {
                advance(); // Consume ',' and continue
            } else if (currentToken().type != TokenType::RIGHT_BRACE) {
                error("Expected ',' or '}' in object");
                break;
            }
        }

        if (currentToken().type == TokenType::RIGHT_BRACE) {
            advance(); // Consume '}'
        } else {
            error("Expected '}' to close object");
        }

        return obj;
    }

    shared_ptr<ASTNode> parseArray() {
        advance(); // Consume '['
        auto arr = make_shared<ASTArray>();

        while (currentToken().type != TokenType::RIGHT_BRACKET && currentToken().type != TokenType::END_OF_FILE) {
            auto value = parseValue();
            if (value) {
                arr->elements.push_back(value);
            }

            if (currentToken().type == TokenType::COMMA) {
                advance(); // Consume ',' and continue
            } else if (currentToken().type != TokenType::RIGHT_BRACKET) {
                error("Expected ',' or ']' in array");
                break;
            }
        }

        if (currentToken().type == TokenType::RIGHT_BRACKET) {
            advance(); // Consume ']'
        } else {
            error("Expected ']' to close array");
        }

        return arr;
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}

    shared_ptr<ASTNode> parse() {
        auto root = parseValue();

        if (hasError || !root) {
            cerr << "Parsing failed due to syntax errors.\n";
            return nullptr;
        }

        return root;
    }
};

