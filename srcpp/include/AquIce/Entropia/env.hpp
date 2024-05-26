#ifndef __ENT_RUNTIME_ENV__
#define __ENT_RUNTIME_ENV__

#include <string>
#include <unordered_map>

#include "values.hpp"
#include "errors.hpp"

namespace ent {
	namespace runtime {

		RuntimeValue* get_result_value(RuntimeValue* dest, RuntimeValue* source) {
			switch(dest->type()) {
				case ValueType::I8:
					return new I8Value(((I8Value*)source)->get_value());
				case ValueType::I16:
					return new I16Value(((I16Value*)source)->get_value());
				case ValueType::I32:
					return new I32Value(((I32Value*)source)->get_value());
				case ValueType::I64:
					return new I64Value(((I64Value*)source)->get_value());
				case ValueType::U8:
					return new U8Value(((U8Value*)source)->get_value());
				case ValueType::U16:
					return new U16Value(((U16Value*)source)->get_value());
				case ValueType::U32:
					return new U32Value(((U32Value*)source)->get_value());
				default: // case ValueType::U64:
					return new U64Value(((U64Value*)source)->get_value());
			}
		}

		RuntimeValue* get_sample_value(enum ent::front::ast::NodeType type) {
			switch(type) {
				case ent::front::ast::NodeType::i8Expression:
					return new I8Value(0);
				case ent::front::ast::NodeType::i16Expression:
					return new I16Value(0);
				case ent::front::ast::NodeType::i32Expression:
					return new I32Value(0);
				case ent::front::ast::NodeType::i64Expression:
					return new I64Value(0);
				case ent::front::ast::NodeType::u8Expression:
					return new U8Value(0);
				case ent::front::ast::NodeType::u16Expression:
					return new U16Value(0);
				case ent::front::ast::NodeType::u32Expression:
					return new U32Value(0);
				case ent::front::ast::NodeType::u64Expression:
					return new U64Value(0);
				case ent::front::ast::NodeType::f32Expression:
					return new F32Value(0);
				case ent::front::ast::NodeType::f64Expression:
					return new F64Value(0);
				case ent::front::ast::NodeType::booleanExpression:
					return new BooleanValue(false);
				default:
					throw (Error(ErrorType::INVALID_TYPE_ERROR, "Trying to get sample value for invalid type to variable")).error();
			}
		}

		RuntimeValue* check_type_compatibility(RuntimeValue* dest, RuntimeValue* source, std::string key) {
			if(dest->type() == source->type()) { return source; } // BOTH SAME TYPE
			if(IsIntegerType(dest->type()) && IsIntegerType(source->type())) { // BOTH INTEGER -> CHECK MAGNITUDE
				if(((IntegerValue*)dest)->magnitude() >= ((IntegerValue*)source)->magnitude()) {
					return get_result_value(dest, source);
				}
			}
			if(dest->type() == ValueType::F64 && IsFloatType(source->type())) { return new F64Value(((F32Value*)source)->get_value()); } // F64 AND Fxx

			throw (Error(ErrorType::INVALID_TYPE_ERROR, "Trying to assign invalid type to variable " + key)).error();
		}

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
					throw (Error(ErrorType::SETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to set non-declared variable " + key)).error();
				}
				
				this->values[key] = check_type_compatibility(this->get(key), value, key);
				return value;
			}
			RuntimeValue* init(std::string key, RuntimeValue* value) {
				if(this->has(key)) {
					throw (Error(ErrorType::REDECLARING_EXISTING_VARIABLE_ERROR, "Trying to redeclare an existing variable " + key)).error();
				}
				this->values[key] = value;

				return value;
			}
			RuntimeValue* get(std::string key) {
				if(!this->has(key)) {
					throw (Error(ErrorType::GETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to get non-declared variable " + key)).error();
				}
				return this->values[key];
			}
		};
	}
}

#endif // __ENT_RUNTIME_ENV__