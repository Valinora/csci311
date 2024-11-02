FLAGS = -std=c++11 -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter

main: HashTable.cpp
	g++ $(FLAGS) HashTable.cpp HashTableDriver.cpp

test: main
	./runTests a.out tests/
