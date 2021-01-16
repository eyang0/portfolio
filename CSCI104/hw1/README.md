To compile **sum_pairs**:  
g++ -g -Wall -std=c++11 sum_pairs.cpp -o sum_pairs

To run **sum_pairs**:  
./sum_pairs (input.txt or other input text file) (output.txt or other output text file)


To compile **tweet_parse**:  
g++ -g -Wall -std=c++11 tweet_parse.cpp -o tweet_parse

To run **tweet_parse**:  
./tweet_parse (tweets.txt or other text file)


To compile **str_test**:  
g++ -g -Wall -std=c++11 str.cpp str_test.cpp -o str_test

To run **str_test**:  
./str_test 

str_test will ask for string to be entered through the keyboard  

- In sum_pairs, a dynamically allocated array of ints was used to hold the integers from the input file
- In tweet_parse, vectors were used to hold both the unique users and unique hashtags that were found
- In str_test, necessary functions were added to create the Str class
