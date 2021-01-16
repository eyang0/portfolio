#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile);

// recursive helper function
void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);


void readWords(char* filename,vector<vector<string> >& words)
{
  ifstream ifile(filename);
  if(ifile.fail())
  {
    cout << "File doesn't exist" << endl;
    return;
  }

  int num_lines = 0;
  string current_line;
  while(getline(ifile, current_line))
  {
    num_lines++;
    if(num_lines > 4) //making sure only 4 lines are read
    {
      break;
    }

    vector<string> inner_vec;
    string curr_word;
    stringstream ss(current_line); 

    while(ss >> curr_word)
    {
      inner_vec.push_back(curr_word);
    }
    words.push_back(inner_vec);
  }

  ifile.close();
}


void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
  int num_of_sentences = 0;
  genHelper(words, ofile, 0, "The", num_of_sentences);
  ofile << num_of_sentences << " sentences." << endl;
}


void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences)
{
  if(currentOption >= 4) //if we hit the base case, output sentence
  {
    ofile << sentence + "." << endl;
    numSentences++;
  }
  else
  {
    if(words[currentOption].empty())
    {
      genHelper(words, ofile, currentOption+1 , sentence, numSentences);
    }
    else
    {
      //adding sentences without adjectives or adverbs or both
      if(currentOption == 0 || currentOption == 3)
      {
        genHelper(words, ofile, currentOption+1 , sentence, numSentences);
      }

      //recurse to use every option for the type of word
      for(unsigned int i = 0; i < words[currentOption].size(); i++)
      {
        genHelper(words, ofile, currentOption+1, sentence + " " + 
          words[currentOption][i], numSentences);
      }
    }
  }
}


int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
