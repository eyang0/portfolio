#include "tweet.h"
#include "util.h"
#include <sstream>
#include "user.h"

using namespace std;

Tweet::Tweet()
{
	
}

Tweet::Tweet(User* user, const DateTime& time, const std::string& text) :
	_user(user), _time(time), _text(text)
{
	//getting the hashtags from the tweet text
	stringstream ss(text);
	string until_hash;
	while(getline(ss, until_hash, '#'))
	{
		string hashtag;
		ss >> hashtag;
		if(ss.fail())
		{
			ss.clear();
			continue;
		}
		//convert to lowercase
		convLower(hashtag);

		//if hashtag does not yet exist in the tweets hashtags, insert it
		set<string>::iterator it = _hashtags.find(hashtag);
		{
			if(it == _hashtags.end())
			{
				_hashtags.insert(hashtag);
			}
		}
	}
}

bool Tweet::isDM() const
{
	if(!_text.empty())
	{
		if(_text[0] == '@')
		{
			return true;
		}
	}
	return false;
}

DateTime const & Tweet::time() const
{
	return _time;
}

std::string const & Tweet::text() const
{
	return _text;
}

std::set<std::string> Tweet::hashTags() const
{
	return _hashtags;
}

User* Tweet::user() const
{
	return _user;
}

bool Tweet::operator<(const Tweet& other) const
{
	return(this->_time < other._time);
}

  
std::ostream& operator<<(std::ostream& os, const Tweet& t)
{
	os << t._time << " " << t._user->name() << " " << t._text;
	return os;
}





