#include "cmdhandler.h"
#include "util.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next) 
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}



AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next) 
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::vector<std::string> search_terms;
	std::string term;
	while(instr >> term)
	{
		search_terms.push_back(term);
	}
	eng->search(search_terms, 0);
	return HANDLER_OK;
}


OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::vector<std::string> search_terms;
	std::string term;
	while(instr >> term)
	{
		search_terms.push_back(term);
	}
	eng->search(search_terms, 1);
	return HANDLER_OK;
}


TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::string username;
	std::string content;

	instr >> username;
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	if(!eng->userExists(username))
	{
		return HANDLER_ERROR;
	}
	getline(instr, content);
	//Users can have blank tweets
	
	trim(content);

	//make a current time DateTime
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	int year = timeinfo->tm_year + 1900;
	int month = timeinfo->tm_mon + 1;
	int day = timeinfo->tm_mday;
	int hour = timeinfo->tm_hour;
	int min = timeinfo->tm_min;
	int sec = timeinfo->tm_sec;

	DateTime current_time(hour, min, sec, year, month, day);
	
	eng->addTweet(username, current_time, content);
	return HANDLER_OK;
}


FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
  : Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::string user1;
	std::string user2;
	std::string extra_users;

	instr >> user1;
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	instr >> user2;
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	//if there are extra users, we ignore the whole command (from Ed)
	instr >> extra_users;
	if(!instr.fail())
	{
		return HANDLER_ERROR;
	}

	if(!eng->userExists(user1))
	{
		cout << "addFollow() " << user1 << " is not a current user" << endl;
		return HANDLER_ERROR;
	}
	if(!eng->userExists(user2))
	{
		cout << "addFollow() " << user2 << " is not a current user" << endl;
		return HANDLER_ERROR;
	}

	eng->addFollow(user1, user2);
	return HANDLER_OK;
}


SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
  : Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::string filename;
	std::string extra_string;

	instr >> filename;
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	//if there is extra stuff on the line (incorrect format), we ignore the command
	instr >> extra_string;
	if(!instr.fail())
	{
		return HANDLER_ERROR;
	}

	eng->save_to_file(filename);

	return HANDLER_OK;
}



