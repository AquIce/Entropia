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
					throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid identifier: " + identifier->name));
				}
			}

			RuntimeValue* evaluateIntegerExpression(ent::front::ast::IntegerExpression* numericExpression) {
				return new IntegerValue(numericExpression->value);
			}

			RuntimeValue* evaluateFloatExpression(ent::front::ast::FloatExpression* numericExpression) {
				return new FloatValue(numericExpression->value);
			}

			RuntimeValue* evaluateTwoIntegerBinaryExpression(IntegerValue* left, IntegerValue* right, char op) {
				switch(op) {
					case '+':
						return new IntegerValue(left->get_value() + right->get_value());
						break;
					case '-':
						return new IntegerValue(left->get_value() - right->get_value());
						break;
					case '*':
						return new IntegerValue(left->get_value() * right->get_value());
						break;
					case '/':
						return new IntegerValue(left->get_value() / right->get_value());
						break;
					default:
						throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op));
				}
			}

			RuntimeValue* evaluateTwoFloatBinaryExpression(FloatValue* left, FloatValue* right, char op) {
				switch(op) {
					case '+':
						return new FloatValue(left->get_value() + right->get_value());
						break;
					case '-':
						return new FloatValue(left->get_value() - right->get_value());
						break;
					case '*':
						return new FloatValue(left->get_value() * right->get_value());
						break;
					case '/':
						return new FloatValue(left->get_value() / right->get_value());
						break;
					default:
						throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid operator: " + op));
				}
			}

			RuntimeValue* evaluateTwoNumberBinaryExpression(NumberValue* left, NumberValue* right, char op) {
				if(left->type() == ent::runtime::ValueType::INTEGER && right->type() == ent::runtime::ValueType::INTEGER) {
					return evaluateTwoIntegerBinaryExpression((IntegerValue*)left, (IntegerValue*)right, op);
				} else if(left->type() == ent::runtime::ValueType::FLOAT && right->type() == ent::runtime::ValueType::FLOAT) {
					return evaluateTwoFloatBinaryExpression((FloatValue*)left, (FloatValue*)right, op);
				} else {
					throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid operands: " + left->pretty_print() + " " + op + " " + right->pretty_print()));
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env);

			RuntimeValue* evaluateBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, Environment* env) {
				RuntimeValue* left = evaluateStatement(binaryExpression->left, env);
				RuntimeValue* right = evaluateStatement(binaryExpression->right, env);

				// Both operands are numbers
				if(
					left->type() == ent::runtime::ValueType::INTEGER || left->type() == ent::runtime::ValueType::FLOAT &&
					right->type() == ent::runtime::ValueType::INTEGER || right->type() == ent::runtime::ValueType::FLOAT
				){
					return evaluateTwoNumberBinaryExpression(
						(NumberValue*)left,
						(NumberValue*)right,
						binaryExpression->operator_symbol[0]
					);
				} else {
					throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print()));
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env) {
				switch(statement->get_type()) {
					case ent::front::ast::NodeType::identifier:
						return evaluateIdentifier((ent::front::ast::Identifier*)statement, env);
					case ent::front::ast::NodeType::integerExpression:
						return evaluateIntegerExpression((ent::front::ast::IntegerExpression*)statement);
					case ent::front::ast::NodeType::floatExpression:
						return evaluateFloatExpression((ent::front::ast::FloatExpression*)statement);
					case ent::front::ast::NodeType::binaryExpression:
						return evaluateBinaryExpression((ent::front::ast::BinaryExpression*)statement, env);
					default:
						throw_err(Error(ErrorType::RUNTIME_ERROR, "Invalid statement: " + statement->type_id()));
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
				env->init("myVar", new IntegerValue(2));
				return evaluateProgram(program, env);
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__