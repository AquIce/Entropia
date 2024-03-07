#include "parser.hpp"

ent::front::ast::Program ent::front::parse(std::vector<ent::type::token> tokens) {
    ent::front::ast::Program program = ent::front::ast::Program(
        std::vector<std::unique_ptr<ent::front::ast::Statement>>()
    );
    program.body.push_back(
        std::make_unique<ent::front::ast::BinaryExpression>(
            ent::front::ast::NumericExpression(12), ent::front::ast::NumericExpression(34), "+"
        )
    );
    return program;
}