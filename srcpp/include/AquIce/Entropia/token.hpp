#ifndef __ENT_TYPES_TOKEN__
#define __ENT_TYPES_TOKEN__

#include <iostream>
#include <string>

namespace ent {
	namespace type {
		enum token_type {
			OPERATOR,

			LET,
			TYPE_SPECIFIER,
			FN,

			IF,
			ELSE,
			FOR,
			WHILE,

			OPEN_PAREN,
			CLOSE_PAREN,
			OPEN_BRACE,
			CLOSE_BRACE,
			COLON,
			SEMICOLON,
			COMMA,
			ASSIGN,

			EQUAL,
			NOT_EQUAL,
			AND,
			OR,
			XOR,
			SMALLER_THAN,
			GREATER_THAN,
			SMALLER_OR_EQUAL,
			GREATER_OR_EQUAL,
			NOT,

			BOOL,

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
					case OPERATOR:
						type = "OPERATOR";
						break;
					case LET:
						type = "LET";
						break;
					case TYPE_SPECIFIER:
						type = "TYPE_SPECIFIER";
						break;
					case FN:
						type = "FN";
						break;
					case IF:
						type = "IF";
						break;
					case ELSE:
						type = "ELSE";
						break;
					case FOR:
						type = "FOR";
						break;
					case WHILE:
						type = "WHILE";
						break;
					case OPEN_PAREN:
						type = "OPEN_PAREN";
						break;
					case CLOSE_PAREN:
						type = "CLOSE_PAREN";
						break;
					case OPEN_BRACE:
						type = "OPEN_BRACE";
						break;
					case CLOSE_BRACE:
						type = "CLOSE_BRACE";
						break;
					case COLON:
						type = "COLON";
						break;
					case SEMICOLON:
						type = "SEMICOLON";
						break;
					case COMMA:
						type = "COMMA";
						break;
					case ASSIGN:
						type = "ASSIGN";
						break;
					case EQUAL:
						type = "EQUAL";
						break;
					case NOT_EQUAL:
						type = "NOT_EQUAL";
						break;
					case AND:
						type = "AND";
						break;
					case OR:
						type = "OR";
						break;
					case XOR:
						type = "XOR";
						break;
					case SMALLER_THAN:
						type = "SMALLER_THAN";
						break;
					case GREATER_THAN:
						type = "GREATER_THAN";
						break;
					case SMALLER_OR_EQUAL:
						type = "SMALLER_OR_EQUAL";
						break;
					case GREATER_OR_EQUAL:
						type = "GREATER_OR_EQUAL";
						break;
					case NOT:
						type = "NOT";
						break;
					case BOOL:
						type = "BOOL";
						break;
					case I8:
						type = "I8";
						break;
					case I16:
						type = "I16";
						break;
					case I32:
						type = "I32";
						break;
					case I64:
						type = "I64";
						break;
						break;
					case U64:
						type = "U64";
						break;
					case F32:
						type = "F32";
						break;
					case F64:
						type = "F64";
						break;
					case IDENTIFIER:
						type = "IDENTIFIER";
						break;
					case EOF_TOKEN:
						type = "EOF_TOKEN";
						break;
				}
				type += ": ";
				type += this->value;
				return type;
			}
		};
	}
}

#endif // __ENT_TYPES_TOKEN__