default: run

build:
	g++ -I include -o entropia main.cpp

test_build:
	g++ -I include -o entropia_test test.cpp

run: build
	./entropia

test: test_build
	./entropia_test

clear:
	rm ./entropia
	rm ./entropia_test