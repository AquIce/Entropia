#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>

#include "token.hpp"
#include "errors.hpp"

std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

namespace ent {
	namespace front {
		struct NumberValue {
			std::string value;
			bool is_integer;
		};

		struct NumberValue get_number(std::string& src) {
			std::string rvalue = "";
			bool is_integer = true;
			while(src[0] == '.' || isdigit(src[0])) {
				if(src[0] == '.') {
					if(!is_integer) {
						ent::throw_err(ent::Error(ent::LEX_ERROR, "Invalid number format"));
					}
					is_integer = false;
				}
				rvalue += shift(src);
			}
			return NumberValue{rvalue, is_integer};
		}

		std::vector<ent::type::token> lex(std::string src) {
			// Create an empty token list
			std::vector<ent::type::token> tokens;
			// Iterate through the source string
			while(src.length() > 0) {
				// If the current character is a space, skip it
				if(src[0] == ' ') {
					shift(src);
					continue;
				} else if(src[0] == '(') { // If the current character is a left parenthesis
					tokens.push_back(ent::type::token(ent::type::OPEN_PAREN, shift(src)));
				} else if(src[0] == ')') { // If the current character is a right parenthesis
					tokens.push_back(ent::type::token(ent::type::CLOSE_PAREN, shift(src)));
				} else if(isdigit(src[0]) || src[0] == '.') { // If the current character is a digit or a dot
					NumberValue number = get_number(src);
					tokens.push_back(ent::type::token(number.is_integer ? ent::type::token_type::INTEGER : ent::type::token_type::FLOAT, number.value));
				} else if(src[0] == '+' || src[0] == '-' || src[0] == '*' || src[0] == '/') { // If the current character is an operator
					tokens.push_back(ent::type::token(ent::type::OPERATOR, shift(src)));
				} else {
					std::string identifier = "";
					while(isalnum(src[0])) {
						identifier += shift(src);
					}
					tokens.push_back(ent::type::token(ent::type::IDENTIFIER, identifier));
				}
			}
			// Add an EOF token to the end of the list
			tokens.push_back(ent::type::token());
			return tokens;
		}
	}
}

#endif // __ENT_FRONT_LEX__