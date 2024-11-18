FLAGS = -std=c++11 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter

main: Graph.cpp
	g++ $(FLAGS) Node.cpp Graph.cpp GraphDriver.cpp

test: main
	./runTests a.out tests/