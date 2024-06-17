#include <AquIce/Entropia/values.hpp>

bool ent::runtime::IsSignedIntegerType(ent::runtime::ValueType type) {
	return type == ent::runtime::ValueType::I8 || type == ent::runtime::ValueType::I16 || type == ent::runtime::ValueType::I32 || type == ent::runtime::ValueType::I64 ;
}

bool ent::runtime::IsIntegerType(ent::runtime::ValueType type) {
	return
		ent::runtime::IsSignedIntegerType(type) ||
		type == ent::runtime::ValueType::U8 || type == ent::runtime::ValueType::U16 || type == ent::runtime::ValueType::U32 || type == ent::runtime::ValueType::U64;
}

bool ent::runtime::IsFloatType(ent::runtime::ValueType type) {
	return type == ent::runtime::ValueType::F32 || type == ent::runtime::ValueType::F64;
}

bool ent::runtime::IsNumericType(ent::runtime::ValueType type) {
	return
		ent::runtime::IsIntegerType(type) ||
		ent::runtime::IsFloatType(type);
}

ent::runtime::ValueType ent::runtime::RuntimeValue::type() {
	return ent::runtime::ValueType::NULL_VAL;
};
std::string ent::runtime::RuntimeValue::repr() {
	return "RuntimeValue";
}
bool ent::runtime::RuntimeValue::IsTrue() {
	return false;
}

ent::runtime::NullValue::NullValue(bool visible) {
	this->visible = visible;
}
ent::runtime::ValueType ent::runtime::NullValue::type() {
	return ent::runtime::ValueType::NULL_VAL;
}
std::string ent::runtime::NullValue::repr() {
	return this->visible ? "null" : "";
}
bool ent::runtime::NullValue::IsTrue() {
	return false;
}

int ent::runtime::NumberValue::magnitude() {
	return -1;
}

ent::runtime::I8Value::I8Value(i8 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::I8Value::type() {
	return ent::runtime::ValueType::I8;
}
i8 ent::runtime::I8Value::get_value() {
	return this->value;
}
int ent::runtime::I8Value::magnitude() {
	return 7;
}
std::string ent::runtime::I8Value::repr() {
	return std::to_string(this->value) + ": i8";
}
bool ent::runtime::I8Value::IsTrue() {
	return value != 0;
}

ent::runtime::I16Value::I16Value(i16 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::I16Value::type() {
	return ent::runtime::ValueType::I16;
}
i16 ent::runtime::I16Value::get_value() {
	return this->value;
}
int ent::runtime::I16Value::magnitude() {
	return 15;
}
std::string ent::runtime::I16Value::repr() {
	return std::to_string(this->value) + ": i16";
}
bool ent::runtime::I16Value::IsTrue() {
	return value != 0;
}

ent::runtime::I32Value::I32Value(i32 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::I32Value::type() {
	return ent::runtime::ValueType::I32;
}
i32 ent::runtime::I32Value::get_value() {
	return this->value;
}
int ent::runtime::I32Value::magnitude() {
	return 31;
}
std::string ent::runtime::I32Value::repr() {
	return std::to_string(this->value) + ": i32";
}
bool ent::runtime::I32Value::IsTrue() {
	return value != 0;
}

ent::runtime::I64Value::I64Value(i64 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::I64Value::type() {
	return ent::runtime::ValueType::I64;
}
i64 ent::runtime::I64Value::get_value() {
	return this->value;
}
int ent::runtime::I64Value::magnitude() {
	return 63;
}
std::string ent::runtime::I64Value::repr() {
	return std::to_string(this->value) + ": i64";
}
bool ent::runtime::I64Value::IsTrue() {
	return value != 0;
}

ent::runtime::U8Value::U8Value(u8 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::U8Value::type() {
	return ent::runtime::ValueType::U8;
}
u8 ent::runtime::U8Value::get_value() {
	return this->value;
}
int ent::runtime::U8Value::magnitude() {
	return 8;
}
std::string ent::runtime::U8Value::repr() {
	return std::to_string(this->value) + ": u8";
}
bool ent::runtime::U8Value::IsTrue() {
	return value != 0;
}

ent::runtime::U16Value::U16Value(u16 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::U16Value::type() {
	return ent::runtime::ValueType::U16;
}
u16 ent::runtime::U16Value::get_value() {
	return this->value;
}
int ent::runtime::U16Value::magnitude() {
	return 16;
}
std::string ent::runtime::U16Value::repr() {
	return std::to_string(this->value) + ": u16";
}
bool ent::runtime::U16Value::IsTrue() {
	return value != 0;
}

ent::runtime::U32Value::U32Value(u32 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::U32Value::type() {
	return ent::runtime::ValueType::U32;
}
u32 ent::runtime::U32Value::get_value() {
	return this->value;
}
int ent::runtime::U32Value::magnitude() {
	return 32;
}
std::string ent::runtime::U32Value::repr() {
	return std::to_string(this->value) + ": u32";
}
bool ent::runtime::U32Value::IsTrue() {
	return value != 0;
}

ent::runtime::U64Value::U64Value(u64 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::U64Value::type() {
	return ent::runtime::ValueType::U64;
}
u64 ent::runtime::U64Value::get_value() {
	return this->value;
}
int ent::runtime::U64Value::magnitude() {
	return 64;
}
std::string ent::runtime::U64Value::repr() {
	return std::to_string(this->value) + ": u64";
}
bool ent::runtime::U64Value::IsTrue() {
	return value != 0;
}

ent::runtime::F32Value::F32Value(f32 value) {
	this->value = value;
}

ent::runtime::ValueType ent::runtime::F32Value::type() {
	return ent::runtime::ValueType::F32;
}
float ent::runtime::F32Value::get_value() {
	return this->value;
}
std::string ent::runtime::F32Value::repr() {
	return std::to_string(this->value) + ": f32";
}
bool ent::runtime::F32Value::IsTrue() {
	return value != 0;
}

ent::runtime::F64Value::F64Value(f64 value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::F64Value::type() {
	return ent::runtime::ValueType::F64;
}
double ent::runtime::F64Value::get_value() {
	return this->value;
}
std::string ent::runtime::F64Value::repr() {
	return std::to_string(this->value) + ": f64";
}
bool ent::runtime::F64Value::IsTrue() {
	return value != 0;
}

ent::runtime::BooleanValue::BooleanValue(bool value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::BooleanValue::type() {
	return ent::runtime::ValueType::BOOL;
}
bool ent::runtime::BooleanValue::get_value() {
	return this->value;
}
std::string ent::runtime::BooleanValue::repr() {
	return this->value ? "true" : "false";
}
bool ent::runtime::BooleanValue::IsTrue() {
	return value;
}

ent::runtime::CharValue::CharValue(char value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::CharValue::type() {
	return ent::runtime::ValueType::CHAR;
}
char ent::runtime::CharValue::get_value() {
	return this->value;
}
std::string ent::runtime::CharValue::repr() {
	return std::string(1, this->value);
}
bool ent::runtime::CharValue::IsTrue() {
	return value != '\0';
}

ent::runtime::StrValue::StrValue(std::string value) {
	this->value = value;
}
ent::runtime::ValueType ent::runtime::StrValue::type() {
	return ent::runtime::ValueType::STR;
}
std::string ent::runtime::StrValue::get_value() {
	return this->value;
}
std::string ent::runtime::StrValue::repr() {
	return this->value;
}
bool ent::runtime::StrValue::IsTrue() {
	return value.size() > 0;
}