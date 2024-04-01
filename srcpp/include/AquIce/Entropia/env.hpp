#ifndef __ENT_RUNTIME_ENV__
#define __ENT_RUNTIME_ENV__

#include <string>
#include <unordered_map>

#include "values.hpp"

namespace ent {
	namespace runtime {

		class Environment {
		private:
			std::unordered_map<std::string, RuntimeValue*> values;

		public:
			Environment() {
				this->values = std::unordered_map<std::string, RuntimeValue*>();
			}

			void set(std::string key, RuntimeValue* value) {
				this->values[key] = value;
			}
			RuntimeValue* get(std::string key) {
				return this->values[key];
			}
			bool has(std::string key) {
				return this->values.find(key) != this->values.end();
			}
		};
	}
}

#endif // __ENT_RUNTIME_ENV__