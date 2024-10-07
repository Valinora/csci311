FLAGS = -std=c++11 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter

BST: BST.cpp
	g++ $(FLAGS) Node.cpp BST.cpp BSTDriver.cpp

test: BST
	./runTests a.out tests/
