#ifndef __ENT_ERRORS__
#define __ENT_ERRORS__

#include <iostream>
#include <stdexcept>

namespace ent {

	enum ErrorType {
		LEX_ERROR,
		PARSE_ERROR,

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
				case LEX_ERROR:
					type = "LEX_ERROR";
					break;
				case PARSE_ERROR:
					type = "PARSE_ERROR";
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