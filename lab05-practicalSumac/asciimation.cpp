/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

int main(int argc, char** argv) {
    // write your program here
    string filename;
    string first_argument=argv[1];
    string compare="--reverse";
    int condition=0;
      if (argc==2){
         filename=argv[1];
       }
      else if(argc==3 && first_argument.compare(compare)==0){//ask professor if this is okay
        condition=1;
        filename=argv[2];
      }
      else{
       cout<<"Invalid input"<<endl;
       exit(1);
     }

  List<pair<int, string>>* frames= loadMovie(filename);
    if(condition==0){
        playMovie(frames);
        delete frames;
      }
    else{
        List<pair<int, string>>* reverse_frames = new LinkedList<pair<int,string>>();
        for (int i=0; i<frames->getSize();i++){
          reverse_frames->insertFirst(frames->get(i));

        }

      playMovie(reverse_frames);
        delete frames;
        delete reverse_frames;
     }

    return 0;
}
