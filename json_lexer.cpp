#include "json_lexer.h"

// Constructor
Lexer::Lexer(const string& input) : input(input), pos(0), line(1), column(1) {
    currentChar = (pos < input.size()) ? input[pos] : '\0';
}

void Lexer::advance() {
    if (pos < input.size()) {
        if (currentChar == '\n') {
            line++;
            column = 0;
        }
        pos++;
        column++;
        currentChar = (pos < input.size()) ? input[pos] : '\0';
    }
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar)) advance();
}

Token Lexer::parseString() {
    string result;
    int startColumn = column;
    advance(); // Skip opening quote

    while (currentChar != '"' && currentChar != '\0') {
        if (currentChar == '\n') {
            return Token(TokenType::ERROR, "Unterminated string (new line encountered)", line, startColumn);
        }
        result += currentChar;
        advance();
    }

    if (currentChar == '"') {
        advance(); // Skip closing quote
        return Token(TokenType::STRING, result, line, startColumn);
    } else {
        return Token(TokenType::ERROR, "Unterminated string (missing closing quote)", line, startColumn);
    }
}

Token Lexer::parseNumber() {
    string result;
    int startColumn = column;
    bool hasDecimal = false;
    bool hasExponent = false;

    while (isdigit(currentChar) || currentChar == '.' || currentChar == '-' || currentChar == 'e' || currentChar == 'E') {
        if (currentChar == '.') {
            if (hasDecimal) return Token(TokenType::ERROR, "Invalid number format: multiple decimal points", line, startColumn);
            hasDecimal = true;
        }
        if (currentChar == 'e' || currentChar == 'E') {
            if (hasExponent) return Token(TokenType::ERROR, "Invalid number format: multiple exponents", line, startColumn);
            hasExponent = true;
        }
        result += currentChar;
        advance();
    }

    return Token(TokenType::NUMBER, result, line, startColumn);
}

Token Lexer::parseKeyword() {
    string result;
    int startColumn = column;

    while (isalpha(currentChar)) {
        result += currentChar;
        advance();
    }

    if (result == "true" || result == "false") {
        return Token(TokenType::BOOLEAN, result, line, startColumn);
    } else if (result == "null") {
        return Token(TokenType::NUL, result, line, startColumn);
    } else {
        return Token(TokenType::ERROR, "Unknown keyword: " + result, line, startColumn);
    }
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    bool hasLexicalError = false;

    while (currentChar != '\0') {
        skipWhitespace();

        if (currentChar == '{') { tokens.emplace_back(TokenType::LEFT_BRACE, "{", line, column); advance(); }
        else if (currentChar == '}') { tokens.emplace_back(TokenType::RIGHT_BRACE, "}", line, column); advance(); }
        else if (currentChar == '[') { tokens.emplace_back(TokenType::LEFT_BRACKET, "[", line, column); advance(); }
        else if (currentChar == ']') { tokens.emplace_back(TokenType::RIGHT_BRACKET, "]", line, column); advance(); }
        else if (currentChar == ':') { tokens.emplace_back(TokenType::COLON, ":", line, column); advance(); }
        else if (currentChar == ',') { tokens.emplace_back(TokenType::COMMA, ",", line, column); advance(); }
        else if (currentChar == '"') { 
            Token token = parseString();
            if (token.type == TokenType::ERROR) hasLexicalError = true;
            tokens.push_back(token);
        }
        else if (isdigit(currentChar) || currentChar == '-') { 
            Token token = parseNumber();
            if (token.type == TokenType::ERROR) hasLexicalError = true;
            tokens.push_back(token);
        }
        else if (isalpha(currentChar)) { 
            Token token = parseKeyword();
            if (token.type == TokenType::ERROR) hasLexicalError = true;
            tokens.push_back(token);
        }
        else if (currentChar == '\0') { 
            break; 
        }
        else {
            // Invalid character handling
            string invalidToken;
            int startColumn = column;
            while (!isspace(currentChar) && currentChar != ',' && currentChar != ':' && currentChar != '}' && currentChar != ']') {
                invalidToken += currentChar;
                advance();
            }
            tokens.emplace_back(TokenType::ERROR, "Invalid token: " + invalidToken, line, startColumn);
            cerr << "Lexical Error: Invalid token '" << invalidToken << "' at line " << line << ", column " << startColumn << endl;
            hasLexicalError = true;
        }
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "EOF", line, column);

    if (hasLexicalError) {
        cerr << "Lexical analysis failed due to errors. Parsing will be skipped.\n";
    }

    return tokens;
}

// Read JSON from a file
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

