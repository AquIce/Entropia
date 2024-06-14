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
#define check_for_chr_token(tk_type, value) \
if(src.at(0) == value) { \
	return ent::lexer::token(tk_type, shift(src)); \
} \

/**
 * Add `if` check for token of given type and string value
 * @param tk_type (ent::type::token_type) - The type of the token
 * @param value (std::string) - The value of the token
 * @return The `if` statement for the token
 */
#define check_for_str_token(tk_type, value) \
if(src.rfind(value, 0) == 0) { \
	(void)shift(src, std::string(value).length()); \
	return ent::lexer::token(tk_type, value); \
}

/**
 * Add `if` check for all type specifiers tokens
 * @return The `if` statement for the tokens
 */
#define check_for_type_specifier_token() \
for(std::string type : validTypes) { \
	check_for_str_token(ent::lexer::token_type::TYPE_SPECIFIER, type) \
} \

/**
 * Shift the first character a string
 * @param str The string to shift
 * @return The shifted character
 */
[[nodiscard]]  std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

/**
 * Shift the `n` first characters of a string
 * @param str The string to shift
 * @param n The number of characters to shift
 * @return The shifted string
 */
[[nodiscard]]  std::string shift(std::string& str, int n) {
	std::string first = str.substr(0, n);
	str = str.substr(n, str.length() - n);
	return first;
}

/**
 * Get the escaped char from the code
 * @param escaped The non-escaped string
 * @return The escaped character
 */
char escape_char(std::string escaped) {
	return std::unordered_map<std::string, char>({
		{"\\a", '\a'},
		{"\\b", '\b'},
		{"\\f", '\f'},
		{"\\n", '\n'},
		{"\\r", '\r'},
		{"\\t", '\t'},
		{"\\v", '\v'},
		{"\\\\", '\\'},
		{"\\'", '\''},
		{"\\\"", '\"'},
		{"\\?", '\?'},
		{"\\0", '\0'}
	}).at(escaped);
}

namespace ent {
	namespace front {

		namespace lexer {
			/**
			 * The valid datatypes
			 */
			std::vector<std::string> validTypes = std::vector<std::string>({
				"i8",
				"i16",
				"i32",
				"i64",
				"u8",
				"u16",
				"u32",
				"u64",
				"f32",
				"f64",
				"bool",
				"char",
				"str",
				"void",
			});

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
			struct NumberValue get_number(std::string& src) {
				std::string rvalue = "";
				bool is_integer = true;
				// Loop while the current character is the decimal separator or a digit
				while(src.at(0) == ENT__DECIMAL_SEPARATOR || isdigit(src.at(0))) {
					if(src.at(0) == ENT__DECIMAL_SEPARATOR) {
						if(!is_integer) {
							// Throw if we have 2 decimal separators in the current number
							throw (ent::Error(ErrorType::LEXER_INVALID_NUMBER_FORMAT_ERROR, "Invalid number format")).error();
						}
						is_integer = false;
					}
					rvalue += shift(src);
				}
				return NumberValue{rvalue, is_integer};
			}

			/**
			 * Get a char value from a source string
			 * @param src The source string
			 * @return The parsed character
			 */
			char get_char(std::string& src) {
				char litteral = shift(src).at(0);
				if(litteral != ENT__ESCAPE_CHARACTER) {
					return litteral;
				}
				char c = shift(src).at(0);
				std::string escaped = "\\";
				escaped.push_back(c);

				try {
					litteral = escape_char(escaped);
				} catch(const std::exception& e) {
					throw (ent::Error(ErrorType::LEXER_INVALID_ESCAPE_CHARACTER_ERROR, "Invalid escape character :" + escaped)).error();
				}
				return litteral;
			}

			/**
			 * Get a string value from a source string
			 * @param src The source string
			 * @return The parsed string
			 */
			std::string get_string(std::string& src) {
				std::string buffer = "";
				while(src.at(0) != ENT__STRING_DELIMITER) {
					buffer += get_char(src);
				}
				return buffer;
			}

			/**
			 * Get a token of type number from a NumberValue
			 * @param n The NumberValue to generate a token from
			 * @return The generated token
			 */
			ent::lexer::token get_number_token(NumberValue n) {
				if(n.is_integer) {

					// Parse the value as signed and unsigned

					i64 value = std::stoll(n.value);
					u64 uValue = std::stoull(n.value);
					if(value > INT8_MIN && value < INT8_MAX) {
						return ent::lexer::token(ent::lexer::I8, n.value);
					} else if(value > _I16_MIN && value < INT16_MAX) {
						return ent::lexer::token(ent::lexer::I16, n.value);
					} else if(value > _I32_MIN && value < INT32_MAX) {
						return ent::lexer::token(ent::lexer::I32, n.value);
					} else if(value > _I64_MIN && value < INT64_MAX) {
						return ent::lexer::token(ent::lexer::I64, n.value);
					} else if(uValue > 0 && uValue < UINT_FAST64_MAX) {
						return ent::lexer::token(ent::lexer::U64, n.value);
					}
				}

				// Parse the value as a double

				double value = std::stod(n.value);
				if(value > FLT_MIN && value < FLT_MAX) {
					return ent::lexer::token(ent::lexer::F32, n.value);
				} else if(value > DBL_MIN && value < DBL_MAX) {
					return ent::lexer::token(ent::lexer::F64, n.value);
				}

				throw (ent::Error(ent::LEXER_VALUE_OUT_OF_RANGE_ERROR, "Value out of range")).error();
			}

			/**
			 * Get a token from a source string
			 * @param src The source string
			 * @param isLastTokenType Whether the last token is `type` (to choose between identifier and type specifier)
			 * @return The token from the string
			 */
			ent::lexer::token get_token(std::string& src, bool& isLastTokenType) {

				// Check for all token types

				check_for_chr_token(ent::lexer::token_type::OPEN_PAREN, '(')
				check_for_chr_token(ent::lexer::token_type::CLOSE_PAREN, ')')
				check_for_chr_token(ent::lexer::token_type::OPEN_BRACE, '{')
				check_for_chr_token(ent::lexer::token_type::CLOSE_BRACE, '}')
				check_for_chr_token(ent::lexer::token_type::COLON, ':')
				check_for_chr_token(ent::lexer::token_type::SEMICOLON, ';')
				check_for_chr_token(ent::lexer::token_type::COMMA, ',')
				check_for_str_token(ent::lexer::EQUAL, "==")
				check_for_str_token(ent::lexer::MATCH_ARROW, "=>")
				check_for_chr_token(ent::lexer::token_type::ASSIGN, '=')
				check_for_str_token(ent::lexer::token_type::SMALLER_OR_EQUAL, "<=")
				check_for_str_token(ent::lexer::token_type::GREATER_OR_EQUAL, ">=")
				check_for_str_token(ent::lexer::token_type::BITWISE_LEFT_SHIFT, "<<")
				check_for_chr_token(ent::lexer::token_type::SMALLER_THAN, '<')
				check_for_str_token(ent::lexer::token_type::BITWISE_RIGHT_SHIFT, ">>")
				check_for_chr_token(ent::lexer::token_type::GREATER_THAN, '>')
				check_for_str_token(ent::lexer::token_type::NOT_EQUAL, "!=")
				check_for_chr_token(ent::lexer::token_type::NOT, '!')
				check_for_str_token(ent::lexer::token_type::INCREMENT, "++")
				check_for_chr_token(ent::lexer::token_type::PLUS, '+')
				check_for_str_token(ent::lexer::token_type::DECREMENT, "--")
				check_for_chr_token(ent::lexer::token_type::MINUS, '-')
				check_for_chr_token(ent::lexer::token_type::TIMES, '*')
				check_for_chr_token(ent::lexer::token_type::DIVIDED_BY, '/')
				check_for_chr_token(ent::lexer::token_type::MODULO, '%')
				check_for_str_token(ent::lexer::token_type::AND, "&&")
				check_for_chr_token(ent::lexer::token_type::BITWISE_AND, '&')
				check_for_str_token(ent::lexer::token_type::OR, "||")
				check_for_chr_token(ent::lexer::token_type::BITWISE_OR, '|')
				check_for_str_token(ent::lexer::token_type::XOR, "^^")
				check_for_chr_token(ent::lexer::token_type::BITWISE_XOR, '^')
				check_for_chr_token(ent::lexer::token_type::BITWISE_NOT, '~')
				check_for_chr_token(ent::lexer::token_type::QUESTION_MARK, '?')
				check_for_str_token(ent::lexer::token_type::LET, "let")
				check_for_str_token(ent::lexer::token_type::MUTABLE, "mut")
				check_for_type_specifier_token()
				check_for_str_token(ent::lexer::token_type::BOOL, "true")
				check_for_str_token(ent::lexer::token_type::BOOL, "false")
				check_for_str_token(ent::lexer::token_type::FN, "fn")
				check_for_str_token(ent::lexer::token_type::RETURN, "return")
				check_for_str_token(ent::lexer::token_type::IF, "if")
				check_for_str_token(ent::lexer::token_type::ELSE, "else")
				check_for_str_token(ent::lexer::token_type::FOR, "for")
				check_for_str_token(ent::lexer::token_type::WHILE, "while")
				check_for_str_token(ent::lexer::token_type::MATCH, "match")
				check_for_str_token(ent::lexer::token_type::DEFAULT, "default")
				check_for_str_token(ent::lexer::token_type::BREAK, "break")
				check_for_str_token(ent::lexer::token_type::IMPL, "impl")
				check_for_chr_token(ent::lexer::token_type::AT, '@')
				check_for_str_token(ent::lexer::token_type::PRIVATE, "private")
				check_for_str_token(ent::lexer::token_type::PUBLIC, "public")

				// Check for `type` token (set `isLastToken` to true)

				if (src.rfind("type", 0) == 0) {
					(void)shift(src, std::string("type").length());
					isLastTokenType = true;
					return ent::lexer::token(ent::lexer::token_type::TYPE, "type");
				}

				// Parse a number if the first character is a digit or a decimal separator
				
				if(isdigit(src.at(0)) || src.at(0) == ENT__DECIMAL_SEPARATOR) {
					NumberValue number = get_number(src);
					return get_number_token(number);
				}

				// Parse a char if the first character is a char delimiter

				if(src.at(0) == ENT__CHAR_DELIMITER) {
					(void)shift(src);
					char char_value = get_char(src);
					(void)shift(src);
					return ent::lexer::token(ent::lexer::token_type::CHAR, std::string(1, char_value));
				}

				// Parse a string if the first character is a string delimiter

				if(src.at(0) == ENT__STRING_DELIMITER) {
					(void)shift(src);
					std::string string_value = get_string(src);
					(void)shift(src);
					return ent::lexer::token(ent::lexer::token_type::STR, string_value);
				}

				// If nothing else is found, parse as an identifiers

				std::string identifier = "";
				while(isalpha(src.at(0)) || src.at(0) == '_') {
					identifier += shift(src);
				}

				// If the identifier is invalid

				if(identifier.length() == 0) {
					std::string unknownToken = "";
					while(!(src.at(0) == ' ' || src.length() == 0)) {
						unknownToken += shift(src);
					}
					throw (ent::Error(ErrorType::LEXER_UNKNOWN_TOKEN_ERROR, "Unknown token " + unknownToken)).error();
				}

				// Parse current token as new datatype

				if(isLastTokenType) {
					validTypes.push_back(identifier);
					isLastTokenType = false;
					return ent::lexer::token(ent::lexer::TYPE_SPECIFIER, identifier);
				}

				return ent::lexer::token(ent::lexer::IDENTIFIER, identifier);
			}

			std::vector<ent::lexer::token> lex(std::string src) {

				std::vector<ent::lexer::token> tokens;
				bool isLastTokenType = false;

				while(src.length() > 0) {
					if(src.at(0) == ' ' || src.at(0) == '\t' || src.at(0) == '\n' || src.at(0) == '\r') {
						(void)shift(src);
						continue;
					}
					if(src.rfind("//", 0) == 0) {
						while(src.at(0) != '\n' && src.length() > 0) {
							(void)shift(src);
						}
						continue;
					}
					if(src.rfind("/*", 0) == 0) {
						while(src.rfind("*/", 0) != 0) {
							try {
								(void)shift(src);
							} catch(const std::exception& e) {
								throw (ent::Error(ErrorType::LEXER_UNCLOSED_COMMENT_ERROR, "Comment being opened and not closed before EOF")).error();
							}
						}
						(void)shift(src, 2);
						continue;
					}
					if(src.rfind("*/", 0) == 0) {
						(void)shift(src, 2);
						throw (ent::Error(ErrorType::LEXER_LONELY_CLOSING_COMMENT_ERROR, "Comment being closed without being opened")).error();
					}
					tokens.push_back(get_token(src, isLastTokenType));
				}
				
				// Add an EOF token to the end of the list
				tokens.push_back(ent::lexer::token());

				return tokens;
			}
		}
	}
}

#endif // __ENT_FRONT_LEX__