#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{
	if (argc < 3)
 	{
 		cout << "usage: ./sum_pairs input_file output_file" << endl;
 		return 1;
 	}

 	//creating filestreams
 	ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    if(ifile.fail())
    {
    	ofile << 0 << endl;
    	return 1;
    }

    int numlines;

    ifile >> numlines;
    //checking if integer on first line could be read in correctly or if it's 0
    if(ifile.fail() || numlines ==0)
    {
    	ofile << 0 << endl;
    	return 1;
    }

    //dynamically allocating an array to hold all ints
    int* integers = new int[numlines];
    for(int i = 0; i<numlines; i++)
    {
    	int current_int;
    	ifile >> current_int;
    	integers[i] = current_int;
    }

    int j = 0;
    int p = numlines-1;
    //finding sums and outputing to ofile
    while(j <= p)
    {
    	int sum = integers[j] + integers[p];
    	ofile << sum << endl;
    	j++;
    	p--;
    }
    ofile.close();
    ifile.close();

    delete [] integers;

}