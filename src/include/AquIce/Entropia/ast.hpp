#ifndef __ENT_FRONT_AST__
#define __ENT_FRONT_AST__

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <limits>

#include "../types/numbers.hpp"
#include "errors.hpp"

/**
 * Generate the condition to cast a value of a type to another type
 * @param expressionType The type of the expression to cast
 * @param destinationType The destination type
 */
#define IS_VALID_CAST_EXPRESSION_TYPE(expressionType, destinationType) \
( \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value >= std::numeric_limits<destinationType>::min() && \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value <= std::numeric_limits<destinationType>::max() && \
	std::dynamic_pointer_cast<expressionType>(value)->get()->value == static_cast<destinationType>(std::dynamic_pointer_cast<I8Expression>(value)->value) \
)

/**
 * Generate the `switch` structure to cast a value to a destination type
 * @param destinationType The destination type
 */
#define SWITCH_EXPRESSION_TYPE(destinationType) \
switch(value->get_type()) { \
	case NodeType::i8Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<I8Expression>, destinationType); \
	case NodeType::i16Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<I16Expression>, destinationType); \
	case NodeType::i32Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<I32Expression>, destinationType); \
	case NodeType::i64Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<I64Expression>, destinationType); \
	case NodeType::u8Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<U8Expression>, destinationType); \
	case NodeType::u16Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<U16Expression>, destinationType); \
	case NodeType::u32Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<U32Expression>, destinationType); \
	case NodeType::u64Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<U64Expression>, destinationType); \
	case NodeType::f32Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<F32Expression>, destinationType); \
	case NodeType::f64Expression: \
		return IS_VALID_CAST_EXPRESSION_TYPE(std::shared_ptr<F64Expression>, destinationType); \
	default: \
		return false; \
}

namespace ent {
    namespace front {
        namespace ast {

			#pragma region Class Prototypes

			class Statement;
			class Scope;
			class Expression;
			class Identifier;
			class I8Expression;
			class I16Expression;
			class I32Expression;
			class I64Expression;
			class U8Expression;
			class U16Expression;
			class U32Expression;
			class U64Expression;
			class F32Expression;
			class F64Expression;
			class BooleanExpression;
			class CharExpression;
			class StrExpression;
			class ParenthesisExpression;
			class BinaryExpression;
			class UnaryExpression;
			class TernaryExpression;
			class FunctionCallExpression;
			class AssignationExpression;
			class Declaration;
			class FunctionDeclaration;
			class Program;
			class ConditionnalBlock;
			class ConditionnalStructure;
			class MatchStructure;
			class BreakStatement;
			class Loop;
			class ForLoop;
			class WhileLoop;
			class TypeDeclaration;
			class TypeImplementation;

			#pragma endregion

			#pragma region Enums / Structs

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

			#pragma endregion

			#pragma region Functions

			/**
			 * Invert an access specifier
			 * @param accessSpecifier The access specifier to invert
			 * @return The inverted access specifier
			 */
			enum ClassAccessSpecifier invertAccessSpecifier(enum ClassAccessSpecifier accessSpecifier);

			/**
			 * Get the string of an access specifier
			 * @param accessSpecifier The access specifier to get the string og
			 * @return The string
			 */
			std::string accessLevelString(enum ClassAccessSpecifier accessSpecifier);

			/**
			 * The list of all declared functions
			 */
			extern std::vector<std::shared_ptr<FunctionDeclaration>> functions;

			/**
			 * Get a function from its identifier
			 * @param identifier The identifier of the function
			 * @return The Function Declaration or `nullptr` if not found
			 */
			std::shared_ptr<FunctionDeclaration> get_function(std::shared_ptr<Identifier> identifier);

			/**
			 * The list of all declared types
			 */
			extern std::vector<std::shared_ptr<TypeDeclaration>> types;

			/**
			 * Get a type from its name
			 * @param typeName The name of the type
			 * @return The Type Declaration or `nullptr` if not found
			 */
			std::shared_ptr<TypeDeclaration> get_type_from_str(std::string typeName);

			/**
			 * Get a sample value for a given Node Type
			 * @param type The Node Type to get a value from
			 * @return An example expression
			 */
			std::shared_ptr<Expression> get_sample_expression(enum NodeType type);

			/**
			 * Get a Node Type from its string representation
			 * @param type The string reprensentation of a type
			 * @return The Node Type
			 */
			enum NodeType get_node_type(std::string type);

			/**
			 * Check if a value can be cast to a given type
			 * @param source The value to try to cast
			 * @param dest The type of the destination
			 * @return Whether the cast is valid
			 */
			bool is_valid_cast(std::shared_ptr<Expression> source, enum NodeType destType);

			/**
			 * Get the valid casts to a given type
			 * @param type The type to cast to
			 */
			std::vector<enum NodeType> valid_casts_to_type(enum NodeType type);

			/**
			 * Get the return type of an operator (from its left member)
			 * @param left The left member of the operator
			 * @param operator_symbol The symbol of the operator to use
			 * @return The NodeType of the result
			 * 
			 * @note This does not take take into account that `i8` * `i8` may result in `i16`, this is evaluated in the interpreter
			 */
			enum NodeType get_operator_return_type(std::shared_ptr<Expression> left, std::string operator_symbol);

			#pragma endregion

			#pragma region Classes

			/**
			 * Statement
			 * @note This class is only used for inheritance purpose, never as a value
			 */
            class Statement {
			public:

				/**
				 * Get the NodeType of the Statement
				 */
				virtual enum NodeType get_type();
				
				/**
				 * Get the string representation of the Statement
				 */
				virtual std::string repr(int indent = 0);

				/**
				 * Get the type id of the Statement
				 */
				virtual std::string type_id();
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
				Scope(std::vector<std::shared_ptr<Statement>> body);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
            };

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
				Identifier(std::string name);

				virtual enum NodeType get_type() override;
				
				enum NodeType get_identifier_type();
				
				void set_identifier_type(enum NodeType type);
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				I8Expression(i8 value = 0);
				
				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				I16Expression(i16 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				I32Expression(i32 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				I64Expression(i64 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				U8Expression(u8 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				U16Expression(u16 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				U32Expression(u32 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				U64Expression(u64 value = 0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				F32Expression(float value = 0.0f);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				F64Expression(double value = 0.0);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
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
				BooleanExpression(bool value = false);

				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
			};

			/**
			 * Char Expression < Expression < Statement
			 */
			class CharExpression: public Expression {
			public:
				/**
				 * The value
				 */
				char value;
				
				/**
				 * Create a Char Expression
				 * @param value The value
				 */
				CharExpression(char value = '\0');
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
			private:
				/**
				 * Format a char to a readable string
				 * @param c The character
				 */
				std::string format_char(char c);
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
				StrExpression(std::string value = "");
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				ParenthesisExpression(std::shared_ptr<Expression> content);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
			};

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
				BinaryExpression(std::shared_ptr<Expression> left, std::string operator_symbol, std::shared_ptr<Expression> right);
				
				virtual enum NodeType get_type() override;
				
				enum NodeType get_return_type();
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				UnaryExpression(std::shared_ptr<Expression> term, std::string operator_symbol);
				
				virtual enum NodeType get_type() override;
				
				enum NodeType get_return_type();
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				TernaryExpression(std::shared_ptr<Expression> condition, std::shared_ptr<Expression> true_value, std::shared_ptr<Expression> false_value);
				
				virtual enum NodeType get_type() override;
				
				enum NodeType get_return_type();
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
            };

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
				FunctionCallExpression(std::shared_ptr<Identifier> functionIdentifier, std::vector<std::shared_ptr<Expression>> arguments);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				AssignationExpression(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				Declaration(std::shared_ptr<Identifier> identifier, std::shared_ptr<Expression> value, bool isMutable, bool isInFunctionSetup = false);
				
				/**
				 * Create a Declaration from an AssignationExpression
				 * @param assignationExpression The assignation to turn into a declaration
				 * @param isMutable Whether the value is mutable
				 */
				Declaration(std::shared_ptr<AssignationExpression> assignationExpression, bool isMutable);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;			
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
				FunctionDeclaration(std::shared_ptr<Identifier> identifier, std::string returnType, std::vector<std::shared_ptr<Declaration>> arguments, std::vector<std::shared_ptr<Statement>> body);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				FunctionReturn(std::shared_ptr<Expression> value);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				Program(std::vector<std::shared_ptr<Statement>> body);

				enum NodeType get_type();
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
            };

			/**
			 * Conditionnal Block < Scope < Statement
			 */
			class ConditionnalBlock: public Scope {				
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
				ConditionnalBlock(std::vector<std::shared_ptr<Statement>> body, std::shared_ptr<Expression> condition, bool isMatch, std::shared_ptr<ConditionnalBlock> before = nullptr);

				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;

			private:
				/**
				 * Get the string representation of an `if`/`else` block
				 */
				std::string if_else_repr(int indent);
				
				/**
				 * Get the string representation of a `match` case block
				 */
				std::string match_case_repr(int indent);
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
				ConditionnalStructure(std::vector<std::shared_ptr<ConditionnalBlock>> conditionnalBlocks);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
            };

			/**
			 * Match Stucture < Statement
			 */
			class MatchStructure: public Statement {
			public:
				/**
				 * The expression to match for each case
				 */
				std::shared_ptr<Expression> matchExpression;
				/**
				 * The `case` blocks
				 */
				std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks;

				/**
				 * Create a Match Structure
				 * @param matchExpression The expression to match for each case
				 * @param casesBlocks The `case` blocks
				 */
				MatchStructure(std::shared_ptr<Expression> matchExpression, std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
            };

			/**
			 * Break Statement < Statement
			 */
			class BreakStatement: public Statement {
			public:

				/**
				 * Create a Break Statement
				 */
				BreakStatement();
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				Loop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body);
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
				ForLoop(std::shared_ptr<Statement> initStatement, std::shared_ptr<Expression> loopCondition, std::shared_ptr<Statement> iterationStatement, std::vector<std::shared_ptr<Statement>> body);
				
				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
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
				WhileLoop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body);

				virtual enum NodeType get_type() override;
				
				virtual std::string repr(int indent = 0) override;
				
				virtual std::string type_id() override;
			};

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
				TypeDeclaration(std::string typeName, std::vector<TypeMember> members);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
			};

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
				TypeImplementation(std::string typeName, std::vector<ImplMethod> methods);

				virtual enum NodeType get_type() override;

				virtual std::string repr(int indent = 0) override;

				virtual std::string type_id() override;
			};

			#pragma endregion
        }
    }
}

#endif // __ENT_FRONT_AST__