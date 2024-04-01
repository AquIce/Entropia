#ifndef __ENT_RUNTIME_VALUES__
#define __ENT_RUNTIME_VALUES__

#include <string>

namespace ent {
	namespace runtime {

		enum ValueType {
			NULL_VAL,
			INTEGER,
			FLOAT,
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

		class NumberValue: public RuntimeValue {};

		class IntegerValue: public NumberValue {
		private:
			int value;
		public:
			IntegerValue(int value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::INTEGER;
			}
			int get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value);
			}
		};

		class FloatValue: public NumberValue {
		private:
			float value;
		public:
			FloatValue(float value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::FLOAT;
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