#include "json_ast.h"
#include "json_ir.h"
#include <iostream>
#include <memory>
#include <set>

using namespace std;

class SemanticAnalyzer {
    bool semanticError = false; // Track semantic errors

public:
    shared_ptr<IRSchema> analyze(shared_ptr<ASTNode> root) {
        semanticError = false;

        if (!root) {
            cerr << "Semantic Error: AST is empty or invalid." << endl;
            return nullptr;
        }

        cout << "\nPerforming Semantic Analysis...\n";
        checkNode(root);

        if (semanticError) {
            cerr << "Semantic analysis failed. IR generation skipped.\n";
            return nullptr;
        }

        return generateIR(root);
    }

private:
    void checkNode(shared_ptr<ASTNode> node) {
        if (auto obj = dynamic_pointer_cast<ASTObject>(node)) {
            checkObject(obj);
        } else if (auto arr = dynamic_pointer_cast<ASTArray>(node)) {
            checkArray(arr);
        } else if (auto val = dynamic_pointer_cast<ASTValue>(node)) {
            checkValue(val);
        }
    }

    void checkObject(shared_ptr<ASTObject> obj) {
        set<string> keys;
        for (const auto& prop : obj->properties) {
            if (keys.count(prop.first)) {
                cerr << "Semantic Error: Duplicate key '" << prop.first << "' found." << endl;
                semanticError = true;
            }
            keys.insert(prop.first);
            checkNode(prop.second);
        }
    }

    void checkArray(shared_ptr<ASTArray> arr) {
        string firstType = "";
        for (const auto& elem : arr->elements) {
            string elemType = detectType(elem);
            if (firstType.empty()) {
                firstType = elemType;
            } else if (elemType != firstType) {
                cerr << "Semantic Error: Inconsistent types in array. Expected all '" << firstType
                     << "', but found '" << elemType << "'." << endl;
                semanticError = true;
            }
            checkNode(elem);
        }
    }

    void checkValue(shared_ptr<ASTValue> val) {
        if (val->value == "null") {
            cerr << "Warning: Null value encountered." << endl;
        }
    }

    string detectType(shared_ptr<ASTNode> node) {
        if (auto val = dynamic_pointer_cast<ASTValue>(node)) {
            if (val->value == "true" || val->value == "false") return "boolean";
            if (isNumber(val->value)) return "number";
            return "string";
        }
        if (dynamic_pointer_cast<ASTObject>(node)) return "object";
        if (dynamic_pointer_cast<ASTArray>(node)) return "array";
        return "unknown";
    }

    bool isNumber(const string& str) {
        return !str.empty() && str.find_first_not_of("0123456789.-") == string::npos;
    }

    shared_ptr<IRSchema> generateIR(shared_ptr<ASTNode> root) {
        return IRGenerator::generate(root);
    }
};

