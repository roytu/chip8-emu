
run: build
	./bin/main

test: build
	./bin/test

build:
	g++ -o bin/main -Iinclude src/*.cpp
	g++ -o bin/test -Iinclude tests/*.cpp
