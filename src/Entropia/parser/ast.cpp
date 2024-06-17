#include <AquIce/Entropia/ast.hpp>

std::vector<std::shared_ptr<ent::front::ast::FunctionDeclaration>> ent::front::ast::functions = std::vector<std::shared_ptr<ent::front::ast::FunctionDeclaration>>();

std::vector<std::shared_ptr<ent::front::ast::TypeDeclaration>> ent::front::ast::types = std::vector<std::shared_ptr<ent::front::ast::TypeDeclaration>>();

#pragma region Functions

std::vector<enum ent::front::ast::NodeType> ent::front::ast::valid_casts_to_type(enum ent::front::ast::NodeType type) {
	return std::unordered_map<enum NodeType, std::vector<enum ent::front::ast::NodeType>>({
		{ent::front::ast::NodeType::i8Expression, std::vector<enum ent::front::ast::NodeType>({})},
		{ent::front::ast::NodeType::i16Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u8Expression,
			ent::front::ast::NodeType::i8Expression,
		})},
		{ent::front::ast::NodeType::i32Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u16Expression,
			ent::front::ast::NodeType::i16Expression,
		})},
		{ent::front::ast::NodeType::i64Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u32Expression,
			ent::front::ast::NodeType::i32Expression,
		})},
		{ent::front::ast::NodeType::u8Expression, std::vector<enum ent::front::ast::NodeType>({})},
		{ent::front::ast::NodeType::u16Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u8Expression,
		})},
		{ent::front::ast::NodeType::u32Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u16Expression,
		})},
		{ent::front::ast::NodeType::u64Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u32Expression,
		})},
		{ent::front::ast::NodeType::f32Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::u64Expression,
			ent::front::ast::NodeType::i64Expression,
		})},
		{ent::front::ast::NodeType::f64Expression, std::vector<enum ent::front::ast::NodeType>({
			ent::front::ast::NodeType::f32Expression,
		})},
	}).at(type);
}

enum ent::front::ast::NodeType ent::front::ast::get_operator_return_type(
	std::shared_ptr<ent::front::ast::Expression> left,
	std::string operator_symbol
) {
	if(operator_symbol == "==" || operator_symbol == "!=" ||
		operator_symbol == "&&" || operator_symbol == "||" ||
		operator_symbol == "<" || operator_symbol == ">" ||
		operator_symbol == "<=" || operator_symbol == ">=" ||
		operator_symbol == "^^" || operator_symbol == "!"
	) {
		return ent::front::ast::NodeType::booleanExpression;
	}

	if(left->get_type() == ent::front::ast::NodeType::binaryExpression) {
		return std::dynamic_pointer_cast<ent::front::ast::BinaryExpression>(left)->get_return_type();
	}
	if(left->get_type() == ent::front::ast::NodeType::identifier) {
		return std::dynamic_pointer_cast<ent::front::ast::Identifier>(left)->get_identifier_type();
	}
	return left->get_type();
}

std::shared_ptr<ent::front::ast::FunctionDeclaration> ent::front::ast::get_function(std::shared_ptr<ent::front::ast::Identifier> identifier) {
	for(std::shared_ptr<ent::front::ast::FunctionDeclaration> function : ent::front::ast::functions) {
		if(function->identifier->name == identifier->name) {
			return function;
		}
	}
	return nullptr;
}

/**
 * Get a type from its name
 * @param typeName The name of the type
 * @return The Type Declaration or `nullptr` if not found
 */
std::shared_ptr<ent::front::ast::TypeDeclaration> ent::front::ast::get_type_from_str(std::string typeName) {
	for(std::shared_ptr<ent::front::ast::TypeDeclaration> type : ent::front::ast::types) {
		if(type->typeName == typeName) {
			return type;
		}
	}
	return nullptr;
}

/**
 * Get a sample value for a given Node Type
 * @param type The Node Type to get a value from
 * @return An example expression
 */
std::shared_ptr<ent::front::ast::Expression> ent::front::ast::get_sample_expression(enum ent::front::ast::NodeType type) {
	switch(type) {
		case ent::front::ast::NodeType::i8Expression:
			return std::make_shared<ent::front::ast::I8Expression>();
		case ent::front::ast::NodeType::i16Expression:
			return std::make_shared<ent::front::ast::I16Expression>();
		case ent::front::ast::NodeType::i32Expression:
			return std::make_shared<ent::front::ast::I32Expression>();
		case ent::front::ast::NodeType::i64Expression:
			return std::make_shared<ent::front::ast::I64Expression>();
		case ent::front::ast::NodeType::u8Expression:
			return std::make_shared<ent::front::ast::U8Expression>();
		case ent::front::ast::NodeType::u16Expression:
			return std::make_shared<ent::front::ast::U16Expression>();
		case ent::front::ast::NodeType::u32Expression:
			return std::make_shared<ent::front::ast::U32Expression>();
		case ent::front::ast::NodeType::u64Expression:
			return std::make_shared<ent::front::ast::U64Expression>();
		case ent::front::ast::NodeType::f32Expression:
			return std::make_shared<ent::front::ast::F32Expression>();
		case ent::front::ast::NodeType::f64Expression:
			return std::make_shared<ent::front::ast::F64Expression>();
		case ent::front::ast::NodeType::booleanExpression:
			return std::make_shared<ent::front::ast::BooleanExpression>();
		case ent::front::ast::NodeType::charExpression:
			return std::make_shared<ent::front::ast::CharExpression>();
		case ent::front::ast::NodeType::strExpression:
			return std::make_shared<ent::front::ast::StrExpression>();
		default:
			throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected valid return type, got " + type)).error();
	}
}

/**
 * Get a Node Type from its string representation
 * @param type The string reprensentation of a type
 * @return The Node Type
 */
enum ent::front::ast::NodeType ent::front::ast::get_node_type(std::string type) {
	if(type == "i8") {
		return ent::front::ast::NodeType::i8Expression;
	} if(type == "i16") {
		return ent::front::ast::NodeType::i16Expression;
	} if(type == "i32") {
		return ent::front::ast::NodeType::i32Expression;
	} if(type == "i64") {
		return ent::front::ast::NodeType::i64Expression;
	} if(type == "u8") {
		return ent::front::ast::NodeType::u8Expression;
	} if(type == "u16") {
		return ent::front::ast::NodeType::u16Expression;
	} if(type == "u32") {
		return ent::front::ast::NodeType::u32Expression;
	} if(type == "u64") {
		return ent::front::ast::NodeType::u64Expression;
	} if(type == "f32") {
		return ent::front::ast::NodeType::f32Expression;
	} if(type == "f64") {
		return ent::front::ast::NodeType::f64Expression;
	} if(type == "bool") {
		return ent::front::ast::NodeType::booleanExpression;
	} if(type == "char") {
		return ent::front::ast::NodeType::charExpression;
	} if(type == "str") {
		return ent::front::ast::NodeType::strExpression;
	}
	throw (ent::Error(ent::ErrorType::PARSER_EXPECTED_OTHER_ERROR, "Expected valid return type, got " + type)).error();
}

/**
 * Check if a value can be cast to a given type
 * @param source The value to try to cast
 * @param dest The type of the destination
 * @return Whether the cast is valid
 */
bool ent::front::ast::is_valid_cast(
	std::shared_ptr<ent::front::ast::Expression> source,
	enum ent::front::ast::NodeType destType
) {
	// If the source type is an Identifier, get its type
	if(source->get_type() == ent::front::ast::NodeType::identifier) {
		std::shared_ptr<ent::front::ast::Identifier> source_identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(source);
		return ent::front::ast::is_valid_cast(get_sample_expression(source_identifier->get_identifier_type()), destType);
	}
	// If the type is a Binary Expression, get the type of its left member
	if(source->get_type() == ent::front::ast::NodeType::binaryExpression) {
		std::shared_ptr<ent::front::ast::BinaryExpression> source_binary_expression = std::dynamic_pointer_cast<ent::front::ast::BinaryExpression>(source);
		return ent::front::ast::is_valid_cast(source_binary_expression->left, destType);
	}
	// If the type is a Ternary Expression, get the type of its true value
	if(source->get_type() == ent::front::ast::NodeType::ternaryExpression) {
		std::shared_ptr<ent::front::ast::TernaryExpression> source_ternary_expression = std::dynamic_pointer_cast<ent::front::ast::TernaryExpression>(source);
		return ent::front::ast::is_valid_cast(source_ternary_expression->true_value, destType);
	}
	// If the value is a Function Call Expression, get its return type
	if(source->get_type() == ent::front::ast::NodeType::functionCallExpression) {
		std::shared_ptr<ent::front::ast::FunctionCallExpression> source_function_call_expression = std::dynamic_pointer_cast<ent::front::ast::FunctionCallExpression>(source);
		std::shared_ptr<ent::front::ast::FunctionDeclaration> function_declaration = ent::front::ast::get_function(source_function_call_expression->functionIdentifier);
		if(function_declaration == nullptr) {
			throw (ent::Error(ent::ErrorType::AST_CALLING_UNDECLARED_FUNCTION_ERROR, "Trying to call undeclared function " + source_function_call_expression->functionIdentifier->name)).error();
		}
		return ent::front::ast::is_valid_cast(ent::front::ast::get_sample_expression(ent::front::ast::get_node_type(function_declaration->returnType)), destType);
	}
	// If they are the same type, return true
	if(source->get_type() == destType) { return true; }
	// Else, check for valid casts
	for(enum ent::front::ast::NodeType dest_valid_cast : ent::front::ast::valid_casts_to_type(destType)) {
		if(ent::front::ast::is_valid_cast(source, dest_valid_cast)) {
			return true;
		}
	}
	return false;
}

enum ent::front::ast::ClassAccessSpecifier ent::front::ast::invertAccessSpecifier(enum ent::front::ast::ClassAccessSpecifier accessSpecifier) {
	return static_cast<enum ent::front::ast::ClassAccessSpecifier>(ent::front::ast::ClassAccessSpecifier::PUBLIC - accessSpecifier);
}

std::string ent::front::ast::accessLevelString(enum ent::front::ast::ClassAccessSpecifier accessSpecifier) {
	switch(accessSpecifier) {
		case ent::front::ast::ClassAccessSpecifier::PRIVATE:
			return "@private";
		default:
			return "@public";
	}
}

#pragma endregion

#pragma region Statement

enum ent::front::ast::NodeType ent::front::ast::Statement::get_type() {
	return NodeType::program;
}
std::string ent::front::ast::Statement::repr(int indent) {
	return std::string(indent, '\t') + "Statement";
}
std::string ent::front::ast::Statement::type_id() {
	return "Statement";
}

#pragma endregion

#pragma region Scope

ent::front::ast::Scope::Scope(std::vector<std::shared_ptr<Statement>> body) {
	this->body = body;
}
enum ent::front::ast::NodeType ent::front::ast::Scope::get_type() {
	return NodeType::scope;
}
std::string ent::front::ast::Scope::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "{\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::Scope::type_id() {
	return "Scope";
}

#pragma endregion

#pragma region Identifier

ent::front::ast::Identifier::Identifier(std::string name) {
	this->name = name;
}
enum ent::front::ast::NodeType ent::front::ast::Identifier::get_type() {
	return NodeType::identifier;
}
enum ent::front::ast::NodeType ent::front::ast::Identifier::get_identifier_type() {
	return this->identifierType;
}
void ent::front::ast::Identifier::set_identifier_type(enum NodeType type) {
	this->identifierType = type;
}
std::string ent::front::ast::Identifier::repr(int indent) {
	return std::string(indent, '\t') + "Identifier(" + this->name + ")";
}
std::string ent::front::ast::Identifier::type_id() {
	return "Identifier";
}

#pragma endregion

#pragma region I8Expression

ent::front::ast::I8Expression::I8Expression(i8 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::I8Expression::get_type() {
	return ent::front::ast::NodeType::i8Expression;
}
std::string ent::front::ast::I8Expression::repr(int indent) {
	return std::string(indent, '\t') + "I8Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::I8Expression::type_id() {
	return "I8Expression";
}

#pragma endregion

#pragma region I16Expression

ent::front::ast::I16Expression::I16Expression(i16 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::I16Expression::get_type() {
	return ent::front::ast::NodeType::i16Expression;
}
std::string ent::front::ast::I16Expression::repr(int indent) {
	return std::string(indent, '\t') + "I16Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::I16Expression::type_id() {
	return "I16Expression";
}

#pragma endregion

#pragma region I32Expression

ent::front::ast::I32Expression::I32Expression(i32 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::I32Expression::get_type() {
	return ent::front::ast::NodeType::i32Expression;
}
std::string ent::front::ast::I32Expression::repr(int indent) {
	return std::string(indent, '\t') + "I32Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::I32Expression::type_id() {
	return "I32Expression";
}

#pragma endregion

#pragma region I64Expression

ent::front::ast::I64Expression::I64Expression(i64 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::I64Expression::get_type() {
	return ent::front::ast::NodeType::i64Expression;
}
std::string ent::front::ast::I64Expression::repr(int indent) {
	return std::string(indent, '\t') + "I64Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::I64Expression::type_id() {
	return "I64Expression";
}

#pragma endregion

#pragma region U8Expression

ent::front::ast::U8Expression::U8Expression(u8 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::U8Expression::get_type() {
	return ent::front::ast::NodeType::u8Expression;
}
std::string ent::front::ast::U8Expression::repr(int indent) {
	return std::string(indent, '\t') + "U8Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::U8Expression::type_id() {
	return "U8Expression";
}

#pragma endregion

#pragma region U16Expression

ent::front::ast::U16Expression::U16Expression(u16 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::U16Expression::get_type() {
	return ent::front::ast::NodeType::u16Expression;
}
std::string ent::front::ast::U16Expression::repr(int indent) {
	return std::string(indent, '\t') + "U16Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::U16Expression::type_id() {
	return "U16Expression";
}

#pragma endregion

#pragma region U32Expression

ent::front::ast::U32Expression::U32Expression(u32 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::U32Expression::get_type() {
	return ent::front::ast::NodeType::u32Expression;
}
std::string ent::front::ast::U32Expression::repr(int indent) {
	return std::string(indent, '\t') + "U32Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::U32Expression::type_id() {
	return "U32Expression";
}

#pragma endregion

#pragma region U64Expression

ent::front::ast::U64Expression::U64Expression(u64 value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::U64Expression::get_type() {
	return ent::front::ast::NodeType::u64Expression;
}
std::string ent::front::ast::U64Expression::repr(int indent) {
	return std::string(indent, '\t') + "U64Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::U64Expression::type_id() {
	return "U64Expression";
}

#pragma endregion

#pragma region F32Expression

ent::front::ast::F32Expression::F32Expression(float value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::F32Expression::get_type() {
	return ent::front::ast::NodeType::f32Expression;
}
std::string ent::front::ast::F32Expression::repr(int indent) {
	return std::string(indent, '\t') + "F32Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::F32Expression::type_id() {
	return "F32Expression";
}

#pragma endregion

#pragma region F64Expression

ent::front::ast::F64Expression::F64Expression(double value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::F64Expression::get_type() {
	return ent::front::ast::NodeType::f64Expression;
}
std::string ent::front::ast::F64Expression::repr(int indent) {
	return std::string(indent, '\t') + "F64Expression(" + std::to_string(this->value) + ")";
}
std::string ent::front::ast::F64Expression::type_id() {
	return "F64Expression";
}

#pragma endregion

#pragma region BooleanExpression

ent::front::ast::BooleanExpression::BooleanExpression(bool value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::BooleanExpression::get_type() {
	return ent::front::ast::NodeType::booleanExpression;
}
std::string ent::front::ast::BooleanExpression::repr(int indent) {
	return std::string(indent, '\t') + "BooleanExpression(" + (this->value ? "true" : "false") + ")";
}
std::string ent::front::ast::BooleanExpression::type_id() {
	return "BooleanExpression";
}

#pragma endregion

#pragma region CharExpression

std::string ent::front::ast::CharExpression::format_char(char c) {
	// Try to parse escaped character
	try {
		return std::unordered_map<char, std::string>({
			{'\a', "\\a"},
			{'\b', "\\b"},
			{'\f', "\\f"},
			{'\n', "\\n"},
			{'\r', "\\r"},
			{'\t', "\\t"},
			{'\v', "\\v"},
			{'\\', "\\\\"},
			{'\'', "\\'"},
			{'\"', "\\\""},
			{'\?', "\\?"},
			{'\0', "\\0"}
		}).at(this->value);
	} catch(const std::exception& e) {
		// Return normal character
		return std::string(1, c);
	}
}

ent::front::ast::CharExpression::CharExpression(char value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::CharExpression::get_type() {
	return ent::front::ast::NodeType::charExpression;
}
std::string ent::front::ast::CharExpression::repr(int indent) {
	return std::string(indent, '\t') + "CharExpression('" + this->format_char(this->value) + "')";
}
std::string ent::front::ast::CharExpression::type_id() {
	return "CharExpression";
}

#pragma endregion

#pragma region StrExpression

ent::front::ast::StrExpression::StrExpression(std::string value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::StrExpression::get_type() {
	return ent::front::ast::NodeType::strExpression;
}
std::string ent::front::ast::StrExpression::repr(int indent) {
	return std::string(indent, '\t') + "StrExpression(\"" + this->value + "\")";
}
std::string ent::front::ast::StrExpression::type_id() {
	return "StrExpression";
}

#pragma endregion

#pragma region ParenthesisExpression

ent::front::ast::ParenthesisExpression::ParenthesisExpression(std::shared_ptr<Expression> content) {
	this->content = content;
}
enum ent::front::ast::NodeType ent::front::ast::ParenthesisExpression::get_type() {
	return ent::front::ast::NodeType::parenthesisExpression;
}
std::string ent::front::ast::ParenthesisExpression::repr(int indent) {
	return std::string(indent, '\t') + "ParenthesisExpression(\n" + this->content->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
}
std::string ent::front::ast::ParenthesisExpression::type_id() {
	return "ParenthesisExpression";
}

#pragma endregion

#pragma region BinaryExpression

ent::front::ast::BinaryExpression::BinaryExpression(
	std::shared_ptr<Expression> left,
	std::string operator_symbol,
	std::shared_ptr<Expression> right
) {
	this->left = left;
	this->operator_symbol = operator_symbol;
	this->right = right;
	// Determine the return type of the Binary Expression
	this->returnType = ent::front::ast::get_operator_return_type(this->left, this->operator_symbol);
}
enum ent::front::ast::NodeType ent::front::ast::BinaryExpression::get_type() {
	return ent::front::ast::NodeType::binaryExpression;
}
enum ent::front::ast::NodeType ent::front::ast::BinaryExpression::get_return_type() {
	return this->returnType;
}
std::string ent::front::ast::BinaryExpression::repr(int indent) {
	return std::string(indent, '\t') + "BinaryExpression(\n" +
		this->left->repr(indent + 1) + "\n" +
		std::string(indent + 1, '\t') + this->operator_symbol + "\n" +
		this->right->repr(indent + 1) + "\n" +
		std::string(indent, '\t') + ")";
}
std::string ent::front::ast::BinaryExpression::type_id() {
	return "BinaryExpression";
}

#pragma endregion

#pragma region UnaryExpression

ent::front::ast::UnaryExpression::UnaryExpression(std::shared_ptr<Expression> term, std::string operator_symbol) {
	this->term = term;
	this->operator_symbol = operator_symbol;
	this->returnType = ent::front::ast::get_operator_return_type(this->term, this->operator_symbol);
}
enum ent::front::ast::NodeType ent::front::ast::UnaryExpression::get_type() {
	return ent::front::ast::NodeType::unaryExpression;
}
enum ent::front::ast::NodeType ent::front::ast::UnaryExpression::get_return_type() {
	return this->returnType;
}
std::string ent::front::ast::UnaryExpression::repr(int indent) {
	return std::string(indent, '\t') + "UnaryExpression(\n" + std::string(indent + 1, '\t') + this->operator_symbol + "\n" + this->term->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
}
std::string ent::front::ast::UnaryExpression::type_id() {
	return "UnaryExpression";
}

#pragma endregion

#pragma region TernaryExpression

ent::front::ast::TernaryExpression::TernaryExpression(
	std::shared_ptr<Expression> condition,
	std::shared_ptr<Expression> true_value,
	std::shared_ptr<Expression> false_value
) {
	this->condition = condition;
	this->true_value = true_value;
	this->false_value = false_value;
	this->returnType = this->true_value->get_type();
}
enum ent::front::ast::NodeType ent::front::ast::TernaryExpression::get_type() {
	return ent::front::ast::NodeType::ternaryExpression;
}
enum ent::front::ast::NodeType ent::front::ast::TernaryExpression::get_return_type() {
	return this->returnType;
}
std::string ent::front::ast::TernaryExpression::repr(int indent) {
	return (
		this->condition->repr(indent + 1) + "\n" + std::string(indent + 1, '\t') + "?\n" +
		this->true_value->repr(indent + 1) + "\n" + std::string(indent + 1, '\t') + ":\n" +
		this->false_value->repr(indent + 1)
	);
}
std::string ent::front::ast::TernaryExpression::type_id() {
	return "TernaryExpression";
}

#pragma endregion

#pragma region FunctionCallExpression

ent::front::ast::FunctionCallExpression::FunctionCallExpression(
	std::shared_ptr<ent::front::ast::Identifier> functionIdentifier,
	std::vector<std::shared_ptr<ent::front::ast::Expression>> arguments
) {
	this->functionIdentifier = functionIdentifier;
	this->arguments = arguments;
}
enum ent::front::ast::NodeType ent::front::ast::FunctionCallExpression::get_type() {
	return ent::front::ast::NodeType::functionCallExpression;
}
std::string ent::front::ast::FunctionCallExpression::repr(int indent) {
	bool has_args = this->arguments.size() > 0;
	std::string pretty = std::string(indent, '\t') + this->functionIdentifier->name + "(" + (has_args ? "\n" : "void");
	for(u64 i = 0; i < this->arguments.size(); i++) {
		pretty += this->arguments[i]->repr(indent + 1) + "\n";
	}
	pretty += (has_args ? std::string(indent, '\t') : "") + ");";
	return pretty;
}
std::string ent::front::ast::FunctionCallExpression::type_id() {
	return "FunctionCallExpression";
}

#pragma endregion

#pragma region AssignationExpression

ent::front::ast::AssignationExpression::AssignationExpression(
	std::shared_ptr<Identifier> identifier,
	std::shared_ptr<Expression> value
) {
	this->identifier = identifier;
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::AssignationExpression::get_type() {
	return ent::front::ast::NodeType::assignationExpression;
}
std::string ent::front::ast::AssignationExpression::repr(int indent) {
	return std::string(indent, '\t') + "AssignationExpression(\n" + std::string(indent + 1, '\t') + this->identifier->name + ",\n" + this->value->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
}
std::string ent::front::ast::AssignationExpression::type_id() {
	return "AssignationExpression";
}

#pragma endregion

#pragma region Declaration

ent::front::ast::Declaration::Declaration(
	std::shared_ptr<ent::front::ast::Identifier> identifier,
	std::shared_ptr<Expression> value,
	bool isMutable,
	bool isInFunctionSetup
) {
	this->identifier = identifier;
	this->isMutable = isMutable;
	this->value = value;
	this->isInFunctionSetup = isInFunctionSetup;
}
ent::front::ast::Declaration::Declaration(
	std::shared_ptr<ent::front::ast::AssignationExpression> assignationExpression,
	bool isMutable
) {
	this->identifier = assignationExpression->identifier;
	this->value = assignationExpression->value;
	this->isMutable = isMutable;
}
enum ent::front::ast::NodeType ent::front::ast::Declaration::get_type() {
	return ent::front::ast::NodeType::declaration;
}
std::string ent::front::ast::Declaration::repr(int indent) {
	return std::string(indent, '\t') + "Declaration\n" + std::string(indent + 1, '\t') + std::string(this->isMutable ? "mut " : "const ") + this->identifier->name + ",\n" + this->value->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")";
}
std::string ent::front::ast::Declaration::type_id() {
	return "Declaration";
}

#pragma endregion

#pragma region FunctionDeclaration

ent::front::ast::FunctionDeclaration::FunctionDeclaration(
	std::shared_ptr<ent::front::ast::Identifier> identifier,
	std::string returnType,
	std::vector<std::shared_ptr<ent::front::ast::Declaration>> arguments,
	std::vector<std::shared_ptr<ent::front::ast::Statement>> body
) : Scope(body) {
	this->identifier = identifier;
	this->returnType = returnType;
	this->arguments = arguments;
}

enum ent::front::ast::NodeType ent::front::ast::FunctionDeclaration::get_type() {
	return ent::front::ast::NodeType::functionDeclaration;
}
std::string ent::front::ast::FunctionDeclaration::repr(int indent) {
	bool has_args = this->arguments.size() > 0;
	std::string pretty = std::string(indent, '\t') + "fn " + this->identifier->name + "(" + (has_args ? "\n" : "void");
	for(u64 i = 0; i < this->arguments.size(); i++) {
		pretty += this->arguments[i]->repr(indent + 1) + "\n";
	}
	pretty += (has_args ? std::string(indent, '\t') : "") + "): " + returnType + " {\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::FunctionDeclaration::type_id() {
	return "FunctionDeclaration";
}

#pragma endregion

#pragma region FunctionReturn

ent::front::ast::FunctionReturn::FunctionReturn(std::shared_ptr<Expression> value) {
	this->value = value;
}
enum ent::front::ast::NodeType ent::front::ast::FunctionReturn::get_type() {
	return ent::front::ast::NodeType::functionReturn;
}
std::string ent::front::ast::FunctionReturn::repr(int indent) {
	return std::string(indent, '\t') + "return " + this->value->repr();
}
std::string ent::front::ast::FunctionReturn::type_id() {
	return "FunctionReturn";
}

#pragma endregion

#pragma region Program

ent::front::ast::Program::Program(std::vector<std::shared_ptr<Statement>> body) : Scope(body) {}
enum ent::front::ast::NodeType ent::front::ast::Program::get_type() {
	return ent::front::ast::NodeType::program;
}
std::string ent::front::ast::Program::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "Program(\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + ")";
	return pretty;
}
std::string ent::front::ast::Program::type_id() {
	return "Program";
}

#pragma endregion

#pragma region ConditionnalBlock

ent::front::ast::ConditionnalBlock::ConditionnalBlock(
	std::vector<std::shared_ptr<ent::front::ast::Statement>> body,
	std::shared_ptr<ent::front::ast::Expression> condition,
	bool isMatch,
	std::shared_ptr<ent::front::ast::ConditionnalBlock> before
) : Scope(body) {
	this->condition = condition;
	this->before = before;
	this->isMatch = isMatch;
}
enum ent::front::ast::NodeType ent::front::ast::ConditionnalBlock::get_type() {
	return ent::front::ast::NodeType::conditionnalBlock;
}
std::string ent::front::ast::ConditionnalBlock::repr(int indent) {
	if(this->isMatch) {
		return match_case_repr(indent);
	}
	return if_else_repr(indent);
}
std::string ent::front::ast::ConditionnalBlock::type_id() {
	return "ConditionnalBlock";
}

std::string ent::front::ast::ConditionnalBlock::if_else_repr(int indent) {
	std::string pretty = std::string(indent, '\t');
	pretty += condition == nullptr ? "else" : 
		(
			(this->before != nullptr ? "else " : "") + std::string("if(\n" + this->condition->repr(indent + 1) + "\n" + std::string(indent, '\t') + ")")
		);
	pretty += " {\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::ConditionnalBlock::match_case_repr(int indent) {
	std::string pretty = std::string(indent, '\t');
	if(this->condition == nullptr) {
		pretty += "default";
	} else {
		pretty += "(\n" + this->condition->repr(indent + 1);
		pretty += "\n" + std::string(indent, '\t') + ")";
	}
	pretty += " => {\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}

#pragma endregion

#pragma region ConditionnalStructure

ent::front::ast::ConditionnalStructure::ConditionnalStructure(std::vector<std::shared_ptr<ent::front::ast::ConditionnalBlock>> conditionnalBlocks) {
	this->conditionnalBlocks = conditionnalBlocks;
}
enum ent::front::ast::NodeType ent::front::ast::ConditionnalStructure::get_type() {
	return ent::front::ast::NodeType::conditionnalStructure;
}
std::string ent::front::ast::ConditionnalStructure::repr(int indent) {
	std::string pretty = "";
	for(std::shared_ptr<ent::front::ast::ConditionnalBlock> block : this->conditionnalBlocks) {
		pretty += block->repr(indent + 1) + "\n";
	}
	return pretty;
}
std::string ent::front::ast::ConditionnalStructure::type_id() {
	return "ConditionnalStructure";
}

#pragma endregion

#pragma region MatchStructure


ent::front::ast::MatchStructure::MatchStructure(
	std::shared_ptr<ent::front::ast::Expression> matchExpression,
	std::vector<std::shared_ptr<ConditionnalBlock>> casesBlocks
) {
	this->matchExpression = matchExpression;
	this->casesBlocks = casesBlocks;
}
enum ent::front::ast::NodeType ent::front::ast::MatchStructure::get_type() {
	return ent::front::ast::NodeType::matchStructure;
}
std::string ent::front::ast::MatchStructure::repr(int indent) {
	std::string pretty = "match(\n";
	pretty += matchExpression->repr(indent + 1);
	pretty += "\n" + std::string(indent, '\t') + ") {\n";
	for(std::shared_ptr<ent::front::ast::ConditionnalBlock> block : this->casesBlocks) {
		pretty += block->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::MatchStructure::type_id() {
	return "MatchStructure";
}

#pragma endregion

#pragma region BreakStatement

ent::front::ast::BreakStatement::BreakStatement() {}
	
enum ent::front::ast::NodeType ent::front::ast::BreakStatement::get_type() {
	return ent::front::ast::NodeType::breakStatement;
}
std::string ent::front::ast::BreakStatement::repr(int indent) {
	return std::string(indent, '\t') + "break;";
}
std::string ent::front::ast::BreakStatement::type_id() {
	return "BreakStatement";
}

#pragma endregion

#pragma region Loop

ent::front::ast::Loop::Loop(
	std::shared_ptr<Expression> loopCondition,
	std::vector<std::shared_ptr<Statement>> body
) : Scope(body) {
	this->loopCondition = loopCondition;
}

#pragma endregion

#pragma region ForLoop

ent::front::ast::ForLoop::ForLoop(
	std::shared_ptr<Statement> initStatement,
	std::shared_ptr<Expression> loopCondition,
	std::shared_ptr<Statement> iterationStatement,
	std::vector<std::shared_ptr<Statement>> body
): Loop(loopCondition, body) {
	this->initStatement = initStatement;
	this->iterationStatement = iterationStatement;
}
enum ent::front::ast::NodeType ent::front::ast::ForLoop::get_type() {
	return ent::front::ast::NodeType::forLoop;
}
std::string ent::front::ast::ForLoop::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "for(\n";
	pretty += this->initStatement->repr(indent + 1) + ";\n";
	pretty += this->loopCondition->repr(indent + 1) + ";\n";
	pretty += this->iterationStatement->repr(indent + 1) + "\n";
	pretty += std::string(indent, '\t') + ") {\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::ForLoop::type_id() {
	return "ForLoop";
}

#pragma endregion

#pragma region WhileLoop

ent::front::ast::WhileLoop::WhileLoop(std::shared_ptr<Expression> loopCondition, std::vector<std::shared_ptr<Statement>> body): Loop(loopCondition, body) {}
enum ent::front::ast::NodeType ent::front::ast::WhileLoop::get_type() {
	return ent::front::ast::NodeType::whileLoop;
}
std::string ent::front::ast::WhileLoop::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "while(\n";
	pretty += this->loopCondition->repr(indent + 1) + ";\n";
	pretty += std::string(indent, '\t') + ") {\n";
	for(u64 i = 0; i < this->body.size(); i++) {
		pretty += this->body[i]->repr(indent + 1) + "\n";
	}
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::WhileLoop::type_id() {
	return "WhileLoop";
}

#pragma endregion

/**
 * Type Declaration < Statement
 */
#pragma region TypeDeclaration

ent::front::ast::TypeDeclaration::TypeDeclaration(std::string typeName, std::vector<TypeMember> members) {
	this->typeName = typeName;
	this->members = members;
}
ent::front::ast::NodeType ent::front::ast::TypeDeclaration::get_type() {
	return ent::front::ast::NodeType::typeDeclaration;
}
std::string ent::front::ast::TypeDeclaration::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "type " + this->typeName + " {\n";

	enum ent::front::ast::ClassAccessSpecifier prev_access = this->members.size() > 0 ?
		ent::front::ast::invertAccessSpecifier(this->members[0].accessLevel) :
		ent::front::ast::ClassAccessSpecifier::PRIVATE;

	for(ent::front::ast::TypeMember member : this->members) {
		if(member.accessLevel != prev_access) {
			pretty += std::string(indent, '\t') + ent::front::ast::accessLevelString(member.accessLevel) + "\n";
		}
		pretty += member.member->repr(indent + 1) + "\n";
		prev_access = member.accessLevel;
	}
	
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::TypeDeclaration::type_id() {
	return "TypeDeclaration";
}

#pragma endregion

#pragma region TypeImplementation

ent::front::ast::TypeImplementation::TypeImplementation(std::string typeName, std::vector<ImplMethod> methods) {
	this->typeName = typeName;
	this->methods = methods;
}
ent::front::ast::NodeType ent::front::ast::TypeImplementation::get_type() {
	return ent::front::ast::NodeType::typeImplementation;
}
std::string ent::front::ast::TypeImplementation::repr(int indent) {
	std::string pretty = std::string(indent, '\t') + "impl" + this->typeName + " {\n";
	enum ent::front::ast::ClassAccessSpecifier prev_access = this->methods.size() > 0 ?
		ent::front::ast::invertAccessSpecifier(this->methods[0].accessLevel) :
		ent::front::ast::ClassAccessSpecifier::PRIVATE;
	
	for(ent::front::ast::ImplMethod method : this->methods) {
		if(method.accessLevel != prev_access) {
			pretty += std::string(indent, '\t') + ent::front::ast::accessLevelString(method.accessLevel) + "\n";
		}
		pretty += method.method->repr(indent + 1) + "\n";
		prev_access = method.accessLevel;
	}
	
	pretty += std::string(indent, '\t') + "}";
	return pretty;
}
std::string ent::front::ast::TypeImplementation::type_id() {
	return "TypeImplementation";
}

#pragma endregion