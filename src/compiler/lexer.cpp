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
	this->source = std::trim(source);
}
Entropia::Lexer::~Lexer() {}
Entropia::Scope Entropia::Lexer::lex() {
	Entropia::Scope main = new Entropia::Scope();

	std::vector<Entropia::TokenType> tokens;
	for(std::string word : this->source.split(" ")) {
		if(regex_match(word, regex("^{$")))
		if(regex_match(word, regex("^}$")))
		for(std::pair <std::string, Entropia::TokenType> pair : this->tokens) {
			if(regex_match(word, regex(pair.first))) { tokens.push_back(pair.second); }
		}
	}
}