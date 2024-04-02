#ifndef __ENT_TYPES_TOKEN__
#define __ENT_TYPES_TOKEN__

#include <iostream>
#include <string>

namespace ent {
	namespace type {
		enum token_type {
			OPERATOR,

			OPEN_PAREN,
			CLOSE_PAREN,

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
					case OPEN_PAREN:
						type = "OPEN_PAREN";
						break;
					case CLOSE_PAREN:
						type = "CLOSE_PAREN";
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