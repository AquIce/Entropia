#ifndef __ENT_RUNTIME_INTERPRETER__
#define __ENT_RUNTIME_INTERPRETER__

#include <iostream>
#include <limits>
#include <cmath>

#include "ast.hpp"
#include "env.hpp"
#include "errors.hpp"

#define evaluateSameIntegerNumberExpression(return_T, function_name, T, max, min, overflow_error, underflow_error) \
std::shared_ptr<return_T> function_name(std::shared_ptr<T> left, std::shared_ptr<T> right, std::string op) { \
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
		return std::make_shared<BooleanValue>(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return std::make_shared<BooleanValue>(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return std::make_shared<BooleanValue>(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return std::make_shared<BooleanValue>(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return std::make_shared<BooleanValue>(left->get_value() < right->get_value()); \
	} if(op == "*") { \
		return std::make_shared<BooleanValue>(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return std::make_shared<BooleanValue>(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return std::make_shared<BooleanValue>(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return std::make_shared<BooleanValue>( \
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
	} if(op == "^") { \
		return cast_to_min_type(left->get_value() ^ right->get_value()); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpression(return_T, function_name, big_T, little_T, max, min, overflow_error, underflow_error) \
std::shared_ptr<return_T> function_name(std::shared_ptr<big_T> left, std::shared_ptr<little_T> right, std::string op) { \
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
		return std::make_shared<BooleanValue>(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return std::make_shared<BooleanValue>(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return std::make_shared<BooleanValue>(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return std::make_shared<BooleanValue>(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return std::make_shared<BooleanValue>(left->get_value() < right->get_value()); \
	} if(op == ">") { \
		return std::make_shared<BooleanValue>(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return std::make_shared<BooleanValue>(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return std::make_shared<BooleanValue>(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return std::make_shared<BooleanValue>( \
			(left->IsTrue() || right->IsTrue()) && \
			!(left->IsTrue() && right->IsTrue()) \
		); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpressionReverse(return_T, function_name, big_T, little_T, max, min, overflow_error, underflow_error) \
std::shared_ptr<return_T> function_name(std::shared_ptr<little_T> left, std::shared_ptr<big_T> right, std::string op) { \
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
		return std::make_shared<BooleanValue>(left->get_value() == right->get_value()); \
	} if(op == "!=") { \
		return std::make_shared<BooleanValue>(left->get_value() != right->get_value()); \
	} if(op == "&&") { \
		return std::make_shared<BooleanValue>(left->IsTrue() && right->IsTrue()); \
	} if(op == "||") { \
		return std::make_shared<BooleanValue>(left->IsTrue() || right->IsTrue()); \
	} if(op == "<") { \
		return std::make_shared<BooleanValue>(left->get_value() < right->get_value()); \
	} if(op == ">") { \
		return std::make_shared<BooleanValue>(left->get_value() > right->get_value()); \
	} if(op == "<=") { \
		return std::make_shared<BooleanValue>(left->get_value() <= right->get_value()); \
	} if(op == ">=") { \
		return std::make_shared<BooleanValue>(left->get_value() >= right->get_value()); \
	} if(op == "^^") { \
		return std::make_shared<BooleanValue>( \
			(left->IsTrue() || right->IsTrue()) && \
			!(left->IsTrue() && right->IsTrue()) \
		); \
	} \
	throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error(); \
}

#define evaluateNumberExpressionBoth(return_T, function_name_first, function_name_second, big_T, little_T, max, min, overflow_error, underflow_error) \
evaluateNumberExpression(return_T, function_name_first, big_T, little_T, max, min, overflow_error, underflow_error) \
evaluateNumberExpressionReverse(return_T, function_name_second, big_T, little_T, max, min, overflow_error, underflow_error)

#define evaluateUnaryAssignationExpression(expression_type, value_type) \
evaluateAssignationExpression( \
	std::make_shared<ent::front::ast::AssignationExpression>( \
		identifier, \
		std::make_shared<ent::front::ast::BinaryExpression>( \
			std::make_shared<expression_type>(std::dynamic_pointer_cast<value_type>(old_value)->get_value()), \
			std::string(1, unaryExpression->operator_symbol[0]), \
			std::make_shared<expression_type>(1) \
		) \
	), \
	env \
)

namespace ent {
	namespace runtime {
		namespace interpreter {

			enum StatementExitCode {
				NONE = 0,
				BREAK_STATEMENT = 1,
				RETURN_STATEMENT = 2,
				BOTH_STATEMENT = 3,
			};

			enum StatementExitCode combineExitCodes(enum StatementExitCode first, enum StatementExitCode second) {
				return static_cast<enum StatementExitCode>(first | second);
			}
			enum StatementExitCode removeExitCode(enum StatementExitCode source, enum StatementExitCode toRemove) {
				return static_cast<enum StatementExitCode>(source ^ toRemove);
			}
			bool hasAnyExitCode(enum StatementExitCode source) {
				return source != StatementExitCode::NONE;
			}
			bool hasExitCode(enum StatementExitCode source, enum StatementExitCode searchingFor) {
				return hasAnyExitCode(static_cast<enum StatementExitCode>(source & searchingFor));
			}

			typedef struct StatementValue {
				std::shared_ptr<RuntimeValue> value;
				StatementExitCode exitCodeType;
			} StatementValue;

			u64 RECURSION_LIMIT = 10000;

			std::shared_ptr<RuntimeValue> evaluateIdentifier(std::shared_ptr<ent::front::ast::Identifier> identifier, std::shared_ptr<Environment> env) {
				return env->get_value(identifier->name);
			}

			std::shared_ptr<RuntimeValue> evaluateI8Expression(std::shared_ptr<ent::front::ast::I8Expression> numericExpression) {
				return std::make_shared<I8Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateI16Expression(std::shared_ptr<ent::front::ast::I16Expression> numericExpression) {
				return std::make_shared<I16Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateI32Expression(std::shared_ptr<ent::front::ast::I32Expression> numericExpression) {
				return std::make_shared<I32Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateI64Expression(std::shared_ptr<ent::front::ast::I64Expression> numericExpression) {
				return std::make_shared<I64Value>(numericExpression->value);
			}
			
			std::shared_ptr<RuntimeValue> evaluateU8Expression(std::shared_ptr<ent::front::ast::U8Expression> numericExpression) {
				return std::make_shared<U8Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateU16Expression(std::shared_ptr<ent::front::ast::U16Expression> numericExpression) {
				return std::make_shared<U16Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateU32Expression(std::shared_ptr<ent::front::ast::U32Expression> numericExpression) {
				return std::make_shared<U32Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateU64Expression(std::shared_ptr<ent::front::ast::U64Expression> numericExpression) {
				return std::make_shared<U64Value>(numericExpression->value);
			}

			std::shared_ptr<RuntimeValue> evaluateF32Expression(std::shared_ptr<ent::front::ast::F32Expression> numericExpression) {
				return std::make_shared<F32Value>(numericExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateF64Expression(std::shared_ptr<ent::front::ast::F64Expression> numericExpression) {
				return std::make_shared<F64Value>(numericExpression->value);
			}

			std::shared_ptr<RuntimeValue> evaluateBooleanExpression(std::shared_ptr<ent::front::ast::BooleanExpression> booleanExpression) {
				return std::make_shared<BooleanValue>(booleanExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateCharExpression(std::shared_ptr<ent::front::ast::CharExpression> charExpression) {
				return std::make_shared<CharValue>(charExpression->value);
			}
			std::shared_ptr<RuntimeValue> evaluateStrExpression(std::shared_ptr<ent::front::ast::StrExpression> strExpression) {
				return std::make_shared<StrValue>(strExpression->value);
			}

			std::shared_ptr<RuntimeValue> cast_to_min_type(double num) {
				if (std::isnan(num) || std::isinf(num) || num > std::numeric_limits<uint64_t>::max() || num < std::numeric_limits<int64_t>::min()) {
					throw (ent::Error(ent::ErrorType::INTERPRETER_OUT_OF_RANGE_NUMBER, std::string("The number is out of range for available types : ") + std::to_string(num))).error();
				}

				if (num >= std::numeric_limits<int8_t>::min() && num <= std::numeric_limits<int8_t>::max() && num == static_cast<int8_t>(num)) {
					return std::make_shared<I8Value>(static_cast<int8_t>(num));
				} else if (num >= std::numeric_limits<int16_t>::min() && num <= std::numeric_limits<int16_t>::max() && num == static_cast<int16_t>(num)) {
					return std::make_shared<I16Value>(static_cast<int16_t>(num));
				} else if (num >= std::numeric_limits<int32_t>::min() && num <= std::numeric_limits<int32_t>::max() && num == static_cast<int32_t>(num)) {
					return std::make_shared<I32Value>(static_cast<int32_t>(num));
				} else if (num >= std::numeric_limits<int64_t>::min() && num <= std::numeric_limits<int64_t>::max() && num == static_cast<int64_t>(num)) {
					return std::make_shared<I64Value>(static_cast<int64_t>(num));
				} else if (num >= 0 && num <= std::numeric_limits<uint64_t>::max() && num == static_cast<uint64_t>(num)) {
					return std::make_shared<U64Value>(static_cast<uint64_t>(num));
				}

				if (num >= -std::numeric_limits<float>::max() && num <= std::numeric_limits<float>::max() && static_cast<float>(num) == num) {
					return std::make_shared<F32Value>(static_cast<float>(num));
				}

				return std::make_shared<F64Value>(num);
			}

			// > I8

			// I8 - I8
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateI8BinaryExpression,
				I8Value,
				INT8_MAX, INT8_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I8_OVERFLOW_ERROR, "I8 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I8_UNDERFLOW_ERROR, "I8 Underflow"))
			)

			// > I16

			// I16 - I16
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateI16BinaryExpression,
				I16Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)
			// I16 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI16I8BinaryExpression, evaluateI8I16BinaryExpression,
				I16Value, I8Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)
			// I16 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI16U8BinaryExpression, evaluateU8I16BinaryExpression,
				I16Value, U8Value,
				INT16_MAX, INT16_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I16_OVERFLOW_ERROR, "I16 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I16_UNDERFLOW_ERROR, "I16 Underflow"))
			)

			// > I32
			
			// I32 - I32
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateI32BinaryExpression,
				I32Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI32I8BinaryExpression, evaluateI8I32BinaryExpression,
				I32Value, I8Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI32I16BinaryExpression, evaluateI16I32BinaryExpression,
				I32Value, I16Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI32U8BinaryExpression, evaluateU8I32BinaryExpression,
				I32Value, U8Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)
			// I32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI32U16BinaryExpression, evaluateU16I32BinaryExpression,
				I32Value, U16Value,
				INT32_MAX, INT32_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I32_OVERFLOW_ERROR, "I32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I32_UNDERFLOW_ERROR, "I32 Underflow"))
			)

			// > I64

			// I64 - I64
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateI64BinaryExpression,
				I64Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64I8BinaryExpression, evaluateI8I64BinaryExpression,
				I64Value, I8Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64I16BinaryExpression, evaluateI16I64BinaryExpression,
				I64Value, I16Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64I32BinaryExpression, evaluateI32I64BinaryExpression,
				I64Value, I32Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64U8BinaryExpression, evaluateU8I64BinaryExpression,
				I64Value, U8Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64U16BinaryExpression, evaluateU16I64BinaryExpression,
				I64Value, U16Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)
			// I64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateI64U32BinaryExpression, evaluateU32I64BinaryExpression,
				I64Value, U32Value,
				INT64_MAX, INT64_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_I64_OVERFLOW_ERROR, "I64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_I64_UNDERFLOW_ERROR, "I64 Underflow"))
			)

			// > U8

			// U8 - U8
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateU8BinaryExpression,
				U8Value,
				UINT8_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U8_OVERFLOW_ERROR, "U8 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U8_UNDERFLOW_ERROR, "U8 Underflow"))
			)

			// > U16

			// U16 - U16
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateU16BinaryExpression,
				U16Value,
				UINT16_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U16_OVERFLOW_ERROR, "U16 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U16_UNDERFLOW_ERROR, "U16 Underflow"))
			)
			// U16 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU16U8BinaryExpression, evaluateU8U16BinaryExpression,
				U16Value, U8Value,
				UINT16_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U16_OVERFLOW_ERROR, "U16 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U16_UNDERFLOW_ERROR, "U16 Underflow"))
			)

			// > U32

			// U32 - U32
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateU32BinaryExpression,
				U32Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)
			// U32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU32U8BinaryExpression, evaluateU8U32BinaryExpression,
				U32Value, U8Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)
			// U32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU32U16BinaryExpression, evaluateU16U32BinaryExpression,
				U32Value, U16Value,
				UINT32_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U32_OVERFLOW_ERROR, "U32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U32_UNDERFLOW_ERROR, "U32 Underflow"))
			)

			// > U64

			// U64 - U64
			evaluateSameIntegerNumberExpression(
				RuntimeValue, evaluateU64BinaryExpression,
				U64Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU64U8BinaryExpression, evaluateU8U64BinaryExpression,
				U64Value, U8Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU64U16BinaryExpression, evaluateU16U64BinaryExpression,
				U64Value, U16Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)
			// U64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateU64U32BinaryExpression, evaluateU32U64BinaryExpression,
				U64Value, U32Value,
				UINT64_MAX, 0,
				(ent::Error(ent::ErrorType::INTERPRETER_U64_OVERFLOW_ERROR, "U64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_U64_UNDERFLOW_ERROR, "U64 Underflow"))
			)

			// > F32

			// F32 - F32
			evaluateNumberExpression(
				RuntimeValue, evaluateF32BinaryExpression,
				F32Value, F32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32I8BinaryExpression, evaluateI8F32BinaryExpression,
				F32Value, I8Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32I16BinaryExpression, evaluateI16F32BinaryExpression,
				F32Value, I16Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32I32BinaryExpression, evaluateI32F32BinaryExpression,
				F32Value, I32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - I64
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32I64BinaryExpression, evaluateI64F32BinaryExpression,
				F32Value, I64Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32U8BinaryExpression, evaluateU8F32BinaryExpression,
				F32Value, U8Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32U16BinaryExpression, evaluateU16F32BinaryExpression,
				F32Value, U16Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32U32BinaryExpression, evaluateU32F32BinaryExpression,
				F32Value, U32Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)
			// F32 - U64
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF32U64BinaryExpression, evaluateU64F32BinaryExpression,
				F32Value, U64Value,
				FLT_MAX, FLT_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F32_OVERFLOW_ERROR, "F32 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F32_UNDERFLOW_ERROR, "F32 Underflow"))
			)

			// > F64

			evaluateNumberExpression(
				RuntimeValue, evaluateF64BinaryExpression,
				F64Value, F64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64I8BinaryExpression, evaluateI8F64BinaryExpression,
				F64Value, I8Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64I16BinaryExpression, evaluateI16F64BinaryExpression,
				F64Value, I16Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64I32BinaryExpression, evaluateI32F64BinaryExpression,
				F64Value, I32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - I64
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64I64BinaryExpression, evaluateI64F64BinaryExpression,
				F64Value, I64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U8
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64U8BinaryExpression, evaluateU8F64BinaryExpression,
				F64Value, U8Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U16
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64U16BinaryExpression, evaluateU16F64BinaryExpression,
				F64Value, U16Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64U32BinaryExpression, evaluateU32F64BinaryExpression,
				F64Value, U32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - U64
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64U64BinaryExpression, evaluateU64F64BinaryExpression,
				F64Value, U64Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)
			// F64 - F32
			evaluateNumberExpressionBoth(
				RuntimeValue,
				evaluateF64F32BinaryExpression, evaluateF32F64BinaryExpression,
				F64Value, F32Value,
				DBL_MAX, DBL_MIN,
				(ent::Error(ent::ErrorType::INTERPRETER_F64_OVERFLOW_ERROR, "F64 Overflow")),
				(ent::Error(ent::ErrorType::INTERPRETER_F64_UNDERFLOW_ERROR, "F64 Underflow"))
			)

			std::shared_ptr<RuntimeValue> evaluateBooleanBinaryExpression(std::shared_ptr<BooleanValue> left, std::shared_ptr<BooleanValue> right, std::string op) {
				if(op == "==") {
					return std::make_shared<BooleanValue>(left->get_value() == right->get_value());
				} if(op == "!=") {
					return std::make_shared<BooleanValue>(left->get_value() != right->get_value());
				} if(op == "&&") {
					return std::make_shared<BooleanValue>(left->get_value() && right->get_value());
				} if(op == "||") {
					return std::make_shared<BooleanValue>(left->get_value() || right->get_value());
				} if(op == "<") {
					return std::make_shared<BooleanValue>(left->get_value() < right->get_value());
				} if(op == "*") {
					return std::make_shared<BooleanValue>(left->get_value() > right->get_value());
				} if(op == "<=") {
					return std::make_shared<BooleanValue>(left->get_value() <= right->get_value());
				} if(op == ">=") {
					return std::make_shared<BooleanValue>(left->get_value() >= right->get_value());
				} if(op == "^^") {
					return std::make_shared<BooleanValue>(
						(left->get_value() || right->get_value()) &&
						!(left->get_value() && right->get_value())
					);
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
			}

			std::shared_ptr<RuntimeValue> evaluateNumberBinaryExpression(std::shared_ptr<ent::front::ast::BinaryExpression> binaryExpression, std::shared_ptr<NumberValue> left, std::shared_ptr<NumberValue> right) {
				switch(left->type()) {
					case ValueType::I8:
							switch(right->type()) {
								case ValueType::I8:
									return evaluateI8BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<I8Value>(right), binaryExpression->operator_symbol);
								case ValueType::I16:
									return evaluateI8I16BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<I16Value>(right), binaryExpression->operator_symbol);
								case ValueType::I32:
									return evaluateI8I32BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
								case ValueType::I64:
									return evaluateI8I64BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
								case ValueType::F32:
									return evaluateI8F32BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
								case ValueType::F64:
									return evaluateI8F64BinaryExpression(std::dynamic_pointer_cast<I8Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
								default:
									throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I8 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
							}
					case ValueType::I16:
							switch(right->type()) {
								case ValueType::I8:
									return evaluateI16I8BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<I8Value>(right), binaryExpression->operator_symbol);
								case ValueType::I16:
									return evaluateI16BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<I16Value>(right), binaryExpression->operator_symbol);
								case ValueType::I32:
									return evaluateI16I32BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
								case ValueType::I64:
									return evaluateI16I64BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
								case ValueType::U8:
									return evaluateI16U8BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
								case ValueType::F32:
									return evaluateI16F32BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
								case ValueType::F64:
									return evaluateI16F64BinaryExpression(std::dynamic_pointer_cast<I16Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
								default:
									throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I16 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
							}
					case ValueType::I32:
						switch(right->type()) {
							case ValueType::I8:
								return evaluateI32I8BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<I8Value>(right), binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateI32I16BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<I16Value>(right), binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateI32BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateI32I64BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateI32U8BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateI32U16BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateI32F32BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateI32F64BinaryExpression(std::dynamic_pointer_cast<I32Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I32 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::I64:
						switch(right->type()) {
							case ValueType::I8:
								return evaluateI64I8BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<I8Value>(right), binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateI64I16BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<I16Value>(right), binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateI64I32BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateI64BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateI64U8BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateI64U16BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateI64U32BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateI64F32BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateI64F64BinaryExpression(std::dynamic_pointer_cast<I64Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (I64 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::U8:
						switch(right->type()) {
							case ValueType::I16:
								return evaluateU8I16BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<I16Value>(right), binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateU8I32BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateU8I64BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU8BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU8U16BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU8U32BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU8F32BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU8F64BinaryExpression(std::dynamic_pointer_cast<U8Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U8 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::U16:
						switch(right->type()) {
							case ValueType::I32:
								return evaluateU16I32BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<I32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateU16I64BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU16U8BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU16BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU16U32BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU16F32BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU16F64BinaryExpression(std::dynamic_pointer_cast<U16Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U16 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::U32:
						switch(right->type()) {
							case ValueType::I64:
								return evaluateU32I64BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<I64Value>(right), binaryExpression->operator_symbol);
							case ValueType::U8:
								return evaluateU32U8BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU32U16BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU32BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU32F32BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU32F64BinaryExpression(std::dynamic_pointer_cast<U32Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U32 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::U64:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateU64U8BinaryExpression(std::dynamic_pointer_cast<U64Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateU64U16BinaryExpression(std::dynamic_pointer_cast<U64Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateU64U32BinaryExpression(std::dynamic_pointer_cast<U64Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateU64F32BinaryExpression(std::dynamic_pointer_cast<U64Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateU64F64BinaryExpression(std::dynamic_pointer_cast<U64Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (U64 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::F32:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateF32U8BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateF32U16BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateF32U32BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::U64:
								return evaluateF32U64BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U64Value>(right), binaryExpression->operator_symbol);
							case ValueType::I8:
								return evaluateF32U8BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateF32U16BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateF32U32BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateF32U32BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateF32BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateF32F64BinaryExpression(std::dynamic_pointer_cast<F32Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (F32 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					case ValueType::F64:
						switch(right->type()) {
							case ValueType::U8:
								return evaluateF64U8BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::U16:
								return evaluateF64U16BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::U32:
								return evaluateF64U32BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::U64:
								return evaluateF64U64BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U64Value>(right), binaryExpression->operator_symbol);
							case ValueType::I8:
								return evaluateF64U8BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U8Value>(right), binaryExpression->operator_symbol);
							case ValueType::I16:
								return evaluateF64U16BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U16Value>(right), binaryExpression->operator_symbol);
							case ValueType::I32:
								return evaluateF64U32BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::I64:
								return evaluateF64U32BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<U32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F32:
								return evaluateF64F32BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<F32Value>(right), binaryExpression->operator_symbol);
							case ValueType::F64:
								return evaluateF64BinaryExpression(std::dynamic_pointer_cast<F64Value>(left), std::dynamic_pointer_cast<F64Value>(right), binaryExpression->operator_symbol);
							default:
								throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands (F64 and ?): " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
						}
					default:
						throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands: " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
				}
			}

			std::shared_ptr<StatementValue> evaluateStatement(std::shared_ptr<ent::front::ast::Statement> statement, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo = StatementExitCode::RETURN_STATEMENT);

			std::shared_ptr<RuntimeValue> evaluateBinaryExpression(std::shared_ptr<ent::front::ast::BinaryExpression> binaryExpression, std::shared_ptr<Environment> env) {
				std::shared_ptr<RuntimeValue> left = evaluateStatement(binaryExpression->left, env)->value;
				std::shared_ptr<RuntimeValue> right = evaluateStatement(binaryExpression->right, env)->value;

				// Both operands are numbers
				if(IsNumericType(left->type()) && IsNumericType(right->type())) {
					std::shared_ptr<RuntimeValue> val = evaluateNumberBinaryExpression(binaryExpression, std::dynamic_pointer_cast<NumberValue>(left), std::dynamic_pointer_cast<NumberValue>(right));
					return val;
				} else if(left->type() == ValueType::BOOL && right->type() == ValueType::BOOL) {
					return evaluateBooleanBinaryExpression(std::dynamic_pointer_cast<BooleanValue>(left), std::dynamic_pointer_cast<BooleanValue>(right), binaryExpression->operator_symbol);
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operands: " + left->repr() + " " + binaryExpression->operator_symbol + " " + right->repr())).error();
			}

			std::shared_ptr<RuntimeValue> evaluateTernaryExpression(std::shared_ptr<ent::front::ast::TernaryExpression> ternaryExpression, std::shared_ptr<Environment> env) {
				std::shared_ptr<RuntimeValue> condition = evaluateStatement(ternaryExpression->condition, env)->value;

				if(condition->IsTrue()) {
					return evaluateStatement(ternaryExpression->true_value, env)->value;
				}
				return evaluateStatement(ternaryExpression->false_value, env)->value;
			}

			std::shared_ptr<RuntimeValue> evaluateParenthesisExpression(std::shared_ptr<ent::front::ast::ParenthesisExpression> parenthesisExpression, std::shared_ptr<Environment> env) {
				return evaluateStatement(parenthesisExpression->content, env)->value;
			}

			std::shared_ptr<RuntimeValue> evaluateAssignationExpression(std::shared_ptr<ent::front::ast::AssignationExpression> assignationExpression, std::shared_ptr<Environment> env);

			std::shared_ptr<RuntimeValue> evaluateUnaryExpression(std::shared_ptr<ent::front::ast::UnaryExpression> unaryExpression, std::shared_ptr<Environment> env) {
				if(unaryExpression->operator_symbol == "!") {
					return std::make_shared<BooleanValue>(!(evaluateStatement(unaryExpression->term, env)->value->IsTrue()));
				} if(unaryExpression->operator_symbol == "~") {
					ent::front::ast::NodeType term_type = unaryExpression->term->get_type();
					std::shared_ptr<RuntimeValue> term_value = evaluateStatement(unaryExpression->term, env)->value;

					if(term_type == ent::front::ast::NodeType::identifier) {
						std::shared_ptr<ent::front::ast::Identifier> identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(unaryExpression->term);
						term_type = identifier->get_identifier_type();
						term_value = env->get_value(identifier->name);
					}
					
					switch(term_type) {
						case ent::front::ast::NodeType::i8Expression:
							return std::make_shared<I8Value>(~std::dynamic_pointer_cast<I8Value>(term_value)->get_value());
						case ent::front::ast::NodeType::i16Expression:
							return std::make_shared<I16Value>(~std::dynamic_pointer_cast<I16Value>(term_value)->get_value());
						case ent::front::ast::NodeType::i32Expression:
							return std::make_shared<I32Value>(~std::dynamic_pointer_cast<I32Value>(term_value)->get_value());
						case ent::front::ast::NodeType::i64Expression:
							return std::make_shared<I64Value>(~std::dynamic_pointer_cast<I64Value>(term_value)->get_value());
						case ent::front::ast::NodeType::u8Expression:
							return std::make_shared<U8Value>(~std::dynamic_pointer_cast<U8Value>(term_value)->get_value());
						case ent::front::ast::NodeType::u16Expression:
							return std::make_shared<U16Value>(~std::dynamic_pointer_cast<U16Value>(term_value)->get_value());
						case ent::front::ast::NodeType::u32Expression:
							return std::make_shared<U32Value>(~std::dynamic_pointer_cast<U32Value>(term_value)->get_value());
						case ent::front::ast::NodeType::u64Expression:
							return std::make_shared<U64Value>(~std::dynamic_pointer_cast<U64Value>(term_value)->get_value());
						default:
							throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operand for bitwise not: " + unaryExpression->term->repr())).error();
					}
				} if(unaryExpression->operator_symbol == "++" || unaryExpression->operator_symbol == "--") {
					std::shared_ptr<ent::front::ast::Identifier> identifier = std::dynamic_pointer_cast<ent::front::ast::Identifier>(unaryExpression->term);
					std::shared_ptr<RuntimeValue> old_value = env->get_value(identifier->name);

					switch(old_value->type()) {
						case ent::runtime::ValueType::I8:
							return evaluateUnaryAssignationExpression(ent::front::ast::I8Expression, ent::runtime::I8Value);
						case ent::runtime::ValueType::I16:
							return evaluateUnaryAssignationExpression(ent::front::ast::I16Expression, ent::runtime::I16Value);
						case ent::runtime::ValueType::I32:
							return evaluateUnaryAssignationExpression(ent::front::ast::I32Expression, ent::runtime::I32Value);
						case ent::runtime::ValueType::I64:
							return evaluateUnaryAssignationExpression(ent::front::ast::I64Expression, ent::runtime::I64Value);
						case ent::runtime::ValueType::U8:
							return evaluateUnaryAssignationExpression(ent::front::ast::U8Expression, ent::runtime::U8Value);
						case ent::runtime::ValueType::U16:
							return evaluateUnaryAssignationExpression(ent::front::ast::U16Expression, ent::runtime::U16Value);
						case ent::runtime::ValueType::U32:
							return evaluateUnaryAssignationExpression(ent::front::ast::U32Expression, ent::runtime::U32Value);
						case ent::runtime::ValueType::U64:
							return evaluateUnaryAssignationExpression(ent::front::ast::U64Expression, ent::runtime::U64Value);
						case ent::runtime::ValueType::F32:
							return evaluateUnaryAssignationExpression(ent::front::ast::F32Expression, ent::runtime::F32Value);
						case ent::runtime::ValueType::F64:
							return evaluateUnaryAssignationExpression(ent::front::ast::F64Expression, ent::runtime::F64Value);
						default:
							throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERANDS_ERROR, "Invalid operand for increment / decrement: " + unaryExpression->term->repr())).error();
					}
				}
				throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_OPERATOR_ERROR, "Invalid operator: " + unaryExpression->operator_symbol)).error();
			}

			std::shared_ptr<RuntimeValue> evaluateDeclaration(std::shared_ptr<ent::front::ast::Declaration> declaration, std::shared_ptr<Environment> env) {
				std::shared_ptr<RuntimeValue> v = evaluateStatement(declaration->value, env)->value;
				check_type_compatibility(get_sample_value(declaration->identifier->identifierType), v, declaration->identifier->name);

				std::shared_ptr<RuntimeValue> value = env->init_value(
					declaration->identifier->name,
					v,
					declaration->isMutable
				);
				return value;
			}

			std::shared_ptr<RuntimeValue> evaluateAssignationExpression(std::shared_ptr<ent::front::ast::AssignationExpression> assignationExpression, std::shared_ptr<Environment> env) {
				return env->set_value(
					assignationExpression->identifier->name,
					evaluateStatement(assignationExpression->value, env)->value
				);
			}

			std::shared_ptr<RuntimeValue> evaluateFunctionDeclaration(std::shared_ptr<ent::front::ast::FunctionDeclaration> functionDeclaration, std::shared_ptr<Environment> env) {
				env->init_function(
					functionDeclaration->identifier->name,
					functionDeclaration
				);

				return std::make_shared<NullValue>();
			}

			std::shared_ptr<RuntimeValue> evaluateFunctionReturn(std::shared_ptr<ent::front::ast::FunctionReturn> functionDeclaration, std::shared_ptr<Environment> env) {
				std::shared_ptr<ent::runtime::RuntimeValue> returnValue = evaluateStatement(functionDeclaration->value, env)->value;

				return returnValue;
			}

			std::shared_ptr<StatementValue> evaluateScope(std::shared_ptr<ent::front::ast::Scope> scope, std::shared_ptr<Environment> parent_env, StatementExitCode sensitiveTo);

			std::shared_ptr<RuntimeValue> evaluateFunctionCallExpression(std::shared_ptr<ent::front::ast::FunctionCallExpression> functionCallExpression, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				std::shared_ptr<ent::front::ast::FunctionDeclaration> calledFunction = env->get_function(functionCallExpression->functionIdentifier->name);

				std::vector<std::shared_ptr<ent::front::ast::Statement>> functionBody = std::vector<std::shared_ptr<ent::front::ast::Statement>>();

				if(functionCallExpression->arguments.size() != calledFunction->arguments.size()) {
					throw (ent::Error(
						ent::ErrorType::INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR,
						"Invalid number of args: " + functionCallExpression->arguments.size() + std::string(" instead of ") + std::to_string(calledFunction->arguments.size())
					)).error();
				}

				for(u64 i = 0; i < functionCallExpression->arguments.size(); i++) {
					// TODO Add argument type check
					functionBody.push_back(
						ent::front::parser::make_declaration(calledFunction->arguments[i], functionCallExpression->arguments[i], calledFunction->arguments[i]->isMutable, true)
					);
				}

				for(std::shared_ptr<ent::front::ast::Statement> statement : calledFunction->body) {
					functionBody.push_back(statement);
				}

				std::shared_ptr<ent::front::ast::Scope> scope = std::make_shared<ent::front::ast::Scope>(functionBody);

				return evaluateScope(scope, env, combineExitCodes(sensitiveTo, StatementExitCode::RETURN_STATEMENT))->value;
			}
			std::shared_ptr<StatementValue> makeStatementValue(std::shared_ptr<ent::runtime::RuntimeValue> value, StatementExitCode exitCode = StatementExitCode::NONE) {
				return std::make_shared<StatementValue>(StatementValue{
					value,
					exitCode
				});
			}

			std::shared_ptr<StatementValue> evaluateConditionnalStructure(std::shared_ptr<ent::front::ast::ConditionnalStructure> conditionnalStructure, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				
				for(std::shared_ptr<ent::front::ast::ConditionnalBlock> block : conditionnalStructure->conditionnalBlocks) {
					if(block->condition == nullptr || evaluateStatement(block->condition, env)->value->IsTrue()) {
						return evaluateScope(std::make_shared<ent::front::ast::Scope>(block->body), env, sensitiveTo);
					}
				}
				return makeStatementValue(std::make_shared<NullValue>());
			}

			std::shared_ptr<StatementValue> evaluateForLoop(std::shared_ptr<ent::front::ast::ForLoop> forLoop, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {

				std::shared_ptr<Environment> forEnv = std::shared_ptr<Environment>(env);

				u64 loopRecursion = 0;

				evaluateStatement(forLoop->initStatement, forEnv);

				std::shared_ptr<StatementValue> last = makeStatementValue(std::shared_ptr<NullValue>());				

				while(evaluateStatement(forLoop->loopCondition, forEnv)->value->IsTrue()) {
					if(loopRecursion >= RECURSION_LIMIT) {
						throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR, "Recursion limit reached (" + std::to_string(RECURSION_LIMIT) + ")")).error();
					}
					last = evaluateScope(std::make_shared<ent::front::ast::Scope>(forLoop->body), forEnv, static_cast<StatementExitCode>(sensitiveTo | StatementExitCode::BREAK_STATEMENT));
					if(hasAnyExitCode(last->exitCodeType)) {
						return last;
					}
					evaluateStatement(forLoop->iterationStatement, forEnv);
					loopRecursion++;
				}

				return last;
			}

			std::shared_ptr<StatementValue> evaluateWhileLoop(std::shared_ptr<ent::front::ast::WhileLoop> whileLoop, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {

				std::shared_ptr<Environment> whileEnv = std::make_shared<Environment>(env);

				std::shared_ptr<StatementValue> last = makeStatementValue(std::shared_ptr<NullValue>());

				u64 loopRecursion = 0;

				while(evaluateStatement(whileLoop->loopCondition, whileEnv)->value->IsTrue()) {
					if(loopRecursion >= RECURSION_LIMIT) {
						throw (ent::Error(ent::ErrorType::INTERPRETER_INVALID_NUMBER_OF_ARGS_FUNCTION_ERROR, "Recursion limit reached (" + std::to_string(RECURSION_LIMIT) + ")")).error();
					}
					last = evaluateScope(std::make_shared<ent::front::ast::Scope>(whileLoop->body), whileEnv, static_cast<StatementExitCode>(sensitiveTo | StatementExitCode::RETURN_STATEMENT));
					if(hasAnyExitCode(last->exitCodeType)) {
						return last;
					}
					loopRecursion++;
				}

				return last;
			}

			std::shared_ptr<StatementValue> evaluateMatchStructure(std::shared_ptr<ent::front::ast::MatchStructure> matchStructure, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				
				std::shared_ptr<StatementValue> last = makeStatementValue(std::shared_ptr<NullValue>());

				for(std::shared_ptr<ent::front::ast::ConditionnalBlock> matchCase : matchStructure->casesBlocks) {
					if(
						matchCase->condition == nullptr ||
						evaluateStatement(std::make_shared<ent::front::ast::BinaryExpression>(
							matchStructure->matchExpression,
							"==",
							matchCase->condition
						), env)->value->IsTrue()
					) {
						last = evaluateScope(
							std::make_shared<ent::front::ast::Scope>(matchCase->body),
							env,
							static_cast<StatementExitCode>(sensitiveTo | StatementExitCode::BREAK_STATEMENT)
						);
						if(hasAnyExitCode(last->exitCodeType)) {
							if(hasExitCode(last->exitCodeType, StatementExitCode::BREAK_STATEMENT)) {
								last->exitCodeType = StatementExitCode::NONE;
							}
							return last;
						}
					}
				}

				return last;
			}

			std::shared_ptr<StatementValue> evaluateTypeDeclaration(std::shared_ptr<ent::front::ast::TypeDeclaration> typeDeclaration, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				return makeStatementValue(std::make_shared<NullValue>());
			}

			std::shared_ptr<StatementValue> evaluateTypeImplementation(std::shared_ptr<ent::front::ast::TypeImplementation> typeImplementation, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				return makeStatementValue(std::make_shared<NullValue>());
			}
			
			std::shared_ptr<StatementValue> evaluateStatement(std::shared_ptr<ent::front::ast::Statement> statement, std::shared_ptr<Environment> env, StatementExitCode sensitiveTo) {
				switch(statement->get_type()) {
					case ent::front::ast::NodeType::identifier:
						return makeStatementValue(
							evaluateIdentifier(std::dynamic_pointer_cast<ent::front::ast::Identifier>(statement), env)
						);
					case ent::front::ast::NodeType::i8Expression:
						return makeStatementValue(
							evaluateI8Expression(std::dynamic_pointer_cast<ent::front::ast::I8Expression>(statement))
						);
					case ent::front::ast::NodeType::i16Expression:
						return makeStatementValue(
							evaluateI16Expression(std::dynamic_pointer_cast<ent::front::ast::I16Expression>(statement))
						);
					case ent::front::ast::NodeType::i32Expression:
						return makeStatementValue(
							evaluateI32Expression(std::dynamic_pointer_cast<ent::front::ast::I32Expression>(statement))
						);
					case ent::front::ast::NodeType::i64Expression:
						return makeStatementValue(
							evaluateI64Expression(std::dynamic_pointer_cast<ent::front::ast::I64Expression>(statement))
						);
					case ent::front::ast::NodeType::u8Expression:
						return makeStatementValue(
							evaluateU8Expression(std::dynamic_pointer_cast<ent::front::ast::U8Expression>(statement))
						);
					case ent::front::ast::NodeType::u16Expression:
						return makeStatementValue(
							evaluateU16Expression(std::dynamic_pointer_cast<ent::front::ast::U16Expression>(statement))
						);
					case ent::front::ast::NodeType::u32Expression:
						return makeStatementValue(
							evaluateU32Expression(std::dynamic_pointer_cast<ent::front::ast::U32Expression>(statement))
						);
					case ent::front::ast::NodeType::u64Expression:
						return makeStatementValue(
							evaluateU64Expression(std::dynamic_pointer_cast<ent::front::ast::U64Expression>(statement))
						);
					case ent::front::ast::NodeType::f32Expression:
						return makeStatementValue(
							evaluateF32Expression(std::dynamic_pointer_cast<ent::front::ast::F32Expression>(statement))
						);
					case ent::front::ast::NodeType::f64Expression:
						return makeStatementValue(
							evaluateF64Expression(std::dynamic_pointer_cast<ent::front::ast::F64Expression>(statement))
						);
					case ent::front::ast::NodeType::binaryExpression:
						return makeStatementValue(
							evaluateBinaryExpression(std::dynamic_pointer_cast<ent::front::ast::BinaryExpression>(statement), env)
						);
					case ent::front::ast::NodeType::ternaryExpression:
						return makeStatementValue(
							evaluateTernaryExpression(std::dynamic_pointer_cast<ent::front::ast::TernaryExpression>(statement), env)
						);
					case ent::front::ast::NodeType::parenthesisExpression:
						return makeStatementValue(
							evaluateParenthesisExpression(std::dynamic_pointer_cast<ent::front::ast::ParenthesisExpression>(statement), env)
						);
					case ent::front::ast::NodeType::unaryExpression:
						return makeStatementValue(
							evaluateUnaryExpression(std::dynamic_pointer_cast<ent::front::ast::UnaryExpression>(statement), env)
						);
					case ent::front::ast::NodeType::booleanExpression:
						return makeStatementValue(
							evaluateBooleanExpression(std::dynamic_pointer_cast<ent::front::ast::BooleanExpression>(statement))
						);
					case ent::front::ast::NodeType::charExpression:
						return makeStatementValue(
							evaluateCharExpression(std::dynamic_pointer_cast<ent::front::ast::CharExpression>(statement))
						);
					case ent::front::ast::NodeType::strExpression:
						return makeStatementValue(
							evaluateStrExpression(std::dynamic_pointer_cast<ent::front::ast::StrExpression>(statement))
						);
					case ent::front::ast::NodeType::declaration:
						return makeStatementValue(
							evaluateDeclaration(std::dynamic_pointer_cast<ent::front::ast::Declaration>(statement), env)
						);
					case ent::front::ast::NodeType::assignationExpression:
						return makeStatementValue(
							evaluateAssignationExpression(std::dynamic_pointer_cast<ent::front::ast::AssignationExpression>(statement), env)
						);
					case ent::front::ast::NodeType::functionDeclaration:
						return makeStatementValue(
							evaluateFunctionDeclaration(std::dynamic_pointer_cast<ent::front::ast::FunctionDeclaration>(statement), env)
						);
					case ent::front::ast::NodeType::functionReturn:
						return makeStatementValue(
							evaluateFunctionReturn(std::dynamic_pointer_cast<ent::front::ast::FunctionReturn>(statement), env),
							StatementExitCode::RETURN_STATEMENT
						);
					case ent::front::ast::NodeType::functionCallExpression:
						return makeStatementValue(
							evaluateFunctionCallExpression(std::dynamic_pointer_cast<ent::front::ast::FunctionCallExpression>(statement), env, sensitiveTo)
						);
					case ent::front::ast::NodeType::scope:
						return evaluateScope(std::dynamic_pointer_cast<ent::front::ast::Scope>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::conditionnalStructure:
						return evaluateConditionnalStructure(std::dynamic_pointer_cast<ent::front::ast::ConditionnalStructure>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::forLoop:
						return evaluateForLoop(std::dynamic_pointer_cast<ent::front::ast::ForLoop>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::whileLoop:
						return evaluateWhileLoop(std::dynamic_pointer_cast<ent::front::ast::WhileLoop>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::matchStructure:
						return evaluateMatchStructure(std::dynamic_pointer_cast<ent::front::ast::MatchStructure>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::breakStatement:
						return makeStatementValue(
							std::make_shared<NullValue>(),
							StatementExitCode::BREAK_STATEMENT
						);
					case ent::front::ast::NodeType::typeDeclaration:
						return evaluateTypeDeclaration(std::dynamic_pointer_cast<ent::front::ast::TypeDeclaration>(statement), env, sensitiveTo);
					case ent::front::ast::NodeType::typeImplementation:
						return evaluateTypeImplementation(std::dynamic_pointer_cast<ent::front::ast::TypeImplementation>(statement), env, sensitiveTo);
					default:
						throw (ent::Error(ent::ErrorType::INTERPRETER_UNKNOWN_STATEMENT_ERROR, "Invalid statement: " + statement->type_id())).error();
				}
			}

			std::shared_ptr<StatementValue> evaluateScope(std::shared_ptr<ent::front::ast::Scope> scope, std::shared_ptr<Environment> parent_env, StatementExitCode sensitiveTo) {
				std::shared_ptr<Environment> scope_env = std::make_shared<Environment>(parent_env);

				std::shared_ptr<StatementValue> result;
				std::shared_ptr<StatementValue> prev_result = makeStatementValue(
					std::make_shared<NullValue>(),
					StatementExitCode::NONE
				);

				for(std::shared_ptr<ent::front::ast::Statement> statement : scope->body) {
					result = evaluateStatement(statement, scope_env, sensitiveTo);
					if(hasExitCode(sensitiveTo, result->exitCodeType)) {
						if(result->exitCodeType == StatementExitCode::BREAK_STATEMENT) {
							prev_result->exitCodeType = StatementExitCode::BREAK_STATEMENT;
							return prev_result;
						}
						return result;
					}
					prev_result = result;
					std::cout << statement->repr() << " -> " << result->value->repr() << std::endl;
				}
				return result;
			}

			std::shared_ptr<RuntimeValue> interpret(std::shared_ptr<ent::front::ast::Scope> scope) {
				return evaluateScope(scope, nullptr, StatementExitCode::NONE)->value;
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__