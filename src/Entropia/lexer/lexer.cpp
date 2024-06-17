#include <AquIce/Entropia/lexer.hpp>

[[nodiscard]] std::string shift(std::string& str) {
	std::string first = str.substr(0, 1);
	str = str.substr(1, str.length() - 1);
	return first;
}

[[nodiscard]] std::string shift(
	std::string& str,
	int n
) {
	std::string first = str.substr(0, n);
	str = str.substr(n, str.length() - n);
	return first;
}

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

std::vector<std::string> ent::front::lexer::valid_types = std::vector<std::string>({
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

struct ent::front::lexer::NumberValue ent::front::lexer::get_number(std::string& src) {
	std::string rvalue = "";
	bool is_integer = true;
	// Loop while the current character is the decimal separator or a digit
	while(src.at(0) == ENT__DECIMAL_SEPARATOR || isdigit(src.at(0))) {
		if(src.at(0) == ENT__DECIMAL_SEPARATOR) {
			if(!is_integer) {
				// Throw if we have 2 decimal separators in the current number
				throw (ent::Error(ent::ErrorType::LEXER_INVALID_NUMBER_FORMAT_ERROR, "Invalid number format")).error();
			}
			is_integer = false;
		}
		rvalue += shift(src);
	}
	return ent::front::lexer::NumberValue{rvalue, is_integer};
}

char ent::front::lexer::get_char(std::string& src) {
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
		throw (ent::Error(ent::ErrorType::LEXER_INVALID_ESCAPE_CHARACTER_ERROR, "Invalid escape character :" + escaped)).error();
	}
	return litteral;
}

std::string ent::front::lexer::get_string(std::string& src) {
	std::string buffer = "";
	while(src.at(0) != ENT__STRING_DELIMITER) {
		buffer += ent::front::lexer::get_char(src);
	}
	return buffer;
}

ent::lexer::token ent::front::lexer::get_number_token(ent::front::lexer::NumberValue n) {
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

ent::lexer::token ent::front::lexer::get_token(
	std::string& src,
	bool& isLastTokenType
) {

	// Check for all token types

	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::OPEN_PAREN, '(')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::CLOSE_PAREN, ')')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::OPEN_BRACE, '{')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::CLOSE_BRACE, '}')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::COLON, ':')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::SEMICOLON, ';')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::COMMA, ',')
	CHECK_FOR_STR_TOKEN(ent::lexer::EQUAL, "==")
	CHECK_FOR_STR_TOKEN(ent::lexer::MATCH_ARROW, "=>")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::ASSIGN, '=')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::SMALLER_OR_EQUAL, "<=")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::GREATER_OR_EQUAL, ">=")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::BITWISE_LEFT_SHIFT, "<<")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::SMALLER_THAN, '<')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::BITWISE_RIGHT_SHIFT, ">>")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::GREATER_THAN, '>')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::NOT_EQUAL, "!=")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::NOT, '!')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::INCREMENT, "++")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::PLUS, '+')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::DECREMENT, "--")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::MINUS, '-')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::TIMES, '*')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::DIVIDED_BY, '/')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::MODULO, '%')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::AND, "&&")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::BITWISE_AND, '&')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::OR, "||")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::BITWISE_OR, '|')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::XOR, "^^")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::BITWISE_XOR, '^')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::BITWISE_NOT, '~')
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::QUESTION_MARK, '?')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::LET, "let")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::MUTABLE, "mut")
	CHECK_FOR_TYPE_SPECIFIER_TOKEN()
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::BOOL, "true")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::BOOL, "false")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::FN, "fn")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::RETURN, "return")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::IF, "if")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::ELSE, "else")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::FOR, "for")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::WHILE, "while")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::MATCH, "match")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::DEFAULT, "default")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::BREAK, "break")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::IMPL, "impl")
	CHECK_FOR_CHR_TOKEN(ent::lexer::token_type::AT, '@')
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::PRIVATE, "private")
	CHECK_FOR_STR_TOKEN(ent::lexer::token_type::PUBLIC, "public")

	// Check for `type` token (set `isLastToken` to true)

	if (src.rfind("type", 0) == 0) {
		(void)shift(src, std::string("type").length());
		isLastTokenType = true;
		return ent::lexer::token(ent::lexer::token_type::TYPE, "type");
	}

	// Parse a number if the first character is a digit or a decimal separator
	
	if(isdigit(src.at(0)) || src.at(0) == ENT__DECIMAL_SEPARATOR) {
		ent::front::lexer::NumberValue number = ent::front::lexer::get_number(src);
		return get_number_token(number);
	}

	// Parse a char if the first character is a char delimiter

	if(src.at(0) == ENT__CHAR_DELIMITER) {
		(void)shift(src);
		char char_value = ent::front::lexer::get_char(src);
		(void)shift(src);
		return ent::lexer::token(ent::lexer::token_type::CHAR, std::string(1, char_value));
	}

	// Parse a string if the first character is a string delimiter

	if(src.at(0) == ENT__STRING_DELIMITER) {
		(void)shift(src);
		std::string string_value = ent::front::lexer::get_string(src);
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
		throw (ent::Error(
			ent::ErrorType::LEXER_UNKNOWN_TOKEN_ERROR,
			"Unknown token " + unknownToken
		)).error();
	}

	// Parse current token as new datatype

	if(isLastTokenType) {
		ent::front::lexer::valid_types.push_back(identifier);
		isLastTokenType = false;
		return ent::lexer::token(ent::lexer::TYPE_SPECIFIER, identifier);
	}

	return ent::lexer::token(ent::lexer::IDENTIFIER, identifier);
}

std::vector<ent::lexer::token> ent::front::lexer::lex(std::string src) {

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
					throw (ent::Error(
						ent::ErrorType::LEXER_UNCLOSED_COMMENT_ERROR,
						"Comment being opened and not closed before EOF"
					)).error();
				}
			}
			(void)shift(src, 2);
			continue;
		}
		if(src.rfind("*/", 0) == 0) {
			(void)shift(src, 2);
			throw (ent::Error(
				ent::ErrorType::LEXER_LONELY_CLOSING_COMMENT_ERROR,
				"Comment being closed without being opened"
			)).error();
		}
		tokens.push_back(ent::front::lexer::get_token(src, isLastTokenType));
	}
	
	// Add an EOF token to the end of the list
	tokens.push_back(ent::lexer::token());

	return tokens;
}