CC = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: sentences sat_solver

sentences: sentences.cpp
	$(CC) $(CPPFLAGS) sentences.cpp -o sentences

sat_solver: sat_solver.cpp
	$(CC) $(CPPFLAGS) sat_solver.cpp -o sat_solver


.PHONY: clean

clean:
	rm sentences
	rm sat_solver
	rm *.out
