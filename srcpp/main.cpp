#include <iostream>
#include <string>

#include "lexer.hpp"
#include "token.hpp"
#include "parser.hpp"
#include "ast.hpp"

int main() {
	std::string src = "1 + 2 * 3";
	std::vector<ent::type::token> tokens = ent::front::lex(src);
	std::cout << "Lexer: " << src << std::endl;
	for(int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].pretty_print() << std::endl;
	}
	std::cout << "Parser" << std::endl;
	ent::front::ast::Program program = ent::front::parse(tokens);
	std::cout << program.pretty_print() << std::endl;
	return 0;
}