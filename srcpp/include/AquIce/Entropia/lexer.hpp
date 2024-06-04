#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>

#include "token.hpp"
#include "errors.hpp"
#include "../types/numbers.hpp"

#define check_for_chr_token(tk_type, value) \
if(src[0] == value) { \
	return ent::type::token(tk_type, shift(src)); \
} \

#define check_for_str_token(tk_type, value) \
if (src.rfind(value, 0) == 0) { \
	(void)shift(src, std::string(value).length()); \
	return ent::type::token(tk_type, value); \
}

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
						throw (ent::Error(ErrorType::LEXER_INVALID_NUMBER_FORMAT_ERROR, "Invalid number format")).error();
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
				if(value > INT8_MIN && value < INT8_MAX) {
					return ent::type::token(ent::type::I8, n.value);
				} else if(value > _I16_MIN && value < INT16_MAX) {
					return ent::type::token(ent::type::I16, n.value);
				} else if(value > _I32_MIN && value < INT32_MAX) {
					return ent::type::token(ent::type::I32, n.value);
				} else if(value > _I64_MIN && value < INT64_MAX) {
					return ent::type::token(ent::type::I64, n.value);
				} else if(uValue > 0 && uValue < UINT_FAST64_MAX) {
					return ent::type::token(ent::type::U64, n.value);
				}
			} 
			double value = std::stod(n.value);
			if(value > FLT_MIN && value < FLT_MAX) {
				return ent::type::token(ent::type::F32, n.value);
			} else if(value > DBL_MIN && value < DBL_MAX) {
				return ent::type::token(ent::type::F64, n.value);
			}
			throw (ent::Error(ent::LEXER_VALUE_OUT_OF_RANGE_ERROR, "Value out of range")).error();
		}

		ent::type::token get_token(std::string& src) {
			check_for_chr_token(ent::type::token_type::OPEN_PAREN, '(')
			check_for_chr_token(ent::type::token_type::CLOSE_PAREN, ')')
			check_for_chr_token(ent::type::token_type::OPEN_BRACE, '{')
			check_for_chr_token(ent::type::token_type::CLOSE_BRACE, '}')
			check_for_chr_token(ent::type::token_type::COLON, ':')
			check_for_chr_token(ent::type::token_type::SEMICOLON, ';')
			check_for_chr_token(ent::type::token_type::COMMA, ',')
			check_for_str_token(ent::type::EQUAL, "==")
			check_for_chr_token(ent::type::token_type::ASSIGN, '=')
			check_for_str_token(ent::type::token_type::SMALLER_OR_EQUAL, "<=")
			check_for_str_token(ent::type::token_type::GREATER_OR_EQUAL, ">=")
			check_for_str_token(ent::type::token_type::BITWISE_LEFT_SHIFT, "<<")
			check_for_chr_token(ent::type::token_type::SMALLER_THAN, '<')
			check_for_str_token(ent::type::token_type::BITWISE_RIGHT_SHIFT, ">>")
			check_for_chr_token(ent::type::token_type::GREATER_THAN, '>')
			check_for_str_token(ent::type::token_type::NOT_EQUAL, "!=")
			check_for_chr_token(ent::type::token_type::NOT, '!')
			check_for_str_token(ent::type::token_type::INCREMENT, "++")
			check_for_chr_token(ent::type::token_type::PLUS, '+')
			check_for_str_token(ent::type::token_type::DECREMENT, "--")
			check_for_chr_token(ent::type::token_type::MINUS, '-')
			check_for_chr_token(ent::type::token_type::TIMES, '*')
			check_for_chr_token(ent::type::token_type::DIVIDED_BY, '/')
			check_for_chr_token(ent::type::token_type::MODULO, '%')
			check_for_str_token(ent::type::token_type::AND, "&&")
			check_for_chr_token(ent::type::token_type::BITWISE_AND, '&')
			check_for_str_token(ent::type::token_type::OR, "||")
			check_for_chr_token(ent::type::token_type::BITWISE_OR, '|')
			check_for_chr_token(ent::type::token_type::BITWISE_XOR, '^')
			check_for_chr_token(ent::type::token_type::BITWISE_NOT, '~')
			check_for_str_token(ent::type::token_type::XOR, "^^")
			check_for_str_token(ent::type::token_type::LET, "let")
			check_for_str_token(ent::type::token_type::MUTABLE, "mut")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "i8")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "i16")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "i32")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "i64")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "u8")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "u16")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "u32")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "u64")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "f32")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "f64")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "bool")
			check_for_str_token(ent::type::token_type::TYPE_SPECIFIER, "void")
			check_for_str_token(ent::type::token_type::BOOL, "true")
			check_for_str_token(ent::type::token_type::BOOL, "false")
			check_for_str_token(ent::type::token_type::FN, "fn")
			check_for_str_token(ent::type::token_type::IF, "if")
			check_for_str_token(ent::type::token_type::ELSE, "else")
			check_for_str_token(ent::type::token_type::FOR, "for")
			check_for_str_token(ent::type::token_type::WHILE, "while")
			
			if(isdigit(src[0]) || src[0] == '.') {
				NumberValue number = get_number(src);
				return get_number_token(number);
			}

			std::string identifier = "";
			while(isalpha(src[0]) || src[0] == '_') {
				identifier += shift(src);
			}
			return ent::type::token(ent::type::IDENTIFIER, identifier);
		}

		std::vector<ent::type::token> lex(std::string src) {

			std::vector<ent::type::token> tokens;

			while(src.length() > 0) {
				
				if(src[0] == ' ' || src[0] == '\t' || src[0] == '\n' || src[0] == '\r') {
					shift(src);
					continue;
				} else {
					tokens.push_back(get_token(src));
				}
			}
			// Add an EOF token to the end of the list
			tokens.push_back(ent::type::token());

			return tokens;
		}
	}
}

#endif // __ENT_FRONT_LEX__