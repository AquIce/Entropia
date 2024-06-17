#ifndef __ENT_RUNTIME_VALUES__
#define __ENT_RUNTIME_VALUES__

#include <string>

#include "../types/numbers.hpp"

namespace ent {
	namespace runtime {

		#pragma region Enums

		/**
		 * The runtime value types
		 */
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

		#pragma endregion

		#pragma region Functions

		bool IsSignedIntegerType(ValueType type);

		bool IsIntegerType(ValueType type);

		bool IsNumericType(ValueType type);

		bool IsFloatType(ValueType type);

		#pragma endregion

		#pragma region Classes

		/**
		 * RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class RuntimeValue {
		public:
			/**
			 * Get the type of the value
			 * @return The type
			 */
			virtual ValueType type();

			/**
			 * Get the string representation of the value
			 * @return The string representation
			 */
			virtual std::string repr();
			
			/**
			 * Checks whether the value is true or false
			 */
			virtual bool IsTrue();
		};

		/**
		 * NullValue < RuntimeValue
		 */
		class NullValue: public RuntimeValue {
		public:
			// TODO check why shit here
			bool visible = true;
			/**
			 * Create a new Null Value
			 */
			NullValue(bool visible = true);
			
			virtual ValueType type() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
		};

		/**
		 * NumberValue < RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class NumberValue: public RuntimeValue {
		public:
			/**
			 * Get the magnitude of a NumberValue
			 */
			virtual int magnitude();
		};

		/**
		 * IntegerValue < NumberValue < RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class IntegerValue: public NumberValue {};

		/**
		 * SignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class SignedIntegerValue: public IntegerValue {};

		/**
		 * I8Value < SignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class I8Value: public SignedIntegerValue {
		public:
			/**
			 * Create a new I8 Value
			 */
			I8Value(i8 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			i8 get_value();
			
			virtual int magnitude() override;

			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			i8 value;
		};

		/**
		 * I16Value < SignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class I16Value: public SignedIntegerValue {
		public:
			I16Value(i16 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			i16 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			i16 value;
		};

		/**
		 * I32Value < SignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class I32Value: public SignedIntegerValue {
		public:
			I32Value(i32 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			i32 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			i32 value;
		};
		
		/**
		 * I64Value < SignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class I64Value: public SignedIntegerValue {
		public:
			I64Value(i64 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			i64 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			i64 value;
		};
		
		/**
		 * UnsignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class UnsignedIntegerValue: public IntegerValue {};

		/**
		 * U8Value < UnsignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class U8Value: public UnsignedIntegerValue {
		public:
			U8Value(u8 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			u8 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			u8 value;
		};
		
		/**
		 * U16Value < UnsignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class U16Value: public UnsignedIntegerValue {
		public:
			U16Value(u16 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			u16 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			u16 value;
		};
		
		/**
		 * U32Value < UnsignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class U32Value: public UnsignedIntegerValue {
		public:
			U32Value(u32 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			u32 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			u32 value;
		};
		
		/**
		 * U64Value < UnsignedIntegerValue < IntegerValue < NumberValue < RuntimeValue
		 */
		class U64Value: public UnsignedIntegerValue {
		public:
			U64Value(u64 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			u64 get_value();
			
			virtual int magnitude() override;
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			u64 value;
		};

		/**
		 * FloatValue < NumberValue < RuntimeValue
		 * @note This class is only used for inheritance purpose, never as a value
		 */
		class FloatValue: public NumberValue {};

		/**
		 * F32Value < FloatValue < NumberValue < RuntimeValue
		 */
		class F32Value: public FloatValue {
		public:
			F32Value(f32 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			float get_value();
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			f32 value;
		};

		/**
		 * F64Value < FloatValue < NumberValue < RuntimeValue
		 */
		class F64Value: public FloatValue {
		public:
			F64Value(f64 value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			double get_value();
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			f64 value;
		};

		/**
		 * BooleanValue < RuntimeValue
		 */
		class BooleanValue : public RuntimeValue {
		public:
			BooleanValue(bool value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			bool get_value();
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			bool value;
		};

		/**
		 * CharValue < RuntimeValue
		 */
		class CharValue : public RuntimeValue {
		public:
			CharValue(char value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			char get_value();
			
			virtual std::string repr() override;
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			char value;
		};

		/**
		 * StrValue < RuntimeValue
		 */
		class StrValue : public RuntimeValue {
		public:
			StrValue(std::string value);
			
			virtual ValueType type() override;
			
			/**
			 * Get the value held by the class
			 * @return The value
			 */
			std::string get_value();
			
			virtual std::string repr();
			
			virtual bool IsTrue();
			
		private:
			/**
			 * The value held by the class
			 */
			std::string value;
		};

		#pragma endregion
	}
}

#endif // __ENT_RUNTIME_VALUES__