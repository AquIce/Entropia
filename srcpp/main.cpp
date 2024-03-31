#include <iostream>
#include <string>

#include <AquIce/Entropia/lexer.hpp>
#include <AquIce/Entropia/token.hpp>
#include <AquIce/Entropia/parser.hpp>
#include <AquIce/Entropia/ast.hpp>

#include <AquIce/unit/assert.hpp>

int main() {
	// Original string
	std::string src = "1 + 2 * 3";

	// Test lexer

	std::vector<ent::type::token> tokens = ent::front::lex(src);

	ASSERT_EQUAL("Tokens size is 5", tokens.size(), 6);
	ASSERT_EQUAL("First token is a number", tokens[0].get_type(), ent::type::NUMBER);
	ASSERT_EQUAL("First token value is 1", tokens[0].get_value(), "1");
	ASSERT_EQUAL("Second token is an operator", tokens[1].get_type(), ent::type::OPERATOR);
	ASSERT_EQUAL("Second token value is +", tokens[1].get_value(), "+");
	ASSERT_EQUAL("Third token is a number", tokens[2].get_type(), ent::type::NUMBER);
	ASSERT_EQUAL("Third token value is 2", tokens[2].get_value(), "2");
	ASSERT_EQUAL("Fourth token is an operator", tokens[3].get_type(), ent::type::OPERATOR);
	ASSERT_EQUAL("Fourth token value is *", tokens[3].get_value(), "*");
	ASSERT_EQUAL("Fifth token is a number", tokens[4].get_type(), ent::type::NUMBER);
	ASSERT_EQUAL("Fifth token value is 3", tokens[4].get_value(), "3");
	ASSERT_EQUAL("Sixth token is EOF", tokens[5].get_type(), ent::type::EOF_TOKEN);

	// Test parser

	ent::front::ast::Program program = ent::front::parser::parse(tokens);

	ASSERT_EQUAL("Program body size is 1", program.body.size(), 1);
	ASSERT_TYPE("Program body is a vector of Statements", program.body, std::vector<ent::front::ast::Statement*>);
	ASSERT_EQUAL("Program body's first element is a BinaryExpression", program.body[0]->type_id(), "BinaryExpression");
	ASSERT_EQUAL("BinaryExpression's left is a NumericExpression", ((ent::front::ast::BinaryExpression*)program.body[0])->left->type_id(), "NumericExpression");
	ASSERT_EQUAL("NumericExpression's value is 1", ((ent::front::ast::NumericExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->left)->value, 1);
	ASSERT_EQUAL("BinaryExpression's operator is +", ((ent::front::ast::BinaryExpression*)program.body[0])->operator_symbol, "+");
	ASSERT_EQUAL("BinaryExpression's right is a BinaryExpression", ((ent::front::ast::BinaryExpression*)program.body[0])->right->type_id(), "BinaryExpression");
	ASSERT_EQUAL("BinaryExpression's right's left is a NumericExpression", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->left->type_id(), "NumericExpression");
	ASSERT_EQUAL("NumericExpression's value is 2", ((ent::front::ast::NumericExpression*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->left)->value, 2);
	ASSERT_EQUAL("BinaryExpression's right's operator is *", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->operator_symbol, "*");
	ASSERT_EQUAL("BinaryExpression's right's right is a NumericExpression", ((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->right->type_id(), "NumericExpression");
	ASSERT_EQUAL("NumericExpression's value is 3", ((ent::front::ast::NumericExpression*)((ent::front::ast::BinaryExpression*)((ent::front::ast::BinaryExpression*)program.body[0])->right)->right)->value, 3);

	print_results();

	return 0;
}