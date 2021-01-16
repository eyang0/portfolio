#include "user.h"
#include <algorithm>
#include "tweet.h"
#include <sstream>
#include "hsort.h"

using namespace std;



User::User(std::string name) :
	_username(name)
{

}


User::~User()
{
	for(list<Tweet*>::iterator it = _tweets.begin(); it != _tweets.end(); ++it)
	{
		//deallocates what the pointer is pointing to: the tweets of the user
		delete *it;
	}
}


std::string User::name() const
{
	return _username;
}


std::set<User*> User::followers() const
{
	return _followers;
}

std::set<User*> User::following() const
{
	return _following;
}

std::list<Tweet*> User::tweets() const
{
	return _tweets;
}

void User::addFollower(User* u)
{
	set<User*>::iterator it = _followers.find(u);
	{
		//if follower hasn't been recorded, insert
		if(it == _followers.end())
		{
			_followers.insert(u);
		}
	}
}

void User::addFollowing(User* u)
{
	set<User*>::iterator it = _following.find(u);
	{
		//if following hasn't been recorded, insert
		if(it == _following.end())
		{
			_following.insert(u);
		}
	}
}

void User::addTweet(Tweet* t)
{
	_tweets.push_back(t);
}


//to get main feed in timestamp order
std::vector<Tweet*> User::getFeed()
{
	vector<Tweet*> to_return;
	//getting the user's own authored tweets
	for(list<Tweet*>::iterator it = _tweets.begin(); it != _tweets.end(); ++it)
	{
		to_return.push_back(*it);
	}

	//getting the main feed tweets of who the user is following
	for(set<User*>::iterator it2 = _following.begin(); it2 != _following.end(); ++it2)
	{
		list<Tweet*> temp = (*it2)->tweets();
		for(list<Tweet*>::iterator it3 = temp.begin(); it3 != temp.end(); ++it3)
		{
			//add if it is not a DM
			if(!(*it3)->isDM())
			{
				to_return.push_back(*it3);
			}
			//if it is a DM, only add if both users are following each other
			else
			{
				//first check if the first mention is the User
				string mention;
				char at_symbol;
				stringstream ss((*it3)->text());
				ss >> at_symbol;
				ss >> mention;
				if(!ss.fail())
				{
					if(mention == this->name())
					{
						//if both users follow each other, add tweet to main feed 
						if(_followers.find(*it2) != _followers.end())
						{
							to_return.push_back(*it3);
						}
					}
				}
			}
		}
	}
	//sorting tweets in timestamp order
	hsort(to_return, TweetComp());
	return to_return;
}

//to get mentions feed in timestamp order
std::vector<Tweet*> User::getMentions()
{

	vector<Tweet*> to_return;
	//getting tweets where user is mentioned
	for(list<Tweet*>::iterator it = _mentions.begin(); it != _mentions.end(); ++it)
	{
		to_return.push_back(*it);
	}

	//sorting tweets in timestamp order
	hsort(to_return, TweetComp());
	return to_return;
}

void User::addMention(Tweet* t)
{
	_mentions.push_back(t);
}






