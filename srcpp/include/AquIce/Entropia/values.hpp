#ifndef __ENT_RUNTIME_VALUES__
#define __ENT_RUNTIME_VALUES__

#include <string>

namespace ent {
	namespace runtime {

		enum ValueType {
			NULL_VAL,
			NUMBER,
		};

		class RuntimeValue {
		public:
			virtual ValueType type() {
				return ValueType::NULL_VAL;
			};
			virtual std::string pretty_print() {
				return "RuntimeValue";
			}
		};

		class NullValue: public RuntimeValue {
		public:
			virtual ValueType type() override {
				return ValueType::NULL_VAL;
			}
			virtual std::string pretty_print() override {
				return "null";
			}
		};
		
		class NumberValue: public RuntimeValue {
		private:
			float value;
		public:
			NumberValue(float value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::NUMBER;
			}
			float get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value);
			}
		};
	}
}

#endif // __ENT_RUNTIME_VALUES__