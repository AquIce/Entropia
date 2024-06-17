#ifndef __ENT_LEXER_TOKEN__
#define __ENT_LEXER_TOKEN__

#include <iostream>
#include <string>

/**
 * Generate the `switch` case to get the type of a token
 * @param tk The token type
 */
#define TOKEN_SWITCH_CASE(tk) \
case tk: \
	type = #tk; \
	break;

namespace ent {
	namespace lexer {

		/**
		 * The type of a token
		 */
		enum token_type {

			// Variables / Constants / Functions

			LET,
			MUTABLE,
			TYPE_SPECIFIER,
			FN,
			RETURN,

			// Conditions

			IF,
			ELSE,
			FOR,
			WHILE,
			MATCH,
			DEFAULT,
			BREAK,

			// Symbols

			OPEN_PAREN,
			CLOSE_PAREN,
			OPEN_BRACE,
			CLOSE_BRACE,
			COLON,
			SEMICOLON,
			COMMA,
			ASSIGN,
			MATCH_ARROW,

			// Binary Operators

			PLUS,
			MINUS,
			TIMES,
			DIVIDED_BY,
			MODULO,
			BITWISE_LEFT_SHIFT,
			BITWISE_RIGHT_SHIFT,
			BITWISE_AND,
			BITWISE_OR,
			BITWISE_XOR,

			// Logical Operators

			EQUAL,
			NOT_EQUAL,
			AND,
			OR,
			XOR,
			SMALLER_THAN,
			GREATER_THAN,
			SMALLER_OR_EQUAL,
			GREATER_OR_EQUAL,

			// Unary Operators

			INCREMENT,
			DECREMENT,
			BITWISE_NOT,
			NOT,

			// Ternary Operator

			QUESTION_MARK,

			// Type Specifiers

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

			// Type Declarations / Implementations

			TYPE,
			IMPL,
			AT,
			PRIVATE,
			PUBLIC,

			// Identifier

			IDENTIFIER,

			// End Of File

			EOF_TOKEN,
		};

		/**
		 * A token
		 * @note This is used by the lexer
		 */
		class token {
		public:

			/**
			 * Create a new token
			 * @param type The type of the token to create
			 * @param value The value of the token
			 */
			token(
				enum token_type type,
				std::string value
			);

			/**
			 * Create a new token
			 * @note This will use `EOF_TOKEN` as the type and `""` as the value
			 */
			token();

			/**
			 * Get the type of the token
			 * @return The type of the token
			 */
			enum token_type get_type();
			
			/**
			 * Get the value of the token
			 * @return The value of the token
			 */
			std::string get_value();
			/**
			 * Set the type of the token
			 * @param type The new type to set
			 */
			void set_type(
				enum token_type type
			);

			/**
			 * Set the value of the token
			 * @param value The new value to set
			 */
			void set_value(
				std::string value
			);

			/**
			 * Get the string representation of the token
			 * @return The string representation
			 */
			std::string repr();

		private:
			/**
			 * The type of the token
			 */
			enum token_type type;

			/**
			 * The value of the token
			 */
			std::string value;
		};
	}
}

#endif // __ENT_LEXER_TOKEN__