#ifndef __ENT_FRONT_PARSER__
#define __ENT_FRONT_PARSER__

#include "token.hpp"
#include "ast.hpp"

namespace ent {
	namespace front {
		namespace parser {

			std::vector<ent::type::token> tks;

			bool eof() {
				return tks.front().get_type() == ent::type::EOF_TOKEN;
			}

			ent::type::token eat() {
				ent::type::token tk = tks.front();
				tks.erase(tks.begin());
				return tk;
			}

			ent::front::ast::Expression* parse_identifier() {
				if(tks.front().get_type() == ent::type::IDENTIFIER) {
					std::string value = tks.front().get_value();
					(void)eat();
					return new ent::front::ast::Identifier(value);
				}
				std::cerr << "Expected identifier, got " << tks.front().get_value() << std::endl;

				return nullptr;
			}

			ent::front::ast::Expression* parse_numeric_expression() {
				// If the current token is a number
				if(tks.front().get_type() == ent::type::NUMBER) {
					// Parse the number
					float value = std::stof(tks.front().get_value());
					(void)eat();
					// Return the numeric expression
					return new ent::front::ast::NumericExpression(value);
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
				while(tks.front().get_value() == "+" || tks.front().get_value() == "-"){
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

			ent::front::ast::Statement* parse_statement() {
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