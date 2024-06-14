#ifndef __ENT_FRONT_PARSER__
#define __ENT_FRONT_PARSER__

#include <set>

#include "token.hpp"
#include "ast.hpp"
#include "errors.hpp"

namespace ent {
	namespace front {
		namespace parser {

			/**
			 * The list of tokens
			 * @note This list is provided by the lexer
			 */
			std::vector<ent::lexer::token> tks;

			/**
			 * The list of original identifiers
			 * 
			 * => Every identifier that is declared
			 */
			std::set<std::shared_ptr<ent::front::ast::Identifier>> original_identifiers;

			/**
			 * Get the original identifier with the same name as a given identifier
			 * @param identifier The identifier whose name to look for
			 * @return The original identifier or itself if not found
			 * @note `identifier` gets added to `original_identifiers` if there is no identifier with the same name
			 */
			std::shared_ptr<ent::front::ast::Identifier> get_original_identifier(std::shared_ptr<ent::front::ast::Identifier> identifier) {
				for(std::shared_ptr<ent::front::ast::Identifier> original_identifier : original_identifiers) {
					if(identifier->name == original_identifier->name) {
						return original_identifier;
					}
				}
				original_identifiers.insert(identifier);
				return identifier;
			}

			/**
			 * The Program Node
			 */
			std::shared_ptr<ent::front::ast::Program> program = std::make_shared<ent::front::ast::Program>(
				std::vector<std::shared_ptr<ent::front::ast::Statement>>()
			);

			/**
			 * The Conditionnal Block before the current node
			 * @note If the last parsed node is not a Conditionnal Block, it will be nullptr
			 * @note This is used to link `if` and `else` statements
			 */
			std::shared_ptr<ent::front::ast::ConditionnalBlock> before = nullptr;

			/**
			 * Get the current token
			 * @return The current token
			 */
			ent::lexer::token peek() {
				return tks.front();
			}

			/**
			 * Check whether the current token is an EOF token or not
			 * @return Whether the token is an EOF token
			 */
			bool eof() {
				return peek().get_type() == ent::lexer::token_type::EOF_TOKEN;
			}

			/**
			 * Remove the current token and return it
			 * @return The current token
			*/
			[[nodiscard]] ent::lexer::token eat() {
				ent::lexer::token tk = peek();
				tks.erase(tks.begin());
				return tk;
			}

			/**
			 * Expect the current token to be of a given type and throw an error if it is not what is expected
			 * @param type The type of the token to expect
			 * @param expected The string representation of the expected token (for error message)
			 * @return The current token
			 */
			[[nodiscard]] ent::lexer::token expect(ent::lexer::token_type type, std::string expected) {
				if(peek().get_type() == type) {
					return eat();
				}
				throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + ", got " + peek().get_value())).error();
			}

			/**
			 * Throw if the value is negative
			 * @param isNegative Whether the value is negative or not
			 */
			void check_for_negative(bool isNegative) {
				if(isNegative) {
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_NEGATIVE_VALUE_ERROR, "Expected signed integer or float after '-'")).error();
				}
			}

			// * EXPRESSIONS

			/**
			 * Parse an Identifier from the current token
			 * @return The Identifier
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_identifier();

			/**
			 * Parse a native expression from the current token
			 * @return The native expression
			 * 
			 * Prescedence #1
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_native_expression();

			/**
			 * Parse a Parenthesis Expression from the current token
			 * @return The Parenthesis Expression
			 * Prescedence #2
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_parenthesis_expression();

			/**
			 * Parse a Function Call Expression from the current token
			 * @return The Function Call Expression
			 * 
			 * Prescedence #3
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_function_call_expression();

			/**
			 * Parse a Unary Expression whose operator is after the term from the current token
			 * @return The Unary Expression
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_non_pre_unary_expression();

			/**
			 * Parse a Unary Expression from the current token
			 * @return The Unary Expression
			 * 
			 * Prescedence #4
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_unary_expression();

			/**
			 * Parse a Multiplicative Expression from the current token
			 * @return The Multiplicative Expression
			 * 
			 * Prescedence #5
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_multiplicative_expression();

			/**
			 * Parse an Additive Expression from the current token
			 * @return The Additive Expression
			 * 
			 * Prescedence #6
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_additive_expression();
			
			/**
			 * Parse a Logical Expression from the current token
			 * @return The Logical Expression
			 * 
			 * Prescedence #7
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_logical_expression();
			
			/**
			 * Parse a Ternary Expression from the current token
			 * @return The Ternary Expression
			 * 
			 * Prescedence #8
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_ternary_expression();

			/**
			 * Parse an Assignation Expression from the current token
			 * @return The Assignation Expression
			 * 
			 * Prescedence #9
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_assignation_expression();

			/**
			 * Parse an Expression from the current token
			 * @return The Expression
			 */
			std::shared_ptr<ent::front::ast::Expression> parse_expression();

			/**
			 * Create an assignation expression expecting a given type
			 * @param type The type to expect
			 * @param expected The expected thing as a string (for error)
			 * @param identifier The identifier to assign to
			 * @param value The value to assign
			 * @return The created Assignation Expression
			 */
			std::shared_ptr<ent::front::ast::AssignationExpression> expect_type_assignation_expression(
				ent::front::ast::NodeType type,
				std::string expected,
				std::shared_ptr<ent::front::ast::Identifier> identifier,
				std::shared_ptr<ent::front::ast::Expression> value
			);

			/**
			 * Parse a Declaration with any provided parameters
			 * @param isMutable Whether the declared value should be mutable
			 * @param identifier The Identifier to declare
			 * @param type_specifier The type specifier to use
			 * @param expectedAfterString The string expected after the declaration (throw if not found)
			 * @param applyExpect Whether to apply `expect` or `eat` on the expectedAfterString
			 * @return The created Declaration
			 */
			std::shared_ptr<ent::front::ast::Declaration> parse_any_declaration(
				bool isMutable,
				std::shared_ptr<ent::front::ast::Identifier> identifier,
				ent::lexer::token type_specifier,
				ent::lexer::token_type expectedAfter,
				std::string expectedAfterString,
				bool applyExpect = true
			);

			/**
			 * Parse a Declaration from the current token
			 * @return The Declaration
			 */
			std::shared_ptr<ent::front::ast::Statement> parse_declaration(bool needsSemicolon);

			/**
			 * Make a Declaration from a Declaration an a new value
			 * @param declarationExpression The original Declaration
			 * @param value The value to put in the Declaration
			 * @param isMutable Whether the declared value should be mutable or not
			 * @param isInFunctionSetup Whether the declaration is a function argument setup
			 */
			std::shared_ptr<ent::front::ast::Declaration> make_declaration(
				std::shared_ptr<ent::front::ast::Declaration> declarationExpression,
				std::shared_ptr<ent::front::ast::Expression> value,
				bool isMutable,
				bool isInFunctionSetup = false
			);

			/**
			 * Parse a Statement from the current token
			 * @param updateBefore Whether to set before to `nullptr` (false when inside a Conditionnal Block)
			 * @param needsSemiColon Whether this Statement needs to end with a semicolon
			 * @return The Statement
			 */
			std::shared_ptr<ent::front::ast::Statement> parse_statement(
				bool updateBefore = true,
				bool needsSemiColon = true
			);

			/**
			 * Parse the arguments from the current token
			 * @return The arguments list
			 */
			std::vector<std::shared_ptr<ent::front::ast::Declaration>> parse_arguments();

			/**
			 * Parse a Scope from the current token
			 * @param scopeType The type of the scope
			 * @return The body of the scope
			 */
			std::vector<std::shared_ptr<ent::front::ast::Statement>> parse_scope(
				std::string scopeType
			);

			/**
			 * Parse a Function Declaration from the current token
			 * @param identifier The function identifier (will be parsed if equal to `nullptr`)
			 * @return The Function Declaration
			 */
			std::shared_ptr<ent::front::ast::Statement> parse_function_declaration(
				std::shared_ptr<ent::front::ast::Identifier> identifier = nullptr
			);

			/**
			 * Parse a Function Return from the current token
			 * @return The Function Return
			 */
			std::shared_ptr<ent::front::ast::FunctionReturn> parse_function_return();

			/**
			 * Parse a Conditionnal Block from the current token
			 * @return The Conditionnal Block
			 */
			std::shared_ptr<ent::front::ast::ConditionnalBlock> parse_conditionnal_block();

			/**
			 * Parse a Conditionnal Structure from the current token
			 * @return The Conditionnal Structure
			 */
			std::shared_ptr<ent::front::ast::ConditionnalStructure> parse_conditionnal_structure();

			/**
			 * Parse a For Loop from the current token
			 * @return The For Loop
			 */
			std::shared_ptr<ent::front::ast::ForLoop> parse_for_loop();

			/**
			 * Parse a While Loop from the current token
			 * @return The While Loop
			 */
			std::shared_ptr<ent::front::ast::WhileLoop> parse_while_loop();

			/**
			 * Parse a Conditionnal Block from the current token
			 * @return The Conditionnal Block
			 */
			std::shared_ptr<ent::front::ast::ConditionnalBlock> parse_match_case();

			/**
			 * Parse a Match Structure from the current token
			 * @return The Match Structure
			 */
			std::shared_ptr<ent::front::ast::MatchStructure> parse_match_structure();

			/**
			 * Parse a Break Statement from the current token
			 * @return The Break Statement
			 */
			std::shared_ptr<ent::front::ast::BreakStatement> parse_break_statement();

			/**
			 * Parse a Type Declaration from the current token
			 * @return The Type Declaration
			 */
			std::shared_ptr<ent::front::ast::TypeDeclaration> parse_type_declaration();

			/**
			 * Parse a Type Implementation from the current token
			 * @return The Type Implementation
			 */
			std::shared_ptr<ent::front::ast::TypeImplementation> parse_type_implementation();

			std::shared_ptr<ent::front::ast::Statement> parse_statement(
				bool updateBefore,
				bool needsSemicolon
			);

			std::shared_ptr<ent::front::ast::Program> parse(
				std::vector<ent::lexer::token> tokens
			);


			std::shared_ptr<ent::front::ast::Expression> parse_identifier() {
				if(peek().get_type() == ent::lexer::token_type::IDENTIFIER) {
					std::string value = peek().get_value();
					(void)eat();
					return get_original_identifier(std::make_shared<ent::front::ast::Identifier>(value));
				}
				throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected identifier, got " + peek().get_value())).error();
			}

			std::shared_ptr<ent::front::ast::Expression> parse_native_expression() {
				bool isNegative = false;
				if(peek().get_type() == ent::lexer::token_type::MINUS) {
					isNegative = true;
					(void)eat();
				}
				// If the current token is a number
				if(peek().get_type() == ent::lexer::token_type::I8) {
					// Parse the number
					i8 value = types::stoi8(peek().get_value());
					(void)eat();
					// Return the integer expression
					return std::make_shared<ent::front::ast::I8Expression>(isNegative ? -value : value);
				} else if(peek().get_type() == ent::lexer::token_type::I16) {
					// Parse the number
					i16 value = types::stoi16(peek().get_value());
					(void)eat();
					// Return the integer expression
					return std::make_shared<ent::front::ast::I16Expression>(isNegative ? -value : value);
				} else if(peek().get_type() == ent::lexer::token_type::I32) {
					// Parse the number
					i32 value = types::stoi32(peek().get_value());
					(void)eat();
					// Return the integer expression
					return std::make_shared<ent::front::ast::I32Expression>(isNegative ? -value : value);
				} else if(peek().get_type() == ent::lexer::token_type::I64) {
					// Parse the number
					i64 value = types::stoi64(peek().get_value());
					(void)eat();
					// Return the integer expression
					return std::make_shared<ent::front::ast::I64Expression>(isNegative ? -value : value);
				} else if(peek().get_type() == ent::lexer::token_type::U64) {
					check_for_negative(isNegative);
					// Parse the number
					u64 value = types::stou64(peek().get_value());
					(void)eat();
					// Return the integer expression
					return std::make_shared<ent::front::ast::U64Expression>(value);
				} else if(peek().get_type() == ent::lexer::token_type::F32) {
					// Parse the number
					float value = types::stof32(peek().get_value());
					(void)eat();
					// Return the float expression
					return std::make_shared<ent::front::ast::F32Expression>(isNegative ? -value : value);
				} else if(peek().get_type() == ent::lexer::token_type::F64) {
					// Parse the number
					double value = types::stof64(peek().get_value());
					(void)eat();
					// Return the float expression
					return std::make_shared<ent::front::ast::F64Expression>(value);
				} else if(peek().get_type() == ent::lexer::token_type::BOOL) {
					check_for_negative(isNegative);
					bool value = eat().get_value() == "true";
					return std::make_shared<ent::front::ast::BooleanExpression>(value);
				} else if(peek().get_type() == ent::lexer::token_type::CHAR) {
					check_for_negative(isNegative);
					char value = eat().get_value()[0];
					return std::make_shared<ent::front::ast::CharExpression>(value);
				} else if(peek().get_type() == ent::lexer::token_type::STR) {
					check_for_negative(isNegative);
					std::string value = eat().get_value();
					return std::make_shared<ent::front::ast::StrExpression>(value);
				}
				return parse_identifier();
			}

			std::shared_ptr<ent::front::ast::Expression> parse_parenthesis_expression() {
				if(peek().get_type() != ent::lexer::token_type::OPEN_PAREN) {
					return parse_native_expression();
				}
				(void)eat();
				std::shared_ptr<ent::front::ast::Expression> content = parse_expression();
				if(peek().get_type() != ent::lexer::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_EXPRESSION_IN_PARENTHESIS, "Invalid expression in parenthesis")).error();
				}
				(void)eat();
				return std::make_shared<ent::front::ast::ParenthesisExpression>(content);
			}

			std::shared_ptr<ent::front::ast::Expression> parse_function_call_expression() {

				std::shared_ptr<ent::front::ast::Expression> call_expr = parse_parenthesis_expression();

				if(peek().get_type() != ent::lexer::token_type::OPEN_PAREN) {
					return call_expr;
				}
				(void)eat();

				if(call_expr->get_type() != ent::front::ast::NodeType::identifier) {
					throw (ent::Error(ent::ErrorType::PARSER_CALLING_NON_FN_ERROR, "Trying to call non-function expression")).error();
				}

				if(ent::front::ast::get_function(std::dynamic_pointer_cast<ent::front::ast::Identifier>(call_expr)) == nullptr) {
					throw (ent::Error(ent::ErrorType::PARSER_CALLING_UNDECLARED_FN_ERROR, "Trying to call undeclared function")).error();
				}

				std::vector<std::shared_ptr<ent::front::ast::Expression>> arguments = std::vector<std::shared_ptr<ent::front::ast::Expression>>();

				if(peek().get_type() == ent::lexer::token_type::TYPE_SPECIFIER && peek().get_value() == "void") {
					(void)eat();
				} else if(peek().get_type() == ent::lexer::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				} else {
					arguments.push_back(parse_expression());

					while(peek().get_type() != ent::lexer::token_type::CLOSE_PAREN) {
						(void)expect(ent::lexer::token_type::COMMA, "comma");
						arguments.push_back(std::dynamic_pointer_cast<ent::front::ast::Expression>(parse_expression()));
					}
				}

				(void)expect(ent::lexer::token_type::CLOSE_PAREN, ")");

				return std::make_shared<ent::front::ast::FunctionCallExpression>(std::dynamic_pointer_cast<ent::front::ast::Identifier>(call_expr), arguments);
			}

			std::shared_ptr<ent::front::ast::Expression> parse_non_pre_unary_expression() {
				std::shared_ptr<ent::front::ast::Expression> term = parse_function_call_expression();
				if(peek().get_type() == ent::lexer::token_type::INCREMENT || peek().get_type() == ent::lexer::token_type::DECREMENT) {
					std::string operator_symbol = eat().get_value();
					if(term->get_type() != ent::front::ast::NodeType::identifier) {
						throw (ent::Error(ent::ErrorType::PARSER_TRYING_TO_INCREMENT_NON_IDENTIFIER_ERROR, "Trying to increment non-identifier")).error();
					}
					return std::make_shared<ent::front::ast::UnaryExpression>(
						term,
						operator_symbol
					);
				}
				return term;
			}

			std::shared_ptr<ent::front::ast::Expression> parse_unary_expression() {
				if(peek().get_type() != ent::lexer::token_type::NOT && peek().get_type() != ent::lexer::token_type::BITWISE_NOT) {
					return parse_non_pre_unary_expression();
				}

				std::string operator_symbol = eat().get_value();
				std::shared_ptr<ent::front::ast::Expression> term = parse_parenthesis_expression();
				
				return std::make_shared<ent::front::ast::UnaryExpression>(
					term,
					operator_symbol
				);
			}

			std::shared_ptr<ent::front::ast::Expression> parse_multiplicative_expression() {
				// Parse the numeric expression first
				std::shared_ptr<ent::front::ast::Expression> left = parse_unary_expression();
				// Parse the rest of the expression
				while(peek().get_value() == "*" || peek().get_value() == "/" || peek().get_value() == "%") {
					std::string operator_symbol = peek().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					std::shared_ptr<ent::front::ast::Expression> right = parse_unary_expression();
					// Set the left as a binary expression
					left = std::make_shared<ent::front::ast::BinaryExpression>(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			std::shared_ptr<ent::front::ast::Expression> parse_additive_expression() {
				// Parse the multiplicative expression first
				std::shared_ptr<ent::front::ast::Expression> left = parse_multiplicative_expression();
				// Parse the rest of the expression
				while(peek().get_value() == "+" || peek().get_value() == "-") {
					std::string operator_symbol = peek().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					std::shared_ptr<ent::front::ast::Expression> right = parse_multiplicative_expression();
					// Set the left as a binary expression
					left = std::make_shared<ent::front::ast::BinaryExpression>(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			std::shared_ptr<ent::front::ast::Expression> parse_logical_expression() {
				// Parse the multiplicative expression first
				std::shared_ptr<ent::front::ast::Expression> left = parse_additive_expression();
				// Parse the rest of the expression
				while(
					peek().get_value() == "==" || peek().get_value() == "!=" ||
					peek().get_value() == "&&" || peek().get_value() == "||" ||
					peek().get_value() == "<" || peek().get_value() == ">" ||
					peek().get_value() == "<=" || peek().get_value() == ">=" ||
					peek().get_value() == "^^" ||
					peek().get_value() == "<<" || peek().get_value() == ">>" ||
					peek().get_value() == "&" || peek().get_value() == "|" || peek().get_value() == "^"
				) {
					std::string operator_symbol = peek().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					std::shared_ptr<ent::front::ast::Expression> right = parse_additive_expression();
					// Set the left as a binary expression
					left = std::make_shared<ent::front::ast::BinaryExpression>(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			std::shared_ptr<ent::front::ast::Expression> parse_ternary_expression() {
				// Parse the multiplicative expression first
				std::shared_ptr<ent::front::ast::Expression> condition = parse_logical_expression();

				if(peek().get_type() != ent::lexer::token_type::QUESTION_MARK) {
					return condition;
				}
				(void)eat();
				std::shared_ptr<ent::front::ast::Expression> true_value = parse_ternary_expression();

				(void)expect(ent::lexer::token_type::COLON, "colon after \"true\" value");

				std::shared_ptr<ent::front::ast::Expression> false_value = parse_ternary_expression();

				return std::make_shared<ent::front::ast::TernaryExpression>(condition, true_value, false_value);
			}

			std::shared_ptr<ent::front::ast::Expression> parse_assignation_expression() {

				std::shared_ptr<ent::front::ast::Expression> assign_expr = parse_ternary_expression();

				ent::lexer::token op = ent::lexer::token(ent::lexer::token_type::EOF_TOKEN, "");

				if(
					peek().get_type() == ent::lexer::token_type::PLUS || peek().get_type() == ent::lexer::token_type::MINUS ||
					peek().get_type() == ent::lexer::token_type::TIMES || peek().get_type() == ent::lexer::token_type::DIVIDED_BY ||
					peek().get_type() == ent::lexer::token_type::MODULO ||
					peek().get_type() == ent::lexer::token_type::BITWISE_AND || peek().get_type() == ent::lexer::token_type::BITWISE_OR || peek().get_type() == ent::lexer::token_type::BITWISE_XOR
				) {
					op = eat();
				}

				if(peek().get_type() != ent::lexer::token_type::ASSIGN) {
					if(op.get_type() != ent::lexer::token_type::EOF_TOKEN) {
						tks.insert(tks.begin(), op);
					}
					return assign_expr;
				}

				(void)eat();

				if(assign_expr->get_type() != ent::front::ast::NodeType::identifier) {
					throw (ent::Error(ent::ErrorType::PARSER_ASSIGNING_NON_IDENTIFIER_ERROR, "Function misses explicit VOID param passing")).error();
				}

				std::shared_ptr<ent::front::ast::Identifier> identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(assign_expr);

				std::shared_ptr<ent::front::ast::Expression> value = parse_ternary_expression();

				if(op.get_type() != ent::lexer::token_type::EOF_TOKEN) {
					value = std::make_shared<ent::front::ast::BinaryExpression>(identifier, op.get_value(), value);
				}
				
				return std::make_shared<ent::front::ast::AssignationExpression>(identifier, value);
			}
			

			std::shared_ptr<ent::front::ast::Expression> parse_expression() {
				return parse_assignation_expression();
			}

			std::shared_ptr<ent::front::ast::AssignationExpression> expect_type_assignation_expression(ent::front::ast::NodeType type, std::string expected, std::shared_ptr<ent::front::ast::Identifier> identifier, std::shared_ptr<ent::front::ast::Expression> value) {
				// TODO: Fix casting (unsigned integers impossible to declare)
				if(!is_valid_cast(value, type)) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + " expression, got " + value->type_id())).error();
				}
				identifier->set_identifier_type(type);
				return std::make_shared<ent::front::ast::AssignationExpression>(identifier, value);
			}

			std::shared_ptr<ent::front::ast::Declaration> parse_any_declaration(bool isMutable, std::shared_ptr<ent::front::ast::Identifier> identifier, ent::lexer::token type_specifier, ent::lexer::token_type expectedAfter, std::string expectedAfterString, bool applyExpect) {
				ent::lexer::token next = peek();

				if(next.get_type() != ent::lexer::token_type::ASSIGN) {
					std::string type = type_specifier.get_value();
					if(applyExpect) {
						(void)expect(expectedAfter, expectedAfterString);
					}
					if(type == "void") {
						throw (ent::Error(ent::ErrorType::PARSER_INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
					} else if(type == "i8") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i8Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::I8Expression>(), isMutable);
					} else if(type == "i16") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i16Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::I16Expression>(), isMutable);
					} else if(type == "i32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i32Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::I32Expression>(), isMutable);
					} else if(type == "i64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i64Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::I64Expression>(), isMutable);
					} else if(type == "u8") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u8Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::U8Expression>(), isMutable);
					} else if(type == "u16") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u16Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::U16Expression>(), isMutable);
					} else if(type == "u32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u32Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::U32Expression>(), isMutable);
					} else if(type == "u64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u64Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::U64Expression>(), isMutable);
					} else if(type == "f32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::f32Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::F32Expression>(), isMutable);
					} else if(type == "f64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::f64Expression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::F64Expression>(), isMutable);
					} else if(type == "bool") {
						identifier->set_identifier_type(ent::front::ast::NodeType::booleanExpression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::BooleanExpression>(), isMutable);
					} else if(type == "char") {
						identifier->set_identifier_type(ent::front::ast::NodeType::charExpression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::CharExpression>(), isMutable);
					} else if(type == "str") {
						identifier->set_identifier_type(ent::front::ast::NodeType::strExpression);
						return std::make_shared<ent::front::ast::Declaration>(identifier, std::make_shared<ent::front::ast::StrExpression>(), isMutable);
					}
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
				}

				return nullptr;
			}

			std::shared_ptr<ent::front::ast::Statement> parse_declaration(bool needsSemicolon) {

				bool isMutable = false;

				if(peek().get_type() == ent::lexer::token_type::MUTABLE) {
					(void)eat();
					isMutable = true;
				}

				std::shared_ptr<ent::front::ast::Identifier> identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(parse_identifier());
				(void)expect(ent::lexer::token_type::COLON, ":");
				ent::lexer::token type_specifier = expect(ent::lexer::token_type::TYPE_SPECIFIER, "type specifier");

				ent::lexer::token next = peek();

				std::shared_ptr<ent::front::ast::Declaration> statement = parse_any_declaration(
					isMutable,
					identifier,
					type_specifier,
					ent::lexer::token_type::SEMICOLON,
					";",
					needsSemicolon
				);
				
				if(statement != nullptr) {
					return statement;
				}
				// Means next.get_type() == ent::type::token_type::ASSIGN
				(void)eat();
				std::shared_ptr<ent::front::ast::Expression> value = parse_expression();
				std::string type = type_specifier.get_value();
				if(needsSemicolon) {
					(void)expect(ent::lexer::token_type::SEMICOLON, ";");
				}
				if(type == "void") {
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
				} else if(type == "i8") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::i8Expression, "i8", identifier, value), isMutable);
				} else if(type == "i16") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::i16Expression, "i16", identifier, value), isMutable);
				} else if(type == "i32") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::i32Expression, "i32", identifier, value), isMutable);
				} else if(type == "i64") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::i64Expression, "i64", identifier, value), isMutable);
				} else if(type == "u8") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::u8Expression, "u8", identifier, value), isMutable);
				} else if(type == "u16") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::u16Expression, "u16", identifier, value), isMutable);
				} else if(type == "u32") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::u32Expression, "u32", identifier, value), isMutable);
				} else if(type == "u64") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::u64Expression, "u64", identifier, value), isMutable);
				} else if(type == "f32") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::f32Expression, "f32", identifier, value), isMutable);
				} else if(type == "f64") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::f64Expression, "f64", identifier, value), isMutable);
				} else if(type == "bool") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::booleanExpression, "bool", identifier, value), isMutable);
				} else if(type == "char") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::charExpression, "char", identifier, value), isMutable);
				} else if(type == "str") {
					return std::make_shared<ent::front::ast::Declaration>(expect_type_assignation_expression(ent::front::ast::NodeType::strExpression, "str", identifier, value), isMutable);
				}
				throw (ent::Error(ent::ErrorType::PARSER_INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
			}

			std::shared_ptr<ent::front::ast::Declaration> make_declaration(std::shared_ptr<ent::front::ast::Declaration> declarationExpression, std::shared_ptr<ent::front::ast::Expression> value, bool isMutable, bool isInFunctionSetup) {
				return std::make_shared<ent::front::ast::Declaration>(declarationExpression->identifier, value, isMutable, isInFunctionSetup);
			}

			std::shared_ptr<ent::front::ast::Statement> parse_statement(bool updateBefore, bool needsSemiColon);

			std::vector<std::shared_ptr<ent::front::ast::Declaration>> parse_arguments() {

				std::vector<std::shared_ptr<ent::front::ast::Declaration>> arguments = std::vector<std::shared_ptr<ent::front::ast::Declaration>>();

				while(true) {
					bool isMutable = false;

					if(peek().get_type() == ent::lexer::token_type::MUTABLE) {
						(void)eat();
						isMutable = true;
					}

					std::shared_ptr<ent::front::ast::Identifier> identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(parse_identifier());
					(void)expect(ent::lexer::token_type::COLON, ":");
					ent::lexer::token type_specifier = expect(ent::lexer::token_type::TYPE_SPECIFIER, "type specifier");

					std::shared_ptr<ent::front::ast::Declaration> declaration;
					
					try {
						declaration = parse_any_declaration(
							isMutable,
							identifier,
							type_specifier,
							ent::lexer::token_type::COMMA,
							","
						);
					} catch(const std::exception& e) {
						declaration = parse_any_declaration(
							isMutable,
							identifier,
							type_specifier,
							ent::lexer::token_type::CLOSE_PAREN,
							")"
						);
						arguments.push_back(declaration);
						break;
					}

					arguments.push_back(declaration);
				}

				return arguments;
			}

			std::vector<std::shared_ptr<ent::front::ast::Statement>> parse_scope(std::string scopeType) {

				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace at start of " + scopeType);

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace at end of " + scopeType);

				return body;
			}

			std::shared_ptr<ent::front::ast::Statement> parse_function_declaration(std::shared_ptr<ent::front::ast::Identifier> identifier) {

				if(identifier == nullptr) {
					identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(parse_identifier());
				}

				(void)expect(ent::lexer::token_type::OPEN_PAREN, "open parenthesis");

				std::vector<std::shared_ptr<ent::front::ast::Declaration>> arguments = std::vector<std::shared_ptr<ent::front::ast::Declaration>>();

				if(peek().get_type() == ent::lexer::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				}
				if(peek().get_type() == ent::lexer::token_type::TYPE_SPECIFIER && peek().get_value() == "void") {
					(void)eat();
					(void)expect(ent::lexer::token_type::CLOSE_PAREN, "close parenthesis");
				} else {
					arguments = parse_arguments();
				}

				(void)expect(ent::lexer::token_type::COLON, "colon");

				std::string returnType = expect(ent::lexer::token_type::TYPE_SPECIFIER, "type specifier").get_value();

				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace at start of function");

				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace at end of function");
				
				std::shared_ptr<ent::front::ast::FunctionDeclaration> function = std::make_shared<ent::front::ast::FunctionDeclaration>(identifier, returnType, arguments, body);

				ent::front::ast::functions.push_back(function);

				return function;
			}

			std::shared_ptr<ent::front::ast::FunctionReturn> parse_function_return() {
				(void)eat();

				std::shared_ptr<ent::front::ast::Expression> value = parse_expression();

				(void)expect(ent::lexer::token_type::SEMICOLON, "semicolon at the end of line");

				return std::make_shared<ent::front::ast::FunctionReturn>(value);
			}

			std::shared_ptr<ent::front::ast::ConditionnalBlock> parse_conditionnal_block() {

				enum ConditionType {
					IF,
					ELSE_IF,
					ELSE
				};
				enum ConditionType conditionType = ConditionType::IF;

				if(peek().get_type() == ent::lexer::token_type::ELSE) {
					if(before == nullptr) {
						throw (ent::Error(ent::ErrorType::PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE, "Else keyword misses if clause before it")).error();
					}
					(void)eat();
					conditionType = peek().get_type() == ent::lexer::IF ? ConditionType::ELSE_IF : ConditionType::ELSE;
				}

				std::shared_ptr<ent::front::ast::Expression> condition = nullptr;

				if(conditionType != ConditionType::ELSE) {
					(void)expect(ent::lexer::token_type::IF, "if keyword");

					if(peek().get_type() == ent::lexer::token_type::ELSE) {
						if(before == nullptr) {
							throw (ent::Error(ent::ErrorType::PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE, "Else keyword misses if clause before it")).error();
						}
						(void)eat();
					}
					
					(void)expect(ent::lexer::token_type::OPEN_PAREN, "open parenthesis before condition");
				
					condition = parse_expression();

					(void)expect(ent::lexer::token_type::CLOSE_PAREN, "close parenthesis after condition");
				}

				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				body = parse_scope("conditionnal block");

				std::shared_ptr<ent::front::ast::ConditionnalBlock> conditionnalBlock = std::make_shared<ent::front::ast::ConditionnalBlock>(body, condition, false);

				if(conditionType != ConditionType::IF) {
					conditionnalBlock->before = before;
				}

				before = conditionnalBlock;

				return conditionnalBlock;
			}

			std::shared_ptr<ent::front::ast::ConditionnalStructure> parse_conditionnal_structure() {

				std::vector<std::shared_ptr<ent::front::ast::ConditionnalBlock>> blocks = std::vector<std::shared_ptr<ent::front::ast::ConditionnalBlock>>();

				while(peek().get_type() == ent::lexer::token_type::IF || peek().get_type() == ent::lexer::token_type::ELSE) {
					blocks.push_back(parse_conditionnal_block());
				}

				return std::make_shared<ent::front::ast::ConditionnalStructure>(blocks);
			}

			std::shared_ptr<ent::front::ast::ForLoop> parse_for_loop() {
				(void)expect(ent::lexer::token_type::OPEN_PAREN, "open parenthesis after for keyword");

				std::shared_ptr<ent::front::ast::Statement> initStatement = parse_statement(true, false);
				(void)expect(ent::lexer::token_type::SEMICOLON, "semicolon after for init statement");
				std::shared_ptr<ent::front::ast::Expression> loopCondition = parse_expression();
				(void)expect(ent::lexer::token_type::SEMICOLON, "semicolon after for condition");
				std::shared_ptr<ent::front::ast::Statement> iterationStatement = parse_statement(true, false);

				(void)expect(ent::lexer::token_type::CLOSE_PAREN, "close parenthesis after for iteration statement");

				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				body = parse_scope("for loop");

				return std::make_shared<ent::front::ast::ForLoop>(initStatement, loopCondition, iterationStatement, body);
			}

			std::shared_ptr<ent::front::ast::WhileLoop> parse_while_loop() {
				(void)eat();

				(void)expect(ent::lexer::token_type::OPEN_PAREN, "open parenthesis after while keyword");
				std::shared_ptr<ent::front::ast::Expression> loopCondition = parse_expression();
				(void)expect(ent::lexer::token_type::CLOSE_PAREN, "close parenthesis after while condition");

				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace before while body");

				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace after while body");

				return std::make_shared<ent::front::ast::WhileLoop>(loopCondition, body);
			}

			std::shared_ptr<ent::front::ast::ConditionnalBlock> parse_match_case() {

				std::shared_ptr<ent::front::ast::Expression> caseToMatch = nullptr;

				if(peek().get_type() != ent::lexer::token_type::DEFAULT) {
					caseToMatch = parse_expression();
				} else {
					(void)eat();
				}

				(void)expect(ent::lexer::token_type::MATCH_ARROW, "match arrow after expression");


				std::vector<std::shared_ptr<ent::front::ast::Statement>> body = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				body = parse_scope("match case");

				return std::make_shared<ent::front::ast::ConditionnalBlock>(body, caseToMatch, true);
			}

			std::shared_ptr<ent::front::ast::MatchStructure> parse_match_structure() {

				std::vector<std::shared_ptr<ent::front::ast::ConditionnalBlock>> cases = std::vector<std::shared_ptr<ent::front::ast::ConditionnalBlock>>();

				(void)eat();

				(void)expect(ent::lexer::token_type::OPEN_PAREN, "open parenthesis before match expression");

				std::shared_ptr<ent::front::ast::Expression> matchExpression = parse_expression();

				(void)expect(ent::lexer::token_type::CLOSE_PAREN, "close parenthesis after match expression");
				
				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace before match body");

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					cases.push_back(parse_match_case());
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace after match body");

				return std::make_shared<ent::front::ast::MatchStructure>(matchExpression, cases);
			}

			std::shared_ptr<ent::front::ast::BreakStatement> parse_break_statement() {
				
				(void)eat();

				(void)expect(ent::lexer::token_type::SEMICOLON, "semi colon at the end of line");

				return std::make_shared<ent::front::ast::BreakStatement>();
			}

			std::shared_ptr<ent::front::ast::TypeDeclaration> parse_type_declaration() {
				(void)eat();

				ent::lexer::token typeName = expect(ent::lexer::token_type::TYPE_SPECIFIER, "valid type name to implement");

				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace before type declaration body");
				
				std::vector<ent::front::ast::TypeMember> members = std::vector<ent::front::ast::TypeMember>();

				enum ent::front::ast::ClassAccessSpecifier currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PUBLIC;

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					if(peek().get_type() == ent::lexer::token_type::AT) {
						(void)eat();
						if(peek().get_type() == ent::lexer::PRIVATE) {
							currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PRIVATE;
							(void)eat();
							continue;
						}
						if(peek().get_type() == ent::lexer::PUBLIC) {
							currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PUBLIC;
							(void)eat();
							continue;
						}
						throw (ent::Error(ent::ErrorType::PARSER_INVALID_ACCESS_SPECIFIER_ERROR, "Expected valid access specifier, got " + peek().get_value())).error();
					}
					std::shared_ptr<ent::front::ast::Declaration> declaration = std::dynamic_pointer_cast<ent::front::ast::Declaration>(
						parse_declaration(true)
					);
					members.push_back(ent::front::ast::TypeMember{
						declaration,
						currentAccessSpecifier
					});
				}

				if(members.size() == 0) {
					throw (ent::Error(ent::ErrorType::PARSER_EMPTY_TYPE_DECLARATION_ERROR, "At least one member is required in a type declaration")).error();
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace after type declaration body");

				std::shared_ptr<ent::front::ast::TypeDeclaration> typeDeclaration = std::make_shared<ent::front::ast::TypeDeclaration>(typeName.get_value(), members);

				return typeDeclaration;
			}

			std::shared_ptr<ent::front::ast::TypeImplementation> parse_type_implementation() {

				(void)eat();

				ent::lexer::token typeName = expect(ent::lexer::token_type::TYPE_SPECIFIER, "valid type name to implement");

				(void)expect(ent::lexer::token_type::OPEN_BRACE, "open brace before type implementation body");
				
				std::vector<ent::front::ast::ImplMethod> methods = std::vector<ent::front::ast::ImplMethod>();

				enum ent::front::ast::ClassAccessSpecifier currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PUBLIC;

				while(peek().get_type() != ent::lexer::token_type::CLOSE_BRACE) {
					if(peek().get_type() == ent::lexer::token_type::AT) {
						(void)eat();
						if(peek().get_type() == ent::lexer::PRIVATE) {
							currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PRIVATE;
							(void)eat();
							continue;
						}
						if(peek().get_type() == ent::lexer::PUBLIC) {
							currentAccessSpecifier = ent::front::ast::ClassAccessSpecifier::PUBLIC;
							(void)eat();
							continue;
						}
						throw (ent::Error(ent::ErrorType::PARSER_INVALID_ACCESS_SPECIFIER_ERROR, "Expected valid access specifier, got " + peek().get_value())).error();
					}

					(void)expect(ent::lexer::token_type::FN, "Function in type implementation");

					std::shared_ptr<ent::front::ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ent::front::ast::FunctionDeclaration>(
						parse_function_declaration()
					);
					methods.push_back({
						functionDeclaration,
						currentAccessSpecifier
					});
				}

				if(methods.size() == 0) {
					throw (ent::Error(ent::ErrorType::PARSER_EMPTY_TYPE_IMPLEMENTATION_ERROR, "At least one method is required in a type implementation")).error();
				}

				(void)expect(ent::lexer::token_type::CLOSE_BRACE, "close brace after class body");

				return std::make_shared<ent::front::ast::TypeImplementation>(typeName.get_value(), methods);
			}

			std::shared_ptr<ent::front::ast::Statement> parse_statement(bool updateBefore, bool needsSemicolon) {

				if(peek().get_type() == ent::lexer::token_type::LET) {
					(void)eat();
					std::shared_ptr<ent::front::ast::Statement> declaration = parse_declaration(needsSemicolon);
					if(updateBefore) { before = nullptr; }
					return declaration;
				}
				if(peek().get_type() == ent::lexer::token_type::FN) {
					(void)eat();
					std::shared_ptr<ent::front::ast::Statement> function_declaration = parse_function_declaration();
					if(updateBefore) { before = nullptr; }
					return function_declaration;
				}
				if(peek().get_type() == ent::lexer::token_type::RETURN) {
					std::shared_ptr<ent::front::ast::Statement> functionReturn = parse_function_return();
					if(updateBefore) { before = nullptr; }
					return functionReturn;
				}
				if(peek().get_type() == ent::lexer::token_type::IF || peek().get_type() == ent::lexer::token_type::ELSE) {
					return parse_conditionnal_structure();
				}
				if(peek().get_type() == ent::lexer::token_type::FOR) {
					(void)eat();
					std::shared_ptr<ent::front::ast::Statement> for_loop = parse_for_loop();
					if(updateBefore) { before = nullptr; }
					return for_loop;
				}
				if(peek().get_type() == ent::lexer::token_type::WHILE) {
					std::shared_ptr<ent::front::ast::Statement> whileLoop = parse_while_loop();
					if(updateBefore) { before = nullptr; }
					return whileLoop;
				}
				if(peek().get_type() == ent::lexer::token_type::MATCH) {
					std::shared_ptr<ent::front::ast::Statement> matchStructure = parse_match_structure();
					if(updateBefore) { before = nullptr; }
					return matchStructure;
				}
				if(peek().get_type() == ent::lexer::token_type::BREAK) {
					std::shared_ptr<ent::front::ast::Statement> breakStatement = parse_break_statement();
					if(updateBefore) { before = nullptr; }
					return breakStatement;
				}
				if(peek().get_type() == ent::lexer::token_type::TYPE) {
					std::shared_ptr<ent::front::ast::Statement> typeDeclaration = parse_type_declaration();
					if(updateBefore) { before = nullptr; }
					return typeDeclaration;
				}
				if(peek().get_type() == ent::lexer::token_type::IMPL) {
					std::shared_ptr<ent::front::ast::Statement> typeImplementation = parse_type_implementation();
					if(updateBefore) { before = nullptr; }
					return typeImplementation;
				}

				std::shared_ptr<ent::front::ast::Expression> expression = parse_expression();
				if(needsSemicolon) {
					(void)expect(ent::lexer::token_type::SEMICOLON, "semi colon at end of line");
				}
				if(updateBefore) { before = nullptr; }

				return expression;
			}

			std::shared_ptr<ent::front::ast::Program> parse(std::vector<ent::lexer::token> tokens) {
				tks = tokens;

				std::cout << peek().repr() << std::endl;
				while(!eof()) {
					program->body.push_back(parse_statement());
				}

				return program;
			}
		}
    }
}

#endif // __ENT_FRONT_PARSER__