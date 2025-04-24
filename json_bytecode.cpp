#include "json_ast.h"
#include "json_bytecode.h"  // Include header with class declaration
#include <iostream>
#include <memory>
#include <string>
#include <cctype>

using namespace std;

void BytecodeGenerator::generate(shared_ptr<ASTNode> node, ostream& out, const string& key) {
    if (auto obj = dynamic_pointer_cast<ASTObject>(node)) {
        if (key.empty()) out << "START_OBJECT\n";
        else out << "  START_OBJECT \"" << key << "\"\n";

        for (const auto& prop : obj->properties) {
            generate(prop.second, out, prop.first);
        }

        out << "END_OBJECT\n";
    } else if (auto arr = dynamic_pointer_cast<ASTArray>(node)) {
        out << "  START_ARRAY \"" << key << "\"\n";
        for (const auto& el : arr->elements) {
            if (auto num = dynamic_pointer_cast<ASTNumber>(el)) {
                out << "    PUSH_NUMBER " << num->value << "\n";
            } else if (auto str = dynamic_pointer_cast<ASTString>(el)) {
                out << "    PUSH_STRING " << str->value << "\n";
            } else if (auto b = dynamic_pointer_cast<ASTBool>(el)) {
                out << "    PUSH_BOOL " << b->value << "\n";
            } else if (auto n = dynamic_pointer_cast<ASTNull>(el)) {
                out << "    PUSH_NULL\n";
            } else {
                generate(el, out); // Nested array or object
            }
        }
        out << "  END_ARRAY\n";
    } else if (auto val = dynamic_pointer_cast<ASTValue>(node)) {
        const string& v = val->value;

        if (v == "true" || v == "false") {
            out << "  SET_BOOL   \"" << key << "\" " << v << "\n";
        } else if (v == "null") {
            out << "  SET_NULL   \"" << key << "\"\n";
        } else if (!v.empty() && (isdigit(v[0]) || v[0] == '-')) {
            out << "  SET_NUMBER \"" << key << "\" " << v << "\n";
        } else if (v.front() == '"' && v.back() == '"') {
            out << "  SET_STRING \"" << key << "\" " << v << "\n";
        } else {
            out << "  SET_STRING \"" << key << "\" \"" << v << "\"\n";
        }
    }
}

