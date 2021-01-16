#include "twiteng.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "util.h"
#include "setops.h"

using namespace std;

TwitEng::TwitEng()
{

}
TwitEng::~TwitEng()
{
	//deallocating the users and along with them, their tweets
	for(set<User*>::iterator set_it = all_users.begin(); set_it != all_users.end(); ++set_it)
	{
		delete *set_it;
	}
}

bool TwitEng::parse(char* filename)
{
 	ifstream ifile(filename);
 	if(ifile.fail())
 	{
 		return true;
 	}

 	int num_users;
 	ifile >> num_users;
 	if(ifile.fail())
 	{
 		return true;
 	}

 	int num_users_recieved = 0;
 	string current_line;
 	while(num_users_recieved < num_users)
 	{
 		getline(ifile, current_line);
 		//if it is an empty line, get next line
 		if(current_line.empty())
 		{
 			continue;
 		}

 		stringstream ss(current_line);
 		string username;
 		ss >> username;
 		if(ss.fail())
 		{
 			return true;
 		}

 		set<string> following;
 		//if the username has not been added yet, create User and add User
 		//this allows for multiple rows of information on the same user
 		if(name_to_userptr.find(username) == name_to_userptr.end())
 		{
 			User* user_to_add = new User(username);
 			name_to_userptr.insert(make_pair(username, user_to_add));
 			all_users.insert(user_to_add);
 			name_to_following.insert(make_pair(username, following));
 			num_users_recieved++;
 		}
 		string name;
 		while(ss >> name)
 		{
 			following.insert(name);
 		}
 		//checking if following relationships have been previously recorded. If not, insert it
 		map<string, set<string>>::iterator current_followings = name_to_following.find(username);
 		for(set<string>::iterator new_names = following.begin(); new_names != following.end(); ++new_names)
 		{
 			if((current_followings->second).find(*new_names) == current_followings->second.end())
 			{
 				(current_followings->second).insert(*new_names);
 			}
 		}
 	}
 	//finishing the user and follow relationships by adding to User
 	map<string, set<string>>::iterator map_it;
 	for(map_it = name_to_following.begin(); map_it != name_to_following.end(); ++map_it)
 	{
 		User* current_user = (name_to_userptr.find(map_it->first))->second;

 		//iterating through the set of followings for current_user
 		set<string>::iterator set_it;
 		for(set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it)
 		{
 			//grabbing the pointer to each user that current_user is following
 			User* temp = (name_to_userptr.find(*set_it))->second;
 			(*current_user).addFollowing(temp);
 			temp->addFollower(current_user);
 		}
 	}
 	//getting the tweets
 	while(getline(ifile, current_line))
 	{
 		//if it is an empty line, get next line
 		if(current_line.empty())
 		{
 			continue;
 		}
 		stringstream s2(current_line);
 		DateTime temp_time;
 		string temp_username;
 		string temp_text;

 		s2 >> temp_time;
 		if(s2.fail())
 		{
 			return true;
 		}
 		s2 >> temp_username;
 		if(s2.fail())
 		{
 			return true;
 		}
 		getline(s2, temp_text);
 		//Users can have blank tweets

 		trim(temp_text);

 		addTweet(temp_username, temp_time, temp_text);
 	}

 	ifile.close();
 	return false;
}


void TwitEng::addTweet(const std::string& username, const DateTime& time, const std::string& text)
{
	User* temp_user;
	map<string, User*>::iterator username_it = name_to_userptr.find(username);
	
	//if user doesn't exist yet, add the user
	if(username_it == name_to_userptr.end())
	{
		temp_user = new User(username);
 		name_to_userptr.insert(make_pair(username, temp_user));
 		all_users.insert(temp_user);

 		set<string> empty_set;
 		name_to_following.insert(make_pair(username, empty_set)); 
	}
	//if user already exists, get User pointer and add tweet to User's tweets
	else
	{
		temp_user = username_it->second;
	}
	Tweet* tweet_to_add = new Tweet(temp_user, time, text);
	temp_user->addTweet(tweet_to_add);

	//dealing with mentions
	string mention;
	stringstream ss(tweet_to_add->text());
	if(tweet_to_add->isDM()) //if it is a DM
	{
		char at_symbol;

		ss >> at_symbol;
		ss >> mention;
		//ignore mention if there is a format error
		if(!ss.fail())
		{
			map<string, User*>::iterator to_mention = name_to_userptr.find(mention);
			//ignore mention if tweet mentions a User that doesn't exist
			if(to_mention != name_to_userptr.end())
			{
				to_mention->second->addMention(tweet_to_add);
			}
		}
	}
	else //if it is not a DM
	{
		//go through and find all mentions and add them
		string until_at;
		while(getline(ss, until_at, '@'))
		{
			ss >> mention;
			if(ss.fail()) //ignore mention if there is a format error
			{
				ss.clear();
				continue;
			}
			map<string, User*>::iterator to_mention = name_to_userptr.find(mention);
			//ignore mention if that User doesn't exist
			if(to_mention != name_to_userptr.end())
			{
				to_mention->second->addMention(tweet_to_add);
			}
		}
	}
	
	//adding hashtags to the index of hashtags and their matching tweets
	set<string> hashtags = tweet_to_add->hashTags();
	for(set<string>::iterator it = hashtags.begin(); it != hashtags.end(); ++it)
	{
		map<string, set<Tweet*>>::iterator map_it = hashtags_to_tweetptr.find(*it);
		//if the hashtag doesn't exist yet, insert it in map
		if(map_it == hashtags_to_tweetptr.end())
		{
			set<Tweet*> first_tweet;
			first_tweet.insert(tweet_to_add);
			hashtags_to_tweetptr.insert(make_pair(*it, first_tweet));
		}
		//if the hashtags already exists, add tweet to set
		else
		{
			map_it->second.insert(tweet_to_add);
		}
	}
}


//to search for tweets using hashtags. Strategy 0 is AND, strategy 1 is OR
vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
	vector<Tweet*> to_return;
	set<Tweet*> result;

	if(strategy != 0 && strategy != 1)
	{
		cout << "strategy not found" << endl;
		displayHits(to_return);
		return to_return;
	}

	for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
	{
		string current_hashtag = *it;
		convLower(current_hashtag);
		set<Tweet*> current_set;
		map<string, set<Tweet*>>::iterator map_it = hashtags_to_tweetptr.find(current_hashtag);
		//if the hashtag exists, get the set of Tweet pointers that match
		if(map_it != hashtags_to_tweetptr.end())
		{
			current_set = map_it->second;
		}

		//if it is the first iteration
		if(it == terms.begin())
		{
			result = current_set;
			continue;
		}
		if(strategy == 0)
		{
			//find intersection
			result = result & current_set;
		}
		else
		{
			//find union
			result = result | current_set;
		}
	}

	//fill in vector using the set of Tweet pointers
	for(set<Tweet*>::iterator set_it = result.begin(); set_it != result.end(); ++set_it)
	{
		to_return.push_back(*set_it);
	}
	displayHits(to_return);
	
	return to_return;
}


void TwitEng::dumpFeeds()
{
	set<User*>::iterator it;
	for(it = all_users.begin(); it != all_users.end(); ++it)
	{
		//creating output files
		string username = (*it)->name();
		string temp = username + ".feed";
		string temp2 = username + ".mentions";

		char* ofile_name = new char[temp.length()+1];
		for(unsigned int i = 0; i < temp.length(); i++)
		{
			ofile_name[i] = temp[i];
		}
		ofile_name[temp.length()] = '\0';
		ofstream ofile(ofile_name);

		char* ofile_name2 = new char[temp2.length()+1];
		for(unsigned int j = 0; j < temp2.length(); j++)
		{
			ofile_name2[j] = temp2[j];
		}
		ofile_name2[temp2.length()] = '\0';
		ofstream ofile2(ofile_name2);
		
		//dumping main feed
		ofile << username << endl;
		vector<Tweet*> temp_vec = (*it)->getFeed();
		for(vector<Tweet*>::iterator it2 = temp_vec.begin(); it2 != temp_vec.end(); ++it2)
		{
			//output each tweet in order
			ofile << *(*it2) << endl;
		}

		//dumping mentions feed
		ofile2 << username << endl;
		vector<Tweet*> temp_vec2 = (*it)->getMentions();
		for(vector<Tweet*>::iterator it_mentions = temp_vec2.begin(); it_mentions != temp_vec2.end(); ++it_mentions)
		{
			//output each tweet in order
			ofile2 << *(*it_mentions) << endl;
		}

		ofile.close();
		ofile2.close();
		delete [] ofile_name;
		delete [] ofile_name2;
	}
}

//checks if a user exists
bool TwitEng::userExists(const std::string& username)
{
	if(name_to_userptr.find(username) == name_to_userptr.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}


void TwitEng::addFollow(const std::string& user1, const std::string& user2)
{
	map<string, User*>::iterator first_user = name_to_userptr.find(user1);
	map<string, User*>::iterator second_user = name_to_userptr.find(user2);

	//if the relationship doesn't already exist
	if((name_to_following.find(user1)->second).find(user2) == (name_to_following.find(user1)->second).end())
	{
		(first_user->second)->addFollowing(second_user->second);
		(second_user->second)->addFollower(first_user->second);

		(name_to_following.find(user1)->second).insert(user2);
	}
}


void TwitEng::save_to_file(const std::string& file)
{
	char* ofile_name = new char[file.length()+1];
	for(unsigned int i = 0; i < file.length(); i++)
	{
		ofile_name[i] = file[i];
	}
	ofile_name[file.length()] = '\0';

	ofstream ofile(ofile_name);

	//outputting number of users
	ofile << name_to_following.size() << endl;

	//outputting users and who they are following
	map<string, set<string>>::iterator it;
	for(it = name_to_following.begin(); it != name_to_following.end(); ++it)
	{
		//output the name
		ofile << it->first;
		//output who the user is following
		set<string>::iterator set_it;
		for(set_it = it->second.begin(); set_it != it->second.end(); ++set_it)
		{
			ofile << " " << *set_it; 
		}
		ofile << endl;
	}

	//outputting tweets
	set<User*>::iterator userptr_it;
	for(userptr_it = all_users.begin(); userptr_it != all_users.end(); ++userptr_it)
	{
		list<Tweet*> temp = (*userptr_it)->tweets();
		for(list<Tweet*>::iterator tweet_it = temp.begin(); tweet_it != temp.end(); ++tweet_it)
		{
			ofile << *(*tweet_it) << endl;
		}
	}

	ofile.close();
	delete [] ofile_name;
}


