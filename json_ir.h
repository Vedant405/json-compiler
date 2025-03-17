#ifndef JSON_IR_H
#define JSON_IR_H

#include <memory>
#include <vector>
#include <string>
#include "json_ast.h"  // Ensure ASTNode is recognized

using namespace std;

// Intermediate Representation Schema
class IRSchema {
public:
    string type;
    vector<string> properties;
    
    IRSchema(string t) : type(t) {}
    void addProperty(const string& prop) { properties.push_back(prop); }
};

// IR Generator Class
class IRGenerator {
public:
    static shared_ptr<IRSchema> generate(shared_ptr<ASTNode> root);
};

#endif // JSON_IR_H

