/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  Distributed as course material for Spring 2019
  CPSC 035: Data Structures and Algorithms
*/
#include <iostream>
#include <string>
#include "mergeSort.h"
using namespace std;
/*
input: this function takes in 3 pointers to our original array, and the
two new arrays respectively,and two integers describing the numbers of
elements in the new arrays we made for sorting
Function:this function copies out the appropriate members of our original array
into the two sub arrays by going through two for loops(one for each sub array)
Return: Nothing
*/

void split(int* c,int* a, int* b,int asize, int bsize){
  for( int i=0;i<asize;i++){
    a[i]=c[i];
  }
  for(int j=0; j<bsize;j++){
    b[j] = c[j+asize];
  }
}
/*
input: this function takes in 3 pointers to our original array, and the
two sub-arrays respectively,and two integers describing the numbers of
elements in the two sub arrays
Function:this function copies out the members of the sorted arrays into our main
array
Return: Nothing
*/
void Merge(int* c, int* a, int* b, int asize, int bsize){
  int i =0;
  int j =0;
  int k=0;
  while (i<asize && j<bsize){
    if(a[i]<b[j]){
      c[k] = a[i];
      i = i+1;
      k++;
    }
    else{
      c[k] = b[j];
      j++;
      k++;
    }
  }
  while(i<asize){
    c[k] = a[i];
    i++;
    k++;
  }
  while(j<bsize){
    c[k] = b[j];
    j++;
    k++;
  }
}

/*
input: this function takes in a pointer to an array and an integer describing
the number of elements in our array
Function:It makes up two arrays of appropriate size, calls the split function to
copy out elements from input array to the new arrays it made, and then calls
mergesort recursively.It then merges the two arranged arays into a big file.
Return: Nothing
*/
void mergeSort(int *array, int length) {
  if(length<=1){
      return;
  }
  else{

      int asize = length/2;
      int bsize = length/2;

    if(length%2!=0){
      bsize = bsize+1;
    }
    int* arrayA = new int[asize];
    int* arrayB = new int[bsize];
    split(array,arrayA,arrayB,asize,bsize);
    mergeSort(arrayA,asize);
    mergeSort(arrayB,bsize);
    Merge(array, arrayA, arrayB,asize, bsize);
  }

}
