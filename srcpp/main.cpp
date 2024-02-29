#include <iostream>
#include <string>

#include "lexer.hpp"
#include "token.hpp"

int main() {
	std::string src = "1 + 2 * 3";
	std::vector<ent::type::token> tokens = ent::front::lex(src);
	printf("Tokens:\n");
	for(int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].pretty_print() << std::endl;
	}
	return 0;
}