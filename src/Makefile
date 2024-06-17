default: run

build:
	g++ -Iinclude -Wall -Wpedantic -Werror Entropia/types/numbers.cpp Entropia/lexer/token.cpp Entropia/lexer/lexer.cpp Entropia/parser/ast.cpp main.cpp Entropia/interpreter/values.cpp Entropia/interpreter/env.cpp main.cpp -o entropia

test_build:
	g++ -I include -Wall -Wpedantic -Werror -o entropia_test test.cpp

debug_build:
	g++ -g -I include -Wall -Wpedantic -Werror -o entropia_dbg main.cpp	

run: build
	./entropia main.etp

test: test_build
	./entropia_test

debug: debug_build
	gdb ./entropia_dbg

clean:
	rm ./entropia.exe
	rm ./entropia_test.exe
	rm ./entropia_dbg.exe