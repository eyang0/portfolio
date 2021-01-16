#include "datetime.h"
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

DateTime::DateTime()
{
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	this->year = timeinfo->tm_year + 1900;
	this->month = timeinfo->tm_mon + 1;
	this->day = timeinfo->tm_mday;
	this->hour = timeinfo->tm_hour;
	this->min = timeinfo->tm_min;
	this->sec = timeinfo->tm_sec;

}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day) :
	hour(hh), min(mm), sec(ss), year(year), month(month), day(day)
{

}

bool DateTime::operator<(const DateTime& other) const
{
	//comparing components of DateTime
	if(year < other.year)
	{
		return true;
	}
	if(year == other.year)
	{
		if(month < other.month)
		{
			return true;
		}
		if(month == other.month)
		{
			if(day < other.day)
			{
				return true;
			}
			if(day == other.day)
			{
				if(hour < other.hour)
				{
					return true;
				}
				if(hour == other.hour)
				{
					if(min < other.min)
					{
						return true;
					}
					if(min == other.min)
					{
						if(sec < other.sec)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}


std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
	//although it seems unlikely that we would date a tweet before the year 2000
	if(other.year < 10)
	{
		os << 0;
	}
	if(other.year < 100)
	{
		os << 0;
	}
	if(other.year < 1000)
	{
		os << 0;
	}
	os << other.year << "-";

	if(other.month < 10)
	{
		os << 0;
	}
	os << other.month << "-";
	if(other.day < 10)
	{
		os << 0;
	}
	os << other.day << " ";
	if(other.hour < 10)
	{
		os << 0;
	}
	os << other.hour << ":";
	if(other.min < 10)
	{
		os << 0;
	}
	os << other.min << ":";
	if(other.sec < 10)
	{
		os << 0;
	}
	os << other.sec;

	return os;
}

//gets timestamp from istream, expecting YYYY-MM-DD HH:MM:SS
std::istream& operator>>(std::istream& is, DateTime& dt)
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	string chunk;
	int current_num;

	//extracting the date and time from input istream until there is an error
	//if there is an error, uses current time
	if(is >> chunk)
	{
		stringstream ss(chunk);
		if(ss >> current_num)
		{
			year = current_num;
			char junk;
			if(ss >> junk)
			{
				if(junk == '-' && ss >> current_num)
				{
					month = current_num;
					if(ss >> junk)
					{
						if(junk == '-' && ss >> current_num)
						{
							day = current_num;
							if(is >> chunk)
							{
								stringstream s2(chunk);
								if(s2 >> current_num)
								{
									hour = current_num;
									if(s2 >> junk)
									{
										if(junk == ':' && s2 >> current_num)
										{
											min = current_num;
											if(s2 >> junk)
											{
												if(junk == ':' && s2 >> current_num)
												{
													sec = current_num;

													dt.year = year;
													dt.month = month;
													dt.day = day;
													dt.hour = hour;
													dt.min = min;
													dt.sec = sec;
													return is;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//if there is an error, use current time
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	dt.year = timeinfo->tm_year + 1900;
	dt.month = timeinfo->tm_mon + 1;
	dt.day = timeinfo->tm_mday;
	dt.hour = timeinfo->tm_hour;
	dt.min = timeinfo->tm_min;
	dt.sec = timeinfo->tm_sec;

	return is;
}

