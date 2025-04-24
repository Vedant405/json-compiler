#include <iostream>
#include "json_lexer.h"
#include "json_parser.cpp"
#include "json_semantic.cpp"
#include "json_ir.h" // Use only the header
#include "json_bytecode.h"

using namespace std;

int main(int argc, char* argv[]) {
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
    ir->generateIntermediateCode(cout);  // Pretty-printed JSON format

    cout << "\nGenerating Bytecode...\n";
    BytecodeGenerator::generate(ast, cout);

    return 0;
}
