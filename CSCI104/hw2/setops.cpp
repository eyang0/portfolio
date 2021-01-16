#include "setops.h"

using namespace std;


// Computes the intersection of s1 and s2
std::set<std::string> operator&(const std::set<std::string>& s1, 
                                const std::set<std::string>& s2)
{
	std::set<std::string> result;
	
	//iterating through smaller set to save time
	if(s1.size() <= s2.size())
	{
		for(std::set<std::string>::iterator it = s1.begin();
			it != s1.end();
			++it)
		{
			//if string also exists in other set, insert to result set
			if(s2.find(*it) != s2.end())
			{
				result.insert(*it);
			}
		}
	}

	//iterating through smaller set to save time
	else
	{
		for(std::set<std::string>::iterator it = s2.begin();
			it != s2.end();
			++it)
		{
			//if string also exists in other set, insert to result set
			if(s1.find(*it) != s1.end())
			{
				result.insert(*it); 
			}
		}
	}
	return result;
}

// Computes the union of s1 and s2
std::set<std::string> operator|(const std::set<std::string>& s1, 
                                const std::set<std::string>& s2)
{
	std::set<std::string> result;
	
	//starting with larger set first so less membership checks need to be made
	if(s1.size() >= s2.size())
	{
		result = s1;
		for(std::set<std::string>::iterator it = s2.begin();
			it != s2.end();
			++it)
		{
			//if string hasn't been included yet, insert to result set
			if(result.find(*it) == result.end())
			{
				result.insert(*it);
			}
		}
	}
	//starting with larger set first so less membership checks need to be made
	else
	{
		result = s2;
		for(std::set<std::string>::iterator it = s1.begin();
			it != s1.end();
			++it)
		{
			//if string hasn't been included yet, insert to result set
			if(result.find(*it) == result.end())
			{
				result.insert(*it);
			}
		}
	}
	return result;
}

// Computes the difference of s1 - s2
std::set<std::string> operator-(const std::set<std::string>& s1,
                                const std::set<std::string>& s2)
{
	std::set<std::string> result;

	for(std::set<std::string>::iterator it = s1.begin();
		it != s1.end();
		++it)
	{
		//if the string is not in s2, add to result
		if(s2.find(*it) == s2.end())
		{
			result.insert(*it);
		}
	}
	return result;
}






