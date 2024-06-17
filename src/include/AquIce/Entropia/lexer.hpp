#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>
#include <unordered_map>

#include "token.hpp"
#include "errors.hpp"
#include "../types/numbers.hpp"

/**
 * Decimal separator
 */
const char ENT__DECIMAL_SEPARATOR = '.';
/**
 * Char delimiter
 */
const char ENT__CHAR_DELIMITER = '\'';
/**
 * String delimiter
 */
const char ENT__STRING_DELIMITER = '"';
/**
 * Escape character
 */
const char ENT__ESCAPE_CHARACTER = '\\';

/**
 * Add `if` check for token of given type and char value
 * @param tk_type (ent::type::token_type) - The type of the token
 * @param value (char) - The value of the token
 * @return The `if` statement for the token
 */
#define CHECK_FOR_CHR_TOKEN(tk_type, value) \
if(src.at(0) == value) { \
	return ent::lexer::token(tk_type, shift(src)); \
} \

/**
 * Add `if` check for token of given type and string value
 * @param tk_type (ent::type::token_type) - The type of the token
 * @param value (std::string) - The value of the token
 * @return The `if` statement for the token
 */
#define CHECK_FOR_STR_TOKEN(tk_type, value) \
if(src.rfind(value, 0) == 0) { \
	(void)shift(src, std::string(value).length()); \
	return ent::lexer::token(tk_type, value); \
}

/**
 * Add `if` check for all type specifiers tokens
 * @return The `if` statement for the tokens
 */
#define CHECK_FOR_TYPE_SPECIFIER_TOKEN() \
for(std::string type : ent::front::lexer::valid_types) { \
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::TYPE_SPECIFIER, type) \
} \

/**
 * Shift the first character a string
 * @param str The string to shift
 * @return The shifted character
 * @note This function uses `[[nodiscard]]`, you need to explicitly cast the value to `void` if not used
 */
[[nodiscard]] std::string shift(std::string& str);

/**
 * Shift the `n` first characters of a string
 * @param str The string to shift
 * @param n The number of characters to shift
 * @return The shifted string
 * @note This function uses `[[nodiscard]]`, you need to explicitly cast the value to `void` if not used
 */
[[nodiscard]] std::string shift(std::string& str, int n);

/**
 * Get the escaped char from the code
 * @param escaped The non-escaped string
 * @return The escaped character
 */
char escape_char(std::string escaped);

namespace ent {
	namespace front {
		namespace lexer {
			/**
			 * The valid datatypes
			 */
			extern std::vector<std::string> valid_types;

			/**
			 * A number value
			 */
			struct NumberValue {
				/**
				 * The number value as a string
				 */
				std::string value;
				/**
				 * Whether or not the value is an integer
				 */
				bool is_integer;
			};

			/**
			 * Get a number from a source string
			 * @param src The source string
			 * @return A NumberValue containing the parsed value
			 */
			struct NumberValue get_number(std::string& src);

			/**
			 * Get a char value from a source string
			 * @param src The source string
			 * @return The parsed character
			 */
			char get_char(std::string& src);

			/**
			 * Get a string value from a source string
			 * @param src The source string
			 * @return The parsed string
			 */
			std::string get_string(std::string& src);

			/**
			 * Get a token of type number from a NumberValue
			 * @param n The NumberValue to generate a token from
			 * @return The generated token
			 */
			ent::lexer::token get_number_token(NumberValue n);

			/**
			 * Get a token from a source string
			 * @param src The source string
			 * @param isLastTokenType Whether the last token is `type` (to choose between identifier and type specifier)
			 * @return The token from the string
			 */
			ent::lexer::token get_token(std::string& src, bool& isLastTokenType);

			/**
			 * Convert a string to a list of tokens
			 * @param src The source string
			 * @return The final token list
			 */
			std::vector<ent::lexer::token> lex(std::string src);
		}
	}
}

#endif // __ENT_FRONT_LEX__