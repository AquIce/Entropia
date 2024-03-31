#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>
#include "token.hpp"

std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

namespace ent {
	namespace front {
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
				} else if(isdigit(src[0])) { // If the current character is a digit
					std::string value = "";
					while(isdigit(src[0])) {
						value += shift(src);
					}
					tokens.push_back(ent::type::token(ent::type::NUMBER, value));
				} else if(src[0] == '+' || src[0] == '-' || src[0] == '*' || src[0] == '/') { // If the current character is an operator
					tokens.push_back(ent::type::token(ent::type::OPERATOR, shift(src)));
				} else {
					std::cout << "Unknown character" << src[0] << std::endl;
					return std::vector<ent::type::token>();
				}
			}
			// Add an EOF token to the end of the list
			tokens.push_back(ent::type::token());
			return tokens;
		}
	}
}

#endif // __ENT_FRONT_LEX__