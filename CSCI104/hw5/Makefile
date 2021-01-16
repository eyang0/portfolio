CC = g++
CPPFLAGS = -g -Wall -std=c++11

all: twitter

twitter: twitter.cpp cmdhandler.o handler.o twiteng.o tweet.o datetime.o util.o user.o setops.o
	$(CC) $(CPPFLAGS) twitter.cpp cmdhandler.o handler.o twiteng.o tweet.o datetime.o util.o user.o setops.o -o twitter

cmdhandler.o: cmdhandler.cpp cmdhandler.h util.h handler.h twiteng.h user.h datetime.h util.h setops.h hsort.h
	$(CC) $(CPPFLAGS) -c cmdhandler.cpp -o cmdhandler.o

handler.o: handler.cpp handler.h twiteng.h user.h datetime.h util.h setops.h hsort.h
	$(CC) $(CPPFLAGS) -c handler.cpp -o handler.o

twiteng.o: twiteng.cpp twiteng.h user.h datetime.h util.h setops.h hsort.h
	$(CC) $(CPPFLAGS) -c twiteng.cpp -o twiteng.o

tweet.o: tweet.cpp tweet.h datetime.h util.h user.h hsort.h
	$(CC) $(CPPFLAGS) -c tweet.cpp -o tweet.o

datetime.o: datetime.cpp datetime.h util.h hsort.h
	$(CC) $(CPPFLAGS) -c datetime.cpp -o datetime.o

util.o: util.cpp util.h tweet.h hsort.h
	$(CC) $(CPPFLAGS) -c util.cpp -o util.o

user.o: user.cpp user.h tweet.h
	$(CC) $(CPPFLAGS) -c user.cpp -o user.o

setops.o: setops.cpp setops.h 
	$(CC) $(CPPFLAGS) -c setops.cpp -o setops.o



clean:
	rm twitter
	rm *.o
	rm *.feed
	rm *.mentions