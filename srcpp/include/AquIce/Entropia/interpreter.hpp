#ifndef __ENT_RUNTIME_INTERPRETER__
#define __ENT_RUNTIME_INTERPRETER__

#include <iostream>
#include <limits>
#include <cmath>

#include "ast.hpp"
#include "env.hpp"
#include "errors.hpp"

#define evaluateSameIntegerNumberExpression(return_T, function_name, T, max, min, overflow_error, underflow_error) \
return_T function_name(T* left, T* right, std::string op) { \
	if(op == "+") { \
		return cast_to_min_type(left->get_value() + right->get_value()); \
	} if(op == "-") { \
		return cast_to_min_type(left->get_value() - right->get_value()); \
	} if(op == "*") { \
		return cast_to_min_type(left->get_value() * right->get_value()); \
	} if(op == "/") { \
		if(right->get_value() == 0) \
			throw (ent::Error(ent::ErrorType::INTERPRETER_DIVISION_BY_ZERO_ERROR, "Division by zero")).error(); \
		return cast_to_min_type(left->get_value() / right->get_value()); \
	} if(op == "%") { \
		if(right->get_value() == 0) \
			throw (ent::Error(ent::ErrorType::INTERPRETER_DIVISION_BY_ZERO_ERROR, "Division by zero")).error(); \
		return cast_to_min_type(left->get_value() % right->get_value()); \
	} if(op == "==") { \
		return new BooleanValue(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return new BooleanValue(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return new BooleanValue(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return new BooleanValue(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return new BooleanValue(left->get_value() < right->get_value()); \
	} if(op == ">") { \
		return new BooleanValue(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return new BooleanValue(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return new BooleanValue(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return new BooleanValue( \
			(left->IsTrue() || right->IsTrue()) && \
			!(left->IsTrue() && right->IsTrue()) \
		); \
	} if(op == "<<") { \
		return cast_to_min_type(left->get_value() << right->get_value()); \
	} if(op == ">>") { \
		return cast_to_min_type(left->get_value() >> right->get_value()); \
	} if(op == "&") { \
		return cast_to_min_type(left->get_value() & right->get_value()); \
	} if(op == "|") { \
		return cast_to_min_type(left->get_value() | right->get_value()); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpression(return_T, function_name, big_T, little_T, max, min, overflow_error, underflow_error) \
return_T function_name(big_T* left, little_T* right, std::string op) { \
	if(op == "+") { \
		return cast_to_min_type(left->get_value() + right->get_value()); \
	} if(op == "-") { \
		return cast_to_min_type(left->get_value() - right->get_value()); \
	} if(op == "*") { \
		return cast_to_min_type(left->get_value() * right->get_value()); \
	} if(op == "/") { \
		if(right->get_value() == 0) \
			throw (ent::Error(ent::ErrorType::INTERPRETER_DIVISION_BY_ZERO_ERROR, "Division by zero")).error(); \
		return cast_to_min_type(left->get_value() / right->get_value()); \
	} if(op == "==") { \
		return new BooleanValue(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return new BooleanValue(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return new BooleanValue(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return new BooleanValue(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return new BooleanValue(left->get_value() < right->get_value()); \
	} if(op == ">") { \
		return new BooleanValue(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return new BooleanValue(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return new BooleanValue(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return new BooleanValue( \
			(left->IsTrue() || right->IsTrue()) && \
			!(left->IsTrue() && right->IsTrue()) \
		); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpressionReverse(return_T, function_name, big_T, little_T, max, min, overflow_error, underflow_error) \
return_T function_name(little_T* left, big_T* right, std::string op) { \
	if(op == "+") { \
		return cast_to_min_type(left->get_value() + right->get_value()); \
	} if(op == "-") { \
		return cast_to_min_type(left->get_value() - right->get_value()); \
	} if(op == "*") { \
		return cast_to_min_type(left->get_value() * right->get_value()); \
	} if(op == "/") { \
		if(right->get_value() == 0) \
			throw (ent::Error(ent::ErrorType::INTERPRETER_DIVISION_BY_ZERO_ERROR, "Division by zero")).error(); \
		return cast_to_min_type(left->get_value() / right->get_value()); \
	} if(op == "==") { \
		return new BooleanValue(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return new BooleanValue(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return new BooleanValue(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return new BooleanValue(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return new BooleanValue(left->get_value() < right->get_value()); \
	} if(op == ">") { \
		return new BooleanValue(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return new BooleanValue(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return new BooleanValue(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return new BooleanValue( \
			(left->IsTrue() || right->IsTrue()) && \
			!(left->IsTrue() && right->IsTrue()) \
		); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpressionBoth(return_T, function_name_first, function_name_second, big_T, little_T, max, min, overflow_error, underflow_error) \
evaluateNumberExpression(return_T, function_name_first, big_T, little_T, max, min, overflow_error, underflow_error) \
evaluateNumberExpressionReverse(return_T, function_name_second, big_T, little_T, max, min, overflow_error, underflow_error)

namespace ent {
	namespace runtime {
		namespace interpreter {
			RuntimeValue* evaluateIdentifier(ent::front::ast::Identifier* identifier, Environment* env) {
				return env->get_value(identifier->name);
			}

			RuntimeValue* evaluateI8Expression(ent::front::ast::I8Expression* numericExpression) {
				return new I8Value(numericExpression->value);
			}
			RuntimeValue* evaluateI16Expression(ent::front::ast::I16Expression* numericExpression) {
				return new I16Value(numericExpression->value);
			}
			RuntimeValue* evaluateI32Expression(ent::front::ast::I32Expression* numericExpression) {
				return new I32Value(numericExpression->value);
			}
			RuntimeValue* evaluateI64Expression(ent::front::ast::I64Expression* numericExpression) {
				return new I64Value(numericExpression->value);
			}
			
			RuntimeValue* evaluateU8Expression(ent::front::ast::U8Expression* numericExpression) {
				return new U8Value(numericExpression->value);
			}
			RuntimeValue* evaluateU16Expression(ent::front::ast::U16Expression* numericExpression) {
				return new U16Value(numericExpression->value);
			}
			RuntimeValue* evaluateU32Expression(ent::front::ast::U32Expression* numericExpression) {
				return new U32Value(numericExpression->value);
			}
			RuntimeValue* evaluateU64Expression(ent::front::ast::U64Expression* numericExpression) {
				return new U64Value(numericExpression->value);
			}

			RuntimeValue* evaluateF32Expression(ent::front::ast::F32Expression* numericExpression) {
				return new F32Value(numericExpression->value);
			}
			RuntimeValue* evaluateF64Expression(ent::front::ast::F64Expression* numericExpression) {
				return new F64Value(numericExpression->value);
			}

			RuntimeValue* evaluateBooleanExpression(ent::front::ast::BooleanExpression* booleanExpression) {
				return new BooleanValue(booleanExpression->value);
			}

			RuntimeValue* cast_to_min_type(double num) {
				if (std::isnan(num) || std::isinf(num) || num > std::numeric_limits<uint64_t>::max() || num < std::numeric_limits<int64_t>::min()) {
					throw (ent::Error(ent::ErrorType::INTERPRETER_OUT_OF_RANGE_NUMBER, std::string("The number is out of range for available types : ") + std::to_string(num))).error();
				}

				if (num >= std::numeric_limits<int8_t>::min() && num <= std::numeric_limits<int8_t>::max() && num == static_cast<int8_t>(num)) {
					return new I8Value(static_cast<int8_t>(num));
				} else if (num >= std::numeric_limits<int16_t>::min() && num <= std::numeric_limits<int16_t>::max() && num == static_cast<int16_t>(num)) {
					return new I16Value(static_cast<int16_t>(num));
				} else if (num >= std::numeric_limits<int32_t>::min() && num <= std::numeric_limits<int32_t>::max() && num == static_cast<int32_t>(num)) {
					return new I32Value(static_cast<int32_t>(num));
				} else if (num >= std::numeric_limits<int64_t>::min() && num <= std::numeric_limits<int64_t>::max() && num == static_cast<int64_t>(num)) {
					return new I64Value(static_cast<int64_t>(num));
				} else if (num >= 0 && num <= std::numeric_limits<uint64_t>::max() && num == static_cast<uint64_t>(num)) {
					return new U64Value(static_cast<uint64_t>(num));
				}

				if (num >= -std::numeric_limits<float>::max() && num <= std::numeric_limits<float>::max() && static_cast<float>(num) == num) {
					return new F32Value(static_cast<float>(num));
				}

				return new F64Value(num);
			}

			// * I8

			// I8 - I8
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateI8BinaryExpression,
				I8Value,
				INT8_MAX, INT8_MIN,
				(ent::Error(ent::ErrorType::I8_OVERFLOW_ERROR, "I8 Overflow")),
				(ent::Error(ent::ErrorType::I8_UNDERFLOW_ERROR, "I8 Underflow"))
			)

			// * I16

			// I16 - I16
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateI16BinaryExpression,
				I16Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)
			// I16 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI16I8BinaryExpression, evaluateI8I16BinaryExpression,
				I16Value, I8Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)
			// I16 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI16U8BinaryExpression, evaluateU8I16BinaryExpression,
				I16Value, U8Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)

			// * I32
			
			// I32 - I32
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateI32BinaryExpression,
				I32Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI32I8BinaryExpression, evaluateI8I32BinaryExpression,
				I32Value, I8Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI32I16BinaryExpression, evaluateI16I32BinaryExpression,
				I32Value, I16Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI32U8BinaryExpression, evaluateU8I32BinaryExpression,
				I32Value, U8Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI32U16BinaryExpression, evaluateU16I32BinaryExpression,
				I32Value, U16Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)

			// * I64

			// I64 - I64
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateI64BinaryExpression,
				I64Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64I8BinaryExpression, evaluateI8I64BinaryExpression,
				I64Value, I8Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64I16BinaryExpression, evaluateI16I64BinaryExpression,
				I64Value, I16Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64I32BinaryExpression, evaluateI32I64BinaryExpression,
				I64Value, I32Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64U8BinaryExpression, evaluateU8I64BinaryExpression,
				I64Value, U8Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64U16BinaryExpression, evaluateU16I64BinaryExpression,
				I64Value, U16Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateI64U32BinaryExpression, evaluateU32I64BinaryExpression,
				I64Value, U32Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)

			// * U8

			// U8 - U8
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateU8BinaryExpression,
				U8Value,
				UINT8_MAX, 0,
				(ent::Error(ent::ErrorType::U8_OVERFLOW_ERROR, "U8 Overflow")),
				(ent::Error(ent::ErrorType::U8_UNDERFLOW_ERROR, "U8 Underflow"))
			)

			// * U16

			// U16 - U16
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateU16BinaryExpression,
				U16Value,
				UINT16_MAX, 0,
				(ent::Error(ent::ErrorType::U16_OVERFLOW_ERROR, "U16 Overflow")),
				(ent::Error(ent::ErrorType::U16_UNDERFLOW_ERROR, "U16 Underflow"))
			)
			// U16 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU16U8BinaryExpression, evaluateU8U16BinaryExpression,
				U16Value, U8Value,
				UINT16_MAX, 0,
				(ent::Error(ent::ErrorType::U16_OVERFLOW_ERROR, "U16 Overflow")),
				(ent::Error(ent::ErrorType::U16_UNDERFLOW_ERROR, "U16 Underflow"))
			)

			// * U32

			// U32 - U32
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateU32BinaryExpression,
				U32Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)
			// U32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU32U8BinaryExpression, evaluateU8U32BinaryExpression,
				U32Value, U8Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)
			// U32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU32U16BinaryExpression, evaluateU16U32BinaryExpression,
				U32Value, U16Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)

			// * U64

			// U64 - U64
			evaluateSameIntegerNumberExpression(
				RuntimeValue*, evaluateU64BinaryExpression,
				U64Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU64U8BinaryExpression, evaluateU8U64BinaryExpression,
				U64Value, U8Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU64U16BinaryExpression, evaluateU16U64BinaryExpression,
				U64Value, U16Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateU64U32BinaryExpression, evaluateU32U64BinaryExpression,
				U64Value, U32Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)

			// * F32

			// F32 - F32
			evaluateNumberExpression(
				RuntimeValue*, evaluateF32BinaryExpression,
				F32Value, F32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32I8BinaryExpression, evaluateI8F32BinaryExpression,
				F32Value, I8Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32I16BinaryExpression, evaluateI16F32BinaryExpression,
				F32Value, I16Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32I32BinaryExpression, evaluateI32F32BinaryExpression,
				F32Value, I32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I64
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32I64BinaryExpression, evaluateI64F32BinaryExpression,
				F32Value, I64Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32U8BinaryExpression, evaluateU8F32BinaryExpression,
				F32Value, U8Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32U16BinaryExpression, evaluateU16F32BinaryExpression,
				F32Value, U16Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32U32BinaryExpression, evaluateU32F32BinaryExpression,
				F32Value, U32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U64
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF32U64BinaryExpression, evaluateU64F32BinaryExpression,
				F32Value, U64Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)

			// * F64

			evaluateNumberExpression(
				RuntimeValue*, evaluateF64BinaryExpression,
				F64Value, F64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64I8BinaryExpression, evaluateI8F64BinaryExpression,
				F64Value, I8Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64I16BinaryExpression, evaluateI16F64BinaryExpression,
				F64Value, I16Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64I32BinaryExpression, evaluateI32F64BinaryExpression,
				F64Value, I32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I64
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64I64BinaryExpression, evaluateI64F64BinaryExpression,
				F64Value, I64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64U8BinaryExpression, evaluateU8F64BinaryExpression,
				F64Value, U8Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64U16BinaryExpression, evaluateU16F64BinaryExpression,
				F64Value, U16Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64U32BinaryExpression, evaluateU32F64BinaryExpression,
				F64Value, U32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U64
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64U64BinaryExpression, evaluateU64F64BinaryExpression,
				F64Value, U64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - F32
			evaluateNumberExpressionBoth(
				RuntimeValue*,
				evaluateF64F32BinaryExpression, evaluateF32F64BinaryExpression,
				F64Value, F32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)

			RuntimeValue* evaluateBooleanBinaryExpression(BooleanValue* left, BooleanValue * right, std::string op) {
				if(op == "==") {
					return new BooleanValue(left->get_value() == right->get_value());
				} if(op == "!=") {
					return new BooleanValue(left->get_value() != right->get_value());
				} if(op == "&&") {
					return new BooleanValue(left->get_value() && right->get_value());
				} if(op == "||") {
					return new BooleanValue(left->get_value() || right->get_value());
				} if(op == "<") {
					return new BooleanValue(left->get_value() < right->get_value());
				} if(op == ">") {
					return new BooleanValue(left->get_value() > right->get_value());
				} if(op == "<=") {
					return new BooleanValue(left->get_value() <= right->get_value());
				} if(op == ">=") {
					return new BooleanValue(left->get_value() >= right->get_value());
				} if(op == "^^") {
					return new BooleanValue(
						(left->get_value() || right->get_value()) &&
						!(left->get_value() && right->get_value())
					);
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
			}

			RuntimeValue* evaluateNumberBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, NumberValue* left, NumberValue* right) {
				switch(left->type()) {
					case ValueType::I8:
							switch(right->type()) {
								case ValueType::I8:
									return evaluateI8BinaryExpression((I8Value*)left, (I8Value*)right, binaryExpression->operator_symbol);
								case ValueType::I16:
									return evaluateI8I16BinaryExpression((I8Value*)left, (I16Value*)right, binaryExpression->operator_symbol);
								case ValueType::I32:
									return evaluateI8I32BinaryExpression((I8Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
								case ValueType::I64:
									return evaluateI8I64BinaryExpression((I8Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
								case ValueType::F32:
									return evaluateI8F32BinaryExpression((I8Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
								case ValueType::F64:
									return evaluateI8F64BinaryExpression((I8Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
								default:
									throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I8 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
							}
					case ValueType::I16:
							switch(right->type()) {
								case ValueType::I8:
									return evaluateI16I8BinaryExpression((I16Value*)left, (I8Value*)right, binaryExpression->operator_symbol);
								case ValueType::I16:
									return evaluateI16BinaryExpression((I16Value*)left, (I16Value*)right, binaryExpression->operator_symbol);
								case ValueType::I32:
									return evaluateI16I32BinaryExpression((I16Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
								case ValueType::I64:
									return evaluateI16I64BinaryExpression((I16Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
								case ValueType::U8:
									return evaluateI16U8BinaryExpression((I16Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
								case ValueType::F32:
									return evaluateI16F32BinaryExpression((I16Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
								case ValueType::F64:
									return evaluateI16F64BinaryExpression((I16Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
								default:
									throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I16 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
							}
					case ValueType::I32:
						switch(right->type()) {
							case ValueType::I8:
								return evaluateI32I8BinaryExpression((I32Value*)left, (I8Value*)right, binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateI32I16BinaryExpression((I32Value*)left, (I16Value*)right, binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateI32BinaryExpression((I32Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateI32I64BinaryExpression((I32Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateI32U8BinaryExpression((I32Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateI32U16BinaryExpression((I32Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateI32F32BinaryExpression((I32Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateI32F64BinaryExpression((I32Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I32 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::I64:
						switch(right->type()) {
							case ValueType::I8:
								return evaluateI64I8BinaryExpression((I64Value*)left, (I8Value*)right, binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateI64I16BinaryExpression((I64Value*)left, (I16Value*)right, binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateI64I32BinaryExpression((I64Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateI64BinaryExpression((I64Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateI64U8BinaryExpression((I64Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateI64U16BinaryExpression((I64Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateI64U32BinaryExpression((I64Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateI64F32BinaryExpression((I64Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateI64F64BinaryExpression((I64Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I64 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::U8:
						switch(right->type()) {
							case ValueType::I16:
								return evaluateU8I16BinaryExpression((U8Value*)left, (I16Value*)right, binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateU8I32BinaryExpression((U8Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateU8I64BinaryExpression((U8Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU8BinaryExpression((U8Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU8U16BinaryExpression((U8Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU8U32BinaryExpression((U8Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU8F32BinaryExpression((U8Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU8F64BinaryExpression((U8Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U8 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::U16:
						switch(right->type()) {
							case ValueType::I32:
								return evaluateU16I32BinaryExpression((U16Value*)left, (I32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateU16I64BinaryExpression((U16Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU16U8BinaryExpression((U16Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU16BinaryExpression((U16Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU16U32BinaryExpression((U16Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU16F32BinaryExpression((U16Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU16F64BinaryExpression((U16Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U16 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::U32:
						switch(right->type()) {
							case ValueType::I64:
								return evaluateU32I64BinaryExpression((U32Value*)left, (I64Value*)right, binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU32U8BinaryExpression((U32Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU32U16BinaryExpression((U32Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU32BinaryExpression((U32Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU32F32BinaryExpression((U32Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU32F64BinaryExpression((U32Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U32 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::U64:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateU64U8BinaryExpression((U64Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU64U16BinaryExpression((U64Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU64U32BinaryExpression((U64Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU64F32BinaryExpression((U64Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU64F64BinaryExpression((U64Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U64 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::F32:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateF32U8BinaryExpression((F32Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateF32U16BinaryExpression((F32Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateF32U32BinaryExpression((F32Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::U64:
								return evaluateF32U64BinaryExpression((F32Value*)left, (U64Value*)right, binaryExpression->operator_symbol);
							case ValueType::I8:
								return evaluateF32U8BinaryExpression((F32Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateF32U16BinaryExpression((F32Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateF32U32BinaryExpression((F32Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateF32U32BinaryExpression((F32Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateF32BinaryExpression((F32Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateF32F64BinaryExpression((F32Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (F32 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					case ValueType::F64:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateF64U8BinaryExpression((F64Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateF64U16BinaryExpression((F64Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateF64U32BinaryExpression((F64Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::U64:
								return evaluateF64U64BinaryExpression((F64Value*)left, (U64Value*)right, binaryExpression->operator_symbol);
							case ValueType::I8:
								return evaluateF64U8BinaryExpression((F64Value*)left, (U8Value*)right, binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateF64U16BinaryExpression((F64Value*)left, (U16Value*)right, binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateF64U32BinaryExpression((F64Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateF64U32BinaryExpression((F64Value*)left, (U32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateF64F32BinaryExpression((F64Value*)left, (F32Value*)right, binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateF64BinaryExpression((F64Value*)left, (F64Value*)right, binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (F64 and ?): " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
						}
					default:
						throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env);

			RuntimeValue* evaluateBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, Environment* env) {
				RuntimeValue* left = evaluateStatement(binaryExpression->left, env);
				RuntimeValue* right = evaluateStatement(binaryExpression->right, env);

				// Both operands are numbers
				if(IsNumericType(left->type()) && IsNumericType(right->type())) {
					RuntimeValue* val = evaluateNumberBinaryExpression(binaryExpression, (NumberValue*)left, (NumberValue*)right);
					return val;
				} else if(left->type() == ValueType::BOOL && right->type() == ValueType::BOOL) {
					return evaluateBooleanBinaryExpression((BooleanValue*)left, (BooleanValue*)right, binaryExpression->operator_symbol);
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
			}

			RuntimeValue* evaluateParenthesisExpression(ent::front::ast::ParenthesisExpression* parenthesisExpression, Environment* env) {
				return evaluateStatement(parenthesisExpression->content, env);
			}

			RuntimeValue* evaluateUnaryExpression(ent::front::ast::UnaryExpression* unaryExpression, Environment* env) {
				if(unaryExpression->operator_symbol == "!") {
					return new BooleanValue(!(evaluateStatement(unaryExpression->term, env)->IsTrue()));
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + unaryExpression->operator_symbol)).error();
			}

			RuntimeValue* evaluateDeclaration(ent::front::ast::Declaration* declaration, Environment* env) {
				RuntimeValue* v = evaluateStatement(declaration->value, env);
				check_type_compatibility(get_sample_value(declaration->identifier->identifierType), v, declaration->identifier->name);
				RuntimeValue* value = env->init_value(
					declaration->identifier->name,
					v
				);
				return value;
			}

			RuntimeValue* evaluateFunctionDeclaration(ent::front::ast::FunctionDeclaration* functionDeclaration, Environment* env) {
				env->init_function(
					functionDeclaration->identifier->name,
					functionDeclaration
				);

				return new NullValue();
			}

			RuntimeValue* evaluateScope(ent::front::ast::Scope* scope, Environment* parent_env);

			RuntimeValue* evaluateFunctionCallExpression(ent::front::ast::FunctionCallExpression* functionCallExpression, Environment* env) {
				ent::front::ast::FunctionDeclaration* calledFunction = env->get_function(functionCallExpression->functionIdentifier->name);

				std::vector<ent::front::ast::Statement*> functionBody = std::vector<ent::front::ast::Statement*>();

				if(functionCallExpression->arguments.size() != calledFunction->arguments.size()) {
					throw (ent::Error(
						ent::ErrorType::INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR,
						"Invalid number of args: " + functionCallExpression->arguments.size() + std::string(" instead of ") + std::to_string(calledFunction->arguments.size())
					)).error();
				}

				for(u64 i = 0; i < functionCallExpression->arguments.size(); i++) {
					functionBody.push_back(
						ent::front::parser::make_declaration(calledFunction->arguments[i], functionCallExpression->arguments[i], true)
					);
				}

				for(ent::front::ast::Statement* statement : calledFunction->body) {
					functionBody.push_back(statement);
				}

				ent::front::ast::Scope* scope = new ent::front::ast::Scope(functionBody);

				return evaluateScope(scope, env);
			}

			RuntimeValue* evaluateConditionnalStructure(ent::front::ast::ConditionnalStructure* conditionnalStructure, Environment* env) {
				for(ent::front::ast::ConditionnalBlock* block : conditionnalStructure->conditionnalBlocks) {
					if(block->condition == nullptr || evaluateStatement(block->condition, env)->IsTrue()) {
						return evaluateScope(new ent::front::ast::Scope(block->body), env);
					}
				}
				return new NullValue();
			}

			RuntimeValue* evaluateForLoop(ent::front::ast::ForLoop* forLoop, Environment* env) {

				Environment* forEnv = new Environment(env);

				evaluateStatement(forLoop->initStatement, forEnv);

				while(evaluateStatement(forLoop->loopCondition, forEnv)->IsTrue()) {
					evaluateStatement(forLoop->iterationStatement, forEnv);
					evaluateScope(new ent::front::ast::Scope(forLoop->body), forEnv);
				}

				return new NullValue();
			}

			RuntimeValue* evaluateWhileLoop(ent::front::ast::WhileLoop* whileLoop, Environment* env) {

				Environment* whileEnv = new Environment(env);

				while(evaluateStatement(whileLoop->loopCondition, whileEnv)->IsTrue()) {
					evaluateScope(new ent::front::ast::Scope(whileLoop->body), whileEnv);
				}

				return new NullValue();
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env) {
				switch(statement->get_type()) {
					case ent::front::ast::NodeType::identifier:
						return evaluateIdentifier((ent::front::ast::Identifier*)statement, env);
					case ent::front::ast::NodeType::i8Expression:
						return evaluateI8Expression((ent::front::ast::I8Expression*)statement);
					case ent::front::ast::NodeType::i16Expression:
						return evaluateI16Expression((ent::front::ast::I16Expression*)statement);
					case ent::front::ast::NodeType::i32Expression:
						return evaluateI32Expression((ent::front::ast::I32Expression*)statement);
					case ent::front::ast::NodeType::i64Expression:
						return evaluateI64Expression((ent::front::ast::I64Expression*)statement);
					case ent::front::ast::NodeType::u8Expression:
						return evaluateU8Expression((ent::front::ast::U8Expression*)statement);
					case ent::front::ast::NodeType::u16Expression:
						return evaluateU16Expression((ent::front::ast::U16Expression*)statement);
					case ent::front::ast::NodeType::u32Expression:
						return evaluateU32Expression((ent::front::ast::U32Expression*)statement);
					case ent::front::ast::NodeType::u64Expression:
						return evaluateU64Expression((ent::front::ast::U64Expression*)statement);
					case ent::front::ast::NodeType::f32Expression:
						return evaluateF32Expression((ent::front::ast::F32Expression*)statement);
					case ent::front::ast::NodeType::f64Expression:
						return evaluateF64Expression((ent::front::ast::F64Expression*)statement);
					case ent::front::ast::NodeType::binaryExpression:
						return evaluateBinaryExpression((ent::front::ast::BinaryExpression*)statement, env);
					case ent::front::ast::NodeType::parenthesisExpression:
						return evaluateParenthesisExpression((ent::front::ast::ParenthesisExpression*)statement, env);
					case ent::front::ast::NodeType::unaryExpression:
						return evaluateUnaryExpression((ent::front::ast::UnaryExpression*)statement, env);
					case ent::front::ast::NodeType::booleanExpression:
						return evaluateBooleanExpression((ent::front::ast::BooleanExpression*)statement);
					case ent::front::ast::NodeType::declaration:
						return evaluateDeclaration((ent::front::ast::Declaration*)statement, env);
					case ent::front::ast::NodeType::assignation:
						return env->set_value(
							((ent::front::ast::Assignation*)statement)->identifier->name,
							evaluateStatement(((ent::front::ast::Assignation*)statement)->value, env)
						);
					case ent::front::ast::NodeType::functionDeclaration:
						return evaluateFunctionDeclaration((ent::front::ast::FunctionDeclaration*)statement, env);
					case ent::front::ast::NodeType::functionCallExpression:
						return evaluateFunctionCallExpression((ent::front::ast::FunctionCallExpression*)statement, env);
					case ent::front::ast::NodeType::scope:
						return evaluateScope((ent::front::ast::Scope*)statement, env);
					case ent::front::ast::NodeType::conditionnalStructure:
						return evaluateConditionnalStructure((ent::front::ast::ConditionnalStructure*)statement, env);
					case ent::front::ast::NodeType::forLoop:
						return evaluateForLoop((ent::front::ast::ForLoop*)statement, env);
					case ent::front::ast::NodeType::whileLoop:
						return evaluateWhileLoop((ent::front::ast::WhileLoop*)statement, env);
					default:
						throw (ent::Error(ent::ErrorType::INTERPRETER_UNKNOWN_STATEMENT_ERROR, "Invalid statement: " + statement->type_id())).error();
				}
			}

			RuntimeValue* evaluateScope(ent::front::ast::Scope* scope, Environment* parent_env) {
				Environment* scope_env = new Environment(parent_env);

				RuntimeValue* result;

				for(ent::front::ast::Statement* statement : scope->body) {
					result = evaluateStatement(statement, scope_env);
					std::cout << result->pretty_print() << std::endl;
				}
				return result;
			}

			RuntimeValue* interpret(ent::front::ast::Scope* scope) {
				return evaluateScope(scope, nullptr);
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__