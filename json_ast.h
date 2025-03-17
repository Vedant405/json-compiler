#ifndef JSON_AST_H
#define JSON_AST_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <set>

using namespace std;

// Abstract Syntax Tree (AST) Node
struct ASTNode {
    virtual void print(int indent = 0) const = 0;
    virtual ~ASTNode() {}
};

// AST Node for JSON values
struct ASTValue : ASTNode {
    string value;
    ASTValue(string val) : value(val) {}
    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Value: " << value << "\n";
    }
};

// AST Node for JSON Objects
struct ASTObject : ASTNode {
    vector<pair<string, shared_ptr<ASTNode>>> properties;
    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Object: {\n";
        for (const auto& prop : properties) {
            cout << string(indent + 2, ' ') << prop.first << ": ";
            prop.second->print(indent + 2);
        }
        cout << string(indent, ' ') << "}\n";
    }
};

// AST Node for JSON Arrays
struct ASTArray : ASTNode {
    vector<shared_ptr<ASTNode>> elements;
    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Array: [\n";
        for (const auto& elem : elements) {
            elem->print(indent + 2);
        }
        cout << string(indent, ' ') << "]\n";
    }
};

#endif // JSON_AST_H

