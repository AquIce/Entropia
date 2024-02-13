#include "lexer.hpp"

std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

std::vector<ent_type_token> ent_front_lex(std::string src) {
	// Create an empty token list
	std::vector<ent_type_token> tokens;
	// Iterate through the source string
	while(src.length() > 0) {
		// If the current character is a space, skip it
		if(src[0] == ' ') {
			shift(src);
			continue;
		} else if(src[0] == '(') { // If the current character is a left parenthesis
			tokens.push_back(ent_type_token(OPEN_PAREN, shift(src)));
		} else if(src[0] == ')') { // If the current character is a right parenthesis
			tokens.push_back(ent_type_token(CLOSE_PAREN, shift(src)));
		} else if(isdigit(src[0])) { // If the current character is a digit
			std::string value = "";
			while(isdigit(src[0])) {
				value += shift(src);
			}
			tokens.push_back(ent_type_token(NUMBER, value));
		} else if(src[0] == '+' || src[0] == '-' || src[0] == '*' || src[0] == '/') { // If the current character is an operator
			tokens.push_back(ent_type_token(OPERATOR, shift(src)));
		} else {
			std::cout << "Unknown character" << src[0] << std::endl;
			return std::vector<ent_type_token>();
		}
	}
	return tokens;
}