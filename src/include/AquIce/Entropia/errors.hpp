#ifndef __ENT_ERRORS__
#define __ENT_ERRORS__

#include <iostream>
#include <stdexcept>

#define error_switch_case(err) \
case err: \
	type = #err; \
	break;

namespace ent {

	enum ErrorType {
		LEXER_INVALID_NUMBER_FORMAT_ERROR,
		LEXER_INVALID_CHARACTER_FORMAT_ERROR,
		LEXER_VALUE_OUT_OF_RANGE_ERROR,
		LEXER_INVALID_ESCAPE_CHARACTER_ERROR,
		LEXER_UNCLOSED_COMMENT_ERROR,
		LEXER_LONELY_CLOSING_COMMENT_ERROR,

		PARSER_EXPECTED_OTHER_ERROR,
		PARSER_INVALID_VOID_VARIABLE_ERROR,
		PARSER_INVALID_TYPE_SPECIFIER_ERROR,
		PARSER_EXPLICIT_VOID_MISSING_FN_ERROR,
		PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE,
		PARSER_INVALID_EXPRESSION_IN_PARENTHESIS,
		PARSER_TRYING_TO_INCREMENT_NON_IDENTIFIER_ERROR,

		I8_OVERFLOW_ERROR,
		I8_UNDERFLOW_ERROR,
		I16_OVERFLOW_ERROR,
		I16_UNDERFLOW_ERROR,
		I32_OVERFLOW_ERROR,
		I32_UNDERFLOW_ERROR,
		I64_OVERFLOW_ERROR,
		I64_UNDERFLOW_ERROR,
		U8_OVERFLOW_ERROR,
		U8_UNDERFLOW_ERROR,
		U16_OVERFLOW_ERROR,
		U16_UNDERFLOW_ERROR,
		U32_OVERFLOW_ERROR,
		U32_UNDERFLOW_ERROR,
		U64_OVERFLOW_ERROR,
		U64_UNDERFLOW_ERROR,
		F32_OVERFLOW_ERROR,
		F32_UNDERFLOW_ERROR,
		F64_OVERFLOW_ERROR,
		F64_UNDERFLOW_ERROR,
		GLOBAL_OVERFLOW_ERROR,

		INTERPRETER_DIVISION_BY_ZERO_ERROR,
		INTERPRETER_INVALID_OPERATOR_ERROR,
		INTERPRETER_INVALID_OPERANDS_ERROR,
		INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR,
		INTERPRETER_OUT_OF_RANGE_NUMBER,
		NON_MATCHED_NUMBER_OPERANDS_ERROR,

		INTERPRETER_UNKNOWN_STATEMENT_ERROR,

		ENV_REDECLARING_EXISTING_VARIABLE_ERROR,
		ENV_SETTING_NON_EXISTING_VARIABLE_ERROR,
		ENV_GETTING_NON_EXISTING_VARIABLE_ERROR,
		ENV_REDECLARING_EXISTING_FUNCTION_ERROR,
		ENV_GETTING_NON_EXISTING_FUNCTION_ERROR,
		ENV_SETTING_NON_MUTABLE_VARIABLE_ERROR,

		ENV_INVALID_TYPE_ERROR,
	};

	class Error {
	private:
		ErrorType type;
		std::string message;

	public:
		Error(ErrorType type, std::string message) {
			this->type = type;
			this->message = message;
		}

		ErrorType get_type() {
			return this->type;
		}

		std::string get_message() {
			return this->message;
		}

		std::runtime_error error() {
			std::string type = "";
			switch(this->type) {
				error_switch_case(ErrorType::LEXER_INVALID_NUMBER_FORMAT_ERROR)
				error_switch_case(ErrorType::LEXER_INVALID_CHARACTER_FORMAT_ERROR)
				error_switch_case(ErrorType::LEXER_VALUE_OUT_OF_RANGE_ERROR)
				error_switch_case(ErrorType::LEXER_INVALID_ESCAPE_CHARACTER_ERROR)
				error_switch_case(ErrorType::LEXER_UNCLOSED_COMMENT_ERROR)
				error_switch_case(ErrorType::LEXER_LONELY_CLOSING_COMMENT_ERROR)

				error_switch_case(ErrorType::PARSER_EXPECTED_OTHER_ERROR)
				error_switch_case(ErrorType::PARSER_INVALID_VOID_VARIABLE_ERROR)
				error_switch_case(ErrorType::PARSER_INVALID_TYPE_SPECIFIER_ERROR)
				error_switch_case(ErrorType::PARSER_EXPLICIT_VOID_MISSING_FN_ERROR)
				error_switch_case(ErrorType::PARSER_MISSING_IF_STATEMENT_BEFORE_ELSE)
				error_switch_case(ErrorType::PARSER_INVALID_EXPRESSION_IN_PARENTHESIS)
				error_switch_case(ErrorType::PARSER_TRYING_TO_INCREMENT_NON_IDENTIFIER_ERROR)

				error_switch_case(ErrorType::I8_OVERFLOW_ERROR)
				error_switch_case(ErrorType::I8_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::I16_OVERFLOW_ERROR)
				error_switch_case(ErrorType::I16_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::I32_OVERFLOW_ERROR)
				error_switch_case(ErrorType::I32_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::I64_OVERFLOW_ERROR)
				error_switch_case(ErrorType::I64_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::U8_OVERFLOW_ERROR)
				error_switch_case(ErrorType::U8_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::U16_OVERFLOW_ERROR)
				error_switch_case(ErrorType::U16_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::U32_OVERFLOW_ERROR)
				error_switch_case(ErrorType::U32_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::U64_OVERFLOW_ERROR)
				error_switch_case(ErrorType::U64_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::F32_OVERFLOW_ERROR)
				error_switch_case(ErrorType::F32_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::F64_OVERFLOW_ERROR)
				error_switch_case(ErrorType::F64_UNDERFLOW_ERROR)
				error_switch_case(ErrorType::GLOBAL_OVERFLOW_ERROR)

				error_switch_case(ErrorType::INTERPRETER_DIVISION_BY_ZERO_ERROR)
				error_switch_case(ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR)
				error_switch_case(ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR)
				error_switch_case(ErrorType::INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR)
				error_switch_case(ErrorType::INTERPRETER_OUT_OF_RANGE_NUMBER)
				error_switch_case(ErrorType::NON_MATCHED_NUMBER_OPERANDS_ERROR)
				error_switch_case(ErrorType::INTERPRETER_UNKNOWN_STATEMENT_ERROR)

				error_switch_case(ErrorType::ENV_REDECLARING_EXISTING_VARIABLE_ERROR)
				error_switch_case(ErrorType::ENV_SETTING_NON_EXISTING_VARIABLE_ERROR)
				error_switch_case(ErrorType::ENV_GETTING_NON_EXISTING_VARIABLE_ERROR)
				error_switch_case(ErrorType::ENV_REDECLARING_EXISTING_FUNCTION_ERROR)
				error_switch_case(ErrorType::ENV_GETTING_NON_EXISTING_FUNCTION_ERROR)
				error_switch_case(ErrorType::ENV_INVALID_TYPE_ERROR)
				error_switch_case(ErrorType::ENV_SETTING_NON_MUTABLE_VARIABLE_ERROR)
			}
			return std::runtime_error(type + ": " + this->message);
		}
	};
}

#endif // __ENT_ERRORS__