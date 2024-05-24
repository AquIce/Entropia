#ifndef __ENT_RUNTIME_ENV__
#define __ENT_RUNTIME_ENV__

#include <string>
#include <unordered_map>

#include "values.hpp"
#include "errors.hpp"

namespace ent {
	namespace runtime {

		class Environment {
		private:
			std::unordered_map<std::string, RuntimeValue*> values;

		public:
			Environment() {
				this->values = std::unordered_map<std::string, RuntimeValue*>();
			}

			bool has(std::string key) {
				return this->values.find(key) != this->values.end();
			}
			RuntimeValue* set(std::string key, RuntimeValue* value) {
				if(!this->has(key)) {
					throw (Error(ErrorType::RUNTIME_ERROR, "Variable is not defined: " + key)).error();
				}
				this->values[key] = value;
				return value;
			}
			RuntimeValue* init(std::string key, RuntimeValue* value) {
				if(this->has(key)) {
					throw (Error(ErrorType::RUNTIME_ERROR, "Variable already defined: " + key)).error();
				}
				this->set(key, value);
				return value;
			}
			RuntimeValue* get(std::string key) {
				return this->values[key];
			}
		};
	}
}

#endif // __ENT_RUNTIME_ENV__