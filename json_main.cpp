#include <iostream>
#include "json_lexer.h"
#include "json_parser.cpp"
#include "json_semantic.cpp"
#include "json_ir.h" // Use only the header file

using namespace std;

int main(int argc, char* argv[]) {
    // Check if a filename was provided as a command-line argument.
    // If not, default to "wrong.json"
    string filename = (argc > 1) ? argv[1] : "wrong.json";
    
    string jsonInput = readFile(filename);

    Lexer lexer(jsonInput);
    vector<Token> tokens = lexer.tokenize();

    cout << "Tokens:\n";
    bool hasLexicalError = false;

    for (const Token& token : tokens) {
        token.print();
        if (token.type == TokenType::ERROR) {
            cerr << "Lexical Error: " << token.value 
                 << " at line " << token.line << ", column " << token.column << endl;
            hasLexicalError = true;
        }
    }

    if (hasLexicalError) {
        cerr << "Lexical analysis failed. Aborting parsing and IR generation.\n";
        return 1;
    }

    Parser parser(tokens);
    shared_ptr<ASTNode> ast = parser.parse();

    if (!ast) {
        cerr << "Parsing failed. Aborting semantic analysis and IR generation.\n";
        return 1;
    }

    cout << "\nGenerated AST:\n";
    ast->print();

    SemanticAnalyzer analyzer;
    shared_ptr<IRSchema> ir = analyzer.analyze(ast);

    if (!ir) {
        cerr << "Semantic errors detected. Skipping IR generation.\n";
        return 1;
    }

    cout << "\nGenerating Intermediate Representation (IR)...\n";
    cout << "IR Type: " << ir->type << "\nProperties: ";
    for (const auto& prop : ir->properties) {
        cout << prop << " ";
    }
    cout << endl;

    return 0;
}

