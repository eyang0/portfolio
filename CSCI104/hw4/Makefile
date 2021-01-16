CC = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread


all: deque_test laundry remdup

deque_test: deque_test.cpp deque.h
	$(CC) $(CPPFLAGS) deque_test.cpp $(GTEST_LL) -o deque_test

laundry: laundry.cpp stack.h
	$(CC) $(CPPFLAGS) laundry.cpp -o laundry

remdup: rem_dup.cpp rem_dup_lib.o
	$(CC) $(CPPFLAGS) rem_dup.cpp rem_dup_lib.o -o remdup

rem_dup_lib.o: rem_dup_lib.cpp rem_dup_lib.h
	$(CC) $(CPPFLAGS) -c rem_dup_lib.cpp -o rem_dup_lib.o


.PHONY: clean

clean:
	rm remdup
	rm deque_test
	rm laundry
	rm *.o

