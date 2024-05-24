#ifndef __ENT_FRONT_PARSER__
#define __ENT_FRONT_PARSER__

#include "token.hpp"
#include "ast.hpp"
#include "errors.hpp"

namespace ent {
	namespace front {
		namespace parser {

			std::vector<ent::type::token> tks;

			bool eof() {
				return tks.front().get_type() == ent::type::token_type::EOF_TOKEN;
			}

			ent::type::token eat() {
				ent::type::token tk = tks.front();
				tks.erase(tks.begin());
				return tk;
			}

			ent::type::token peek() {
				return tks.front();
			}

			ent::type::token expect(ent::type::token_type type, std::string expected) {
				if(tks.front().get_type() == type) {
					return eat();
				}
				throw (ent::Error(ent::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + ", got " + tks.front().get_value())).error();
			}

			ent::front::ast::Expression* parse_identifier() {
				if(tks.front().get_type() == ent::type::token_type::IDENTIFIER) {
					std::string value = tks.front().get_value();
					(void)eat();
					return new ent::front::ast::Identifier(value);
				}
				throw (ent::Error(ent::PARSER_EXPECTED_OTHER_ERROR, "Expected identifier, got " + tks.front().get_value())).error();
			}

			ent::front::ast::Expression* parse_numeric_expression() {
				// If the current token is a number
				if(tks.front().get_type() == ent::type::token_type::I8) {
					// Parse the number
					i8 value = types::stoi8(tks.front().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I8Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::I16) {
					// Parse the number
					i16 value = types::stoi16(tks.front().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I16Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::I32) {
					// Parse the number
					i32 value = types::stoi32(tks.front().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I32Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::I64) {
					// Parse the number
					i64 value = types::stoi64(tks.front().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::I64Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::U64) {
					// Parse the number
					u64 value = types::stou64(tks.front().get_value());
					(void)eat();
					// Return the integer expression
					return new ent::front::ast::U64Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::F32) {
					// Parse the number
					float value = types::stof32(tks.front().get_value());
					(void)eat();
					// Return the float expression
					return new ent::front::ast::F32Expression(value);
				} else if(tks.front().get_type() == ent::type::token_type::F64) {
					// Parse the number
					double value = types::stof64(tks.front().get_value());
					(void)eat();
					// Return the float expression
					return new ent::front::ast::F64Expression(value);
				} else {
					return parse_identifier();
				}
				return nullptr;
			}

			ent::front::ast::Expression* parse_multiplicative_expression() {
				// Parse the multiplicative expression first
				ent::front::ast::Expression* left = parse_numeric_expression();
				// Parse the rest of the expression
				while(tks.front().get_value() == "*" || tks.front().get_value() == "/"){
					std::string operator_symbol = tks.front().get_value();
					(void)eat();
					// Parse the next multiplicative expression
					ent::front::ast::Expression* right = parse_numeric_expression();
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
				while(tks.front().get_value() == "+" || tks.front().get_value() == "-") {
					std::string operator_symbol = tks.front().get_value();
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

			ent::front::ast::Expression* parse_expression() {
				return parse_additive_expression();
			}

			ent::front::ast::Assignation* expect_type_assignation_expression(ent::front::ast::NodeType type, std::string expected, ent::front::ast::Identifier* identifier, ent::front::ast::Expression* value) {
				if(value->get_type() == ent::front::ast::NodeType::identifier) {
					return new ent::front::ast::Assignation(identifier, (ent::front::ast::Identifier*)value);
				}
				if(value->get_type() != type) {
					throw (ent::Error(ent::PARSER_EXPECTED_OTHER_ERROR, "Expected " + expected + " expression, got " + value->type_id())).error();
				}
				return new ent::front::ast::Assignation(identifier, value);
			}

			ent::front::ast::Statement* parse_declaration() {
				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				expect(ent::type::token_type::COLON, ":");
				ent::type::token type_specifier = expect(ent::type::token_type::TYPE_SPECIFIER, "type specifier");

				ent::type::token next = peek();
				
				if(next.get_type() == ent::type::token_type::SEMICOLON) {
					std::string type = type_specifier.get_value();
					(void)expect(ent::type::token_type::SEMICOLON, ";");
					if(type == "void") {
						throw (ent::Error(ent::INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
					} else if(type == "i8") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I8Expression());
					} else if(type == "i16") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I16Expression());
					} else if(type == "i32") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I32Expression());
					} else if(type == "i64") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::I64Expression());
					} else if(type == "u8") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U8Expression());
					} else if(type == "u16") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U16Expression());
					} else if(type == "u32") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U32Expression());
					} else if(type == "u64") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::U64Expression());
					} else if(type == "f32") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::F32Expression());
					} else if(type == "f64") {
						return new ent::front::ast::Declaration(identifier, new ent::front::ast::F64Expression());
					} else {
						throw (ent::Error(ent::INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
					}
				}
				// Means next.get_type() == ent::type::token_type::ASSIGN
				eat();
				ent::front::ast::Expression* value = parse_expression();
				std::string type = type_specifier.get_value();
				(void)expect(ent::type::token_type::SEMICOLON, ";");
				// ! let foo: i8 = 2 + 3; is breaking because BinaryExpression is not i8
				if(type == "void") {
					throw (ent::Error(ent::INVALID_VOID_VARIABLE_ERROR, "Cannot declare a variable of type void")).error();
				} else if(type == "i8") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i8Expression, "i8", identifier, value));
				} else if(type == "i16") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i16Expression, "i16", identifier, value));
				} else if(type == "i32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i32Expression, "i32", identifier, value));
				} else if(type == "i64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::i64Expression, "i64", identifier, value));
				} else if(type == "u8") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u8Expression, "u8", identifier, value));
				} else if(type == "u16") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u16Expression, "u16", identifier, value));
				} else if(type == "u32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u32Expression, "u32", identifier, value));
				} else if(type == "u64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::u64Expression, "u64", identifier, value));
				} else if(type == "f32") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::f32Expression, "f32", identifier, value));
				} else if(type == "f64") {
					return new ent::front::ast::Declaration(expect_type_assignation_expression(ent::front::ast::NodeType::f64Expression, "f64", identifier, value));
				} else {
					throw (ent::Error(ent::INVALID_TYPE_SPECIFIER_ERROR, "Invalid type specifier " + type)).error();
				}
			}

			ent::front::ast::Statement* parse_assignation(ent::front::ast::Identifier* identifier) {
				(void)expect(ent::type::token_type::ASSIGN, "equals sign");

				ent::front::ast::Expression* value = parse_expression();

				(void)expect(ent::type::token_type::SEMICOLON, ";");
				
				return new ent::front::ast::Assignation(identifier, value);
			}

			ent::front::ast::Statement* parse_function_call(ent::front::ast::Identifier* identifier) {
				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis");

				std::vector<ent::front::ast::Expression*> arguments = std::vector<ent::front::ast::Expression*>();
				
				if(tks.front().get_type() == ent::type::token_type::TYPE_SPECIFIER && tks.front().get_value() == "void") {
					(void)eat();
				} else if(tks.front().get_type() == ent::type::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				} else {
					arguments.push_back((ent::front::ast::Expression*)parse_expression());

					while(tks.front().get_type() != ent::type::token_type::CLOSE_PAREN) {
						(void)expect(ent::type::token_type::COMMA, "comma");
						arguments.push_back((ent::front::ast::Expression*)parse_expression());
					}
				}

				(void)expect(ent::type::token_type::CLOSE_PAREN, ")");
				(void)expect(ent::type::token_type::SEMICOLON, ";");

				// ! Figure out return
				return new ent::front::ast::Statement();
			}

			ent::front::ast::Statement* parse_identifier_starting_expression() {
				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				
				if(tks.front().get_type() == ent::type::token_type::ASSIGN) {
					return parse_assignation(identifier);
				} else {
					return parse_function_call(identifier);
				}
			}		

			ent::front::ast::Statement* parse_statement();

			ent::front::ast::Statement* parse_function_declaration() {
				ent::front::ast::Identifier* identifier = (ent::front::ast::Identifier*)parse_identifier();
				(void)expect(ent::type::token_type::OPEN_PAREN, "open parenthesis");

				std::vector<ent::front::ast::Declaration*> arguments = std::vector<ent::front::ast::Declaration*>();


				if(tks.front().get_type() == ent::type::token_type::TYPE_SPECIFIER && tks.front().get_value() == "void") {
					(void)eat();
				} else if(tks.front().get_type() == ent::type::token_type::CLOSE_PAREN) {
					throw (ent::Error(ent::EXPLICIT_VOID_MISSING_FN_ERROR, "Function misses explicit VOID param passing")).error();
				} else {
					arguments.push_back((ent::front::ast::Declaration*)parse_declaration());

					while(tks.front().get_type() != ent::type::token_type::CLOSE_PAREN) {
						(void)expect(ent::type::token_type::COMMA, "comma");
						arguments.push_back((ent::front::ast::Declaration*)parse_declaration());
					}
				}

				(void)eat();

				(void)expect(ent::type::token_type::COLON, "colon");

				std::string returnType = expect(ent::type::token_type::TYPE_SPECIFIER, "type specifier").get_value();

				(void)expect(ent::type::token_type::OPEN_BRACE, "open brace at start of function");

				std::vector<ent::front::ast::Statement*> body = std::vector<ent::front::ast::Statement*>();

				while(tks.front().get_type() != ent::type::token_type::CLOSE_BRACE) {
					body.push_back(parse_statement());
				}

				(void)expect(ent::type::token_type::CLOSE_BRACE, "close brace at end of function");
				
				return new ent::front::ast::FunctionDeclaration(identifier, returnType, arguments, body);
			}

			ent::front::ast::Statement* parse_statement() {
				if(tks.front().get_type() == ent::type::token_type::LET) {
					(void)eat();
					ent::front::ast::Statement* declaration = parse_declaration();
					return declaration;
				}
				if(tks.front().get_type() == ent::type::token_type::IDENTIFIER) {
					ent::front::ast::Statement* expression = parse_identifier_starting_expression();
					return expression;
				}
				if(tks.front().get_type() == ent::type::token_type::FN) {
					(void)eat();
					ent::front::ast::Statement* function_declaration = parse_function_declaration();
					return function_declaration;
				}
				return parse_expression();
			}

			ent::front::ast::Program parse(std::vector<ent::type::token> tokens) {
				tks = tokens;

				ent::front::ast::Program program = ent::front::ast::Program(
					std::vector<ent::front::ast::Statement*>()
				);

				while(!ent::front::parser::eof()) {
					program.body.push_back(ent::front::parser::parse_statement());
				}

				return program;
			}
		}
    }
}

#endif // __ENT_FRONT_PARSER__