#ifndef __ENT_RUNTIME_VALUES__
#define __ENT_RUNTIME_VALUES__

#include <string>

namespace ent {
	namespace runtime {

		enum ValueType {
			NULL_VAL,

			I8,
			I16,
			I32,
			I64,

			U8,
			U16,
			U32,
			U64,

			F32,
			F64,

			BOOL,

			CHAR,
			STR,
		};

		class RuntimeValue {
		public:
			virtual ValueType type() {
				return ValueType::NULL_VAL;
			};
			virtual std::string pretty_print() {
				return "RuntimeValue";
			}
			virtual bool IsTrue() {
				return false;
			}
		};

		class NullValue: public RuntimeValue {
		public:
			bool visible = true;
			NullValue(bool visible = true) {
				this->visible = visible;
			}
			virtual ValueType type() override {
				return ValueType::NULL_VAL;
			}
			virtual std::string pretty_print() override {
				return this->visible ? "null" : "";
			}
			virtual bool IsTrue() {
				return false;
			}
		};

		class NumberValue: public RuntimeValue {
		public:
			virtual int magnitude() {
				return -1;
			}
		};

		class IntegerValue: public NumberValue {};

		bool IsSignedIntegerType(ValueType type) {
			return type == ValueType::I8 || type == ValueType::I16 || type == ValueType::I32 || type == ValueType::I64 ;
		}

		bool IsIntegerType(ValueType type) {
			return
				IsSignedIntegerType(type) ||
				type == ValueType::U8 || type == ValueType::U16 || type == ValueType::U32 || type == ValueType::U64;
		}

		bool IsNumericType(ValueType type) {
			return
				IsIntegerType(type) ||
				type == ValueType::F32 || type == ValueType::F64;
		}

		class SignedIntegerValue: public IntegerValue {};

		class I8Value: public SignedIntegerValue {
		private:
			i8 value;
		public:
			I8Value(i8 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::I8;
			}
			i8 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 7;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": i8";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class I16Value: public SignedIntegerValue {
		private:
			i16 value;
		public:
			I16Value(i16 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::I16;
			}
			i16 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 15;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": i16";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class I32Value: public SignedIntegerValue {
		private:
			i32 value;
		public:
			I32Value(i32 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::I32;
			}
			i32 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 31;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": i32";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class I64Value: public SignedIntegerValue {
		private:
			i64 value;
		public:
			I64Value(i64 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::I64;
			}
			i64 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 63;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": i64";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class UnsignedIntegerValue: public IntegerValue {};

		class U8Value: public UnsignedIntegerValue {
		private:
			u8 value;
		public:
			U8Value(u8 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::U8;
			}
			u8 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 8;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": u8";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};
		class U16Value: public UnsignedIntegerValue {
		private:
			u16 value;
		public:
			U16Value(u16 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::U16;
			}
			u16 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 16;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": u16";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};
		class U32Value: public UnsignedIntegerValue {
		private:
			u32 value;
		public:
			U32Value(u32 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::U32;
			}
			u32 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 32;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": u32";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};
		class U64Value: public UnsignedIntegerValue {
		private:
			u64 value;
		public:
			U64Value(u64 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::U64;
			}
			u64 get_value() {
				return this->value;
			}
			virtual int magnitude() {
				return 64;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": u64";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class FloatValue: public NumberValue {};

		bool IsFloatType(ValueType type) {
			return type == ValueType::F32 || type == ValueType::F64;
		}

		class F32Value: public FloatValue {
		private:
			f32 value;
		public:
			F32Value(f32 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::F32;
			}
			float get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": f32";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class F64Value: public FloatValue {
		private:
			f64 value;
		public:
			F64Value(f64 value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::F64;
			}
			double get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return std::to_string(this->value) + ": f64";
			}
			virtual bool IsTrue() {
				return value != 0;
			}
		};

		class BooleanValue : public RuntimeValue {
		private:
			bool value;
		public:
			BooleanValue(bool value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::BOOL;
			}
			bool get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return this->value ? "true" : "false";
			}
			virtual bool IsTrue() {
				return value;
			}
		};

		class CharValue : public RuntimeValue {
		private:
			char value;
		public:
			CharValue(char value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::CHAR;
			}
			char get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return std::string(1, this->value);
			}
			virtual bool IsTrue() {
				return value != '\0';
			}
		};

		class StrValue : public RuntimeValue {
		private:
			std::string value;
		public:
			StrValue(std::string value) {
				this->value = value;
			}
			virtual ValueType type() override {
				return ValueType::STR;
			}
			std::string get_value() {
				return this->value;
			}
			virtual std::string pretty_print() override {
				return this->value;
			}
			virtual bool IsTrue() {
				return value.size() > 0;
			}
		};
	}
}

#endif // __ENT_RUNTIME_VALUES__