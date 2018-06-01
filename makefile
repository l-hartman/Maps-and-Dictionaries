all: build

build: src/main.cpp
		g++ -std=c++14 src/main.cpp -o run

run: all 
	./run

clean: 
		rm run.o 