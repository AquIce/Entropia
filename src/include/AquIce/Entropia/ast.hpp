#ifndef __ENT_FRONT_AST__
#define __ENT_FRONT_AST__

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <limits>

#include "../types/numbers.hpp"

/**
 * Generate the condition to cast a value of a type to another type
 * @param expressionType The type of the expression to cast
 * @param destinationType The destination type
 */
#define is_valid_cast_expression_type(expressionType, destinationType) \
( \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value >= std::numeric_limits<destinationType>::min() && \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value <= std::numeric_limits<destinationType>::max() && \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value == static_cast<destinationType>(std::dynamic_pointer_cast<I8Expression>(value)->value) \
)

/**
 * Generate the `switch` structure to cast a value to a destination type
 * @param destinationType The destination type
 * @return Whether the cast is valid
 */
#define switch_expression_type(destinationType) \
switch(value->get_type()) { \
	case NodeType::i8Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<I8Expression>, destinationType); \
	case NodeType::i16Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<I16Expression>, destinationType); \
	case NodeType::i32Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<I32Expression>, destinationType); \
	case NodeType::i64Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<I64Expression>, destinationType); \
	case NodeType::u8Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<U8Expression>, destinationType); \
	case NodeType::u16Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<U16Expression>, destinationType); \
	case NodeType::u32Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<U32Expression>, destinationType); \
	case NodeType::u64Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<U64Expression>, destinationType); \
	case NodeType::f32Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<F32Expression>, destinationType); \
	case NodeType::f64Expression: \
		return is_valid_cast_expression_type(std::shared_ptr<F64Expression>, destinationType); \
	default: \
		return false; \
}

namespace ent {
    namespace front {
        namespace ast {

			/**
			 * Type of an AST Node
			 */
            enum NodeType {

				// Scope-based

				scope,
                program,

				// Numbers

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

				// Other datatypes

				booleanExpression,
				charExpression,
				strExpression,

				// Other expressions

				identifier,
				assignationExpression,
                binaryExpression,
				unaryExpression,
				ternaryExpression,
				parenthesisExpression,

				// Other statements

				declaration,

				// Conditions

				conditionnalBlock,
				conditionnalStructure,
				matchStructure,
				breakStatement,

				// Functions

				functionDeclaration,
				functionReturn,
				functionCallExpression,

				// Loops
				forLoop,
				whileLoop,
				typeDeclaration,
				typeImplementation,
            };

			/**
			 * Access specifier (public/private)
			 */
			enum ClassAccessSpecifier {
				PRIVATE,
				PUBLIC,
			};

			/**
			 * Get the valid casts to a given type
			 * @param type The type to cast to
			 */
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
				}).at(type);
			}

			/**
			 * Statement
			 * @note This class is only used for inheritance purpose, never as a value
			 */
            class Statement {
			public:
				/**
				 * Get the NodeType of the Statement
				 */
				virtual NodeType get_type() {
					return NodeType::program;
				}
				/**
				 * Get the string representation of the Statement
				 */
				virtual std::string repr(int indent = 0) {
					return std::string(indent, '\t') + "Statement";
				}
				/**
				 * Get the type id of the Statement
				 */
				virtual std::string type_id() {
					return "Statement";
				}
            };

			/**
			 * Scope < Statement 
			 */
			class Scope: public Statement {
			public:
				/**
				 * The body of the scope
				 */
				std::vector<std::shared_ptr<Statement>> body;

				/**
				 * Create a Scope
				 * @param body The statements inside the scope
				 */
				Scope(std::vector<std::shared_ptr<Statement>> body) {
					this->body = body;
				}
				virtual NodeType get_type() override {
					return NodeType::scope;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "{\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "Scope";
				}
            };

            class Program;

			/**
			 * Expression < Statement
			 * @note This class is only used for inheritance purpose, never as a value
			 */
            class Expression: public Statement {};

			/**
			 * Identifier < Expression < Statement
			 */
			class Identifier: public Expression {
			public:
				/**
				 * The name of the identifier
				 */
				std::string name;
				/**
				 * The type of the value held by the identifier
				 */
				enum NodeType identifierType;

				/**
				 * Create an Identifier
				 * @param name The name of the identifier
				 */
				Identifier(std::string name) {
					this->name = name;
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
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "Identifier(" + this->name + ")";
				}
				virtual std::string type_id() override {
					return "Identifier";
				}
			};

			/**
			 * I8 Expression < Expression < Statement
			 */
            class I8Expression: public Expression {
			public:
				/**
				 * The value
				 */
				i8 value;

				/**
				 * Create an I8 Expression
				 * @param value The value
				 */
				I8Expression(i8 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::i8Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "I8Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I8Expression";
				}
            };

			/**
			 * I16 Expression < Expression < Statement
			 */
			class I16Expression: public Expression {
			public:
				/**
				 * The value
				*/
				i16 value;
				
				/**
				 * Create an I16 Expression
				 * @param value The value
				 */
				I16Expression(i16 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::i16Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "I16Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I16Expression";
				}
			};

			/**
			 * I32 Expression < Expression < Statement
			 */
			class I32Expression: public Expression {
			public:
				/**
				 * The value
				*/
				i32 value;
				
				/**
				 * Create an I32 Expression
				 * @param value The value
				 */
				I32Expression(i32 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::i32Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "I32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I32Expression";
				}
			};

			/**
			 * I64 Expression < Expression < Statement
			 */
			class I64Expression: public Expression {
			public:
				/**
				 * The value
				*/
				i64 value;
				
				/**
				 * Create an I64 Expression
				 * @param value The value
				 */
				I64Expression(i64 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::i64Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "I64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "I64Expression";
				}
			};

			/**
			 * U8 Expression < Expression < Statement
			 */
			class U8Expression: public Expression {
			public:
				/**
				 * The value
				*/
				u8 value;
				
				/**
				 * Create a U8 Expression
				 * @param value The value
				 */
				U8Expression(u8 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::u8Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "U8Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U8Expression";
				}
			};

			/**
			 * U16 Expression < Expression < Statement
			 */
			class U16Expression: public Expression {
			public:
				/**
				 * The value
				*/
				u16 value;
								
				/**
				 * Create a U16 Expression
				 * @param value The value
				 */
				U16Expression(u16 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::u16Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "U16Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U16Expression";
				}
			};

			/**
			 * U32 Expression < Expression < Statement
			 */
			class U32Expression: public Expression {
			public:
				/**
				 * The value
				*/
				u32 value;
								
				/**
				 * Create a U32 Expression
				 * @param value The value
				 */
				U32Expression(u32 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::u32Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "U32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U32Expression";
				}
			};

			/**
			 * U64 Expression < Expression < Statement
			 */
			class U64Expression: public Expression {
			public:
				/**
				 * The value
				*/
				u64 value;
								
				/**
				 * Create a U64 Expression
				 * @param value The value
				 */
				U64Expression(u64 value = 0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::u64Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "U64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "U64Expression";
				}
			};

			/**
			 * F32 Expression < Expression < Statement
			 */
			class F32Expression: public Expression {
			public:
				/**
				 * The value
				*/
				float value;

				/**
				 * Create an F32 Expression
				 * @param value The value
				 */
				F32Expression(float value = 0.0f) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::f32Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "F32Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "F32Expression";
				}
			};

			/**
			 * F64 Expression < Expression < Statement
			 */
			class F64Expression: public Expression {
			public:
				/**
				 * The value
				*/
				double value;
								
				/**
				 * Create an F64 Expression
				 * @param value The value
				 */
				F64Expression(double value = 0.0) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::f64Expression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "F64Expression(" + std::to_string(this->value) + ")";
				}
				virtual std::string type_id() override {
					return "F64Expression";
				}
			};
			
			/**
			 * Boolean Expression < Expression < Statement
			 */
			class BooleanExpression: public Expression {
			public:
				/**
				 * The value
				 */
				bool value;
								
				/**
				 * Create a Boolean Expression
				 * @param value The value
				 */
				BooleanExpression(bool value = false) {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::booleanExpression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "BooleanExpression(" + (this->value ? "true" : "false") + ")";
				}
				virtual std::string type_id() override {
					return "BooleanExpression";
				}
			};

			/**
			 * Char Expression < Expression < Statement
			 */
			class CharExpression: public Expression {
			private:
				/**
				 * Format a char to a readable string
				 * @param c The character
				 */
				std::string format_char(char c) {
					// Try to parse escaped character
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
						// Return normal character
						return std::string(1, c);
					}
				}
			public:
				/**
				 * The value
				 */
				char value;
				
				/**
				 * Create a Char Expression
				 * @param value The value
				 */
				CharExpression(char value = '\0') {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::charExpression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "CharExpression('" + format_char(this->value) + "')";
				}
				virtual std::string type_id() override {
					return "CharExpression";
				}
			};

			/**
			 * String Expression < Expression < Statement
			 */
			class StrExpression: public Expression {
			public:
				/**
				 * The value
				 */
				std::string value;
								
				/**
				 * Create a String Expression
				 * @param value The value
				 */
				StrExpression(std::string value = "") {
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::strExpression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "StrExpression(\"" + this->value + "\")";
				}
				virtual std::string type_id() override {
					return "StrExpression";
				}
			};

			/**
			 * Parenthesis Expression < Expression < Statement
			 */
			class ParenthesisExpression: public Expression {
			public:
				/**
				 * The content inside of the parenthesis
				 */
				std::shared_ptr<Expression> content;

				/**
				 * Create a Parenthesis Expression
				 * @param conent The content of the parenthesis
				 */
				ParenthesisExpression(std::shared_ptr<Expression> content) {
					this->content = content;
				}
				virtual NodeType get_type() override {
					return NodeType::parenthesisExpression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "ParenthesisExpression(\n" + this->content->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "ParenthesisExpression";
				}
			};

			/**
			 * Get the return type of an operator (from its left member)
			 * @param left The left member of the operator
			 * @param operator_symbol The symbol of the operator to use
			 * @return The NodeType of the result
			 * 
			 * @note This does not take take into account that `i8` * `i8` may result in `i16`, this is evaluated in the interpreter
			 */
			enum NodeType get_operator_return_type(std::shared_ptr<Expression> left, std::string operator_symbol);

			/**
			 * Binary Expression < Expression < Statement
			 */
            class BinaryExpression: public Expression {
			public:
				/**
				 * The left member
				 */
				std::shared_ptr<Expression> left;
				/**
				 * The right member
				 */
				std::shared_ptr<Expression> right;
				/**
				 * The return type
				 */
				enum NodeType returnType;
				/**
				 * The operator symbol
				 */
				std::string operator_symbol;
				
				/**
				 * Create a Binary Expression
				 * @param left The left member
				 * @param operator_symbol The operator symbol
				 * @param right The right member
				 */
				BinaryExpression(std::shared_ptr<Expression> left, std::string operator_symbol, std::shared_ptr<Expression> right) {
					this->left = left;
					this->operator_symbol = operator_symbol;
					this->right = right;
					// Determine the return type of the function
					this->returnType = get_operator_return_type(this->left, this->operator_symbol);
				}
				virtual NodeType get_type() override {
					return NodeType::binaryExpression;
				}
				enum NodeType get_return_type() {
					return this->returnType;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "BinaryExpression(\n" + this->left->repr(indent + 1) + "\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->right->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "BinaryExpression";
				}
            };

			/**
			 * Unary Expression < Expression < Statement
			 */
			class UnaryExpression: public Expression {
			public:
				/**
				 * The term
				 */
				std::shared_ptr<Expression> term;
				/**
				 * The return type
				 */
				enum NodeType returnType;
				/**
				 * The operator symbol
				 */
				std::string operator_symbol;
								
				/**
				 * Create a Unary Expression
				 * @param term The term
				 * @param operator_symbol The operator symbol
				 */
				UnaryExpression(std::shared_ptr<Expression> term, std::string operator_symbol) {
					this->term = term;
					this->operator_symbol = operator_symbol;
					this->returnType = get_operator_return_type(this->term, this->operator_symbol);
				}
				virtual NodeType get_type() override {
					return NodeType::unaryExpression;
				}
				enum NodeType get_return_type() {
					return this->returnType;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "UnaryExpression(\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->term->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "UnaryExpression";
				}
            };

			/**
			 * Ternary Expression < Expression < Statement
			 */
			class TernaryExpression: public Expression {
			public:
				/**
				 * The condition
				 */
				std::shared_ptr<Expression> condition;
				/**
				 * The value if the condition is true
				 */
				std::shared_ptr<Expression> true_value;
				/**
				 * The value if the condition is false
				 */
				std::shared_ptr<Expression> false_value;
				/**
				 * The return type
				 */
				enum NodeType returnType;
								
				/**
				 * Create a Ternary Expression
				 * @param condition The condition
				 * @param true_value The value if the condition is true
				 * @param false_value The value if the condition is false
				 */
				TernaryExpression(std::shared_ptr<Expression> condition, std::shared_ptr<Expression> true_value, std::shared_ptr<Expression> false_value) {
					this->condition = condition;
					this->true_value = true_value;
					this->false_value = false_value;
					this->returnType = this->true_value->get_type();
				}
				virtual NodeType get_type() override {
					return NodeType::ternaryExpression;
				}
				enum NodeType get_return_type() {
					return this->returnType;
				}
				virtual std::string repr(int indent = 0) override {
					return (
						this->condition->repr(indent + 1) + "\n" + std::string(indent + 1, '\t') + "?\n" +
						this->true_value->repr(indent + 1) + "\n" + std::string(indent + 1, '\t') + ":\n" +
						this->false_value->repr(indent + 1)
					);
				}
				virtual std::string type_id() override {
					return "TernaryExpression";
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

			/**
			 * Function Call Expression < Expression < Statement
			 */
			class FunctionCallExpression: public Expression {
			public:
				/**
				 * The identifier of the called function
				 */
				std::shared_ptr<Identifier> functionIdentifier;
				/**
				 * The arguments to pass to the function
				 */
				std::vector<std::shared_ptr<Expression>> arguments;

								
				/**
				 * Create a Function Call Expression
				 * @param functionIdentifier The identifier of the called function
				 * @param arguments The arguments to pass to the function
				 */
				FunctionCallExpression(std::shared_ptr<Identifier> functionIdentifier, std::vector<std::shared_ptr<Expression>> arguments) {
					this->functionIdentifier = functionIdentifier;
					this->arguments = arguments;
				}
				virtual NodeType get_type() override {
					return NodeType::functionCallExpression;
				}
				virtual std::string repr(int indent = 0) override {
					bool has_args = this->arguments.size() > 0;
					std::string pretty = std::string(indent, '\t') + this->functionIdentifier->name + "(" + (has_args ? "\n" : "void");
					for(u64 i = 0; i < this->arguments.size(); i++) {
						pretty += this->arguments[i]->repr(indent + 1) + "\n";
					}
					pretty += (has_args ? std::string(indent, '\t') : "") + ");";
					return pretty;
				}
				virtual std::string type_id() override {
					return "FunctionCallExpression";
				}
            };

			/**
			 * Assignation Expression < Expression < Statement
			 */
			class AssignationExpression: public Expression {
			public:
				/**
				 * The identifier to assign to
				 */
				std::shared_ptr<Identifier> identifier;
				/**
				 * The value to assign
				 */
				std::shared_ptr<Expression> value;

				/**
				 * Create an Assignation Expression
				 * @param identifier The identifier to assign to
				 * @param value The value to assign
				 */
				AssignationExpression(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value) {
					this->identifier = identifier;
					this->value = value;
				}
				virtual NodeType get_type() override {
					return NodeType::assignationExpression;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "AssignationExpression(\n" + std::string(indent + 1, '\t') + this->identifier->name + ",\n" + this->value->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "AssignationExpression";
				}
			
			};

			/**
			 *  Declaration < Statement
			 */
			class Declaration: public Statement {
			public:
				/**
				 * The identifier to declare
				 */
				std::shared_ptr<Identifier> identifier;
				/**
				 * Whether the value is mutable
				 */
				bool isMutable = false;
				/**
				 * The actual value
				 */
				std::shared_ptr<Expression> value;
				/**
				 * Whether the declaration is from a function arguments setup (see interpreter)
				 */
				bool isInFunctionSetup = false;
				
				/**
				 * Create a Declaration
				 * @param identifier The identifier to declare
				 * @param isMutable Whether the value is mutable
				 * @param isInFunctionSetup Whether the declaration is from a function arguments setup
				 */
				Declaration(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value, bool isMutable, bool isInFunctionSetup = false) {
					this->identifier = identifier;
					this->isMutable = isMutable;
					this->value = value;
					this->isInFunctionSetup = isInFunctionSetup;
				}
				/**
				 * Create a Declaration from an AssignationExpression
				 * @param assignationExpression The assignation to turn into a declaration
				 * @param isMutable Whether the value is mutable
				 */
				Declaration(std::shared_ptr<AssignationExpression> assignationExpression, bool isMutable) {
					this->identifier = assignationExpression->identifier;
					this->value = assignationExpression->value;
					this->isMutable = isMutable;
				}
				virtual NodeType get_type() override {
					return NodeType::declaration;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "Declaration\n" + std::string(indent + 1, '\t') + std::string(this->isMutable ? "mut " : "const ") + this->identifier->name + ",\n" + this->value->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
				}
				virtual std::string type_id() override {
					return "Declaration";
				}
			
			};

			/**
			 * Function Declaration < Scope < Statement
			 */
			class FunctionDeclaration: public Scope {
			public:
				/**
				 * The identifier of the function
				 */
				std::shared_ptr<Identifier> identifier;
				/**
				 * The return type of the function
				 */
				std::string returnType;
				/**
				 * The arguments of the function
				 */
				std::vector<std::shared_ptr<Declaration>> arguments;

				/**
				 * Create a Function Declaration
				 * @param identifier The identifier of the function
				 * @param returnType The return type of the function
				 * @param arguments The arguments of the function
				 * @param body The body of the function
				 */
				FunctionDeclaration(std::shared_ptr<Identifier> identifier, std::string returnType, std::vector<std::shared_ptr<Declaration>> arguments, std::vector<std::shared_ptr<Statement>> body) : Scope(body) {
					this->identifier = identifier;
					this->returnType = returnType;
					this->arguments = arguments;
				}
				
				virtual NodeType get_type() override {
					return NodeType::functionDeclaration;
				}
				virtual std::string repr(int indent = 0) override {
					bool has_args = this->arguments.size() > 0;
					std::string pretty = std::string(indent, '\t') + "fn " + this->identifier->name + "(" + (has_args ? "\n" : "void");
					for(u64 i = 0; i < this->arguments.size(); i++) {
						pretty += this->arguments[i]->repr(indent + 1) + "\n";
					}
					pretty += (has_args ? std::string(indent, '\t') : "") + "): " + returnType + " {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "FunctionDeclaration";
				}
			};

			/**
			 * Function Return < Statement
			 */
			class FunctionReturn: public Statement {
			public:
				/**
				 * The value that is being returned
				*/
				std::shared_ptr<Expression> value;

				/**
				 * Create a Function Return
				 * @param value The value that is being returned
				 */
				FunctionReturn(std::shared_ptr<Expression> value) {
					this->value = value;
				}
				
				virtual NodeType get_type() override {
					return NodeType::functionReturn;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "return " + this->value->repr();
				}
				virtual std::string type_id() override {
					return "FunctionReturn";
				}
			};

			/**
			 * Program < Scope < Statement
			 */
			class Program: public Scope {
			public:
				/**
				 * Create a Program
				 * @param body The body of the program
				 */
				Program(std::vector<std::shared_ptr<Statement>> body) : Scope(body) {}
				virtual NodeType get_type() override {
					return NodeType::program;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "Program(\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + ")";
					return pretty;
				}
				virtual std::string type_id() override {
					return "Program";
				}
            };

			/**
			 * Conditionnal Block < Scope < Statement
			 */
			class ConditionnalBlock: public Scope {
			private:
				/**
				 * Get the string representation of an `if`/`else` block
				 */
				std::string if_else_repr(int indent) {
					std::string pretty = std::string(indent, '\t');
					pretty += condition == nullptr ? "else" : 
						(
							(this->before != nullptr ? "else " : "") + std::string("if(\n" + this->condition->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")")
						);
					pretty += " {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				/**
				 * Get the string representation of a `match` case block
				 */
				std::string match_case_repr(int indent) {
					std::string pretty = std::string(indent, '\t');
					if(this->condition == nullptr) {
						pretty += "default";
					} else {
						pretty += "(\n" + this->condition->repr(indent + 1);
						pretty += "\n" + std::string(indent, '\t') + ")";
					}
					pretty += " => {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
			public:
				/**
				 * The condition to get inside the block
				 */
				std::shared_ptr<Expression> condition;
				/**
				 * The block that is before this one (in the case of an `else`/`else if`)
				 */
				std::shared_ptr<ConditionnalBlock> before;
				/**
				 * Whether the condition is a `match` case
				 */
				bool isMatch;

				/**
				 * Create a Conditionnal Block
				 * @param body The body of the block
				 * @param condition The condition to get inside the block
				 * @param isMatch Whether the condition is a `match` case
				 * @param before The block that is before this one (in the case of an `else`/`else if`)
				 */
				ConditionnalBlock(std::vector<std::shared_ptr<Statement>> body, std::shared_ptr<Expression> condition, bool isMatch, std::shared_ptr<ConditionnalBlock> before = nullptr) : Scope(body) {
					this->condition = condition;
					this->before = before;
					this->isMatch = isMatch;
				}
				virtual NodeType get_type() override {
					return NodeType::conditionnalBlock;
				}
				virtual std::string repr(int indent = 0) override {
					if(this->isMatch) {
						return match_case_repr(indent);
					}
					return if_else_repr(indent);
				}
				virtual std::string type_id() override {
					return "ConditionnalBlock";
				}
            };

			/**
			 * Conditionnal Structure < Statement
			 */
			class ConditionnalStructure: public Statement {
			public:
				/**
				 * The blocks of the structure
				 */
				std::vector<std::shared_ptr<ConditionnalBlock>> conditionnalBlocks;

				/**
				 * Create a Condtionnal Stucture
				 * @param conditionnalBlocks The blocks of the structure
				 */
				ConditionnalStructure(std::vector<std::shared_ptr<ConditionnalBlock>> conditionnalBlocks) {
					this->conditionnalBlocks = conditionnalBlocks;
				}
				virtual NodeType get_type() override {
					return NodeType::conditionnalStructure;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = "";
					for(std::shared_ptr<ConditionnalBlock> block : this->conditionnalBlocks) {
						pretty += block->repr(indent + 1) + "\n";
					}
					return pretty;
				}
				virtual std::string type_id() override {
					return "ConditionnalStructure";
				}
            };

			/**
			 * Match Stucture < Statement
			 */
			class MatchStructure: public Statement {
			public:
				/**
				 * The expression to match for each case
				 */
				std::shared_ptr<ent::front::ast::Expression> matchExpression;
				/**
				 * The `case` blocks
				 */
				std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks;

				/**
				 * Create a Match Structure
				 * @param matchExpression The expression to match for each case
				 * @param casesBlocks The `case` blocks
				 */
				MatchStructure(std::shared_ptr<ent::front::ast::Expression> matchExpression, std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks) {
					this->matchExpression = matchExpression;
					this->casesBlocks = casesBlocks;
				}
				virtual NodeType get_type() override {
					return NodeType::matchStructure;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = "match(\n";
					pretty += matchExpression->repr(indent + 1);
					pretty += "\n" + std::string(indent, '\t') + ") {\n";
					for(std::shared_ptr<ConditionnalBlock> block : this->casesBlocks) {
						pretty += block->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "MatchStructure";
				}
            };

			/**
			 * Break Statement < Statement
			 */
			class BreakStatement: public Statement {
			public:

				/**
				 * Create a Break Statement
				 */
				BreakStatement() {}
				
				virtual NodeType get_type() override {
					return NodeType::breakStatement;
				}
				virtual std::string repr(int indent = 0) override {
					return std::string(indent, '\t') + "break;";
				}
				virtual std::string type_id() override {
					return "BreakStatement";
				}
			};

			/**
			 * Loop < Scope < Statement
			 * @note This class is only used for inheritance purpose, never as a value
			 */
			class Loop: public Scope {
			public:
				/**
				 * The condition to continue the loop
				 */
				std::shared_ptr<Expression> loopCondition;

				/**
				 * Create a Loop
				 * @param loopCondition The condition to continue the loop
				 * @param body The body of the loop
				 */
				Loop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body) : Scope(body) {
					this->loopCondition = loopCondition;
				}
			};

			/**
			 * For Loop < Loop < Scope < Statement
			 */
			class ForLoop: public Loop {
			public:
				/**
				 * The statement to run before the first iteration
				 */
				std::shared_ptr<Statement> initStatement;
				/**
				 * The statement to run before the condition at each iteration
				 */
				std::shared_ptr<Statement> iterationStatement;

				/**
				 * Create a For Loop
				 * @param initStatement The statement to run before the first iteration
				 * @param loopCondition The condition to continue the loop
				 * @param iterationStatement The statement to run before the condition at each iteration
				 * @param body The body of the loop
				 */
				ForLoop(std::shared_ptr<Statement> initStatement, std::shared_ptr<Expression> loopCondition, std::shared_ptr<Statement> iterationStatement, std::vector<std::shared_ptr<Statement>> body): Loop(loopCondition, body) {
					this->initStatement = initStatement;
					this->iterationStatement = iterationStatement;
				}
				virtual NodeType get_type() override {
					return NodeType::forLoop;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "for(\n";
					pretty += this->initStatement->repr(indent + 1) + ";\n";
					pretty += this->loopCondition->repr(indent + 1) + ";\n";
					pretty += this->iterationStatement->repr(indent + 1) + "\n";
					pretty += std::string(indent, '\t') + ") {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "ForLoop";
				}
			};

			/**
			 * While Loop < Loop < Scope < Statement
			 */
			class WhileLoop: public Loop {
			public:
				/**
				 * Create a While Loop
				 * @param loopCondition The condition to continue the loop
				 * @param body The body of the loop
				 */
				WhileLoop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body): Loop(loopCondition, body) {}
				virtual NodeType get_type() override {
					return NodeType::whileLoop;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "while(\n";
					pretty += this->loopCondition->repr(indent + 1) + ";\n";
					pretty += std::string(indent, '\t') + ") {\n";
					for(u64 i = 0; i < this->body.size(); i++) {
						pretty += this->body[i]->repr(indent + 1) + "\n";
					}
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "WhileLoop";
				}
			};

			/**
			 * A Member of a Type
			 */
			typedef struct TypeMember {
				/**
				 * The actual member
				 */
				std::shared_ptr<Declaration> member;
				/**
				 * The access specifier of the member
				 */
				enum ClassAccessSpecifier accessLevel;
			} TypeMember;

			/**
			 * Invert an access specifier
			 * @param accessSpecifier The access specifier to invert
			 * @return The inverted access specifier
			 */
			enum ClassAccessSpecifier invertAccessSpecifier(enum ClassAccessSpecifier accessSpecifier) {
				return static_cast<enum ClassAccessSpecifier>(ClassAccessSpecifier::PUBLIC - accessSpecifier);
			}

			/**
			 * Get the string of an access specifier
			 * @param accessSpecifier The access specifier to get the string og
			 * @return The string
			 */
			std::string accessLevelString(enum ClassAccessSpecifier accessSpecifier) {
				switch(accessSpecifier) {
					case ClassAccessSpecifier::PRIVATE:
						return "@private";
					default:
						return "@public";
				}
			}

			/**
			 * Type Declaration < Statement
			 */
			class TypeDeclaration : public Statement {
			public:
				/**
				 * The name of the type
				 */
				std::string typeName;
				/**
				 * The members of the type
				 */
				std::vector<TypeMember> members;

				/**
				 * Create a Type Declaration
				 * @param typeName The name of the type
				 * @param members The members of the type
				 */
				TypeDeclaration(std::string typeName, std::vector<TypeMember> members) {
					this->typeName = typeName;
					this->members = members;
				}
				virtual NodeType get_type() override {
					return NodeType::typeDeclaration;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "type " + this->typeName + " {\n";
					enum ClassAccessSpecifier prev_access = this->members.size() > 0 ?
						invertAccessSpecifier(this->members[0].accessLevel) :
						ClassAccessSpecifier::PRIVATE;

					for(TypeMember member : this->members) {
						if(member.accessLevel != prev_access) {
							pretty += std::string(indent, '\t') + accessLevelString(member.accessLevel) + "\n";
						}
						pretty += member.member->repr(indent + 1) + "\n";
						prev_access = member.accessLevel;
					}
					
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "TypeDeclaration";
				}
			};

			/**
			 * A Method of a Type Implementation
			 */
			typedef struct ImplMethod {
				/**
				 * The actual method
				 */
				std::shared_ptr<FunctionDeclaration> method;
				/**
				 * The access specifier of the method
				 */
				enum ClassAccessSpecifier accessLevel;
			} ImplMethod;

			/**
			 * Type Implementation < Statement
			 */
			class TypeImplementation : public Statement {
			public:
				/**
				 * The name of the type to implement
				 */
				std::string typeName;
				/**
				 * The methods to implement
				 */
				std::vector<ImplMethod> methods;

				/**
				 * Create a Type Implementation
				 * @param typeName The name of the type to implement
				 * @param methods The methods to implement
				 */
				TypeImplementation(std::string typeName, std::vector<ImplMethod> methods) {
					this->typeName = typeName;
					this->methods = methods;
				}
				virtual NodeType get_type() override {
					return NodeType::typeImplementation;
				}
				virtual std::string repr(int indent = 0) override {
					std::string pretty = std::string(indent, '\t') + "impl" + this->typeName + " {\n";
					enum ClassAccessSpecifier prev_access = this->methods.size() > 0 ?
						invertAccessSpecifier(this->methods[0].accessLevel) :
						ClassAccessSpecifier::PRIVATE;
					
					for(ImplMethod method : this->methods) {
						if(method.accessLevel != prev_access) {
							pretty += std::string(indent, '\t') + accessLevelString(method.accessLevel) + "\n";
						}
						pretty += method.method->repr(indent + 1) + "\n";
						prev_access = method.accessLevel;
					}
					
					pretty += std::string(indent, '\t') + "}";
					return pretty;
				}
				virtual std::string type_id() override {
					return "TypeImplementation";
				}
			};

			/**
			 * The list of all declared functions
			 */
			std::vector<std::shared_ptr<ent::front::ast::FunctionDeclaration>> functions;

			/**
			 * Get a function from its identifier
			 * @param identifier The identifier of the function
			 * @return The Function Declaration or `nullptr` if not found
			 */
			std::shared_ptr<ent::front::ast::FunctionDeclaration> get_function(std::shared_ptr<ent::front::ast::Identifier> identifier) {
				for(std::shared_ptr<ent::front::ast::FunctionDeclaration> function : functions) {
					if(function->identifier->name == identifier->name) {
						return function;
					}
				}
				return nullptr;
			}

			/**
			 * The list of all user-declared types
			 */
			std::vector<std::shared_ptr<ent::front::ast::TypeDeclaration>> types;

			/**
			 * Get a type from its name
			 * @param typeName The name of the type
			 * @return The Type Declaration or `nullptr` if not found
			 */
			std::shared_ptr<ent::front::ast::TypeDeclaration> get_type(std::string typeName) {
				for(std::shared_ptr<ent::front::ast::TypeDeclaration> type : types) {
					if(type->typeName == typeName) {
						return type;
					}
				}
				return nullptr;
			}

			/**
			 * Get a sample value for a given Node Type
			 * @param type The Node Type to get a value from
			 * @return An example expression
			 */
			std::shared_ptr<Expression> get_sample_expression(enum NodeType type) {
				switch(type) {
					case NodeType::i8Expression:
						return std::make_shared<I8Expression>();
					case NodeType::i16Expression:
						return std::make_shared<I16Expression>();
					case NodeType::i32Expression:
						return std::make_shared<I32Expression>();
					case NodeType::i64Expression:
						return std::make_shared<I64Expression>();
					case NodeType::u8Expression:
						return std::make_shared<U8Expression>();
					case NodeType::u16Expression:
						return std::make_shared<U16Expression>();
					case NodeType::u32Expression:
						return std::make_shared<U32Expression>();
					case NodeType::u64Expression:
						return std::make_shared<U64Expression>();
					case NodeType::f32Expression:
						return std::make_shared<F32Expression>();
					case NodeType::f64Expression:
						return std::make_shared<F64Expression>();
					case NodeType::booleanExpression:
						return std::make_shared<BooleanExpression>();
					case NodeType::charExpression:
						return std::make_shared<CharExpression>();
					case NodeType::strExpression:
						return std::make_shared<StrExpression>();
					default:
						throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected valid return type, got " + type)).error();
				}
			}

			/**
			 * Get a Node Type from its string representation
			 * @param type The string reprensentation of a type
			 * @return The Node Type
			 */
			enum NodeType get_node_type(std::string type) {
				if(type == "i8") {
					return NodeType::i8Expression;
				} if(type == "i16") {
					return NodeType::i16Expression;
				} if(type == "i32") {
					return NodeType::i32Expression;
				} if(type == "i64") {
					return NodeType::i64Expression;
				} if(type == "u8") {
					return NodeType::u8Expression;
				} if(type == "u16") {
					return NodeType::u16Expression;
				} if(type == "u32") {
					return NodeType::u32Expression;
				} if(type == "u64") {
					return NodeType::u64Expression;
				} if(type == "f32") {
					return NodeType::f32Expression;
				} if(type == "f64") {
					return NodeType::f64Expression;
				} if(type == "bool") {
					return NodeType::booleanExpression;
				} if(type == "char") {
					return NodeType::charExpression;
				} if(type == "str") {
					return NodeType::strExpression;
				}
				throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected valid return type, got " + type)).error();
			}

			/**
			 * Check if a value can be cast to a given type
			 * @param source The value to try to cast
			 * @param dest The type of the destination
			 * @return Whether the cast is valid
			 */
			bool is_valid_cast(std::shared_ptr<Expression> source, enum NodeType destType) {
				if(source->get_type() == NodeType::identifier) {
					std::shared_ptr<Identifier> source_identifier = std::dynamic_pointer_cast<Identifier>(source);
					return is_valid_cast(get_sample_expression(source_identifier->get_identifier_type()), destType);
				}
				if(source->get_type() == NodeType::binaryExpression) {
					std::shared_ptr<BinaryExpression> source_binary_expression = std::dynamic_pointer_cast<BinaryExpression>(source);
					return is_valid_cast(source_binary_expression->left, destType);
				}
				if(source->get_type() == NodeType::ternaryExpression) {
					std::shared_ptr<TernaryExpression> source_ternary_expression = std::dynamic_pointer_cast<TernaryExpression>(source);
					return is_valid_cast(source_ternary_expression->true_value, destType);
				}
				if(source->get_type() == NodeType::functionCallExpression) {
					std::shared_ptr<FunctionCallExpression> source_function_call_expression = std::dynamic_pointer_cast<FunctionCallExpression>(source);
					std::shared_ptr<FunctionDeclaration> function_declaration = get_function(source_function_call_expression->functionIdentifier);
					if(function_declaration == nullptr) {
						throw (ent::Error(ent::ErrorType::AST_CALLING_UNDECLARED_FUNCTION_ERROR, "Trying to call undeclared function " + source_function_call_expression->functionIdentifier->name)).error();
					}
					return is_valid_cast(get_sample_expression(get_node_type(function_declaration->returnType)), destType);
				}
				if(source->get_type() == destType) { return true; }
				for(enum NodeType dest_valid_cast : valid_casts_to_type(destType)) {
					if(is_valid_cast(source, dest_valid_cast)) {
						return true;
					}
				}
				return false;
			}
        }
    }
}

#endif // __ENT_FRONT_AST__