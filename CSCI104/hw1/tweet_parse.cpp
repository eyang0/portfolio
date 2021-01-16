#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
 	{
 		cout << "usage: ./tweet_parse input_file" << endl;
 		return 1;
 	}

 	ifstream ifile(argv[1]);
 	if(ifile.fail())
 	{
 		cout << "File doesn't exist" << endl;
 		return 1;
 	}

 	int num_tweets = 0;
 	vector<string> users;
 	vector<string> hashtags;

 	string current_line;
 	//getting each line
 	while(getline(ifile, current_line))
 	{
 		//skipping entire iteration if it is an empty line
 		if(current_line.empty())
 		{
 			continue;
 		}
 		num_tweets++;

 		stringstream ss(current_line);
 		string until_at;
 		//getting each chunk up to '@', or until end of stream
 		while(getline(ss, until_at, '@')) 
 		{
 			string until_hash;
 			stringstream ss_2(until_at);
 			//getting each chunk up to '#', or until end of stream
 			while(getline(ss_2, until_hash, '#'))
 			{
 				string hashtag;
 				//if there is a hashtag, now we get it
 				ss_2 >> hashtag;
 				
 				//if there wasn't a hashtag, >> fails and we go to next iteration
 				if(ss_2.fail())
 				{
 					//clearing the fail flag
 					ss_2.clear(); 
 					continue;
 				}

 				//flag for duplicate hashtag
 				bool duplicate1 = false;
 				for(unsigned int i = 0; i<hashtags.size(); i++)
 				{
 					if(hashtags[i].compare(hashtag) == 0)
 					{
 						duplicate1 = true;
 					}
 				}

 				//don't add to vector if it is a duplicate
 				if(duplicate1)
 				{
 					duplicate1 = false;
 					continue;
 				}

 				hashtags.push_back(hashtag);
 			}

 			string username;
 			ss >> username;
 			//if there wasn't an @, >> fails and we go to next iteration
 			if(ss.fail())
 			{
 				ss.clear();
 				continue;
 			}

 			bool duplicate2 = false;
 			for(unsigned int j = 0; j<users.size(); j++)
			{
				if(users[j].compare(username) == 0)
				{
					duplicate2 = true;
				}
			}

			//don't add to vector if it is a duplicate
			if(duplicate2)
			{
				duplicate2 = false;
				continue;
			}

			users.push_back(username);
 		}
 	}

 	//outputting results
 	cout << "1. Number of tweets=" << num_tweets << endl;
 	cout << "2. Unique users" << endl;
 	for(unsigned int j=0; j<users.size(); j++)
 	{
 		cout << users[j] << endl;
 	}
 	cout << "3. Unique hashtags" << endl;
 	for(unsigned int i=0; i<hashtags.size(); i++)
 	{
 		cout << hashtags[i] << endl;
 	}

}