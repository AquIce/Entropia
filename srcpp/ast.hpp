#ifndef __ENT_FRONT_AST__
#define __ENT_FRONT_AST__

#include <string>
#include <vector>
#include <memory>

namespace ent {
    namespace front {
        namespace ast {
            enum NodeType {
                program,
                binaryExpression,
                numericExpression,
            };

            std::string node_type_name(enum NodeType type);

            class Statement {
                public:
                    virtual std::string pretty_print();
            };

            class Program: public Statement {
                public:
                    enum NodeType type = NodeType::program;
                    std::vector<std::unique_ptr<ent::front::ast::Statement>> body;
                    Program(std::vector<std::unique_ptr<ent::front::ast::Statement>> body);
                    virtual std::string pretty_print() override;
            };

            class Expression: public Statement {};

            class NumericExpression: public Expression {
                public:
                    enum NodeType type = NodeType::numericExpression;
                    float value;
                    NumericExpression(float value);
                    virtual std::string pretty_print() override;
            };

            class BinaryExpression: public Expression {
                public:
                    enum NodeType type = NodeType::binaryExpression;
                    ent::front::ast::Expression left;
                    ent::front::ast::Expression right;
                    std::string operator_symbol;
                    BinaryExpression(ent::front::ast::Expression left, ent::front::ast::Expression right, std::string operator_symbol);
                    virtual std::string pretty_print() override;
            };
        }
    }
}

#endif