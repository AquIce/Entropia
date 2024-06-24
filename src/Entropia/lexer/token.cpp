#include <AquIce/Entropia/token.hpp>

ent::lexer::token::token(
	enum ent::lexer::token_type type, 
	std::string value
) {
	this->type = type;
	this->value = value;
}

ent::lexer::token::token() {
	this->type = EOF_TOKEN;
	this->value = "";
}

enum ent::lexer::token_type ent::lexer::token::get_type() {
	return this->type;
}

std::string ent::lexer::token::get_value() {
	return this->value;
}

void ent::lexer::token::set_type(enum ent::lexer::token_type type) {
	this->type = type;
}

void ent::lexer::token::set_value(std::string value) {
	this->value = value;
}

std::string ent::lexer::token::repr() {
	std::string type = "";
	switch(this->type) {
		TOKEN_SWITCH_CASE(LET)
		TOKEN_SWITCH_CASE(MUTABLE)
		TOKEN_SWITCH_CASE(TYPE_SPECIFIER)
		TOKEN_SWITCH_CASE(FN)
		TOKEN_SWITCH_CASE(RETURN)

		TOKEN_SWITCH_CASE(IF)
		TOKEN_SWITCH_CASE(ELSE)
		TOKEN_SWITCH_CASE(FOR)
		TOKEN_SWITCH_CASE(WHILE)
		TOKEN_SWITCH_CASE(MATCH)
		TOKEN_SWITCH_CASE(DEFAULT)
		TOKEN_SWITCH_CASE(BREAK)

		TOKEN_SWITCH_CASE(OPEN_PAREN)
		TOKEN_SWITCH_CASE(CLOSE_PAREN)
		TOKEN_SWITCH_CASE(OPEN_BRACE)
		TOKEN_SWITCH_CASE(CLOSE_BRACE)
		TOKEN_SWITCH_CASE(COLON)
		TOKEN_SWITCH_CASE(SEMICOLON)
		TOKEN_SWITCH_CASE(COMMA)
		TOKEN_SWITCH_CASE(ASSIGN)
		TOKEN_SWITCH_CASE(MATCH_ARROW)

		TOKEN_SWITCH_CASE(PLUS)
		TOKEN_SWITCH_CASE(MINUS)
		TOKEN_SWITCH_CASE(TIMES)
		TOKEN_SWITCH_CASE(DIVIDED_BY)

		TOKEN_SWITCH_CASE(EQUAL)
		TOKEN_SWITCH_CASE(NOT_EQUAL)
		TOKEN_SWITCH_CASE(AND)
		TOKEN_SWITCH_CASE(OR)
		TOKEN_SWITCH_CASE(XOR)
		TOKEN_SWITCH_CASE(SMALLER_THAN)
		TOKEN_SWITCH_CASE(GREATER_THAN)
		TOKEN_SWITCH_CASE(SMALLER_OR_EQUAL)
		TOKEN_SWITCH_CASE(GREATER_OR_EQUAL)
		TOKEN_SWITCH_CASE(NOT)

		TOKEN_SWITCH_CASE(MODULO)
		TOKEN_SWITCH_CASE(BITWISE_LEFT_SHIFT)
		TOKEN_SWITCH_CASE(BITWISE_RIGHT_SHIFT)
		TOKEN_SWITCH_CASE(BITWISE_AND)
		TOKEN_SWITCH_CASE(BITWISE_OR)
		TOKEN_SWITCH_CASE(BITWISE_XOR)

		TOKEN_SWITCH_CASE(INCREMENT)
		TOKEN_SWITCH_CASE(DECREMENT)
		
		TOKEN_SWITCH_CASE(BITWISE_NOT)

		TOKEN_SWITCH_CASE(QUESTION_MARK)

		TOKEN_SWITCH_CASE(BOOL)

		TOKEN_SWITCH_CASE(CHAR)
		TOKEN_SWITCH_CASE(STR)

		TOKEN_SWITCH_CASE(I8)
		TOKEN_SWITCH_CASE(I16)
		TOKEN_SWITCH_CASE(I32)
		TOKEN_SWITCH_CASE(I64)
		TOKEN_SWITCH_CASE(U64)
		TOKEN_SWITCH_CASE(F32)
		TOKEN_SWITCH_CASE(F64)

		TOKEN_SWITCH_CASE(TYPE)
		TOKEN_SWITCH_CASE(IMPL)
		TOKEN_SWITCH_CASE(AT)
		TOKEN_SWITCH_CASE(PUBLIC)
		TOKEN_SWITCH_CASE(PRIVATE)

		TOKEN_SWITCH_CASE(IDENTIFIER)

		TOKEN_SWITCH_CASE(EOF_TOKEN)
	}
	type += ": ";
	type += this->value;
	return type;
}