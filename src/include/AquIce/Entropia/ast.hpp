#ifndef __ENT_FRONT_AST__
#define __ENT_FRONT_AST__

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "../types/numbers.hpp"

namespace ent {
    namespace front {
        namespace ast {
            enum NodeType {
				scope,
                program,
				assignation,
				declaration,
				functionDeclaration,
				functionReturn,
                binaryExpression,
				unaryExpression,
				functionCallExpression,
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
				parenthesisExpression,
				booleanExpression,
				charExpression,
				strExpression,
				identifier,
				conditionnalBlock,
				conditionnalStructure,
				matchStructure,
				breakStatement,
				forLoop,
				whileLoop,
            };

			std::vector<enum NodeType> valid_casts_to_type(enum NodeType type) {
				return std::unordered_map<enum NodeType, std::vector<enum NodeType>>({
					{NodeType::i8Expression, std::vector<enum NodeType>({})},
					{NodeType::i16Expression, std::vector<enum NodeType>({
						NodeType::u8Expression,
						NodeType::i8Expression,
					})},
					{NodeType::i32Expression, std::vector<enum NodeType>({
						NodeType::u16Expression,
						NodeType::i16Expression,
					})},
					{NodeType::i64Expression, std::vector<enum NodeType>({
						NodeType::u32Expression,
						NodeType::i32Expression,
					})},
					{NodeType::u8Expression, std::vector<enum NodeType>({})},
					{NodeType::u16Expression, std::vector<enum NodeType>({
						NodeType::u8Expression,
					})},
					{NodeType::u32Expression, std::vector<enum NodeType>({
						NodeType::u16Expression,
					})},
					{NodeType::u64Expression, std::vector<enum NodeType>({
						NodeType::u32Expression,
					})},
					{NodeType::f32Expression, std::vector<enum NodeType>({
						NodeType::u64Expression,
						NodeType::i64Expression,
					})},
					{NodeType::f64Expression, std::vector<enum NodeType>({
						NodeType::f32Expression,
					})},
				})[type];
			}

			bool is_valid_cast(enum NodeType source, enum NodeType dest) {
				if(source == dest) { return true; }
				for(enum NodeType dest_valid_cast : valid_casts_to_type(dest)) {
					if(is_valid_cast(source, dest_valid_cast)) {
						return true;
					}
				}
				for(enum NodeType source_valid_cast : valid_casts_to_type(source)) {
					if(is_valid_cast(dest, source_valid_cast)) {
						return true;
					}
				}
				return false;
			}

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

			class Scope: public Statement {
			public:
				enum NodeType type = NodeType::scope;
				std::vector<std::shared_ptr<Statement>> body;

				Scope(std::vector<std::shared_ptr<Statement>> body) {
					this->body = body;
					this->type = NodeType::scope;
				}
				virtual NodeType get_type() override {
					return NodeType::scope;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "{\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "Scope";
				}
            };

            class Program;

            class Expression: public Statement {};

			class Identifier: public Expression {
			public:
				enum NodeType type = NodeType::identifier;
				std::string name;
				enum NodeType identifierType;// = NodeType::identifier;

				Identifier(std::string name) {
					this->name = name;
					this->type = NodeType::identifier;
				}
				virtual NodeType get_type() override {
					return NodeType::identifier;
				}
				enum NodeType get_identifier_type() {
					return this->identifierType;
				}
				void set_identifier_type(enum NodeType type) {
					this->identifierType = type;
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

			class BooleanExpression: public Expression {
			public:
				enum NodeType type = NodeType::booleanExpression;
				bool value;
				BooleanExpression(bool value = false) {
					this->value = value;
					this->type = NodeType::booleanExpression;
				}
				virtual NodeType get_type() override {
					return NodeType::booleanExpression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "BooleanExpression(" + (this->value ? "true" : "false") + ")";
				}
				virtual std::string type_id() override {
					return "BooleanExpression";
				}
			};

			class CharExpression: public Expression {
			private:
				std::string format_char(char c) {
					try {
						return std::unordered_map<char, std::string>({
							{'\a', "\\a"},
							{'\b', "\\b"},
							{'\f', "\\f"},
							{'\n', "\\n"},
							{'\r', "\\r"},
							{'\t', "\\t"},
							{'\v', "\\v"},
							{'\\', "\\\\"},
							{'\'', "\\'"},
							{'\"', "\\\""},
							{'\?', "\\?"},
							{'\0', "\\0"}
						}).at(this->value);
					} catch(const std::exception& e) {
						return std::string(1, c);
					}
				}
			public:
				enum NodeType type = NodeType::charExpression;
				char value;
				CharExpression(char value = '\0') {
					this->value = value;
					this->type = NodeType::charExpression;
				}
				virtual NodeType get_type() override {
					return NodeType::charExpression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "CharExpression('" + format_char(this->value) + "')";
				}
				virtual std::string type_id() override {
					return "CharExpression";
				}
			};

			class StrExpression: public Expression {
			public:
				enum NodeType type = NodeType::strExpression;
				std::string value;
				StrExpression(std::string value = "") {
					this->value = value;
					this->type = NodeType::strExpression;
				}
				virtual NodeType get_type() override {
					return NodeType::strExpression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "StrExpression(\"" + this->value + "\")";
				}
				virtual std::string type_id() override {
					return "StrExpression";
				}
			};

			class ParenthesisExpression: public Expression {
			public:
				enum NodeType type = NodeType::parenthesisExpression;
				std::shared_ptr<Expression> content;

				ParenthesisExpression(std::shared_ptr<Expression> content) {
					this->content = content;
					this->type = NodeType::booleanExpression;
				}
				virtual NodeType get_type() override {
					return NodeType::parenthesisExpression;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "ParenthesisExpression(\n" + this->content->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "ParenthesisExpression";
				}
			};

			enum NodeType get_operator_return_type(std::shared_ptr<Expression> left, std::string operator_symbol);

            class BinaryExpression: public Expression {
                public:
                    enum NodeType type = NodeType::binaryExpression;
                    std::shared_ptr<Expression> left;
                    std::shared_ptr<Expression> right;
					enum NodeType returnType;
                    std::string operator_symbol;
                    BinaryExpression(std::shared_ptr<Expression> left, std::string operator_symbol, std::shared_ptr<Expression> right) {
						this->left = left;
						this->operator_symbol = operator_symbol;
						this->right = right;
						this->type = NodeType::binaryExpression;
						this->returnType = get_operator_return_type(this->left, this->operator_symbol);
					}
					virtual NodeType get_type() override {
						return NodeType::binaryExpression;
					}
					enum NodeType get_return_type() {
						return this->returnType;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "BinaryExpression(\n" + this->left->pretty_print(indent + 1) + "\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->right->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
					}
					virtual std::string type_id() override {
						return "BinaryExpression";
					}
            };

			 class UnaryExpression: public Expression {
                public:
                    enum NodeType type = NodeType::unaryExpression;
                    std::shared_ptr<Expression> term;
					enum NodeType returnType;
                    std::string operator_symbol;
                    UnaryExpression(std::shared_ptr<Expression> term, std::string operator_symbol) {
						this->term = term;
						this->operator_symbol = operator_symbol;
						this->type = NodeType::unaryExpression;
						this->returnType = get_operator_return_type(this->term, this->operator_symbol);
					}
					virtual NodeType get_type() override {
						return NodeType::unaryExpression;
					}
					enum NodeType get_return_type() {
						return this->returnType;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						return std::string(indent, '\t') + "UnaryExpression(\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->term->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
					}
					virtual std::string type_id() override {
						return "UnaryExpression";
					}
            };

			enum NodeType get_operator_return_type(std::shared_ptr<Expression> left, std::string operator_symbol) {
				if(operator_symbol == "==" || operator_symbol == "!=" ||
					operator_symbol == "&&" || operator_symbol == "||" ||
					operator_symbol == "<" || operator_symbol == ">" ||
					operator_symbol == "<=" || operator_symbol == ">=" ||
					operator_symbol == "^^" || operator_symbol == "!"
				) {
					return NodeType::booleanExpression;
				};
				if(left->get_type() == NodeType::binaryExpression) {
					return std::dynamic_pointer_cast<BinaryExpression>(left)->get_return_type();
				}
				if(left->get_type() == NodeType::identifier) {
					return std::dynamic_pointer_cast<Identifier>(left)->get_identifier_type();
				}
				return left->get_type();
			}

			class FunctionCallExpression: public Expression {
                public:
                    enum NodeType type = NodeType::functionCallExpression;
					std::shared_ptr<Identifier> functionIdentifier;
                    std::vector<std::shared_ptr<Expression>> arguments;

                    FunctionCallExpression(std::shared_ptr<Identifier> functionIdentifier, std::vector<std::shared_ptr<Expression>> arguments) {
						this->functionIdentifier = functionIdentifier;
						this->arguments = arguments;
						this->type = NodeType::functionCallExpression;
					}
					virtual NodeType get_type() override {
						return NodeType::functionCallExpression;
					}
                    virtual std::string pretty_print(int indent = 0) override {
						bool has_args = this->arguments.size() > 0;
						std::string pretty = std::string(indent, '\t') + this->functionIdentifier->name + "(" + (has_args ? "\n" : "void");
						for(u64 i = 0; i < this->arguments.size(); i++) {
							pretty += this->arguments[i]->pretty_print(indent + 1) + "\n";
						}
						pretty += (has_args ? std::string(indent, '\t') : "") + ");";
						return pretty;
					}
					virtual std::string type_id() override {
						return "FunctionCallExpression";
					}
            };

			class Assignation: public Statement {
			public:
				enum NodeType type = NodeType::assignation;
				std::shared_ptr<Identifier> identifier;
				std::shared_ptr<Expression> value;
				Assignation(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value) {
					this->identifier = identifier;
					this->value = value;
					this->type = NodeType::assignation;
				}
				virtual NodeType get_type() override {
					return NodeType::assignation;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "Assignation(\n" + std::string(indent + 1, '\t') + this->identifier->name + ",\n" + this->value->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "Assignation";
				}
			
			};

			class Declaration: public Statement {
			public:
				enum NodeType type = NodeType::declaration;
				std::shared_ptr<Identifier> identifier;
				bool isMutable = false;
				std::shared_ptr<Expression> value;
				bool isInFunctionSetup = false;
				Declaration(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value, bool isMutable, bool isInFunctionSetup = false) {
					this->identifier = identifier;
					this->isMutable = isMutable;
					this->value = value;
					this->type = NodeType::declaration;
					this->isInFunctionSetup = isInFunctionSetup;
				}
				Declaration(std::shared_ptr<Assignation> assignation, bool isMutable) {
					this->identifier = assignation->identifier;
					this->value = assignation->value;
					this->type = NodeType::declaration;
					this->isMutable = isMutable;
				}
				virtual NodeType get_type() override {
					return NodeType::declaration;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "Declaration\n" + std::string(indent + 1, '\t') + std::string(this->isMutable ? "mut " : "const ") + this->identifier->name + ",\n" + this->value->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "Declaration";
				}
			
			};

			class FunctionDeclaration: public Statement {
			public:
				enum NodeType type = NodeType::functionDeclaration;
				std::shared_ptr<Identifier> identifier;
				std::string returnType;
				std::vector<std::shared_ptr<Declaration>> arguments;
				std::vector<std::shared_ptr<Statement>> body;

				FunctionDeclaration(std::shared_ptr<Identifier> identifier, std::string returnType, std::vector<std::shared_ptr<Declaration>> arguments, std::vector<std::shared_ptr<Statement>> body) {
					this->identifier = identifier;
					this->returnType = returnType;
					this->arguments = arguments;
					this->body = body;
				}
				
				virtual NodeType get_type() override {
					return NodeType::functionDeclaration;
				}
				virtual std::string pretty_print(int indent = 0) override {
					bool has_args = this->arguments.size() > 0;
					std::string pretty = std::string(indent, '\t') + "fn " + this->identifier->name + "(" + (has_args ? "\n" : "void");
					for(u64 i = 0; i < this->arguments.size(); i++) {
						pretty += this->arguments[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += (has_args ? std::string(indent, '\t') : "") + "): " + returnType + " {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "FunctionDeclaration";
				}
			};

			class FunctionReturn: public Statement {
			public:
				enum NodeType type = NodeType::functionReturn;
				std::shared_ptr<Expression> value;

				FunctionReturn(std::shared_ptr<Expression> value) {
					this->value = value;
				}
				
				virtual NodeType get_type() override {
					return NodeType::functionReturn;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "return " + this->value->pretty_print();
				}
				virtual std::string type_id() override {
					return "FunctionReturn";
				}
			};

			class Program: public Scope {
			public:
				enum NodeType type = NodeType::program;

				Program(std::vector<std::shared_ptr<Statement>> body) : Scope(body) {
					this->type = NodeType::program;
				}
				virtual NodeType get_type() override {
					return NodeType::program;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "Program(\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + ")";
					return pretty;
				}
				virtual std::string type_id() override {
					return "Program";
				}
            };

			class ConditionnalBlock: public Scope {
			private:
				std::string if_else_pretty_print(int indent) {
					std::string pretty = std::string(indent, '\t');
					pretty += condition == nullptr ? "else" : 
						(
							(this->before != nullptr ? "else " : "") + std::string("if(\n" + this->condition->pretty_print(indent + 1) + "\n" + std::string(indent, '\t') + ")")
						);
					pretty += " {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				std::string match_case_pretty_print(int indent) {
					std::string pretty = std::string(indent, '\t');
					if(this->condition == nullptr) {
						pretty += "default";
					} else {
						pretty += "(\n" + this->condition->pretty_print(indent + 1);
						pretty += "\n" + std::string(indent, '\t') + ")";
					}
					pretty += " => {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
			public:
				enum NodeType type = NodeType::conditionnalBlock;
				std::shared_ptr<Expression> condition;
				std::shared_ptr<ConditionnalBlock> before;
				bool isMatch;

				ConditionnalBlock(std::vector<std::shared_ptr<Statement>> body, std::shared_ptr<Expression> condition, bool isMatch, std::shared_ptr<ConditionnalBlock> before = nullptr) : Scope(body) {
					this->type = NodeType::program;
					this->condition = condition;
					this->before = before;
					this->isMatch = isMatch;
				}
				virtual NodeType get_type() override {
					return NodeType::conditionnalBlock;
				}
				virtual std::string pretty_print(int indent = 0) override {
					if(this->isMatch) {
						return match_case_pretty_print(indent);
					}
					return if_else_pretty_print(indent);
				}
				virtual std::string type_id() override {
					return "ConditionnalBlock";
				}
            };

			class ConditionnalStructure: public Statement {
			public:
				enum NodeType type = NodeType::conditionnalStructure;
				std::vector<std::shared_ptr<ConditionnalBlock>> conditionnalBlocks;

				ConditionnalStructure(std::vector<std::shared_ptr<ConditionnalBlock>> conditionnalBlocks) {
					this->type = NodeType::conditionnalStructure;
					this->conditionnalBlocks = conditionnalBlocks;
				}
				virtual NodeType get_type() override {
					return NodeType::conditionnalStructure;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = "";
					for(std::shared_ptr<ConditionnalBlock> block : this->conditionnalBlocks) {
						pretty += block->pretty_print(indent + 1) + "\n";
					}
					return pretty;
				}
				virtual std::string type_id() override {
					return "ConditionnalStructure";
				}
            };

			class MatchStructure: public Statement {
			public:
				enum NodeType type = NodeType::matchStructure;
				std::shared_ptr<ent::front::ast::Expression> matchExpression;
				std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks;

				MatchStructure(std::shared_ptr<ent::front::ast::Expression> matchExpression, std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks) {
					this->type = NodeType::matchStructure;
					this->matchExpression = matchExpression;
					this->casesBlocks = casesBlocks;
				}
				virtual NodeType get_type() override {
					return NodeType::matchStructure;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = "match(\n";
					pretty += matchExpression->pretty_print(indent + 1);
					pretty += "\n" + std::string(indent, '\t') + ") {\n";
					for(std::shared_ptr<ConditionnalBlock> block : this->casesBlocks) {
						pretty += block->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "MatchStructure";
				}
            };

			class BreakStatement: public Statement {
			public:
				enum NodeType type = NodeType::breakStatement;

				BreakStatement() {
					this->type = NodeType::breakStatement;
				}
				
				virtual NodeType get_type() override {
					return NodeType::breakStatement;
				}
				virtual std::string pretty_print(int indent = 0) override {
					return std::string(indent, '\t') + "break;";
				}
				virtual std::string type_id() override {
					return "BreakStatement";
				}
			};

			class Loop: public Scope {
			public:
				std::shared_ptr<Expression> loopCondition;

				Loop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body) : Scope(body) {
					this->loopCondition = loopCondition;
				}
			};

			class ForLoop: public Loop {
			public:
				enum NodeType type = NodeType::forLoop;
				std::shared_ptr<Statement> initStatement;
				std::shared_ptr<Statement> iterationStatement;

				ForLoop(std::shared_ptr<Statement> initStatement, std::shared_ptr<Expression> loopCondition, std::shared_ptr<Statement> iterationStatement, std::vector<std::shared_ptr<Statement>> body): Loop(loopCondition, body) {
					this->type = NodeType::forLoop;
					this->initStatement = initStatement;
					this->iterationStatement = iterationStatement;
				}
				virtual NodeType get_type() override {
					return NodeType::forLoop;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "for(\n";
					pretty += this->initStatement->pretty_print(indent + 1) + ";\n";
					pretty += this->loopCondition->pretty_print(indent + 1) + ";\n";
					pretty += this->iterationStatement->pretty_print(indent + 1) + "\n";
					pretty += std::string(indent, '\t') + ") {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "ForLoop";
				}
			};

			class WhileLoop: public Loop {
			public:
				enum NodeType type = NodeType::whileLoop;

				WhileLoop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body): Loop(loopCondition, body) {
					this->type = NodeType::whileLoop;
				}
				virtual NodeType get_type() override {
					return NodeType::whileLoop;
				}
				virtual std::string pretty_print(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "while(\n";
					pretty += this->loopCondition->pretty_print(indent + 1) + ";\n";
					pretty += std::string(indent, '\t') + ") {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->pretty_print(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "WhileLoop";
				}
			};
        }
    }
}

#endif // __ENT_FRONT_AST__