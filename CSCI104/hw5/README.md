To compile **twitter**:  
make

To run **twitter**:  
./twitter (input file)

**User Interface**:  
AND (hashtags separated by spaces) - Search for tweets with certain hashtags using AND strategy  
OR (hashtags separated by spaces) - Search for tweets with certain hashtags using OR strategy  
TWEET (username) (tweet text) - Create a tweet  
FOLLOW (name of follower) (name to follow) - Add a follow relationship  
SAVE (new filename) - Save a new database file of all users, their following relationships, and tweets  
QUIT - Quit and output files for each User's feed (sorted with hsort)

To clean up files:  
make clean  



hsort.h contains code for sorting with a heap of a templated type using a comparator (including a heapify helper function):
hsort(vector of your data, comparator you would like to use)  

heap.h contains code for an m-ary Heap of a templated class. To construct the heap, use Heap(m-ary number m, comparator you would like to use). Supports pushing, popping, getting the top item, and checking if heap is empty.  
Use #include "heap.h" to use this Heap class.
