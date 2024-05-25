#ifndef __ENT_RUNTIME_INTERPRETER__
#define __ENT_RUNTIME_INTERPRETER__

#include <iostream>

#include "ast.hpp"
#include "env.hpp"
#include "errors.hpp"

namespace ent {
	namespace runtime {
		namespace interpreter {
			RuntimeValue* evaluateIdentifier(ent::front::ast::Identifier* identifier, Environment* env) {
				if(env->has(identifier->name)) {
					return env->get(identifier->name);
				} else {
					throw (Error(ErrorType::INVALID_IDENTIFIER_ERROR, "Invalid identifier: " + identifier->name)).error();
				}
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

			RuntimeValue* evaluateI8BinaryExpression(I8Value* left, I8Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT8_MAX)
							throw (Error(ErrorType::I8_OVERFLOW_ERROR, "I8 Overflow")).error();
						if(left->get_value() + right->get_value() < INT8_MIN)
							throw (Error(ErrorType::I8_UNDERFLOW_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT8_MAX)
							throw (Error(ErrorType::I8_OVERFLOW_ERROR, "I8 Overflow")).error();
						if(left->get_value() - right->get_value() < INT8_MIN)
							throw (Error(ErrorType::I8_UNDERFLOW_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT8_MAX)
							throw (Error(ErrorType::I8_OVERFLOW_ERROR, "I8 Overflow")).error();
						if(left->get_value() * right->get_value() < INT8_MIN)
							throw (Error(ErrorType::I8_UNDERFLOW_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new I8Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI16BinaryExpression(I16Value* left, I16Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT16_MAX)
							throw (Error(ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")).error();
						if(left->get_value() + right->get_value() < INT16_MIN)
							throw (Error(ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT16_MAX)
							throw (Error(ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")).error();
						if(left->get_value() - right->get_value() < INT16_MIN)
							throw (Error(ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT16_MAX)
							throw (Error(ErrorType::I16_OVERFLOW_ERROR, "I16 Overflow")).error();
						if(left->get_value() * right->get_value() < INT16_MIN)
							throw (Error(ErrorType::I16_UNDERFLOW_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new I16Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI32BinaryExpression(I32Value* left, I32Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT32_MAX)
							throw (Error(ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")).error();
						if(left->get_value() + right->get_value() < INT32_MIN)
							throw (Error(ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT32_MAX)
							throw (Error(ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")).error();
						if(left->get_value() - right->get_value() < INT32_MIN)
							throw (Error(ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT32_MAX)
							throw (Error(ErrorType::I32_OVERFLOW_ERROR, "I32 Overflow")).error();
						if(left->get_value() * right->get_value() < INT32_MIN)
							throw (Error(ErrorType::I32_UNDERFLOW_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new I32Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI64BinaryExpression(I64Value* left, I64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT64_MAX)
							throw (Error(ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")).error();
						if(left->get_value() + right->get_value() < INT64_MIN)
							throw (Error(ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow"));
						return new I64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT64_MAX)
							throw (Error(ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")).error();
						if(left->get_value() - right->get_value() < INT64_MIN)
							throw (Error(ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow")).error();
						return new I64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT64_MAX)
							throw (Error(ErrorType::I64_OVERFLOW_ERROR, "I64 Overflow")).error();
						if(left->get_value() * right->get_value() < INT64_MIN)
							throw (Error(ErrorType::I64_UNDERFLOW_ERROR, "I64 Underflow")).error();
						return new I64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new I64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}

			RuntimeValue* evaluateU8BinaryExpression(U8Value* left, U8Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > UINT8_MAX)
							throw (Error(ErrorType::U8_OVERFLOW_ERROR, "U8 Overflow")).error();
						return new U8Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() < 0)
							throw (Error(ErrorType::U8_UNDERFLOW_ERROR, "U8 Underflow")).error();
						return new U8Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > UINT8_MAX)
							throw (Error(ErrorType::U8_OVERFLOW_ERROR, "U8 Overflow")).error();
						return new U8Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new U8Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateU16BinaryExpression(U16Value* left, U16Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > UINT16_MAX)
							throw (Error(ErrorType::U16_OVERFLOW_ERROR, "U16 Overflow")).error();
						return new U16Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() < 0)
							throw (Error(ErrorType::U16_UNDERFLOW_ERROR, "U16 Underflow")).error();
						return new U16Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > UINT16_MAX)
							throw (Error(ErrorType::U16_OVERFLOW_ERROR, "U16 Overflow")).error();
						return new U16Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new U16Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateU32BinaryExpression(U32Value* left, U32Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > UINT32_MAX)
							throw (Error(ErrorType::U32_OVERFLOW_ERROR, "U32 Overflow")).error();
						return new U32Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() < 0)
							throw (Error(ErrorType::U32_UNDERFLOW_ERROR, "U32 Underflow")).error();
						return new U32Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > UINT32_MAX)
							throw (Error(ErrorType::U32_OVERFLOW_ERROR, "U32 Overflow")).error();
						return new U32Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new U32Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateU64BinaryExpression(U64Value* left, U64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > UINT64_MAX)
							throw (Error(ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")).error();
						return new U64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() < 0)
							throw (Error(ErrorType::U64_UNDERFLOW_ERROR, "U64 Underflow")).error();
						return new U64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > UINT64_MAX)
							throw (Error(ErrorType::U64_OVERFLOW_ERROR, "U64 Overflow")).error();
						return new U64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new U64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}

			RuntimeValue* evaluateF32BinaryExpression(F32Value* left, F32Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > FLT_MAX)
							throw (Error(ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")).error();
						if(left->get_value() + right->get_value() < FLT_MIN)
							throw (Error(ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > FLT_MAX)
							throw (Error(ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")).error();
						if(left->get_value() - right->get_value() < FLT_MIN)
							throw (Error(ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > FLT_MAX)
							throw (Error(ErrorType::F32_OVERFLOW_ERROR, "F32 Overflow")).error();
						if(left->get_value() * right->get_value() < FLT_MIN)
							throw (Error(ErrorType::F32_UNDERFLOW_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new F32Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateF64BinaryExpression(F64Value* left, F64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > DBL_MAX)
							throw (Error(ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")).error();
						if(left->get_value() + right->get_value() < DBL_MIN)
							throw (Error(ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > DBL_MAX)
							throw (Error(ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")).error();
						if(left->get_value() - right->get_value() < DBL_MIN)
							throw (Error(ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > DBL_MAX)
							throw (Error(ErrorType::F64_OVERFLOW_ERROR, "F64 Overflow")).error();
						if(left->get_value() * right->get_value() < DBL_MIN)
							throw (Error(ErrorType::F64_UNDERFLOW_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::DIVISION_BY_ZERO_ERROR, "Division by zero")).error();
						return new F64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::INVALID_OPERATOR_ERROR, "Invalid operator: " + op)).error();
				}
			}

			RuntimeValue* evaluateNumberBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, NumberValue* left, NumberValue* right) {
				if(left->type() == right->type()) {
					switch(left->type()) {
						case ValueType::I8:
							return evaluateI8BinaryExpression((I8Value*)left, (I8Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::I16:
							return evaluateI16BinaryExpression((I16Value*)left, (I16Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::I32:
							return evaluateI32BinaryExpression((I32Value*)left, (I32Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::I64:
							return evaluateI64BinaryExpression((I64Value*)left, (I64Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::U8:
							return evaluateU8BinaryExpression((U8Value*)left, (U8Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::U16:
							return evaluateU16BinaryExpression((U16Value*)left, (U16Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::U32:
							return evaluateU32BinaryExpression((U32Value*)left, (U32Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::U64:
							return evaluateU64BinaryExpression((U64Value*)left, (U64Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::F32:
							return evaluateF32BinaryExpression((F32Value*)left, (F32Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::F64:
							return evaluateF64BinaryExpression((F64Value*)left, (F64Value*)right, binaryExpression->operator_symbol[0]);
						default:
							throw (Error(ErrorType::INVALID_OPERANDS_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
					}
				} else {
					throw (Error(ErrorType::NON_MATCHED_NUMBER_OPERANDS_ERROR, "Non-matched number operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env);

			RuntimeValue* evaluateBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, Environment* env) {
				RuntimeValue* left = evaluateStatement(binaryExpression->left, env);
				RuntimeValue* right = evaluateStatement(binaryExpression->right, env);

				// Both operands are numbers
				if(IsNumericType(left->type()) && IsNumericType(right->type())) {
					return evaluateNumberBinaryExpression(binaryExpression, (NumberValue*)left, (NumberValue*)right);
				} else {
					throw (Error(ErrorType::INVALID_OPERANDS_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
				}
			}

			std::vector<RuntimeValue*> interpret(ent::front::ast::Scope* scope);

			RuntimeValue* evaluateDeclaration(ent::front::ast::Declaration* declaration, Environment* env) {
				RuntimeValue* value = env->init(
					declaration->identifier->name,
					evaluateStatement(declaration->value, env)
				);
				return declaration->isInFunctionSetup  ? new NullValue(false) : value;
			}

			RuntimeValue* evaluateSubScope(ent::front::ast::Scope* scope) {
				std::vector<RuntimeValue*> sub_values = interpret(scope);
				for(RuntimeValue* sub_value : sub_values) {
					std::cout << sub_value->pretty_print() << std::endl;
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
					case ent::front::ast::NodeType::declaration:
						return evaluateDeclaration((ent::front::ast::Declaration*)statement, env);
					case ent::front::ast::NodeType::assignation:
						return env->set(
							((ent::front::ast::Assignation*)statement)->identifier->name,
							evaluateStatement(((ent::front::ast::Assignation*)statement)->value, env)
						);
					case ent::front::ast::NodeType::functionDeclaration:
						return new NullValue();
					case ent::front::ast::NodeType::scope:
						return evaluateSubScope((ent::front::ast::Scope*)statement);
					default:
						throw (Error(ErrorType::UNKNOWN_STATEMENT_ERROR, "Invalid statement: " + statement->type_id())).error();
				}
			}

			std::vector<RuntimeValue*> evaluateScope(ent::front::ast::Scope* scope, Environment* env) {
				std::vector<RuntimeValue*> results = std::vector<RuntimeValue*>();
				for(ent::front::ast::Statement* statement : scope->body) {
					results.push_back(evaluateStatement(statement, env));
				}
				return results;
			}

			std::vector<RuntimeValue*> interpret(ent::front::ast::Scope* scope) {
				Environment* env = new Environment();
				//env->init("myVar", new I8Value(2));
				return evaluateScope(scope, env);
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__