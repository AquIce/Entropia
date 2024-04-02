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
					throw (Error(ErrorType::RUNTIME_ERROR, "Invalid identifier: " + identifier->name)).error();
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
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Overflow")).error();
						if(left->get_value() + right->get_value() < INT8_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT8_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Overflow")).error();
						if(left->get_value() - right->get_value() < INT8_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT8_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Overflow")).error();
						if(left->get_value() * right->get_value() < INT8_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I8 Underflow")).error();
						return new I8Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new I8Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI16BinaryExpression(I16Value* left, I16Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT16_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Overflow")).error();
						if(left->get_value() + right->get_value() < INT16_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT16_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Overflow")).error();
						if(left->get_value() - right->get_value() < INT16_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT16_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Overflow")).error();
						if(left->get_value() * right->get_value() < INT16_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I16 Underflow")).error();
						return new I16Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new I16Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI32BinaryExpression(I32Value* left, I32Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT32_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Overflow")).error();
						if(left->get_value() + right->get_value() < INT32_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT32_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Overflow")).error();
						if(left->get_value() - right->get_value() < INT32_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT32_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Overflow")).error();
						if(left->get_value() * right->get_value() < INT32_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I32 Underflow")).error();
						return new I32Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new I32Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateI64BinaryExpression(I64Value* left, I64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > INT64_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Overflow")).error();
						if(left->get_value() + right->get_value() < INT64_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Underflow"));
						return new I64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > INT64_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Overflow")).error();
						if(left->get_value() - right->get_value() < INT64_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Underflow")).error();
						return new I64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > INT64_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Overflow")).error();
						if(left->get_value() * right->get_value() < INT64_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "I64 Underflow")).error();
						return new I64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new I64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateU64BinaryExpression(U64Value* left, U64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > UINT64_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "U64 Overflow")).error();
						return new U64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() < 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "U64 Underflow")).error();
						return new U64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > UINT64_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "U64 Overflow")).error();
						return new U64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new U64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}

			RuntimeValue* evaluateF32BinaryExpression(F32Value* left, F32Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > FLT_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Overflow")).error();
						if(left->get_value() + right->get_value() < FLT_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > FLT_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Overflow")).error();
						if(left->get_value() - right->get_value() < FLT_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > FLT_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Overflow")).error();
						if(left->get_value() * right->get_value() < FLT_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F32 Underflow")).error();
						return new F32Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new F32Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
				}
			}
			RuntimeValue* evaluateF64BinaryExpression(F64Value* left, F64Value * right, char op) {
				switch(op) {
					case '+':
						if(left->get_value() + right->get_value() > DBL_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Overflow")).error();
						if(left->get_value() + right->get_value() < DBL_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() + right->get_value());
						break;
					case '-':
						if(left->get_value() - right->get_value() > DBL_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Overflow")).error();
						if(left->get_value() - right->get_value() < DBL_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() - right->get_value());
						break;
					case '*':
						if(left->get_value() * right->get_value() > DBL_MAX)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Overflow")).error();
						if(left->get_value() * right->get_value() < DBL_MIN)
							throw (Error(ErrorType::RUNTIME_ERROR, "F64 Underflow")).error();
						return new F64Value(left->get_value() * right->get_value());
						break;
					case '/':
						if(right->get_value() == 0)
							throw (Error(ErrorType::RUNTIME_ERROR, "Division by zero")).error();
						return new F64Value(left->get_value() / right->get_value());
						break;
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op)).error();
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
						case ValueType::U64:
							return evaluateU64BinaryExpression((U64Value*)left, (U64Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::F32:
							return evaluateF32BinaryExpression((F32Value*)left, (F32Value*)right, binaryExpression->operator_symbol[0]);
						case ValueType::F64:
							return evaluateF64BinaryExpression((F64Value*)left, (F64Value*)right, binaryExpression->operator_symbol[0]);
						default:
							throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
					}
				} else {
					throw (Error(ErrorType::RUNTIME_ERROR, "Non-matched number operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
				}
			}

			bool IsNumericType(ValueType type) {
				return
					type == ValueType::I8 || type == ValueType::I16 || type == ValueType::I32 || type == ValueType::I64 ||
					type == ValueType::U64 ||
					type == ValueType::F32 || type == ValueType::F64;
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env);

			RuntimeValue* evaluateBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, Environment* env) {
				RuntimeValue* left = evaluateStatement(binaryExpression->left, env);
				RuntimeValue* right = evaluateStatement(binaryExpression->right, env);

				// Both operands are numbers
				if(IsNumericType(left->type()) && IsNumericType(right->type())) {
					return evaluateNumberBinaryExpression(binaryExpression, (NumberValue*)left, (NumberValue*)right);
				} else {
					throw (Error(ErrorType::RUNTIME_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print())).error();
				}
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
					case ent::front::ast::NodeType::u64Expression:
						return evaluateU64Expression((ent::front::ast::U64Expression*)statement);
					case ent::front::ast::NodeType::f32Expression:
						return evaluateF32Expression((ent::front::ast::F32Expression*)statement);
					case ent::front::ast::NodeType::f64Expression:
						return evaluateF64Expression((ent::front::ast::F64Expression*)statement);
					case ent::front::ast::NodeType::binaryExpression:
						return evaluateBinaryExpression((ent::front::ast::BinaryExpression*)statement, env);
					default:
						throw (Error(ErrorType::RUNTIME_ERROR, "Invalid statement: " + statement->type_id())).error();
				}
			}

			std::vector<RuntimeValue*> evaluateProgram(ent::front::ast::Program* program, Environment* env) {
				std::vector<RuntimeValue*> results = std::vector<RuntimeValue*>();
				for(int i = 0; i < program->body.size(); i++) {
					results.push_back(evaluateStatement(program->body[i], env));
				}
				return results;
			}

			std::vector<RuntimeValue*> interpret(ent::front::ast::Program* program) {
				Environment* env = new Environment();
				env->init("myVar", new I8Value(2));
				return evaluateProgram(program, env);
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__