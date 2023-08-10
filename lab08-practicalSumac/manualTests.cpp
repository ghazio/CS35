/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

#include "keywordSearcher.h"

using namespace std;



int main(int argc, char** argv) {

      KeywordSearcher* ks= new KeywordSearcher();
      ks->loadWords("test_data/small.txt");
      
      delete ks;
}
