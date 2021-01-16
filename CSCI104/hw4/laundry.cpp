#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3)
 	{
 		cout << "usage: ./laundry input_file output_file" << endl;
 		return 1;
 	}

 	ifstream ifile(argv[1]);
 	if(ifile.fail())
 	{
 		cout << "File doesn't exist" << endl;
 		return 1;
 	}

 	ofstream ofile(argv[2]);

 	//create the stack to represent the towel bin
 	Stack<string> towel_bin;
 	int number;
 	while(ifile >> number)
 	{
 		//adding a black towel
 		if(number == 0)
 		{
 			towel_bin.push("black");
 		}

 		//adding a white towel
 		else if(number == -1)
 		{
 			towel_bin.push("white");
 		}

 		//there will be no format errors
 		//employee collects towels
 		else
 		{
 			for(int i = 0; i < number; i++)
 			{
 				if(!(towel_bin.empty()))
 				{
 					//output the towel
 					ofile << towel_bin.top() << " ";
 					//then pop it off the stack
 					towel_bin.pop();
 				}
 			}
 			ofile << endl;
 		}
 	}

 	ifile.close();
 	ofile.close();

}