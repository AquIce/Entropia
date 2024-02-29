#include "token.hpp"

ent::type::token::token(enum token_type type, std::string value) {
	this->type = type;
	this->value = value;
}
ent::type::token::token() {
	this->type = OPERATOR;
	this->value = "";
}
enum ent::type::token_type ent::type::token::get_type() {
	return this->type;
}
std::string ent::type::token::get_value() {
	return this->value;
}
void ent::type::token::set_type(enum ent::type::token_type type) {
	this->type = type;
}
void ent::type::token::set_value(std::string value) {
	this->value = value;
}

std::string ent::type::token::pretty_print() {
	std::string type = "";
	switch(this->type) {
		case OPERATOR:
			type = "OPERATOR";
			break;
		case OPEN_PAREN:
			type = "OPEN_PAREN";
			break;
		case CLOSE_PAREN:
			type = "CLOSE_PAREN";
			break;
		case NUMBER:
			type = "NUMBER";
			break;
	}
	type += ": ";
	type += this->value;
	return type;
}