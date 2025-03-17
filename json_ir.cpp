#include "json_ir.h"

shared_ptr<IRSchema> IRGenerator::generate(shared_ptr<ASTNode> root) {
    if (!root) return nullptr;
    
    auto schema = make_shared<IRSchema>("object");

    if (auto obj = dynamic_pointer_cast<ASTObject>(root)) {
        for (const auto& prop : obj->properties) {
            schema->addProperty(prop.first);
        }
    }

    return schema;
}

