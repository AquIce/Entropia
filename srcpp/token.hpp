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

			NUMBER,
		};

		class token {
		private:
			enum token_type type;
			std::string value;
		public:
			token(enum token_type type, std::string value);
			token();
			enum token_type get_type();
			std::string get_value();
			void set_type(enum token_type type);
			void set_value(std::string value);
			std::string pretty_print();
		};
	}
}

#endif // __ENT_TYPES_TOKEN__