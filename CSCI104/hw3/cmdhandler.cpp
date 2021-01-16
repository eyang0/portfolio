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

	std::string username;
	std::string content;

	instr >> username;
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	getline(instr, content);
	//Users can have blank tweets
	
	trim(content);
	
	eng->addTweet(username, current_time, content);
	return HANDLER_OK;
}











