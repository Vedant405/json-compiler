#ifndef JSON_BYTECODE_H
#define JSON_BYTECODE_H

#include <iostream>
#include <memory>
#include "json_ast.h"

class BytecodeGenerator {
public:
    static void generate(std::shared_ptr<ASTNode> node, std::ostream& out, const std::string& key = "");
};

#endif // JSON_BYTECODE_H

