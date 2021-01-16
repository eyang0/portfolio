To compile **sentences** and **sat_solver**:  
make

To run **sentences**:  
./sentences (input file) (output file)

To run **sat_solver**:  
./sat_solver (input file) (output file)

To clean up files:  
make clean  


**sentences** uses recursion to generate all combinations of words given in the input file that create valid sentences. Expected format of input file by line: adjective(s), subjects(s), verb(s), adverb(s). Legal sentences are of the from The (adjective) subject verb (adverb). At the end of the output file will be the number of sentences generated.  

**sat_solver** uses reursion and backtracking to evaluate boolean satisfiability of a boolean expression in conjunctive normal form. The input file is expected in the DIMACs format. Using backtracking, sat_solver will attempt to find a solution to the expression. If a solution is found, the variable assignments (of the first solution found) will be output to the output file. If a solution cannot be found, "No solution" will be output to the output file. 