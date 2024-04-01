#ifndef __ENT_ERRORS__
#define __ENT_ERRORS__

#include <iostream>

namespace ent {

	enum ErrorType {
		LEX_ERROR,
		PARSE_ERROR,
		RUNTIME_ERROR,
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

		std::string pretty_print() {
			std::string type = "";
			switch(this->type) {
				case LEX_ERROR:
					type = "LEX_ERROR";
					break;
				case PARSE_ERROR:
					type = "PARSE_ERROR";
					break;
				case RUNTIME_ERROR:
					type = "RUNTIME_ERROR";
					break;
			}
			return type + ": " + this->message;
		}
	};

	void throw_err(Error err) {
		std::cerr << err.pretty_print() << std::endl;
		exit(1);
	}
}

#endif // __ENT_ERRORS__