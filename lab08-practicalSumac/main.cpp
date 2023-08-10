/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <vector>

#include "keywordSearcher.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc<2){
    cout << "Run the function again with a valid input" << endl;
    return 0;
  }


  string filename = argv[1];
  KeywordSearcher* ks = new KeywordSearcher();
  //load the file
  ks->loadWords(filename);

  string word;
  vector<pair<int, int>> items;

  //while the user does not want to quit
  while(word!="!"){
    cout << "Please enter a search word or '!' to quit: ";
    cin>>word;
    //call the search method
    items=ks->search(word);
    //if the item vector has something in it
    if(items.size()!=0){

      cout << "The word " << word << " appears in the file..." << endl;

      //we print out the top 10 or less occurences
      for(int i=0;i<items.size();i++){
        cout << "on page " << items[i].first << "( " << items[i].second << " occurrences)" << endl;
       }
    }
    else if(word == "!"){
      //do nothing
    }

    else{
      cout<<"The word " << word << " does not appear in the file." << endl;
    }
  }

  cout << "Goodbye!" << endl;
  delete ks;


  return 0;
}
