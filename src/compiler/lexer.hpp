#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <iostream>
#include <string>
#include <vector>

namespace Entropia {

	enum TokenType {
		TYPE,
		OPERATOR,
		BOOLEAN,
		BITWISE,
		LOOP,
		STATEMENT,
		OOP,
		ERROR,
		FUNCTION,
		SPACE,
		IDENTIFIER,
		NUMBER,
		STRING,
		CHAR,
		UNKNOWN
	};

	class Lexer {
		private:
			std::string source;
			std::vector<std::pair<std::vector<std::string>, TokenType>> tokens = {
				{{"int8", "int16", "int32", "int64", "int128", "double", "byte", "char", "bool", "str", "const", "auto", "udf", "void"}, TokenType::TYPE},
				{{"+", "-", "*", "/", "%", "**", "<<", "++", "--"}, TokenType::OPERATOR},
				{{"and", "or", "not", "xor"}, TokenType::BOOLEAN},
				{{"&", "|", "~", "^"}, TokenType::BITWISE},
				{{"loop", "for", "while", "do", "break", "continue"}, TokenType::LOOP},
				{{"if", "elsif", "else", "switch", "case", "default", "==", "!="}, TokenType::STATEMENT},
				{{"class", "typedef", "public", "protected", "private", "self", "super"}, TokenType::OOP},
				{{"try", "catch", "even", "raise"}, TokenType::ERROR},
				{{"fn", "return", "yield"}, TokenType::FUNCTION},
				{{"codespace", "use"}, TokenType::SPACE}
			};
		public:
			Lexer(std::string source);
			~Lexer();
			std::vector<std::string> lex();
	};
}

keywords = {
            "int", "double", "byte", "char", "bool", "str", "const", "auto", "udf", // Types
            "+", "-", "*", "/", "%", "**", "<<", "++", "--", // Operators
            "and", "or", "not", "xor", // Booleans operators
            "&", "|", "~", "^", // Bitwise operators
            "loop", "for", "while", "do", "break", "continue", // Loops
            "if", "elsif", "else", "switch", "case", "default", "==", "!=", // Statements
            "class", "typedef", "public", "protected", "private", "self", "super", // Object Oriented
            "try", "catch", "even", "raise", // Errors
            "fn", "return", "yield", // Functions
            "codespace", "use" // Spaces and Imports
            // https://www.programiz.com/cpp-programming/keywords-identifiers
        };

#endif // __LEXER_HPP__