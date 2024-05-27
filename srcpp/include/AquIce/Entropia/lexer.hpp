#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>

#include "token.hpp"
#include "errors.hpp"
#include "../types/numbers.hpp"

std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

std::string shift(std::string& str, int n) {
	std::string first = str.substr(0, n);
	str = str.substr(n, str.length() - n);
	return first;
}

namespace ent {
	namespace front {
		struct NumberValue {
			std::string value;
			bool is_integer;
		};

		struct NumberValue get_number(std::string& src) {
			std::string rvalue = "";
			bool is_integer = true;
			while(src[0] == '.' || isdigit(src[0])) {
				if(src[0] == '.') {
					if(!is_integer) {
						throw (ent::Error(ent::INVALID_NUMBER_FORMAT_ERROR, "Invalid number format")).error();
					}
					is_integer = false;
				}
				rvalue += shift(src);
			}
			return NumberValue{rvalue, is_integer};
		}

		ent::type::token get_number_token(NumberValue n) {
			if(n.is_integer) {
				i64 value = std::stoll(n.value);
				u64 uValue = std::stoull(n.value);
				if(value > _I64_MIN && value < INT64_MAX) {
					return ent::type::token(ent::type::I64, n.value);
				} else if(uValue > 0 && uValue < UINT_FAST64_MAX) {
					return ent::type::token(ent::type::U64, n.value);
				} else {
					throw (ent::Error(ent::INTEGER_OUT_OF_RANGE_ERROR, "Integer value out of range")).error();
				}
			} else {
				double value = std::stod(n.value);
				if(value > FLT_MIN && value < FLT_MAX) {
					return ent::type::token(ent::type::F32, n.value);
				} else if(value > DBL_MIN && value < DBL_MAX) {
					return ent::type::token(ent::type::F64, n.value);
				} else {
					throw (ent::Error(ent::FLOAT_OUT_OF_RANGE_ERROR, "Float value out of range")).error();
				}
			}
		}

		ent::type::token get_token(std::string& src) {
			if(src[0] == '(') {
				return ent::type::token(ent::type::OPEN_PAREN, shift(src));
			} else if(src[0] == ')') {
				return ent::type::token(ent::type::CLOSE_PAREN, shift(src));
			} else if(src[0] == '{') {
				return ent::type::token(ent::type::OPEN_BRACE, shift(src));
			} else if(src[0] == '}') {
				return ent::type::token(ent::type::CLOSE_BRACE, shift(src));
			} else if(src[0] == ':') {
				return ent::type::token(ent::type::COLON, shift(src));
			} else if(src[0] == ';') {
				return ent::type::token(ent::type::SEMICOLON, shift(src));
			} else if(src[0] == ',') {
				return ent::type::token(ent::type::COMMA, shift(src));
			} else if (src.rfind("==", 0) == 0) {
				(void)shift(src, 2); // Remove "==" from the source string
				return ent::type::token(ent::type::EQUAL, "==");
			} else if(src[0] == '=') {
				return ent::type::token(ent::type::ASSIGN, shift(src));
			} else if (src.rfind("<=", 0) == 0) {
				(void)shift(src, 2); // Remove "<=" from the source string
				return ent::type::token(ent::type::SMALLER_OR_EQUAL, "<=");
			} else if (src.rfind(">=", 0) == 0) {
				(void)shift(src, 2); // Remove ">=" from the source string
				return ent::type::token(ent::type::GREATER_OR_EQUAL, ">=");
			} else if(src[0] == '<') {
				return ent::type::token(ent::type::SMALLER_THAN, shift(src));
			} else if(src[0] == '>') {
				return ent::type::token(ent::type::GREATER_THAN, shift(src));
			} else if (src.rfind("!=", 0) == 0) {
				(void)shift(src, 2); // Remove "!=" from the source string
				return ent::type::token(ent::type::NOT_EQUAL, "!=");
			} else if(src[0] == '!') {
				return ent::type::token(ent::type::NOT, shift(src));
			} else if(src[0] == '+' || src[0] == '-' || src[0] == '*' || src[0] == '/') {
				return ent::type::token(ent::type::OPERATOR, shift(src));
			} else if (src.rfind("&&", 0) == 0) {
				(void)shift(src, 2); // Remove "&&" from the source string
				return ent::type::token(ent::type::AND, "&&");
			} else if (src.rfind("||", 0) == 0) {
				(void)shift(src, 2); // Remove "||" from the source string
				return ent::type::token(ent::type::OR, "||");
			} else if (src.rfind("^^", 0) == 0) {
				(void)shift(src, 2); // Remove "^^" from the source string
				return ent::type::token(ent::type::XOR, "^^");
			} else if(isdigit(src[0]) || src[0] == '.') {
				NumberValue number = get_number(src);
				return get_number_token(number);
			} else if (src.rfind("let", 0) == 0) {
				(void)shift(src, 3); // Remove "let" from the source string
				return ent::type::token(ent::type::LET, "let");
			} else if (src.rfind("i8", 0) == 0) {
				(void)shift(src, 2); // Remove "i8" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "i8");
			} else if (src.rfind("i16", 0) == 0) {
				(void)shift(src, 3); // Remove "i16" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "i16");
			} else if (src.rfind("i32", 0) == 0) {
				(void)shift(src, 3); // Remove "i32" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "i32");
			} else if (src.rfind("i64", 0) == 0) {
				(void)shift(src, 3); // Remove "i64" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "i64");
			} else if(src.rfind("u8", 0) == 0) {
				(void)shift(src, 2); // Remove "u8" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "u8");
			} else if (src.rfind("u16", 0) == 0) {
				(void)shift(src, 3); // Remove "u16" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "u16");
			} else if (src.rfind("u32", 0) == 0) {
				(void)shift(src, 3); // Remove "u32" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "u32");
			} else if (src.rfind("u64", 0) == 0) {
				(void)shift(src, 3); // Remove "u64" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "u64");
			} else if (src.rfind("f32", 0) == 0) {
				(void)shift(src, 3); // Remove "f32" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "f32");
			} else if (src.rfind("f64", 0) == 0) {
				(void)shift(src, 3); // Remove "f64" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "f64");
			} else if (src.rfind("bool", 0) == 0) {
				(void)shift(src, 4); // Remove "bool" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "bool");
			} else if (src.rfind("true", 0) == 0) {
				(void)shift(src, 4); // Remove "true" from the source string
				return ent::type::token(ent::type::BOOL, "true");
			} else if (src.rfind("false", 0) == 0) {
				(void)shift(src, 5); // Remove "false" from the source string
				return ent::type::token(ent::type::BOOL, "false");
			} else if (src.rfind("void", 0) == 0) {
				(void)shift(src, 4); // Remove "void" from the source string
				return ent::type::token(ent::type::TYPE_SPECIFIER, "void");
			} else if (src.rfind("fn", 0) == 0) {
				(void)shift(src, 2); // Remove "fn" from the source string
				return ent::type::token(ent::type::FN, "fn");
			} else if (src.rfind("if", 0) == 0) {
				(void)shift(src, 2); // Remove "if" from the source string
				return ent::type::token(ent::type::IF, "if");
			} else if (src.rfind("else", 0) == 0) {
				(void)shift(src, 4); // Remove "else" from the source string
				return ent::type::token(ent::type::ELSE, "else");
			} else if (src.rfind("for", 0) == 0) {
				(void)shift(src, 3); // Remove "for" from the source string
				return ent::type::token(ent::type::FOR, "for");
			} else {
				std::string identifier = "";
				while(isalnum(src[0])) {
					identifier += shift(src);
				}
				return ent::type::token(ent::type::IDENTIFIER, identifier);
			}
		}

		std::vector<ent::type::token> lex(std::string src) {
			// Create an empty token list
			std::vector<ent::type::token> tokens;
			// Iterate through the source string
			while(src.length() > 0) {
				// If the current character is a space, skip it
				if(src[0] == ' ' || src[0] == '\t' || src[0] == '\n' || src[0] == '\r') {
					shift(src);
					continue;
				} else {
					// Get the next token
					ent::type::token tk = get_token(src);
					// Add the token to the list
					tokens.push_back(tk);
				}
			}
			// Add an EOF token to the end of the list
			tokens.push_back(ent::type::token());
			return tokens;
		}
	}
}

#endif // __ENT_FRONT_LEX__