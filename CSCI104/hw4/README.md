To compile **deque_test**, **laundry**, and **remdup**:  
make

To run **deque_test**:  
./deque_test

To run **laundry**:  
./laundry (input file) (output file)

To run **remdup**:  
./remdup (input file) (output file)


To clean up files:  
make clean



deque\_test uses GTest to test an Array-based deque with a circular buffer  

laundry uses a stack to represent a towel basket, in which white and black towels are put in and taken out  

remdup reads in two lists from an input file as linked lists, removes duplicates from the first list, and returns a concatenated list of the first and second lists  