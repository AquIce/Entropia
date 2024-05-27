default: run

build:
	g++ -I include -Wall -o entropia main.cpp

test_build:
	g++ -I include -Wall -o entropia_test test.cpp

run: build
	./entropia main.etp

test: test_build
	./entropia_test

clear:
	rm ./entropia
	rm ./entropia_test