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
		ACCESS_MODIFIER,
		CLASS,
		EXTENDS,
		THIS,
		PARENT,
		STATIC,
		TRY,
		CATCH,
		EVEN,
		THROW,
		FUNCTION,
		CODESPACE,
		USE,
		ASYNC,
		AWAIT,
		SL_COMMENT,
		ML_COMMENT_OPEN,
		ML_COMMENT_CLOSE,
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
				{"^((=|!|>|<)=)|(<|>)$", TokenType::COMPARISON},
				{"^(\\+|\\-|\\*|\\/|\\*\\*|%)?=$", TokenType::ASSIGN},
				{"^(and|or|not|xor)$", TokenType::BOOLEAN},
				{"^(&|\\||~|\\^|<<|>>)$", TokenType::BITWISE},
				{"^(loop|for|in|while|do|if|elif|else)$", TokenType::STATEMENT},
				{"^(break|continue)$", TokenType::GOTO},
				{"^(@public|@protected|@private)$", TokenType::ACCESS_MODIFIER},
				{"^class$", TokenType::CLASS},
				{"^extends$", TokenType::EXTENDS},
				{"^this$", TokenType::THIS},
				{"^parent$", TokenType::PARENT},
				{"^static$", TokenType::STATIC},
				{"^try$", TokenType::TRY},
				{"^catch$", TokenType::CATCH},
				{"^even$", TokenType::EVEN},
				{"^throw$", TokenType::THROW},
				{"^(return|yield)$", TokenType::FUNCTION},
				{"^codespace$", TokenType::CODESPACE},
				{"^use$", TokenType::USE},
				{"^async$", TokenType::ASYNC},
				{"^await$", TokenType::AWAIT},
				{"^\\/\\/$", TokenType::SL_COMMENT},
				{"^\\/\\*$", TokenType::ML_COMMENT_OPEN},
				{"^\\*\\/$", TokenType::ML_COMMENT_CLOSE},
				{"^(->)$", TokenType::ARROW},
				{"^((0d)?[0-9]*.[0-9]+)$", TokenType::VALUE_DEC},
				{"^(0x([0-9]|[a-f])+)$", TokenType::VALUE_HEX},
				{"^(0b[0-1]+)$", TokenType::VALUE_BIN},
				{"^(0o[0-7]+)$", TokenType::VALUE_OCT},
				{"^\'([^\\]|(\\(t|b|n|r|f|d|'|\"|\\)))\'$", TokenType::VALUE_STR},
				{"^(('\\\\['tnr\\\\]')|('[^\\\\']'))$", TokenType::VALUE_CHAR},
			};
		public:
			Lexer(std::string source);
			~Lexer();
			std::vector<std::string> lex();
	};
}

#endif // __LEXER_HPP__
