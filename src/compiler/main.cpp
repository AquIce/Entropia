#include <iostream>
#include "lexer.hpp"

int main() {
	Entropia::Lexer lexer = Entropia::Lexer("class Test { }");
	std::vector<std::string> val = lexer.lex();
	for(std::string s : val) {
		std::cout << s << std::endl;
	}
}