#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <regex>

namespace Entropia {

	enum TokenType {
		TYPE,
		MUTABLE,
		OPERATOR,
		COMPARISON,
		ASSIGN,
		BOOLEAN,
		BITWISE,
		STATEMENT,
		GOTO,
		OOP,
		ERROR,
		FUNCTION,
		IMPORT,
		ASYNC,
		COMMENT,
		ARROW,
		VALUE_DEC,
		VALUE_HEX,
		VALUE_BIN,
		VALUE_OCT,
		VALUE_STR,
		VALUE_CHAR,
	};

	class Lexer {
		private:
			std::string source;
			std::vector<std::pair<std::string, TokenType>> tokens = {
				{"^(int|double|byte|char|bool|str|auto|fn)$", TokenType::TYPE},
				{"^(mut)$", TokenType::MUTABLE},
				{"^(\\+|\\-|\\*|\\/|\\%|\\*\\*|\\+\\+|\\-\\-)$", TokenType::OPERATOR},
				{"^(==|!=|>=|<=)$", TokenType::COMPARISON},
				{"^(\\+|\\-|\\*|\\/|\\*\\*|%)?=$", TokenType::ASSIGN},
				{"^(and|or|not|xor)$", TokenType::BOOLEAN},
				{"^(&|\\||~|\\^|<<|>>)$", TokenType::BITWISE},
				{"^(loop|for|in|while|do|if|elif|else)$", TokenType::STATEMENT},
				{"^(break|continue)$", TokenType::GOTO},
				{"^(class|extends|@public|@protected|@private|self|this|super|static)$", TokenType::OOP},
				{"^(try|catch|even|throw)$", TokenType::ERROR},
				{"^(return|yield)$", TokenType::FUNCTION},
				{"^(codespace|use)$", TokenType::IMPORT},
				{"^(async|await)$", TokenType::ASYNC},
				{"^(\\/\\/|\\/\\*|\\*\\/)$", TokenType::COMMENT},
				{"^(->)$", TokenType::ARROW},
				{"^((0d)?[0-9]*.[0-9]+)$", TokenType::VALUE_DEC},
				{"^(0x([0-9]|[a-h])+)$", TokenType::VALUE_HEX},
				{"^(0b[0-1]+)$", TokenType::VALUE_BIN},
				{"^(0o[0-7]+)$", TokenType::VALUE_OCT},
				{"^(\"((\\\\['abfnrtv\\\\])|([^\\\\\"]))*\")$", TokenType::VALUE_STR},
				{"^(('\\\\['tnr\\\\]')|('[^\\\\']'))$", TokenType::VALUE_CHAR},
			};
		public:
			Lexer(std::string source);
			~Lexer();
			std::vector<std::string> lex();
	};
}

#endif // __LEXER_HPP__