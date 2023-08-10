  /*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>
#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

List<pair<int, string>>* loadMovie(string filename) {
  cout<<filename<<endl;
  ifstream myFile;
  string data;
  myFile.open(filename);
  getline(myFile, data);


  LinkedList<pair<int,string>>* frames = new LinkedList<pair<int,string>>();


  while (!myFile.eof()) {
    int frame_time= stoi(data);
    string frame_string= "";
    for (int i=0;i<13;i++){
      getline(myFile, data);
      frame_string += data ;
      frame_string +="\n";
     }
    pair<int,string> current_frame(frame_time,frame_string);
    frames->insertLast(current_frame);
    getline(myFile, data);

  }

return frames;
}

void playMovie(List<pair<int, string>>* list) {
    int count=0;
    int size_list=list->getSize();

    while(count<size_list) {
      pair<int, string> frame=list->get(count);

      cout << frame.second  << endl;

      usleep((1000000/15)*frame.first);
      system("clear");


      count++;
    }
}
