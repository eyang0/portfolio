#include "setops.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		cout << "usage: ./majors input_file command_file output_file" << endl;
 		return 1;
	}

	//checking for input file
 	ifstream ifile(argv[1]);
 	if(ifile.fail())
 	{
 		cout << "Input file doesn't exist" << endl;
 		return 1;
 	}
 	//checking for command file
 	ifstream ifile2(argv[2]);
 	if(ifile2.fail())
 	{
 		cout << "Command file doesn't exist" << endl;
 		return 1;
 	}

 	ofstream ofile(argv[3]);

 	map<string, set<string>> data;
 	string current_line;

 	//looking at each line from input file
 	while(getline(ifile, current_line))
 	{
 		if(current_line.empty())
 		{
 			continue;
 		}

 		stringstream ss(current_line);
 		string name;
 		string majors;
 		getline(ss, name, ',');
 		
 		int str_index = 0;
 		//erasing leading whitespace from name
 		while(isspace(name[str_index]))
 		{
 			name.erase(str_index, 1);
 			str_index++;
 		}
 		//erasing trailing whitespace from name
 		str_index = name.size()-1;
 		while(isspace(name[str_index]))
 		{
 			name.erase(str_index, 1);
 			str_index--;
 		}

 		//get the rest of the line after the comma
 		getline(ss, majors);
 		
 		stringstream ss2(majors);
 		string current_major;

 		//extracting each major on the line
 		while(ss2 >> current_major)
 		{
 			//changing all majors to upper case
 			for(unsigned int i=0; i<current_major.size(); i++)
 			{
 				current_major[i] = toupper(current_major[i]);
 			}

 			map<string, set<string>>::iterator it = data.find(current_major);
 			//if major doesn't exist yet, add it to the map's keys and add person's name as set
 			if(it == data.end())
 			{
 				set<string> people;
 				people.insert(name);
 				data.insert(make_pair(current_major, people));
 			}
 			/*
 			if major already exists, check to see if the person was already added to
 			the set with that major. If the person has not beed added yet, add name to set
 			*/
 			else
 			{
 				set<string>::iterator it2 = it->second.find(name);
 				{
 					//if name does not yet exist in set
 					if(it2 == it->second.end())
 					{
 						//add the person's name to the set
 						it->second.insert(name);
 					}
 				}
 			}
 		}
 	}


 	//answer queries from the command file
 	while(getline(ifile2, current_line))
 	{
 		if(current_line.empty())
 		{
 			continue;
 		}

 		set<string> names_output;
 		string majors_reprint;
 		stringstream ss3(current_line);
 		string query;

 		int num_majors = 0;

 		while(ss3 >> query)
 		{
 			num_majors++;
 			majors_reprint += query;
 			majors_reprint += " ";
 			//changing all queries to upper case
 			for(unsigned int j=0; j<query.size(); j++)
 			{
 				query[j] = toupper(query[j]);
 			}

 			map<string, set<string>>::iterator it3 = data.find(query);
 			{
 				//if the major is found in the keys
 				if(it3 != data.end())
 				{
 					//if it is the first major of the line, we don't perform set operations
 					if(num_majors == 1)
 					{
 						names_output = it3->second;
 					}
 					//performing set operations for multiple majors
 					else
 					{
 						names_output = names_output & it3->second;
 					}
 				}
 				//if major is not found, no names to output
 				else
 				{
 					names_output.clear();
 				}
 			}
 		}

 		//outputting queries to output file
 		ofile << majors_reprint << endl;

 		//outputting each name 
 		for(set<string>::iterator it4 = names_output.begin();
 			it4 != names_output.end();
 			++it4)
 		{
 			ofile << *it4 << endl;
 		}
 		//adding a blank line
 		ofile << endl;

 	}

 	ifile.close();
 	ifile2.close();
 	ofile.close();

}