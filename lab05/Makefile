FLAGS = -std=c++11 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter

AVLTree: AVLTree.cpp
	g++ $(FLAGS) AVLNode.cpp AVLTree.cpp AVLTreeDriver.cpp

test: AVLTree
	./runTests a.out tests/
