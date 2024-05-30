#include <iostream>
#include <string>
#include <fstream>

#include <AquIce/Entropia/lexer.hpp>
#include <AquIce/Entropia/token.hpp>
#include <AquIce/Entropia/parser.hpp>
#include <AquIce/Entropia/ast.hpp>
#include <AquIce/Entropia/interpreter.hpp>

#include <AquIce/unit/assert.hpp>

int main(int argc, char** argv) {

	if(argc != 2) {
		std::cout << "Usage: entropia <filename: " << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	
	if((&filename)->rfind(".etp") != filename.length() - 4) {
		std::cout << "Invalid file format" << std::endl;
		return 1;
	}

	std::ifstream file = std::ifstream(argv[1]);
	std::string code = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::vector<ent::type::token> tokens;
	try {
		tokens = ent::front::lex(code);
	} catch (const std::exception& e) {
		std::cout << "LEXER ERROR : " << e.what() << std::endl;
		return 1;
	}

	for(u64 i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].get_value() << " ";
	}
	std::cout << std::endl;

	// Test parser

	ent::front::ast::Program* program;
	try {
		program = ent::front::parser::parse(tokens);
	} catch (const std::exception& e) {
		std::cout << "PARSER ERROR : " << e.what() << std::endl;
		return 1;
	}

	std::cout << program->pretty_print() << std::endl;

	// Test interpreter

	ent::runtime::RuntimeValue* result;
	try {
		result = ent::runtime::interpreter::interpret(program);
	} catch (const std::exception& e) {
		std::cout << "INTERPRETER ERROR : " << e.what() << std::endl;
		return 1;
	}
	
	std::cout << result->pretty_print() << std::endl;

	return 0;
}