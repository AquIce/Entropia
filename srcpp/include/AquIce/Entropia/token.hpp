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

			INTEGER,
			FLOAT,

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
					case INTEGER:
						type = "INTEGER";
						break;
					case FLOAT:
						type = "FLOAT";
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