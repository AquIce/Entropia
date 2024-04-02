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
	std::string src = "1 / myVar + 2 * 3";

	// Test lexer

	std::vector<ent::type::token> tokens = ent::front::lex(src);

	ASSERT_BLOCK("LEXER", {
		ASSERT_EQUAL("Tokens size is 5", tokens.size(), 8);
		ASSERT_BLOCK("Token 1", {
			ASSERT_EQUAL("First token is an i8", tokens[0].get_type(), ent::type::I8);
			ASSERT_EQUAL("First token value is 1", tokens[0].get_value(), "1");
		});
		ASSERT_BLOCK("Token 2", {
			ASSERT_EQUAL("Second token is an operator", tokens[1].get_type(), ent::type::OPERATOR);
			ASSERT_EQUAL("Second token value is /", tokens[1].get_value(), "/");
		});
		ASSERT_BLOCK("Token 3", {
			ASSERT_EQUAL("Third token is an identifier", tokens[2].get_type(), ent::type::IDENTIFIER);
			ASSERT_EQUAL("Third token value is myVar", tokens[2].get_value(), "myVar");
		});
		ASSERT_BLOCK("Token 4", {
			ASSERT_EQUAL("Fourth token is an operator", tokens[3].get_type(), ent::type::OPERATOR);
			ASSERT_EQUAL("Fourth token value is +", tokens[3].get_value(), "+");
		});
		ASSERT_BLOCK("Token 5", {
			ASSERT_EQUAL("Fifth token is an i8", tokens[4].get_type(), ent::type::I8);
			ASSERT_EQUAL("Fifth token value is 2", tokens[4].get_value(), "2");
		});
		ASSERT_BLOCK("Token 6", {
			ASSERT_EQUAL("Sixth token is an operator", tokens[5].get_type(), ent::type::OPERATOR);
			ASSERT_EQUAL("Sixth token value is *", tokens[5].get_value(), "*");
		});
		ASSERT_BLOCK("Token 7", {
			ASSERT_EQUAL("Seventh token is an i8", tokens[6].get_type(), ent::type::I8);
			ASSERT_EQUAL("Seventh token value is 3", tokens[6].get_value(), "3");
		});
		ASSERT_BLOCK("Token 8", {
			ASSERT_EQUAL("Eighth token is an EOF token", tokens[7].get_type(), ent::type::EOF_TOKEN);
		});
	});

	// Test parser

	ent::front::ast::Program program = ent::front::parser::parse(tokens);

	ASSERT_BLOCK("PARSER", {
		ASSERT_BLOCK("Program body", {
			ASSERT_EQUAL("Program body size is 1", program.body.size(), 1);
			ASSERT_TYPE("Program body is a vector of Statements", program.body, std::vector<ent::front::ast::Statement*>);
		});
		ASSERT_BLOCK("Left of the main BinaryExpression (1 / myVar)", {
			ASSERT_EQUAL("BinaryExpression's left is a BinaryExpression", ((ent::front::ast::BinaryExpression*)program.body[0])->left->type_id(), "BinaryExpression");
			ASSERT_BLOCK("Left's left of the first BinaryExpression (1)", {
				ASSERT_EQUAL("BinaryExpression's left's left is an I8Expression", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->left)->left->type_id(), "I8Expression");
				ASSERT_EQUAL("I8Expression's value is 1", ((ent::front::ast::I8Expression*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->left)->left)->value, 1);
			});
			ASSERT_BLOCK("Left's right of the first BinaryExpression (myVar)", {
				ASSERT_EQUAL("BinaryExpression's left's right's value an Identifier", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->left)->right->type_id(), "Identifier");
				ASSERT_EQUAL("Identifier's name is myVar", ((ent::front::ast::Identifier*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->left)->right)->name, "myVar");
			});
		});
		ASSERT_BLOCK("Right of the main BinaryExpression (2 * 3)", {
			ASSERT_EQUAL("BinaryExpression's right is a BinaryExpression", ((ent::front::ast::BinaryExpression*)program.body[0])->right->type_id(), "BinaryExpression");
			ASSERT_BLOCK("Right's left of the first BinaryExpression (2)", {
				ASSERT_EQUAL("BinaryExpression's right's left is an I8Expression", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->left->type_id(), "I8Expression");
				ASSERT_EQUAL("I8Expression's value is 2", ((ent::front::ast::I8Expression*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->left)->value, 2);
			});
			ASSERT_BLOCK("Right's right of the first BinaryExpression (3)", {
				ASSERT_EQUAL("BinaryExpression's right's right is an I8Expression", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->right->type_id(), "I8Expression");
				ASSERT_EQUAL("I8Expression's value is 3", ((ent::front::ast::I8Expression*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->right)->value, 3);
			});
		});
	});

	// Test interpreter

	ent::runtime::RuntimeValue* result = ent::runtime::interpreter::interpret(&program)[0];

	ASSERT_BLOCK("INTERPRETER", {
		ASSERT_EQUAL("Result is an I8", result->type(), ent::runtime::ValueType::I8);
		ASSERT_EQUAL("Result's value is 6", ((ent::runtime::I8Value*)result)->get_value(), 6);
	});
	
	print_results();

	return 0;
}