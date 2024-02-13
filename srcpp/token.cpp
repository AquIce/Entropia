#include "token.hpp"

ent_type_token::ent_type_token(enum ent_type_token_type type, std::string value) {
	this->type = type;
	this->value = value;
}
ent_type_token::ent_type_token() {
	this->type = OPERATOR;
	this->value = "";
}
enum ent_type_token_type ent_type_token::get_type() {
	return this->type;
}
std::string ent_type_token::get_value() {
	return this->value;
}
void ent_type_token::set_type(enum ent_type_token_type type) {
	this->type = type;
}
void ent_type_token::set_value(std::string value) {
	this->value = value;
}

std::string ent_type_token::pretty_print() {
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