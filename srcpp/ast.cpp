#include "ast.hpp"

std::string ent::front::ast::node_type_name(enum NodeType type) {
    std::vector<std::string> node_type_names = std::vector<std::string>{ "Program", "BinaryExpression", "NumericExpression" };
    return node_type_names[type];
}

std::string ent::front::ast::Statement::pretty_print() {
    if(ent::front::ast::BinaryExpression* be = dynamic_cast<ent::front::ast::BinaryExpression*>(this)) {
        return "BE";
    }
    return "Statement";
}

ent::front::ast::Program::Program(std::vector<std::unique_ptr<ent::front::ast::Statement>> body) {
    this->body = body;
}
std::string ent::front::ast::Program::pretty_print() {
    std::string printer = "";
    printer += node_type_name(this->type);
    printer += "\nBody:";
    if(this->body.size() == 0) {
        return printer + "\n None";
    }
    for(auto statement : this->body) {
        printer += "\n " + statement->pretty_print();
    }
    return printer;
}

ent::front::ast::NumericExpression::NumericExpression(float value) {
    this->value = value;
}
std::string ent::front::ast::NumericExpression::pretty_print() {
    std::string printer = "";
    printer += node_type_name(this->type);
    printer += "\n" + std::to_string(this->value);
    return printer;
}

ent::front::ast::BinaryExpression::BinaryExpression(ent::front::ast::Expression left, ent::front::ast::Expression right, std::string operator_symbol) {
    this->left = left;
    this->right = right;
    this->operator_symbol = operator_symbol;
}
std::string ent::front::ast::BinaryExpression::pretty_print() {
    std::string printer = "";
    printer += node_type_name(this->type);
    printer += "\n" + this->left.pretty_print() + this->operator_symbol + this->right.pretty_print();
    return printer;
}