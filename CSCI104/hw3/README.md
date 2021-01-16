To compile **twitter**:  
make

To run **twitter**:  
./twitter (input file)

**User Interface**:  
AND (hashtags separated by spaces) - Search for tweets with certain hashtags using AND strategy  
OR (hashtags separated by spaces) - Search for tweets with certain hashtags using OR strategy  
TWEET (username) (tweet text) - Create a tweet  
QUIT - Quit and output files for each User's feed  

To clean up files:  
make clean


setops.cpp and setops.h were added to deal with set operations  

Given an input file with twitter data, twitter will parse the data to obtain information about users and user relationships, tweets, and hashtags. Then, using the user interface, one can search for tweets that contain certain hashtags using the AND and OR strategies. Upon quitting, users' feeds will be output to files named username.feed

Note: Users can have blank tweets