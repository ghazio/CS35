/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "keywordSearcher.h"
#include "./adts/stlMaxPriorityQueue.h"
#include <stdexcept>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

KeywordSearcher::KeywordSearcher() {
  //we decalare our new hash table
  this->wordtable= new HashTable<string,HashTable<int,int>*>();

}

KeywordSearcher::~KeywordSearcher() {

  vector<pair<string,HashTable<int,int>*>> keys=this->wordtable->getItems();
  //while we still have elements in hashtable left

  for(int i =0; i < keys.size();i++){
    delete keys[i].second;
  }

  // delete the main hashtable
  delete this->wordtable;
}


void KeywordSearcher::loadWords(string filename) {
  int check = 0;
  int page_number;
  ifstream myFile;
  //open the file
  myFile.open(filename);


  //this was us trying to handle the file name being valid or not
  // if(myFile.is_open()){
  //   cout<<"file loaded"<<endl;
  // }
  // else{
  //   cout<<"file name invalid"<<endl;
  // }

  string word;
  //copy a word
  myFile >> word;
  //while we do not reach end of file
  while (!myFile.eof()){
    //if the word is a page marker,
    if(word == "$$@@$$PAGE:"){
      //read in the next word and convert it to an integer
      myFile >> word;
      page_number = stoi(word);
    }else{
      //add the word to our table
      adder(word,page_number);

    }
    //go to the next file
    myFile >> word;
  }
  //close the file
  myFile.close();
}

vector<pair<int, int>> KeywordSearcher::search(string word) {

  //if the table does not contain the file
  if(!(this->wordtable->contains(word))){
    //return an empty vector cuz the word does not exist
    vector<pair<int, int>> empty_vector;
    return empty_vector;  
  }
  //otherwise if the word exists in the dictionary
  else{
    //we get the vector of pairs of the occurences page number pair values
    vector<pair<int, int>> temp_vector;
    temp_vector=this->wordtable->get(word)->getItems();

    //we flip the arrangement of the first and second variables
    for(int a = 0; a<temp_vector.size();a++){
      //stores the page number
      // cout << temp_vector[a].first << endl;
      int temp_value=temp_vector[a].first;
      //stores the number of occurrences as the first
      temp_vector[a].first = temp_vector[a].second;
      temp_vector[a].second = temp_value;

    }

    vector<pair<int, int>> final_vector;

    //we input our vector into the priority queue
    STLMaxPriorityQueue<int, int>* myqueue= new STLMaxPriorityQueue<int, int>(temp_vector);

    int k = myqueue->getSize();
    int counter = 0;
    //if we have more than 10 elements
    if(k >10){
    //set size to 10
     k=10;
    }
    //for the top ten elements of our priority queue
    for(int a=0; a < k;a++){
      //we peek both the page number and the occurences of the element
      //with wthe most priority
      int page_number=myqueue->peek();
      int occurrences=myqueue->peekPriority();

      myqueue->remove();
      pair<int,int> new_pair;
      //we copy over our page number and occurences
      new_pair.first=page_number;
      new_pair.second=occurrences;
      final_vector.push_back(new_pair);
    }
    //increment our counter
    counter ++;
    //delete the priority list
    delete myqueue;
    //return the final vector
    return final_vector;
  }
}

void KeywordSearcher::adder(string word, int page_number){

  //if the word isn't in the word table
   if(!(this->wordtable->contains(word))){
     // we create a new hashtable for that word
      HashTable<int,int>* newhashtable=new HashTable<int,int>();
      this->wordtable->insert(word,newhashtable);
      newhashtable->insert(page_number,1);
   }

   //if the word is already in the word table
   else{
     //if the word was read before on the same page
     if(this->wordtable->get(word)->contains(page_number)){
       // we go into the hash table for the word and increment by 1
       this->wordtable->get(word)->update(page_number,(this->wordtable->get(word)->get(page_number)+1)
     );
     //else we make a new entry into the hash table for the word
     }else{
      this->wordtable->get(word)->insert(page_number,1);
     }
   }
}
