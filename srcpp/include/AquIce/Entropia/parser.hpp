#ifndef __ENT_FRONT_PARSER__
#define __ENT_FRONT_PARSER__

#include "token.hpp"
#include "ast.hpp"
#include "errors.hpp"

namespace ent {
	namespace front {
		namespace parser {

			std::vector<ent::type::token> tks;

			std::vector<ent::front::ast::Identifier*> original_identifiers;

			ent::front::ast::Identifier* get_original_identifier(ent::front::ast::Identifier* identifier) {
				for(ent::front::ast::Identifier* original_identifier : original_identifiers) {
					if(identifier->name == original_identifier->name) {
						return original_identifier;
					}
				}
				original_identifiers.push_back(identifier);
				return identifier;
			}

			ent::front::ast::Program* program = new ent::front::ast::Program(
				std::vector<ent::front::ast::Statement*>()
			);

			ent::front::ast::ConditionnalBlock* before = nullptr;

			ent::type::token peek() {
				return tks.front();
			}

			bool eof() {
				return peek().get_type() == ent::type::token_type::EOF_TOKEN;
			}

			ent::type::token eat() {
				ent::type::token tk = peek();
				tks.erase(tks.begin());
				return tk;
			}

			ent::type::token expect(ent::type::token_type type, std::string expected) {
				if(peek().get_type() == type) {
					return eat();
				}
				throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + ", got " + peek().get_value())).error();
			}

			ent::front::ast::Expression* parse_identifier() {
				if(peek().get_type() == ent::type::token_type::IDENTIFIER) {
					std::string value = peek().get_value();
					(void)eat();
					return get_original_identifier(new ent::front::ast::Identifier(value));
				}
				throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected identifier, got " + peek().get_value())).error();
			}

			ent::front::ast::Expression* parse_expression();

			ent::front::ast::Expression* parse_numeric_expression() {
				// If the current token is a number
				if(peek().get_type() == ent::type::token_type::I8) {
					// Parse the number
					i8 value = types::stoi8(peek().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I8Expression(value);
				} else if(peek().get_type() == ent::type::token_type::I16) {
					// Parse the number
					i16 value = types::stoi16(peek().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I16Expression(value);
				} else if(peek().get_type() == ent::type::token_type::I32) {
					// Parse the number
					i32 value = types::stoi32(peek().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I32Expression(value);
				} else if(peek().get_type() == ent::type::token_type::I64) {
					// Parse the number
					i64 value = types::stoi64(peek().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I64Expression(value);
				} else if(peek().get_type() == ent::type::token_type::U64) {
					// Parse the number
					u64 value = types::stou64(peek().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::U64Expression(value);
				} else if(peek().get_type() == ent::type::token_type::F32) {
					// Parse the number
					float value = types::stof32(peek().get_value());
					(void)eat();
					// Return the float expression
					return new ent::front::ast::F32Expression(value);
				} else if(peek().get_type() == ent::type::token_type::F64) {
					// Parse the number
					double value = types::stof64(peek().get_value());
					(void)eat();
					// Return the float expression
					return new ent::front::ast::F64Expression(value);
				} else if(peek().get_type() == ent::type::token_type::BOOL) {
					bool value = eat().get_value() == "true";
					return new ent::front::ast::BooleanExpression(value);
				}
				return parse_identifier();
			}

			ent::front::ast::Expression* parse_parenthesis_expression() {
				if(peek().get_type() != ent::type::token_type::OPEN_PAREN) {
					return parse_numeric_expression();
				}
				(void)eat();
				ent::front::ast::Expression* content = parse_expression();
				if(peek().get_type() != ent::type::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_EXPRESSION_IN_PARENTHESIS, "Invalid expression in parenthesis")).error();
				}
				(void)eat();
				return new ent::front::ast::ParenthesisExpression(content);
			}

			ent::front::ast::Expression* parse_non_pre_unary_expression() {
				ent::front::ast::Expression* term = parse_parenthesis_expression();
				if(peek().get_type() == ent::type::token_type::INCREMENT || peek().get_type() == ent::type::token_type::DECREMENT) {
					std::string operator_symbol = eat().get_value();
					if(term->get_type() != ent::front::ast::NodeType::identifier) {
						throw (ent::Error(ent::ErrorType::PARSER_TRYING_TO_INCREMENT_NON_IDENTIFIER_ERROR, "Trying to increment non-identifier")).error();
					}
					return new ent::front::ast::UnaryExpression(
						term,
						operator_symbol
					);
				}
				return term;
			}

			ent::front::ast::Expression* parse_unary_expression() {
				if(peek().get_type() != ent::type::token_type::NOT && peek().get_type() != ent::type::token_type::BITWISE_NOT) {
					return parse_non_pre_unary_expression();
				}

				std::string operator_symbol = eat().get_value();
				ent::front::ast::Expression* term = parse_parenthesis_expression();
				
				return new ent::front::ast::UnaryExpression(
					term,
					operator_symbol
				);
			}

			ent::front::ast::Expression* parse_multiplicative_expression() {
				// Parse the numeric expression first
				ent::front::ast::Expression* left = parse_unary_expression();
				// Parse the rest of the expression
				while(peek().get_value() == "*" || peek().get_value() == "/" || peek().get_value() == "%") {
					std::string operator_symbol = peek().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					ent::front::ast::Expression* right = parse_unary_expression();
					// Set the left as a binary expression
					left = new ent::front::ast::BinaryExpression(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			ent::front::ast::Expression* parse_additive_expression() {
				// Parse the multiplicative expression first
				ent::front::ast::Expression* left = parse_multiplicative_expression();
				// Parse the rest of the expression
				while(peek().get_value() == "+" || peek().get_value() == "-") {
					std::string operator_symbol = peek().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					ent::front::ast::Expression* right = parse_multiplicative_expression();
					// Set the left as a binary expression
					left = new ent::front::ast::BinaryExpression(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			ent::front::ast::Expression* parse_logical_expression() {
				// Parse the multiplicative expression first
				ent::front::ast::Expression* left = parse_additive_expression();
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
					ent::front::ast::Expression* right = parse_additive_expression();
					// Set the left as a binary expression
					left = new ent::front::ast::BinaryExpression(
						left,
						operator_symbol,
						right
					);
				}
				return left;
			}

			ent::front::ast::Expression* parse_expression() {
				return parse_logical_expression();
			}

			ent::front::ast::Assignation* expect_type_assignation_expression(ent::front::ast::NodeType type, std::string expected, ent::front::ast::Identifier* identifier, ent::front::ast::Expression* value) {
				// Value is an identifier
				if(value->get_type() == ent::front::ast::NodeType::identifier) {
					ent::front::ast::Identifier* value_identifier = (ent::front::ast::Identifier*)value;
					if(is_valid_cast(value_identifier->get_identifier_type(), type)) {
						identifier->set_identifier_type(type);
						return new ent::front::ast::Assignation(identifier, value_identifier);
					}
					throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + " expression, got " + value->type_id() + " returning other type")).error();
				}
				// Value is a binary expression
				if(value->get_type() == ent::front::ast::NodeType::binaryExpression) {
					ent::front::ast::BinaryExpression* value_binary_expression = (ent::front::ast::BinaryExpression*)value;
					if(is_valid_cast(value_binary_expression->get_return_type(), type)) {
						identifier->set_identifier_type(type);
						return new ent::front::ast::Assignation(identifier, (ent::front::ast::BinaryExpression*)value);
					}
					throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + " expression, got " + value->type_id() + " returning other type")).error();
				}
				// Invalid cast
				if(!is_valid_cast(value->get_type(), type)) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + " expression, got " + value->type_id())).error();
				}
				// Valid cast
				identifier->set_identifier_type(type);
				return new ent::front::ast::Assignation(identifier, value);
			}

			ent::front::ast::Declaration* parse_any_declaration(bool isMutable, ent::front::ast::Identifier* identifier, ent::type::token type_specifier, ent::type::token_type expectedAfter, std::string expectedAfterString, bool applyExpect = true) {
				ent::type::token next = peek();

				if(next.get_type() != ent::type::token_type::ASSIGN) {
					std::string type = type_specifier.get_value();
					if(applyExpect) {
						(void)expect(expectedAfter, expectedAfterString);
					}
					if(type == "void") {
						throw (ent::Error(ent::ErrorType::PARSER_INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
					} else if(type == "i8") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i8Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I8Expression(), isMutable);
					} else if(type == "i16") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i16Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I16Expression(), isMutable);
					} else if(type == "i32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i32Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I32Expression(), isMutable);
					} else if(type == "i64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::i64Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I64Expression(), isMutable);
					} else if(type == "u8") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u8Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U8Expression(), isMutable);
					} else if(type == "u16") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u16Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U16Expression(), isMutable);
					} else if(type == "u32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u32Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U32Expression(), isMutable);
					} else if(type == "u64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::u64Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U64Expression(), isMutable);
					} else if(type == "f32") {
						identifier->set_identifier_type(ent::front::ast::NodeType::f32Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::F32Expression(), isMutable);
					} else if(type == "f64") {
						identifier->set_identifier_type(ent::front::ast::NodeType::f64Expression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::F64Expression(), isMutable);
					} else if(type == "bool") {
						identifier->set_identifier_type(ent::front::ast::NodeType::booleanExpression);
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::BooleanExpression(), isMutable);
					}
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
				}

				return nullptr;
			}

			ent::front::ast::Statement* parse_declaration(bool needsSemicolon) {


				bool isMutable = false;

				if(peek().get_type() == ent::type::token_type::MUTABLE) {
					(void)eat();
					isMutable = true;
				}

				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				expect(ent::type::token_type::COLON, ":");
				ent::type::token type_specifier = expect(ent::type::token_type::TYPE_SPECIFIER, "type specifier");

				ent::type::token next = peek();

				ent::front::ast::Declaration* statement = parse_any_declaration(
					isMutable,
					identifier,
					type_specifier,
					ent::type::token_type::SEMICOLON,
					";",
					needsSemicolon
				);
				
				if(statement != nullptr) {
					return statement;
				}
				// Means next.get_type() == ent::type::token_type::ASSIGN
				(void)eat();
				ent::front::ast::Expression* value = parse_expression();
				std::string type = type_specifier.get_value();
				if(needsSemicolon) {
					(void)expect(ent::type::token_type::SEMICOLON, ";");
				}
				if(type == "void") {
					throw (ent::Error(ent::ErrorType::PARSER_INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
				} else if(type == "i8") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i8Expression, "i8", identifier, value), isMutable);
				} else if(type == "i16") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i16Expression, "i16", identifier, value), isMutable);
				} else if(type == "i32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i32Expression, "i32", identifier, value), isMutable);
				} else if(type == "i64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i64Expression, "i64", identifier, value), isMutable);
				} else if(type == "u8") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u8Expression, "u8", identifier, value), isMutable);
				} else if(type == "u16") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u16Expression, "u16", identifier, value), isMutable);
				} else if(type == "u32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u32Expression, "u32", identifier, value), isMutable);
				} else if(type == "u64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u64Expression, "u64", identifier, value), isMutable);
				} else if(type == "f32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::f32Expression, "f32", identifier, value), isMutable);
				} else if(type == "f64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::f64Expression, "f64", identifier, value), isMutable);
				} else if(type == "bool") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::booleanExpression, "bool", identifier, value), isMutable);
				}
				throw (ent::Error(ent::ErrorType::PARSER_INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
			}

			ent::front::ast::Declaration* make_declaration(ent::front::ast::Declaration* declarationExpression, ent::front::ast::Expression* value, bool isInFunctionSetup = false) {
				return new ent::front::ast::Declaration(declarationExpression->identifier, value, isInFunctionSetup);
			}

			ent::front::ast::Statement* parse_assignation(ent::front::ast::Identifier* identifier, bool needsSemicolon) {
				ent::type::token assignationTk = peek();
				
				if(assignationTk.get_type() != ent::type::token_type::ASSIGN) {
					(void)eat();
				}
				(void)expect(ent::type::token_type::ASSIGN, "equals sign");

				ent::front::ast::Expression* value = parse_expression();

				if(assignationTk.get_type() != ent::type::token_type::ASSIGN) {
					value = new ent::front::ast::BinaryExpression(identifier, assignationTk.get_value(), value);
				}

				if(needsSemicolon) {
					(void)expect(ent::type::token_type::SEMICOLON, ";");
				}
				
				return new ent::front::ast::Assignation(identifier, value);
			}

			std::vector<ent::front::ast::Statement*> get_child_nodes(ent::front::ast::Statement* statement) {
				switch(statement->get_type()) {
					case ent::front::ast::NodeType::functionDeclaration:
						return ((ent::front::ast::FunctionDeclaration*)statement)->body;
					case ent::front::ast::NodeType::program:
						return ((ent::front::ast::Program*)statement)->body;
					default:
						return std::vector<ent::front::ast::Statement*>();
				}
			}

			ent::front::ast::Statement* parse_function_call(ent::front::ast::Identifier* identifier, bool needsSemicolon) {
				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis");

				std::vector<ent::front::ast::Expression*> arguments = std::vector<ent::front::ast::Expression*>();
				
				if(peek().get_type() == ent::type::token_type::TYPE_SPECIFIER && peek().get_value() == "void") {
					(void)eat();
				} else if(peek().get_type() == ent::type::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				} else {
					arguments.push_back((ent::front::ast::Expression*)parse_expression());

					while(peek().get_type() != ent::type::token_type::CLOSE_PAREN) {
						(void)expect(ent::type::token_type::COMMA, "comma");
						arguments.push_back((ent::front::ast::Expression*)parse_expression());
					}
				}

				(void)expect(ent::type::token_type::CLOSE_PAREN, ")");
				if(needsSemicolon) {
					(void)expect(ent::type::token_type::SEMICOLON, ";");
				}

				return new ent::front::ast::FunctionCallExpression(identifier, arguments);
			}

			ent::front::ast::Statement* parse_identifier_starting_expression(bool needsSemicolon) {

				ent::type::token identifier_token = peek();
				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				
				if(needsSemicolon && peek().get_type() == ent::type::token_type::SEMICOLON) {
					(void)eat();
					return identifier;
				}

				ent::type::token op = ent::type::token(ent::type::token_type::EOF_TOKEN, "");

				if(
					peek().get_type() == ent::type::token_type::PLUS || peek().get_type() == ent::type::token_type::MINUS ||
					peek().get_type() == ent::type::token_type::TIMES || peek().get_type() == ent::type::token_type::DIVIDED_BY ||
					peek().get_type() == ent::type::token_type::MODULO ||
					peek().get_type() == ent::type::token_type::BITWISE_AND || peek().get_type() == ent::type::token_type::BITWISE_OR || peek().get_type() == ent::type::token_type::BITWISE_XOR
				) {
					op = eat();
				}

				if(peek().get_type() == ent::type::token_type::ASSIGN) {
					if(op.get_type() != ent::type::token_type::EOF_TOKEN) {
						tks.insert(tks.begin(), op);
					}
					return parse_assignation(identifier, needsSemicolon);
				}

				if(op.get_type() != ent::type::token_type::EOF_TOKEN) {
					tks.insert(tks.begin(), op);
				}

				if(peek().get_type() == ent::type::OPEN_PAREN) {
					return parse_function_call(identifier, needsSemicolon);
				}

				tks.insert(tks.begin(), identifier_token);

				ent::front::ast::Expression* expression = parse_expression();

				if(needsSemicolon) {
					(void)expect(ent::type::token_type::SEMICOLON, ";");
				}

				return expression;
			}		

			ent::front::ast::Statement* parse_statement(bool updateBefore = true, bool needsSemiColon = true);

			ent::front::ast::Statement* parse_function_declaration() {
				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis");

				std::vector<ent::front::ast::Declaration*> arguments = std::vector<ent::front::ast::Declaration*>();

				if(peek().get_type() == ent::type::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::ErrorType::PARSER_EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				}
				if(peek().get_type() == ent::type::token_type::TYPE_SPECIFIER && peek().get_value() == "void") {
					(void)eat();
					(void)expect(ent::type::token_type::CLOSE_PAREN, "close parenthesis");
				} else {
					while(true) {

						bool isMutable = false;

						if(peek().get_type() == ent::type::token_type::MUTABLE) {
							(void)eat();
							isMutable = true;
						}

						ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
						expect(ent::type::token_type::COLON, ":");
						ent::type::token type_specifier = expect(ent::type::token_type::TYPE_SPECIFIER, "type specifier");

						ent::front::ast::Declaration* declaration;
						
						try {
							declaration = parse_any_declaration(
								isMutable,
								identifier,
								type_specifier,
								ent::type::token_type::COMMA,
								","
							);
						} catch(const std::exception& e) {
							declaration = parse_any_declaration(
								isMutable,
								identifier,
								type_specifier,
								ent::type::token_type::CLOSE_PAREN,
								")"
							);
							arguments.push_back(declaration);
							break;
						}

						arguments.push_back(declaration);
					}
				}

				(void)expect(ent::type::token_type::COLON, "colon");

				std::string returnType = expect(ent::type::token_type::TYPE_SPECIFIER, "type specifier").get_value();

				(void)expect(ent::type::token_type::OPEN_BRACE, "open brace at start of function");

				std::vector<ent::front::ast::Statement*> body = std::vector<ent::front::ast::Statement*>();

				while(peek().get_type() != ent::type::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::type::token_type::CLOSE_BRACE, "close brace at end of function");
				
				return new ent::front::ast::FunctionDeclaration(identifier, returnType, arguments, body);
			}

			ent::front::ast::ConditionnalBlock* parse_conditionnal_block() {

				enum ConditionType {
					IF,
					ELSE_IF,
					ELSE
				};
				enum ConditionType conditionType = ConditionType::IF;

				if(peek().get_type() == ent::type::token_type::ELSE) {
					if(before == nullptr) {
						throw (ent::Error(ent::ErrorType::PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE, "Else keyword misses if clause before it")).error();
					}
					(void)eat();
					conditionType = peek().get_type() == ent::type::IF ? ConditionType::ELSE_IF : ConditionType::ELSE;
				}

				ent::front::ast::Expression* condition = nullptr;

				if(conditionType != ConditionType::ELSE) {
					(void)expect(ent::type::token_type::IF, "if keyword");

					if(peek().get_type() == ent::type::token_type::ELSE) {
						if(before == nullptr) {
							throw (ent::Error(ent::ErrorType::PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE, "Else keyword misses if clause before it")).error();
						}
						(void)eat();
					}
					
					(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis before condition");
				
					condition = parse_expression();

					(void)expect(ent::type::token_type::CLOSE_PAREN, "close parenthesis after condition");
				}

				(void)expect(ent::type::token_type::OPEN_BRACE, "open brace before body");

				std::vector<ent::front::ast::Statement*> body = std::vector<ent::front::ast::Statement*>();

				while(peek().get_type() != ent::type::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement(false));
				}

				(void)expect(ent::type::token_type::CLOSE_BRACE, "close brace after body");

				ent::front::ast::ConditionnalBlock* conditionnalBlock = new ent::front::ast::ConditionnalBlock(body, condition);

				if(conditionType != ConditionType::IF) {
					conditionnalBlock->before = before;
				}

				before = conditionnalBlock;

				return conditionnalBlock;
			}

			ent::front::ast::ConditionnalStructure* parse_conditionnal_structure() {

				std::vector<ent::front::ast::ConditionnalBlock*> blocks = std::vector<ent::front::ast::ConditionnalBlock*>();

				while(peek().get_type() == ent::type::token_type::IF || peek().get_type() == ent::type::token_type::ELSE) {
					blocks.push_back(parse_conditionnal_block());
				}

				return new ent::front::ast::ConditionnalStructure(blocks);
			}

			ent::front::ast::ForLoop* parse_for_loop() {
				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis after for keyword");

				ent::front::ast::Statement* initStatement = parse_statement(true, false);
				(void)expect(ent::type::token_type::SEMICOLON, "semicolon after for init statement");
				ent::front::ast::Expression* loopCondition = parse_expression();
				(void)expect(ent::type::token_type::SEMICOLON, "semicolon after for condition");
				ent::front::ast::Statement* iterationStatement = parse_statement(true, false);

				(void)expect(ent::type::token_type::CLOSE_PAREN, "close parenthesis after for iteration statement");
				(void)expect(ent::type::token_type::OPEN_BRACE, "open brace before for body");

				std::vector<ent::front::ast::Statement*> body = std::vector<ent::front::ast::Statement*>();

				while(peek().get_type() != ent::type::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::type::token_type::CLOSE_BRACE, "close brace after for body");

				return new ent::front::ast::ForLoop(initStatement, loopCondition, iterationStatement, body);
			}

			ent::front::ast::WhileLoop* parse_while_loop() {
				(void)eat();

				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis after while keyword");
				ent::front::ast::Expression* loopCondition = parse_expression();
				(void)expect(ent::type::token_type::CLOSE_PAREN, "close parenthesis after while condition");

				(void)expect(ent::type::token_type::OPEN_BRACE, "open brace before while body");

				std::vector<ent::front::ast::Statement*> body = std::vector<ent::front::ast::Statement*>();

				while(peek().get_type() != ent::type::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::type::token_type::CLOSE_BRACE, "close brace after while body");

				return new ent::front::ast::WhileLoop(loopCondition, body);
			}

			ent::front::ast::Statement* parse_statement(bool updateBefore, bool needsSemicolon) {

				if(peek().get_type() == ent::type::token_type::LET) {
					(void)eat();
					ent::front::ast::Statement* declaration = parse_declaration(needsSemicolon);
					if(updateBefore) { before = nullptr; }
					return declaration;
				}
				if(peek().get_type() == ent::type::token_type::IDENTIFIER) {
					ent::front::ast::Statement* expression = parse_identifier_starting_expression(needsSemicolon);
					if(updateBefore) { before = nullptr; }
					return expression;
				}
				if(peek().get_type() == ent::type::token_type::FN) {
					(void)eat();
					ent::front::ast::Statement* function_declaration = parse_function_declaration();
					if(updateBefore) { before = nullptr; }
					return function_declaration;
				}
				if(peek().get_type() == ent::type::token_type::IF || peek().get_type() == ent::type::token_type::ELSE) {
					return parse_conditionnal_structure();
				}
				if(peek().get_type() == ent::type::token_type::FOR) {
					(void)eat();
					ent::front::ast::Statement* for_loop = parse_for_loop();
					if(updateBefore) { before = nullptr; }
					return for_loop;
				}
				if(peek().get_type() == ent::type::token_type::WHILE) {
					ent::front::ast::Statement* whileLoop = parse_while_loop();
					if(updateBefore) { before = nullptr; }
					return whileLoop;
				}

				ent::front::ast::Expression* expression = parse_expression();
				(void)expect(ent::type::token_type::SEMICOLON, "semi colon at end of line");
				if(updateBefore) { before = nullptr; }

				return expression;
			}

			ent::front::ast::Program* parse(std::vector<ent::type::token> tokens) {
				tks = tokens;

				while(!eof()) {
					program->body.push_back(parse_statement());
				}

				return program;
			}
		}
    }
}

#endif // __ENT_FRONT_PARSER__