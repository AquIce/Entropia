#include <iostream>
#include <string>

#include <AquIce/Entropia/lexer.hpp>
#include <AquIce/Entropia/token.hpp>
#include <AquIce/Entropia/parser.hpp>
#include <AquIce/Entropia/ast.hpp>
#include <AquIce/Entropia/interpreter.hpp>

#include <AquIce/unit/assert.hpp>

int main() {
	// Original string
	std::string src = "if(0) { 1 + 1; } else if(1) { 2 + 2; } else { 3 + 3; }";

	std::vector<ent::type::token> tokens = ent::front::lex(src);

	for(int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].get_value() << " ";
	}
	std::cout << std::endl;

	// Test parser

	ent::front::ast::Program* program = ent::front::parser::parse(tokens);

	std::cout << program->pretty_print() << std::endl;

	// Test interpreter

	std::vector<ent::runtime::RuntimeValue*> results = ent::runtime::interpreter::interpret(program);
	
	for(int i = 0; i < results.size(); i++) {
		std::cout << results[i]->pretty_print() << std::endl;
	}

	return 0;
}