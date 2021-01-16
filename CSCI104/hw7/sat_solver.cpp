#include <fstream>
#include <sstream>
#include <iostream>
#include "avlbst.h"
#include <vector>
#include <stdlib.h>

using namespace std;

//helper function to read data from file
void readFile(char* filename,vector<vector<int> >& clauses, AVLTree<int,int>& assignments)
{
  ifstream ifile(filename);
  if(ifile.fail())
  {
    cout << "File doesn't exist" << endl;
    return;
  }

  string current_line;

  int num_vars;
  int num_clauses;

  //go through all comments and p line
  while(getline(ifile, current_line))
  {
  	string check;
  	stringstream ss(current_line);
  	ss >> check;
  	if(ss.fail())
  	{
  		cout << "Error reading file" << endl;
  		return;
  	}
  	if(check == "c")
  	{
  		continue;
  	}
  	if(check == "p")
  	{
  		ss >> check;
  		if(ss.fail())
  		{
  			cout << "Error reading file" << endl;
  			return;
  		}
  		ss >> num_vars;
  		ss >> num_clauses;
  		if(ss.fail())
  		{
  			cout << "Error reading file" << endl;
  			return;
  		}
  		break;
  	}
  }

  //read in the clauses
  for(int i = 0; i < num_clauses; i++)
  {
  	getline(ifile, current_line, '0');
	int curr_var;
	vector<int> curr_clause;
	stringstream s2(current_line);

	while(s2 >> curr_var)
	{
		curr_clause.push_back(curr_var);
	}
	clauses.push_back(curr_clause);
  }
  ifile.close();


  //assuming variables go from 1 to num_vars
  for(int j = 1; j <= num_vars; j++)
  {
  	//assigning all variables as unassigned
  	assignments.insert(make_pair(j, -1));
  }

}

//helper function to check if current assignment is valid
//returns 1 for solution, 2 for no solution, and 3 for unknown
int isValid(vector<vector<int>> clauses, AVLTree<int,int> curr_assignments)
{
	unsigned int true_clauses = 0;

	for(unsigned int i = 0; i < clauses.size(); i++)
	{
		unsigned int false_vars = 0;
		for(unsigned int j = 0; j < clauses[i].size(); j++)
		{
			int var_assign = (curr_assignments.find(abs(clauses[i][j])))->second;
			if(var_assign == -1)
			{
				continue;
			}

			if(clauses[i][j] > 0)
			{
				if(var_assign == 1)
				{
					true_clauses++;
					break; //breaking because we know the clause will be true
				}
				else
				{
					false_vars++;
				}
			}
			else //less than 0, so inverted
			{
				if(var_assign == 0)
				{
					true_clauses++;
					break;
				}
				else
				{
					false_vars++;
				}
			}
			//if all vars of clause are false, clause is false
			//if one clause is false, whole statement is false
			if(false_vars == clauses[i].size()) 
			{
				return 2;
			}
		}
	}

	//if all clauses are true, we have a solution
	if(true_clauses == clauses.size())
	{
		return 1;
	}

	//if it is unknown 
	return 3;
}

//helper function to output result if there is a solution
void outputResult(AVLTree<int, int> curr_assignments, ofstream& ofile)
{
	for(AVLTree<int,int>::iterator it = curr_assignments.begin();
		it != curr_assignments.end();
		++it)
	{
		if(it->second != -1)
		{
			ofile << it->first << " = " <<it->second << endl;
		}
	}
}

//recursive helper function that performs backtracking
bool recursiveHelper(vector<vector<int>> clauses, AVLTree<int, int>& curr_assignments, int curr_var)
{
	if(isValid(clauses, curr_assignments) == 1)
	{
		return true;
	}

	else if(isValid(clauses, curr_assignments) == 2)
	{
		return false;
	}

	else //if answer is unknown yet, keep going
	{
		AVLTree<int, int>::iterator it = curr_assignments.find(curr_var);

		it->second = 0;
		bool status = recursiveHelper(clauses, curr_assignments, curr_var+1);
		if(status)
		{
			return true;
		}

		it->second = 1;
		status = recursiveHelper(clauses, curr_assignments, curr_var+1);
		if(status)
		{
			return true;
		}

		it->second = -1; //reset to 'unassigned'
		return false;
	}
}




int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cout << "Usage ./sat_solver input_file output_file" << endl;
	}
	vector<vector<int>> clauses;
	AVLTree<int, int> curr_assignments; //-1, 0, 1
	readFile(argv[1], clauses, curr_assignments);
	

	ofstream ofile(argv[2]);
	if(recursiveHelper(clauses, curr_assignments, 1))
	{
		outputResult(curr_assignments, ofile);
	}
	else
	{
		ofile << "No solution" << endl;
	}

	ofile.close();

}

