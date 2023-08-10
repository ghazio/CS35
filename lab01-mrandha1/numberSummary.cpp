/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/*
Input: Takes in the file name
Funtion: Opens the file. Reads the first integer, and then run a loop to read
        every other integer in the file and stores it in an array
Output: Returns a pointer to an array containing the data
*/

int*  readFile(string filename){

  ifstream myfile;
  myfile.open(filename);
  int numberOfWords;
  myfile >> numberOfWords;
  int* words = new int[numberOfWords];
  for(int i=0;i<numberOfWords;i++){
    myfile >>words[i];
    }

  myfile.close();
  return words;
}
/*
Input: Takes in the name of the file
Funtion: Finds out the first integer of the file amd saves it
Output: Returns the number of integers in the file
*/

int counter(string filename){
  ifstream myfile;
  myfile.open(filename);
  int numberOfWords;
  myfile>> numberOfWords;
  myfile.close();
  return numberOfWords;
}
/*
Input: pointer to data array and the number of integers
Funtion: Finds out the largest integer
Output: Returns the largest integer
*/
int largest(int* data, int count){

    int largest_int=data[0];
    for(int i=0;i<count;i++){
      if (data[i]>largest_int){
        largest_int=data[i];
      }
    }
    return largest_int;
}


/*
Input: Takes in the pointer to the data array, the number of integers, and the
largest integer in the list
Funtion: Finds out the second largest integer
Output: Returns the second largest integer
*/

int second_largest(int* data, int count,int largest){

    int second_largest_int=data[0];
    if (second_largest_int==largest){
      second_largest_int=data[1];
    }
    for(int i=1;i<count;i++){
      if (data[i]>second_largest_int && data[i] < largest){
        second_largest_int=data[i];
      }
    }
    return second_largest_int;
}



/*
Input: Takes in the string to the data array, and the number of integers
Funtion: Calculates the mean of the data in the array
Output: Returns the mean of the data
*/

float mean(int* data, int count){
    float sum=0;
    for(int i=0;i<count;i++){
      sum=sum+data[i];
    }
    float mean_data=sum/count;
    return mean_data;
}

int main() {
    cout <<"Please enter a file name:"<<endl;
    string filename;
    cin >> filename;//stores the name of the file provided by the user


    //calls the readFile function and saves the returned pointer
    int* numbers=readFile(filename);

    int n_numbers=counter(filename);//saves the number of integers in the file

    //stores the largest integer by calling the approppriate function
    int largest_int=largest(numbers,n_numbers);
    //stores the second largest integer by calling the approppriate function
    int second_largest_int=second_largest(numbers,n_numbers,largest_int);
    //stores the calculated mean of the numbers
    float mean_data=mean(numbers,n_numbers);
    //stores the last integer in the data
    int last_int=numbers[n_numbers-1];
    //prints as required
    cout <<"Last integer is: " << last_int<< endl;
    cout <<"Largest integer is: " << largest_int<< endl;
    cout <<"Second largest integer is: " << second_largest_int<< endl;
    cout <<"Mean of the data is: " << mean_data << endl;

    return 0;
}
