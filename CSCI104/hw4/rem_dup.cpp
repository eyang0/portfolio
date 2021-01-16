#include "rem_dup_lib.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//helper functions
void destructList(Item* head);
void read_to_List(Item*& head, string line);


int main(int argc, char *argv[])
{
	if (argc < 3)
 	{
 		cout << "usage: ./remdup input_file output_file" << endl;
 		return 1;
 	}

 	ifstream ifile(argv[1]);
 	if(ifile.fail())
 	{
 		cout << "File doesn't exist" << endl;
 		return 1;
 	}

 	ofstream ofile(argv[2]);
 	
 	Item* head1;
 	Item* head2;
 	Item* head3; //to hold concatenated list

 	string line1;
 	string line2;

 	//there will be no formatting errors in the input file
 	getline(ifile, line1);
 	getline(ifile, line2);

 	//reading in lists
 	read_to_List(head1, line1);
 	read_to_List(head2, line2);

 	removeConsecutive(head1);
 	head3 = concatenate(head1, head2);

 	Item* to_output = head3;
 	while(to_output != NULL)
 	{
 		ofile << to_output->val << " ";
 		to_output = to_output->next;
 	}

 	//dellocate all lists
 	destructList(head1);
 	destructList(head2);
 	destructList(head3);

 	ifile.close();
 	ofile.close();

}



