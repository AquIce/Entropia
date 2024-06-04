#ifndef __ENT_RUNTIME_ENV__
#define __ENT_RUNTIME_ENV__

#include <string>
#include <unordered_map>

#include "values.hpp"
#include "errors.hpp"

namespace ent {
	namespace runtime {

		std::shared_ptr<RuntimeValue> get_result_value(std::shared_ptr<RuntimeValue> dest, std::shared_ptr<RuntimeValue> source) {
			switch(dest->type()) {
				case ValueType::I8:
					return std::make_shared<I8Value>(std::dynamic_pointer_cast<I8Value>(source)->get_value());
				case ValueType::I16:
					return std::make_shared<I16Value>(std::dynamic_pointer_cast<I16Value>(source)->get_value());
				case ValueType::I32:
					return std::make_shared<I32Value>(std::dynamic_pointer_cast<I32Value>(source)->get_value());
				case ValueType::I64:
					return std::make_shared<I64Value>(std::dynamic_pointer_cast<I64Value>(source)->get_value());
				case ValueType::U8:
					return std::make_shared<U8Value>(std::dynamic_pointer_cast<U8Value>(source)->get_value());
				case ValueType::U16:
					return std::make_shared<U16Value>(std::dynamic_pointer_cast<U16Value>(source)->get_value());
				case ValueType::U32:
					return std::make_shared<U32Value>(std::dynamic_pointer_cast<U32Value>(source)->get_value());
				default: // case ValueType::U64:
					return std::make_shared<U64Value>(std::dynamic_pointer_cast<U64Value>(source)->get_value());
			}
		}

		std::shared_ptr<RuntimeValue> get_sample_value(enum ent::front::ast::NodeType type) {
			switch(type) {
				case ent::front::ast::NodeType::i8Expression:
					return std::make_shared<I8Value>(0);
				case ent::front::ast::NodeType::i16Expression:
					return std::make_shared<I16Value>(0);
				case ent::front::ast::NodeType::i32Expression:
					return std::make_shared<I32Value>(0);
				case ent::front::ast::NodeType::i64Expression:
					return std::make_shared<I64Value>(0);
				case ent::front::ast::NodeType::u8Expression:
					return std::make_shared<U8Value>(0);
				case ent::front::ast::NodeType::u16Expression:
					return std::make_shared<U16Value>(0);
				case ent::front::ast::NodeType::u32Expression:
					return std::make_shared<U32Value>(0);
				case ent::front::ast::NodeType::u64Expression:
					return std::make_shared<U64Value>(0);
				case ent::front::ast::NodeType::f32Expression:
					return std::make_shared<F32Value>(0);
				case ent::front::ast::NodeType::f64Expression:
					return std::make_shared<F64Value>(0);
				case ent::front::ast::NodeType::booleanExpression:
					return std::make_shared<BooleanValue>(false);
				case ent::front::ast::NodeType::charExpression:
					return std::make_shared<CharValue>('\0');
				case ent::front::ast::NodeType::strExpression:
					return std::make_shared<StrValue>("");
				default:
					throw (ent::Error(ent::ErrorType::ENV_INVALID_TYPE_ERROR, "Trying to get sample value for invalid type to variable")).error();
			}
		}

		std::shared_ptr<RuntimeValue> check_type_compatibility(std::shared_ptr<RuntimeValue> dest, std::shared_ptr<RuntimeValue> source, std::string key) {
			if(dest->type() == source->type()) { return source; } // BOTH SAME TYPE
			if(IsIntegerType(dest->type()) && IsIntegerType(source->type())) { // BOTH INTEGER -> CHECK MAGNITUDE
				if(std::dynamic_pointer_cast<IntegerValue>(dest)->magnitude() >= std::dynamic_pointer_cast<IntegerValue>(source)->magnitude()) {
					return get_result_value(dest, source);
				}
			}
			if(dest->type() == ValueType::F64 && IsFloatType(source->type())) { return std::make_shared<F64Value>(std::dynamic_pointer_cast<F32Value>(source)->get_value()); } // F64 AND Fxx

			throw (ent::Error(ent::ErrorType::ENV_INVALID_TYPE_ERROR, "Trying to assign invalid type to variable " + key)).error();
		}

		typedef struct EnvValue {
			std::shared_ptr<RuntimeValue> value;
			bool isMutable;
		} EnvValue;

		class Environment {
		private:
			std::shared_ptr<Environment> parent = nullptr;
			std::unordered_map<std::string, std::shared_ptr<EnvValue>> values;
			std::unordered_map<std::string, std::shared_ptr<ent::front::ast::FunctionDeclaration>> functions;

		public:
			Environment(std::shared_ptr<Environment> parent = nullptr) {
				this->parent = parent;
				this->values = std::unordered_map<std::string, std::shared_ptr<EnvValue>>();
				this->functions = std::unordered_map<std::string, std::shared_ptr<ent::front::ast::FunctionDeclaration>>();
			}

			bool has_value(std::string key) {
				return this->values.find(key) != this->values.end();
			}
			std::shared_ptr<RuntimeValue> set_value(std::string key, std::shared_ptr<RuntimeValue> value) {
				if(!this->has_value(key)) {
					if(this->parent != nullptr) {
						return this->parent->set_value(key, value);
					}
					throw (ent::Error(ent::ErrorType::ENV_SETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to set non-declared variable " + key)).error();
				}
				
				std::shared_ptr<RuntimeValue> old_val = get_value(key);

				std::shared_ptr<EnvValue> dest = this->values.at(key);
				if(!dest->isMutable) {
					throw (ent::Error(ent::ErrorType::ENV_SETTING_NON_MUTABLE_VARIABLE_ERROR, "Trying to set non-mutable variable " + key)).error();
				}
				this->values.at(key)->value = check_type_compatibility(this->get_value(key), value, key);

				return old_val;
			}
			std::shared_ptr<RuntimeValue> init_value(std::string key, std::shared_ptr<RuntimeValue> value, bool isMutable) {
				if(this->has_value(key)) {
					throw (ent::Error(ent::ErrorType::ENV_REDECLARING_EXISTING_VARIABLE_ERROR, "Trying to redeclare an existing variable " + key)).error();
				}
				this->values[key] = std::make_shared<EnvValue>(EnvValue{value, isMutable});

				return value;
			}
			std::shared_ptr<RuntimeValue> get_value(std::string key) {
				if(!this->has_value(key)) {
					if(this->parent != nullptr) {
						return this->parent->get_value(key);
					}
					throw (ent::Error(ent::ErrorType::ENV_GETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to get non-declared variable " + key)).error();
				}
				return this->values.at(key)->value;
			}
			
			bool has_function(std::string key) {
				if(this->functions.find(key) == this->functions.end()) {
					if(this->parent != nullptr) {
						return parent->has_function(key);
					}

					return false;
				}
				
				return true;
			}
			std::shared_ptr<ent::front::ast::FunctionDeclaration> init_function(std::string key, std::shared_ptr<ent::front::ast::FunctionDeclaration> function) {
				if(this->has_function(key)) {
					throw (ent::Error(ent::ErrorType::ENV_REDECLARING_EXISTING_FUNCTION_ERROR, "Trying to redeclare an existing function " + key)).error();
				}
				this->functions[key] = function;

				return function;
			}
			std::shared_ptr<ent::front::ast::FunctionDeclaration> get_function(std::string key) {
				if(!this->has_function(key)) {
					if(this->parent != nullptr) {
						return this->parent->get_function(key);
					}
					throw (ent::Error(ent::ErrorType::ENV_GETTING_NON_EXISTING_FUNCTION_ERROR, "Trying to get non-declared function " + key)).error();
				}
				return this->functions.at(key);
			}
		};
	}
}

#endif // __ENT_RUNTIME_ENV__