#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string*  readFile(string filename){

  ifstream myfile;
  myfile.open(filename);
  int numberOfWords;
  myfile >> numberOfWords;
  string* words =new string[numberOfWords];
  for(int i=0;i<numberOfWords;i++){
    myfile >>words[i];
    }
  myfile.close();
  return words;
}

int size_file(string filename){
  ifstream myfile;
  myfile.open(filename);
  int numberOfWords;
  myfile>> numberOfWords;
  myfile.close();
  return numberOfWords;
}

int main(){


  string* myfile = readFile("data.txt");
  int numberOfWords=size_file("data.txt");
  for (int i= numberOfWords-1;i>=0;i--){
    cout<<myfile[i]<<endl;
  }
  delete[] myfile;
  return 0;
}
