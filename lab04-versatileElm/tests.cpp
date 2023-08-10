/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  Distributed as course material for Spring 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>

#include "mergeSort.h"

using namespace std;

TEST(threeElements) {
  // Create a static array containing the numbers 4, 8, 6.
  int array[3] = {4, 8, 6};
  mergeSort(array, 3);
  CHECK_EQUAL(4, array[0]);
  CHECK_EQUAL(6, array[1]);
  CHECK_EQUAL(8, array[2]);
}

TEST(reverseSorted) {
  int size = 20;
  // Create a dynamically-allocated array
  int *array = new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = size - 1 - i;
  }
  mergeSort(array, size);
  for (int i = 0; i < size; i++) {
    CHECK_EQUAL(i, array[i]);
  }
  // de-allocate array
  delete[] array;
  array = nullptr;
}

// This test checks if our algorithm is able to deal with single element arrays.

TEST(single_element) {

  int size=1;
  int* array= new int[size];
  array[0]={1};
  mergeSort(array, size);
  CHECK_EQUAL(1, array[0]);
  delete[] array;
  array = nullptr;
}
// This test checks if our algorithm is able to deal with Null arrays.
TEST(zero_element) {

  int size=0;
  int* array= new int[size];
  mergeSort(array, size);
  CHECK_EQUAL(NULL, array[0]);
  delete[] array;
  array = nullptr;
}


// This test checks if our algorithm is able to deal with arrays that already
//has been sorted
TEST(sorted_array) {

  int size=5;
  int* array= new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = i;
  }
  mergeSort(array, size);
  for (int i = 0; i < size; i++) {
    CHECK_EQUAL(i, array[i]);
  }
  delete[] array;
  array = nullptr;
}
// This test checks if our algorithm is able to deal with arrays that have
// duplicated elements
TEST(duplicated_array) {

  int size=5;
  int array[5] = {4, 8, 4, 6, 6};

  mergeSort(array, size);

  CHECK_EQUAL(4, array[0]);
  CHECK_EQUAL(4, array[1]);
  CHECK_EQUAL(6, array[2]);
  CHECK_EQUAL(6, array[3]);
  CHECK_EQUAL(8, array[4]);

}
// This test checks if our algorithm is able to deal with arrays sorted in
// reverse order
TEST(reverse_sorted_array) {

  int size=5;
  int array[5] = {9,7,5,3,1};
  mergeSort(array, size);
  CHECK_EQUAL(1, array[0]);
  CHECK_EQUAL(3, array[1]);
  CHECK_EQUAL(5, array[2]);
  CHECK_EQUAL(7, array[3]);
  CHECK_EQUAL(9, array[4]);
}

// This test checks if our algorithm is able to deal with arrays
//that are approaching a midpoint 

TEST(midpoint_approaching) {

  int size=1000;
  int* array= new int[size];
  for (int i = 0; i < size; i=i+2) {
    array[i] = i;
  }
  for (int i = 1; i < size; i=i+2) {
    array[i] = 1000-i;
  }
  mergeSort(array, size);

  for (int i = 0; i < size; i++) {
      CHECK_EQUAL(i, array[i]);
  }


}



/* no need to modify main */
int main() {
  return UnitTest::RunAllTests();
}
