#ifndef __ENT_ERRORS__
#define __ENT_ERRORS__

#include <iostream>
#include <stdexcept>

namespace ent {

	enum ErrorType {
		INVALID_NUMBER_FORMAT_ERROR,
		INTEGER_OUT_OF_RANGE_ERROR,
		FLOAT_OUT_OF_RANGE_ERROR,

		PARSER_EXPECTED_OTHER_ERROR,
		INVALID_VOID_VARIABLE_ERROR,
		INVALID_TYPE_SPECIFIER_ERROR,
		EXPLICIT_VOID_MISSING_FN_ERROR,

		INVALID_IDENTIFIER_ERROR,

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

		DIVISION_BY_ZERO_ERROR,
		INVALID_OPERATOR_ERROR,
		INVALID_OPERANDS_ERROR,
		NON_MATCHED_NUMBER_OPERANDS_ERROR,

		UNKNOWN_STATEMENT_ERROR,

		REDECLARING_EXISTING_VARIABLE_ERROR,
		SETTING_NON_EXISTING_VARIABLE_ERROR,
		GETTING_NON_EXISTING_VARIABLE_ERROR,

		INVALID_TYPE_ERROR,
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
				case INVALID_NUMBER_FORMAT_ERROR:
					type = "INVALID_NUMBER_FORMAT_ERROR";
					break;
				case INTEGER_OUT_OF_RANGE_ERROR:
					type = "INTEGER_OUT_OF_RANGE_ERROR";
					break;
				case FLOAT_OUT_OF_RANGE_ERROR:
					type = "FLOAT_OUT_OF_RANGE_ERROR";
					break;
				case PARSER_EXPECTED_OTHER_ERROR:
					type = "PARSER_EXPECTED_OTHER_ERROR";
					break;
				case INVALID_VOID_VARIABLE_ERROR:
					type = "INVALID_VOID_VARIABLE_ERROR";
					break;
				case INVALID_TYPE_SPECIFIER_ERROR:
					type = "INVALID_TYPE_SPECIFIER_ERROR";
					break;
				case INVALID_IDENTIFIER_ERROR:
					type = "INVALID_IDENTIFIER_ERROR";
					break;
				case EXPLICIT_VOID_MISSING_FN_ERROR:
					type = "EXPLICIT_VOID_MISSING_FN_ERROR";
					break;
				case I8_OVERFLOW_ERROR:
					type = "I8_OVERFLOW_ERROR";
					break;
				case I8_UNDERFLOW_ERROR:
					type = "I8_UNDERFLOW_ERROR";
					break;
				case I16_OVERFLOW_ERROR:
					type = "I16_OVERFLOW_ERROR";
					break;
				case I16_UNDERFLOW_ERROR:
					type = "I16_UNDERFLOW_ERROR";
					break;
				case I32_OVERFLOW_ERROR:
					type = "I32_OVERFLOW_ERROR";
					break;
				case I32_UNDERFLOW_ERROR:
					type = "I32_UNDERFLOW_ERROR";
					break;
				case I64_OVERFLOW_ERROR:
					type = "I64_OVERFLOW_ERROR";
					break;
				case I64_UNDERFLOW_ERROR:
					type = "I64_UNDERFLOW_ERROR";
					break;
				case U8_OVERFLOW_ERROR:
					type = "U8_OVERFLOW_ERROR";
					break;
				case U8_UNDERFLOW_ERROR:
					type = "U8_UNDERFLOW_ERROR";
					break;
				case U16_OVERFLOW_ERROR:
					type = "U16_OVERFLOW_ERROR";
					break;
				case U16_UNDERFLOW_ERROR:
					type = "U16_UNDERFLOW_ERROR";
					break;
				case U32_OVERFLOW_ERROR:
					type = "U32_OVERFLOW_ERROR";
					break;
				case U32_UNDERFLOW_ERROR:
					type = "U32_UNDERFLOW_ERROR";
					break;
				case U64_OVERFLOW_ERROR:
					type = "U64_OVERFLOW_ERROR";
					break;
				case U64_UNDERFLOW_ERROR:
					type = "U64_UNDERFLOW_ERROR";
					break;
				case F32_OVERFLOW_ERROR:
					type = "F32_OVERFLOW_ERROR";
					break;
				case F32_UNDERFLOW_ERROR:
					type = "F32_UNDERFLOW_ERROR";
					break;
				case F64_OVERFLOW_ERROR:
					type = "F64_OVERFLOW_ERROR";
					break;
				case F64_UNDERFLOW_ERROR:
					type = "F64_UNDERFLOW_ERROR";
					break;
				case DIVISION_BY_ZERO_ERROR:
					type = "DIVISION_BY_ZERO_ERROR";
					break;
				case INVALID_OPERATOR_ERROR:
					type = "INVALID_OPERATOR_ERROR";
					break;
				case INVALID_OPERANDS_ERROR:
					type = "INVALID_OPERANDS_ERROR";
					break;
				case NON_MATCHED_NUMBER_OPERANDS_ERROR:
					type = "NON_MATCHED_NUMBER_OPERANDS_ERROR";
					break;
				case UNKNOWN_STATEMENT_ERROR:
					type = "UNKNOWN_STATEMENT_ERROR";
					break;
				case REDECLARING_EXISTING_VARIABLE_ERROR:
					type = "REDECLARING_EXISTING_VARIABLE_ERROR";
					break;
				case SETTING_NON_EXISTING_VARIABLE_ERROR:
					type = "SETTING_NON_EXISTING_VARIABLE_ERROR";
					break;
				case GETTING_NON_EXISTING_VARIABLE_ERROR:
					type = "GETTING_NON_EXISTING_VARIABLE_ERROR";
					break;
				case INVALID_TYPE_ERROR:
					type = "INVALID_TYPE_ERROR";
					break;
			}
			return std::runtime_error(type + ": " + this->message);
		}
	};
}

#endif // __ENT_ERRORS__