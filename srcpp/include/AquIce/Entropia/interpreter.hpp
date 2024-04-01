#ifndef __ENT_RUNTIME_INTERPRETER__
#define __ENT_RUNTIME_INTERPRETER__

#include <iostream>

#include "ast.hpp"
#include "env.hpp"

namespace ent {
	namespace runtime {
		namespace interpreter {
			RuntimeValue* evaluateIdentifier(ent::front::ast::Identifier* identifier, Environment* env) {
				if(env->has(identifier->name)) {
					return env->get(identifier->name);
				} else {
					// Invalid identifier
					throw std::runtime_error("Invalid identifier: " + identifier->name);
					return nullptr;
				}
			}

			RuntimeValue* evaluateNumericExpression(ent::front::ast::NumericExpression* numericExpression) {
				return new NumberValue(numericExpression->value);
			}

			RuntimeValue* evaluateTwoNumberBinaryExpression(NumberValue* left, NumberValue* right, char op) {
				switch(op) {
					case '+':
						return new NumberValue(left->get_value() + right->get_value());
						break;
					case '-':
						return new NumberValue(left->get_value() - right->get_value());
						break;
					case '*':
						return new NumberValue(left->get_value() * right->get_value());
						break;
					case '/':
						return new NumberValue(left->get_value() / right->get_value());
						break;
					default:
						// Invalid operator
						throw std::runtime_error("Invalid operator: " + op);
						return nullptr;
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env);

			RuntimeValue* evaluateBinaryExpression(ent::front::ast::BinaryExpression* binaryExpression, Environment* env) {
				RuntimeValue* left = evaluateStatement(binaryExpression->left, env);
				RuntimeValue* right = evaluateStatement(binaryExpression->right, env);

				// Both operands are numbers
				if(left->type() == ent::runtime::ValueType::NUMBER || right->type() == ent::runtime::ValueType::NUMBER) {
					return evaluateTwoNumberBinaryExpression(
						(NumberValue*)left,
						(NumberValue*)right,
						binaryExpression->operator_symbol[0]
					);
				} else {
					// Invalid operands
					throw std::runtime_error("Invalid operands: " + left->pretty_print() + " " + binaryExpression->operator_symbol + " " + right->pretty_print());
					return nullptr;
				}
			}

			RuntimeValue* evaluateStatement(ent::front::ast::Statement* statement, Environment* env) {
				switch(statement->get_type()) {
					case ent::front::ast::NodeType::identifier:
						return evaluateIdentifier((ent::front::ast::Identifier*)statement, env);
					case ent::front::ast::NodeType::numericExpression:
						return evaluateNumericExpression((ent::front::ast::NumericExpression*)statement);
					case ent::front::ast::NodeType::binaryExpression:
						return evaluateBinaryExpression((ent::front::ast::BinaryExpression*)statement, env);
					default:
						// Invalid statement
						throw std::runtime_error("Invalid statement " + statement->type_id());
						return nullptr;
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
				env->set("myVar", new NumberValue(2));
				return evaluateProgram(program, env);
			}
		}
	}
}

#endif // __ENT_RUNTIME_INTERPRETER__