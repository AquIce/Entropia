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

            class Statement {
                public:
                    virtual std::string pretty_print(int indent = 0) {
						return std::string(indent, '\t') + "Statement";
					}
					virtual std::string type_id() {
						return "Statement";
					}
            };

            class Program: public Statement {
                public:
                    enum NodeType type = NodeType::program;
                    std::vector<ent::front::ast::Statement*> body;
                    Program(std::vector<ent::front::ast::Statement*> body) {
						this->body = body;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						std::string pretty = std::string(indent, '\t') + "Program(\n";
						for(int i = 0; i < this->body.size(); i++) {
							pretty += std::string(indent, '\t') + this->body[i]->pretty_print(indent + 1) + "\n";
						}
						pretty += std::string(indent, '\t') + ")";
						return pretty;
					}
					virtual std::string type_id() override {
						return "Program";
					}
            };

            class Expression: public Statement {
				public:
					virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "Expression";
					}
					virtual std::string type_id() override {
						return "Expression";
					}
			};

            class NumericExpression: public Expression {
                public:
                    enum NodeType type = NodeType::numericExpression;
                    float value;
                    NumericExpression(float value) {
						this->value = value;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "NumericExpression(" + std::to_string(this->value) + ")";
					}
					virtual std::string type_id() override {
						return "NumericExpression";
					}
            };

            class BinaryExpression: public Expression {
                public:
                    enum NodeType type = NodeType::binaryExpression;
                    ent::front::ast::Expression* left;
                    ent::front::ast::Expression* right;
                    std::string operator_symbol;
                    BinaryExpression(ent::front::ast::Expression* left, std::string operator_symbol, ent::front::ast::Expression* right) {
						this->left = left;
						this->operator_symbol = operator_symbol;
						this->right = right;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "BinaryExpression(\n" + this->left->pretty_print(indent + 1) + "\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->right->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
					}
					virtual std::string type_id() override {
						return "BinaryExpression";
					}
            };
        }
    }
}

#endif