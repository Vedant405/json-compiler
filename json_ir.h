#ifndef JSON_IR_H
#define JSON_IR_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "json_ast.h"  // Ensure ASTNode is recognized

using namespace std;

// Intermediate Representation Schema
class IRSchema {
public:
    string type;  // e.g., "object"
    unordered_map<string, string> properties;  // property name -> type

    IRSchema(string t) : type(t) {}

    void addProperty(const string& name, const string& datatype) {
        properties[name] = datatype;
    }

    // Outputs the IR in JSON format
    void generateIntermediateCode(ostream& out) const {
        out << "{\n";
        out << "  \"type\": \"" << type << "\",\n";
        out << "  \"properties\": {\n";

        int count = 0;
        for (auto it = properties.begin(); it != properties.end(); ++it) {
            out << "    \"" << it->first << "\": \"" << it->second << "\"";
            if (++count < properties.size()) out << ",";
            out << "\n";
        }

        out << "  }\n";
        out << "}\n";
    }
};

// IR Generator Class
class IRGenerator {
public:
    static shared_ptr<IRSchema> generate(shared_ptr<ASTNode> root);
};

#endif // JSON_IR_H

