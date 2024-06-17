#ifndef __ENT_RUNTIME_ENV__
#define __ENT_RUNTIME_ENV__

#include <string>
#include <unordered_map>

#include "values.hpp"
#include "ast.hpp"
#include "errors.hpp"

/**
 * Generate the `switch` structure to cast a value to a destination type
 * @param dest_type The destination type
 */
#define get_sub_result_value(dest_type) \
switch(source->type()) { \
	case ent::runtime::ValueType::I8: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::I8Value>(source)->get_value()); \
	case ent::runtime::ValueType::I16: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::I16Value>(source)->get_value()); \
	case ent::runtime::ValueType::I32: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::I32Value>(source)->get_value()); \
	case ent::runtime::ValueType::I64: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::I64Value>(source)->get_value()); \
	case ent::runtime::ValueType::U8: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::U8Value>(source)->get_value()); \
	case ent::runtime::ValueType::U16: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::U16Value>(source)->get_value()); \
	case ent::runtime::ValueType::U32: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::U32Value>(source)->get_value()); \
	default: \
		return std::make_shared<dest_type>(std::dynamic_pointer_cast<ent::runtime::U64Value>(source)->get_value()); \
}

namespace ent {
	namespace runtime {

		/**
		 * An environnment value
		 */
		typedef struct EnvValue {
			/**
			 * The actual runtime value
			 */
			std::shared_ptr<RuntimeValue> value;
			/**
			 * Whether the value is mutable
			 */
			bool isMutable;
		} EnvValue;

		#pragma region Functions

		/**
		 * Get the result value from the source and destination value
		 * @param dest The destination value
		 * @param source The source value
		 * @return The result value
		 */
		std::shared_ptr<RuntimeValue> get_result_value(
			std::shared_ptr<RuntimeValue> dest,
			std::shared_ptr<RuntimeValue> source
		);

		/**
		 * Get a sample value for a given type
		 * @param type The type to generate a sample value for
		 * @return The sample value
		 */
		std::shared_ptr<RuntimeValue> get_sample_value(enum ent::front::ast::NodeType type);

		/**
		 * Check the type compatibility from a type to another
		 * @param dest The destination value
		 * @param source The source value
		 * @param key The name of the variable (for error messages)
		 * @return The new value
		 */
		std::shared_ptr<RuntimeValue> check_type_compatibility(
			std::shared_ptr<RuntimeValue> dest,
			std::shared_ptr<RuntimeValue> source,
			std::string key
		);

		#pragma endregion

		#pragma region Classes

		/**
		 * An Environment
		 */
		class Environment {
		private:
			/**
			 * The parent environment
			 */
			std::shared_ptr<Environment> parent = nullptr;
			/**
			 * The values held by the environment (variables / constants)
			 */
			std::unordered_map<std::string, std::shared_ptr<EnvValue>> values;
			/**
			 * The functions held by the environment
			 */
			std::unordered_map<std::string, std::shared_ptr<ent::front::ast::FunctionDeclaration>> functions;

		public:
			/**
			 * Create a new Environment
			 */
			Environment(std::shared_ptr<Environment> parent = nullptr);

			/**
			 * Check whether this environment has a given key (variable / constant)
			 */
			bool has_value(std::string key);

			/**
			 * Set a value in the environment or its parents
			 * @param key The key to set the value for
			 * @param value The value to set
			 * @return The result value
			 */
			std::shared_ptr<RuntimeValue> set_value(
				std::string key,
				std::shared_ptr<RuntimeValue> value
			);
			
			/**
			 * Initialize a value at a given key
			 * @param key The key of the value
			 * @param value The value
			 * @param isMutable Whether the value is mutable
			 */
			std::shared_ptr<RuntimeValue> init_value(
				std::string key,
				std::shared_ptr<RuntimeValue> value,
				bool isMutable
			);
			
			/**
			 * Get a value at a given key in the environment or its parents
			 * @param key The key of the value
			 * @return The value
			 */
			std::shared_ptr<RuntimeValue> get_value(std::string key);
			
			/**
			 * Check whether this environment has a given key (function)
			 */
			bool has_function(std::string key);
			
			/**
			 * Initialize a function at a given key
			 * @param key The key of the fuhction
			 * @param function The function
			 */
			std::shared_ptr<ent::front::ast::FunctionDeclaration> init_function(
				std::string key,
				std::shared_ptr<ent::front::ast::FunctionDeclaration> function
			);
			
			/**
			 * Get a function at a given key in the environment or its parents
			 * @param key The key of the function
			 * @return The function
			 */
			std::shared_ptr<ent::front::ast::FunctionDeclaration> get_function(std::string key);
		};

		#pragma endregion
	}
}

#endif // __ENT_RUNTIME_ENV__