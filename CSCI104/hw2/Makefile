all: setops_test majors

setops_test: setops_test.cpp setops.o 
	g++ -g -Wall -std=c++11 setops_test.cpp setops.o -o setops_test

majors: majors.cpp setops.o
	g++ -g -Wall -std=c++11 majors.cpp setops.o -o majors

setops.o: setops.h setops.cpp
	g++ -g -Wall -std=c++11 -c setops.cpp -o setops.o

clean:
	rm setops_test
	rm majors
	rm *.o
