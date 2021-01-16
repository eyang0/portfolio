To compile **bst-test** and **sat_solver**:  
make

To run **bst-test**:  
./bst-test  

To run **sat_solver**:  
./sat_solver (input file) (output file)

To clean up files:  
make clean  


**bst-test** tests both a binary search tree and an AVL binary search tree. The AVL binary search tree performs rotations to keep a balanced structure. Note: when removing nodes with two children, a swap with the node's predecessor is performed.   


**sat_solver** uses recursion and backtracking to evaluate boolean satisfiability of a boolean expression in conjunctive normal form. The input file is expected in the DIMACs format. Using backtracking, sat_solver will attempt to find a solution to the expression. If a solution is found, the variable assignments (of the first solution found) will be output to the output file. If a solution cannot be found, "No solution" will be output to the output file. sat_solver uses an AVLTree implementation in place of std::map.  