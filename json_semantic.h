#ifndef JSON_SEMANTIC_H
#define JSON_SEMANTIC_H

#include <memory>
#include <string>
#include "json_ast.h"

using namespace std;

class SemanticAnalyzer {
public:
    void analyze(shared_ptr<ASTNode> root);

private:
    void checkNode(shared_ptr<ASTNode> node, const string& expectedType);
    void checkObject(shared_ptr<ASTObject> obj);
    void checkArray(shared_ptr<ASTArray> arr);
    void checkValue(shared_ptr<ASTValue> val, const string& expectedType);
    string detectType(shared_ptr<ASTNode> node);
};

// Function to check if a string is a valid number
bool isNumber(const string& str);

#endif // JSON_SEMANTIC_H

