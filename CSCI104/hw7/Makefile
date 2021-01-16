CC = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: bst-test sat_solver

bst-test: bst-test.cpp bst.h avlbst.h
	$(CC) $(CPPFLAGS) bst-test.cpp -o bst-test

sat_solver: sat_solver.cpp bst.h avlbst.h
	$(CC) $(CPPFLAGS) sat_solver.cpp -o sat_solver


.PHONY: clean

clean:
	rm bst-test
	rm sat_solver
	rm *.out
