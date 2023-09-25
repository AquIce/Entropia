#include "lexer.hpp"

Entropia::Scope::Scope(Scope* parent) {
	this->parent = parent;
	this->parent.AddChild(this);
}
Entropia::Scope::AddChild(Scope* child) {
	children.push_back(child);
}
Entropia::Scope::GetChildren() { return children; }

Entropia::Lexer::Lexer(std::string source) {
	this->source = source;
}
Entropia::Lexer::~Lexer() {}
std::vector<std::string> Entropia::Lexer::lex() {
	
}