#include "hsort.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	
	vector<int> my_vec;
	my_vec.push_back(5);
	my_vec.push_back(2);
	my_vec.push_back(20);
	my_vec.push_back(49);
	my_vec.push_back(109);
	my_vec.push_back(78);
	my_vec.push_back(32);
	my_vec.push_back(5);

	
	less<int> c1;
	greater<int> c2;
	

	
	/*
	vector<string> my_vec;
	my_vec.push_back("zinc");
	my_vec.push_back("air");
	my_vec.push_back("robot");
	my_vec.push_back("peach");
	my_vec.push_back("education");
	my_vec.push_back("bus");
	my_vec.push_back("tail");

	less<string> c1;
	greater<string> c2;
	*/


	hsort(my_vec, c2);

	for(unsigned int i = 0; i < my_vec.size(); i++)
	{
		cout << my_vec[i] << ", ";
	}

	hsort(my_vec, c1);

	for(unsigned int i = 0; i < my_vec.size(); i++)
	{
		cout << my_vec[i] << ", ";
	}
	
	cout << endl;


	return 0;
}