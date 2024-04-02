#ifndef __ENT_FRONT_AST__
#define __ENT_FRONT_AST__

#include <string>
#include <vector>
#include <memory>

#include "../types/numbers.hpp"

namespace ent {
    namespace front {
        namespace ast {
            enum NodeType {
                program,
				declaration,
                binaryExpression,
                i8Expression,
				i16Expression,
				i32Expression,
				i64Expression,
				u8Expression,
				u16Expression,
				u32Expression,
				u64Expression,
				f32Expression,
				f64Expression,
				identifier
            };

            class Statement {
			public:
				virtual NodeType get_type() {
					return NodeType::program;
				}
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
					this->type = NodeType::program;
				}
				virtual NodeType get_type() override {
					return NodeType::program;
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

            class Expression: public Statement {};

			class Identifier: public Expression {
			public:
				enum NodeType type = NodeType::identifier;
				std::string name;
				Identifier(std::string name) {
					this->name = name;
					this->type = NodeType::identifier;
				}
				virtual NodeType get_type() override {
					return NodeType::identifier;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "Identifier(" + this->name + ")";
				}
				virtual std::string type_id() override {
					return "Identifier";
				}
			};

            class I8Expression: public Expression {
			public:
				enum NodeType type = NodeType::i8Expression;
				i8 value;
				I8Expression(i8 value = 0) {
					this->value = value;
					this->type = NodeType::i8Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::i8Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "I8Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I8Expression";
				}
            };

			class I16Expression: public Expression {
			public:
				enum NodeType type = NodeType::i16Expression;
				i16 value;
				I16Expression(i16 value = 0) {
					this->value = value;
					this->type = NodeType::i16Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::i16Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "I16Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I16Expression";
				}
			};

			class I32Expression: public Expression {
			public:
				enum NodeType type = NodeType::i32Expression;
				i32 value;
				I32Expression(i32 value = 0) {
					this->value = value;
					this->type = NodeType::i32Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::i32Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "I32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I32Expression";
				}
			};

			class I64Expression: public Expression {
			public:
				enum NodeType type = NodeType::i64Expression;
				i64 value;
				I64Expression(i64 value = 0) {
					this->value = value;
					this->type = NodeType::i64Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::i64Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "I64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I64Expression";
				}
			};

			class U8Expression: public Expression {
			public:
				enum NodeType type = NodeType::u8Expression;
				u8 value;
				U8Expression(u8 value = 0) {
					this->value = value;
					this->type = NodeType::u8Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::u8Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "U8Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U8Expression";
				}
			};

			class U16Expression: public Expression {
			public:
				enum NodeType type = NodeType::u16Expression;
				u16 value;
				U16Expression(u16 value = 0) {
					this->value = value;
					this->type = NodeType::u16Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::u16Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "U16Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U16Expression";
				}
			};

			class U32Expression: public Expression {
			public:
				enum NodeType type = NodeType::u32Expression;
				u32 value;
				U32Expression(u32 value = 0) {
					this->value = value;
					this->type = NodeType::u32Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::u32Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "U32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U32Expression";
				}
			};

			class U64Expression: public Expression {
			public:
				enum NodeType type = NodeType::u64Expression;
				u64 value;
				U64Expression(u64 value = 0) {
					this->value = value;
					this->type = NodeType::u64Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::u64Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "U64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U64Expression";
				}
			};

			class F32Expression: public Expression {
			public:
				enum NodeType type = NodeType::f32Expression;
				float value;
				F32Expression(float value = 0.0f) {
					this->value = value;
					this->type = NodeType::f32Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::f32Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "F32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "F32Expression";
				}
			};

			class F64Expression: public Expression {
			public:
				enum NodeType type = NodeType::f64Expression;
				double value;
				F64Expression(double value = 0.0) {
					this->value = value;
					this->type = NodeType::f64Expression;
				}
				virtual NodeType get_type() override {
					return NodeType::f64Expression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "F64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "F64Expression";
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
						this->type = NodeType::binaryExpression;
					}
					virtual NodeType get_type() override {
						return NodeType::binaryExpression;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "BinaryExpression(\n" + this->left->pretty_print(indent + 1) + "\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->right->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
					}
					virtual std::string type_id() override {
						return "BinaryExpression";
					}
            };

			class Declaration: public Statement {
			public:
				enum NodeType type = NodeType::declaration;
				Identifier* identifier;
				ent::front::ast::Expression* value;
				Declaration(Identifier* identifier, ent::front::ast::Expression* value) {
					this->identifier = identifier;
					this->value = value;
					this->type = NodeType::declaration;
				}
				virtual NodeType get_type() override {
					return NodeType::declaration;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "Declaration(" + this->identifier->name + ",\n" + this->value->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "Declaration";
				}
			
			};
        }
    }
}

#endif