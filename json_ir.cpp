#include "json_ir.h"
#include "json_parser.h" // Required for AST definitions
#include <cctype>
#include <algorithm>

// Enhanced type inference from ASTValue content
std::string inferType(const std::shared_ptr<ASTNode>& node) {
    if (auto val = std::dynamic_pointer_cast<ASTValue>(node)) {
        const std::string& v = val->value;

        if (v == "true" || v == "false") return "boolean";
        if (v == "null") return "null";

        bool isNumber = !v.empty() && all_of(v.begin(), v.end(), [](char c) {
            return isdigit(c) || c == '.' || c == '-';
        });

        if (isNumber) return "number";

        return "string";
    }

    if (auto arr = std::dynamic_pointer_cast<ASTArray>(node)) {
        if (!arr->elements.empty()) {
            std::string elemType = inferType(arr->elements[0]);
            bool homogeneous = all_of(arr->elements.begin(), arr->elements.end(), [&](const auto& el) {
                return inferType(el) == elemType;
            });
            return "array<" + (homogeneous ? elemType : "mixed") + ">";
        }
        return "array<unknown>";
    }

    if (std::dynamic_pointer_cast<ASTObject>(node)) return "object";

    return "unknown";
}

std::shared_ptr<IRSchema> IRGenerator::generate(std::shared_ptr<ASTNode> root) {
    if (!root) return nullptr;

    auto schema = std::make_shared<IRSchema>("object");

    if (auto obj = std::dynamic_pointer_cast<ASTObject>(root)) {
        for (const auto& prop : obj->properties) {
            std::string type = inferType(prop.second);
            schema->addProperty(prop.first, type);
        }
    }

    return schema;
}

