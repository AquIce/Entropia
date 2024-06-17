#include <AquIce/Entropia/env.hpp>

std::shared_ptr<ent::runtime::RuntimeValue> ent::runtime::get_result_value(
	std::shared_ptr<ent::runtime::RuntimeValue> dest,
	std::shared_ptr<ent::runtime::RuntimeValue> source
) {
	switch(dest->type()) {
		case ent::runtime::ValueType::I8:
			get_sub_result_value(ent::runtime::I8Value);
		case ent::runtime::ValueType::I16:
			get_sub_result_value(ent::runtime::I16Value);
		case ent::runtime::ValueType::I32:
			get_sub_result_value(ent::runtime::I32Value);
		case ent::runtime::ValueType::I64:
			get_sub_result_value(ent::runtime::I64Value);
		case ent::runtime::ValueType::U8:
			get_sub_result_value(ent::runtime::U8Value);
		case ent::runtime::ValueType::U16:
			get_sub_result_value(ent::runtime::U16Value);
		case ent::runtime::ValueType::U32:
			get_sub_result_value(ent::runtime::U32Value);
		default: // case ent::runtime::ValueType::U64:
			get_sub_result_value(ent::runtime::U64Value);
	}
}

std::shared_ptr<ent::runtime::RuntimeValue> ent::runtime::get_sample_value(enum ent::front::ast::NodeType type) {
	switch(type) {
		case ent::front::ast::NodeType::i8Expression:
			return std::make_shared<ent::runtime::I8Value>(0);
		case ent::front::ast::NodeType::i16Expression:
			return std::make_shared<ent::runtime::I16Value>(0);
		case ent::front::ast::NodeType::i32Expression:
			return std::make_shared<ent::runtime::I32Value>(0);
		case ent::front::ast::NodeType::i64Expression:
			return std::make_shared<ent::runtime::I64Value>(0);
		case ent::front::ast::NodeType::u8Expression:
			return std::make_shared<ent::runtime::U8Value>(0);
		case ent::front::ast::NodeType::u16Expression:
			return std::make_shared<ent::runtime::U16Value>(0);
		case ent::front::ast::NodeType::u32Expression:
			return std::make_shared<ent::runtime::U32Value>(0);
		case ent::front::ast::NodeType::u64Expression:
			return std::make_shared<ent::runtime::U64Value>(0);
		case ent::front::ast::NodeType::f32Expression:
			return std::make_shared<ent::runtime::F32Value>(0);
		case ent::front::ast::NodeType::f64Expression:
			return std::make_shared<ent::runtime::F64Value>(0);
		case ent::front::ast::NodeType::booleanExpression:
			return std::make_shared<ent::runtime::BooleanValue>(false);
		case ent::front::ast::NodeType::charExpression:
			return std::make_shared<ent::runtime::CharValue>('\0');
		case ent::front::ast::NodeType::strExpression:
			return std::make_shared<ent::runtime::StrValue>("");
		default:
			throw (ent::Error(ent::ErrorType::ENV_INVALID_TYPE_ERROR, "Trying to get sample value for invalid type to variable")).error();
	}
}

std::shared_ptr<ent::runtime::RuntimeValue> check_type_compatibility(
	std::shared_ptr<ent::runtime::RuntimeValue> dest,
	std::shared_ptr<ent::runtime::RuntimeValue> source,
	std::string key
) {
	if(dest->type() == source->type()) { return source; } // BOTH SAME TYPE
	if(ent::runtime::IsIntegerType(dest->type()) && ent::runtime::IsIntegerType(source->type())) { // BOTH INTEGER -> CHECK MAGNITUDE
		if(std::dynamic_pointer_cast<ent::runtime::IntegerValue>(dest)->magnitude() >= std::dynamic_pointer_cast<ent::runtime::IntegerValue>(source)->magnitude()) {
			return ent::runtime::get_result_value(dest, source);
		}
	}
	if(dest->type() == ent::runtime::ValueType::F64 && ent::runtime::IsFloatType(source->type())) { return std::make_shared<ent::runtime::F64Value>(std::dynamic_pointer_cast<ent::runtime::F32Value>(source)->get_value()); } // F64 AND Fxx

	throw (ent::Error(ent::ErrorType::ENV_INVALID_TYPE_ERROR, "Trying to assign invalid type to variable " + key)).error();
}

ent::runtime::Environment::Environment(std::shared_ptr<Environment> parent) {
	this->parent = parent;
	this->values = std::unordered_map<std::string, std::shared_ptr<EnvValue>>();
	this->functions = std::unordered_map<std::string, std::shared_ptr<ent::front::ast::FunctionDeclaration>>();
}

bool ent::runtime::Environment::has_value(std::string key) {
	return this->values.find(key) != this->values.end();
}

std::shared_ptr<ent::runtime::RuntimeValue> ent::runtime::Environment::set_value(
	std::string key,
	std::shared_ptr<ent::runtime::RuntimeValue> value
) {
	if(!this->has_value(key)) {
		if(this->parent != nullptr) {
			return this->parent->set_value(key, value);
		}
		throw (ent::Error(ent::ErrorType::ENV_SETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to set non-declared variable " + key)).error();
	}
	
	std::shared_ptr<ent::runtime::RuntimeValue> old_val = this->get_value(key);

	std::shared_ptr<ent::runtime::EnvValue> dest = this->values.at(key);
	if(!dest->isMutable) {
		throw (ent::Error(ent::ErrorType::ENV_SETTING_NON_MUTABLE_VARIABLE_ERROR, "Trying to set non-mutable variable " + key)).error();
	}
	this->values.at(key)->value = ent::runtime::check_type_compatibility(this->get_value(key), value, key);

	return old_val;
}

std::shared_ptr<ent::runtime::RuntimeValue> ent::runtime::Environment::init_value(
	std::string key,
	std::shared_ptr<ent::runtime::RuntimeValue> value,
	bool isMutable
) {
	if(this->has_value(key)) {
		throw (ent::Error(ent::ErrorType::ENV_REDECLARING_EXISTING_VARIABLE_ERROR, "Trying to redeclare an existing variable " + key)).error();
	}
	this->values[key] = std::make_shared<ent::runtime::EnvValue>(ent::runtime::EnvValue{value, isMutable});

	return value;
}

std::shared_ptr<ent::runtime::RuntimeValue> ent::runtime::Environment::get_value(std::string key) {
	if(!this->has_value(key)) {
		if(this->parent != nullptr) {
			return this->parent->get_value(key);
		}
		throw (ent::Error(ent::ErrorType::ENV_GETTING_NON_EXISTING_VARIABLE_ERROR, "Trying to get non-declared variable " + key)).error();
	}
	return this->values.at(key)->value;
}

bool ent::runtime::Environment::has_function(std::string key) {
	return this->functions.find(key) != this->functions.end();
}

std::shared_ptr<ent::front::ast::FunctionDeclaration> ent::runtime::Environment::init_function(
	std::string key,
	std::shared_ptr<ent::front::ast::FunctionDeclaration> function
) {
	if(this->has_function(key)) {
		throw (ent::Error(ent::ErrorType::ENV_REDECLARING_EXISTING_FUNCTION_ERROR, "Trying to redeclare an existing function " + key)).error();
	}
	this->functions[key] = function;

	return function;
}

std::shared_ptr<ent::front::ast::FunctionDeclaration> ent::runtime::Environment::get_function(std::string key) {
	if(!this->has_function(key)) {
		if(this->parent != nullptr) {
			return this->parent->get_function(key);
		}
		throw (ent::Error(ent::ErrorType::ENV_GETTING_NON_EXISTING_FUNCTION_ERROR, "Trying to get non-declared function " + key)).error();
	}
	return this->functions.at(key);
}