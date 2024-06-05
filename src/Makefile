default: run

build:
	g++ -I include -Wall -o entropia main.cpp

test_build:
	g++ -I include -Wall -o entropia_test test.cpp

debug_build:
	g++ -g -I include -Wall -o entropia_dbg main.cpp	

run: build
	./entropia main.etp

test: test_build
	./entropia_test

debug: debug_build
	gdb ./entropia_dbg

clear:
	rm ./entropia
	rm ./entropia_test