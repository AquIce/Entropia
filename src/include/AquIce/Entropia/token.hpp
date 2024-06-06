#ifndef __ENT_TYPES_TOKEN__
#define __ENT_TYPES_TOKEN__

#include <iostream>
#include <string>

#define token_switch_case(tk) \
case tk: \
	type = #tk; \
	break;

namespace ent {
	namespace type {
		enum token_type {
			LET,
			MUTABLE,
			TYPE_SPECIFIER,
			FN,
			RETURN,

			IF,
			ELSE,
			FOR,
			WHILE,
			MATCH,
			DEFAULT,
			BREAK,

			OPEN_PAREN,
			CLOSE_PAREN,
			OPEN_BRACE,
			CLOSE_BRACE,
			COLON,
			SEMICOLON,
			COMMA,
			ASSIGN,
			MATCH_ARROW,

			PLUS,
			MINUS,
			TIMES,
			DIVIDED_BY,

			EQUAL,
			NOT_EQUAL,
			AND,
			OR,
			XOR,
			SMALLER_THAN,
			GREATER_THAN,
			SMALLER_OR_EQUAL,
			GREATER_OR_EQUAL,

			MODULO,
			BITWISE_LEFT_SHIFT,
			BITWISE_RIGHT_SHIFT,
			BITWISE_AND,
			BITWISE_OR,
			BITWISE_XOR,

			INCREMENT,
			DECREMENT,
			BITWISE_NOT,

			NOT,

			BOOL,

			CHAR,
			STR,

			I8,
			I16,
			I32,
			I64,
			// Ux with x less than 64 is not needed because it is only determined at runtime
			U64,
			F32,
			F64,

			IDENTIFIER,

			EOF_TOKEN,
		};

		class token {
		private:
			enum token_type type;
			std::string value;
		public:
			token(enum token_type type, std::string value) {
				this->type = type;
				this->value = value;
			}
			token() {
				this->type = EOF_TOKEN;
				this->value = "";
			}
			enum token_type get_type() {
				return this->type;
			}
			std::string get_value() {
				return this->value;
			}
			void set_type(enum token_type type) {
				this->type = type;
			}
			void set_value(std::string value) {
				this->value = value;
			}
			std::string pretty_print() {
				std::string type = "";
				switch(this->type) {
					token_switch_case(LET)
					token_switch_case(MUTABLE)
					token_switch_case(TYPE_SPECIFIER)
					token_switch_case(FN)
					token_switch_case(RETURN)

					token_switch_case(IF)
					token_switch_case(ELSE)
					token_switch_case(FOR)
					token_switch_case(WHILE)
					token_switch_case(MATCH)
					token_switch_case(DEFAULT)
					token_switch_case(BREAK)

					token_switch_case(OPEN_PAREN)
					token_switch_case(CLOSE_PAREN)
					token_switch_case(OPEN_BRACE)
					token_switch_case(CLOSE_BRACE)
					token_switch_case(COLON)
					token_switch_case(SEMICOLON)
					token_switch_case(COMMA)
					token_switch_case(ASSIGN)
					token_switch_case(MATCH_ARROW)

					token_switch_case(PLUS)
					token_switch_case(MINUS)
					token_switch_case(TIMES)
					token_switch_case(DIVIDED_BY)

					token_switch_case(EQUAL)
					token_switch_case(NOT_EQUAL)
					token_switch_case(AND)
					token_switch_case(OR)
					token_switch_case(XOR)
					token_switch_case(SMALLER_THAN)
					token_switch_case(GREATER_THAN)
					token_switch_case(SMALLER_OR_EQUAL)
					token_switch_case(GREATER_OR_EQUAL)
					token_switch_case(NOT)

					token_switch_case(MODULO)
					token_switch_case(BITWISE_LEFT_SHIFT)
					token_switch_case(BITWISE_RIGHT_SHIFT)
					token_switch_case(BITWISE_AND)
					token_switch_case(BITWISE_OR)
					token_switch_case(BITWISE_XOR)

					token_switch_case(INCREMENT)
					token_switch_case(DECREMENT)
					token_switch_case(BITWISE_NOT)

					token_switch_case(BOOL)

					token_switch_case(CHAR)
					token_switch_case(STR)

					token_switch_case(I8)
					token_switch_case(I16)
					token_switch_case(I32)
					token_switch_case(I64)
					token_switch_case(U64)
					token_switch_case(F32)
					token_switch_case(F64)

					token_switch_case(IDENTIFIER)

					token_switch_case(EOF_TOKEN)
				}
				type += ": ";
				type += this->value;
				return type;
			}
		};
	}
}

#endif // __ENT_TYPES_TOKEN__