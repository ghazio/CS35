/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "hashFunctions.h"
#include "linearDictionary.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    this -> size = 0;
    //we initialise our capacity to 10
    this -> capacity = 10;
    this -> load_factor = size/capacity;

    //we declare a dynamic array of pointers to linear dicitionaries
    this->array = new LinearDictionary<K,V>*[this->capacity];

    //we allocate a dictionary for each element of our array
    for  (int i=0; i<this->capacity;i++){
      this->array[i] = new LinearDictionary<K,V>();
    }
    //this is our max load factor if one is not given
    this->maxLoadFactor = .75;

}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {

  this -> size = 0;
  //we initialise our capacity to 10
  this -> capacity = 10;
  this -> load_factor = size/capacity;

  //we declare a dynamic array of pointers to linear dicitionaries
  this->array = new LinearDictionary<K,V>*[this->capacity];

  //we allocate a dictionary for each element of our array
  for  (int i=0; i<this->capacity;i++){
        this->array[i] = new LinearDictionary<K,V>*();
  }

  //this is our max load factor
  this->maxLoadFactor = maxLoadFactor;
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
  //we delete each of the linear dictionaries
  for  (int i=0; i<this->capacity;i++){
    delete this->array[i] ;
  }
  //we delete the main array
  delete[] this->array;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
  //return the size
    return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
//if there are no key/value pairs in the entire has table,
  if(this->size ==0){
    //we return 1
    return 1;
  }
  //otherwise we return 0
  return 0;
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {

  int index;
  float temp_size=this->size;
  float temp_capacity=this->capacity;
  float temp_factor = (temp_size + 1)/(temp_capacity);


  //if the load factor will increase with new addition, we call expandCapacity()
  if (temp_factor > this->maxLoadFactor){
    expandCapacity();
  }

  //find the appropriate hash index and then insert it that place
  index = hash(key,this->capacity);
  this->array[index]-> insert(key,value);
  //increment the size and update the load factor
  this->size++;
  this->load_factor = this->size/this->capacity;
}

template <typename K, typename V> void HashTable<K, V>::expandCapacity() {

   int index;
   //we declare an array of pointers to a linear dictionary with double the capcacity
   //and allocate dictionaries to them
   LinearDictionary<K,V>** new_array = new LinearDictionary<K,V>*[2*this->capacity];
   for  (int i=0; i<2*(this->capacity);i++){
     new_array[i] = new LinearDictionary<K,V>();
   }


   LinearDictionary<K,V>** old_array = this->array;
   this->array = new_array;
   int new_capacity = 2*this->capacity;
   vector<pair<K,V>> items;

   //for each linear dicionary in our old array
   for (int i=0; i<this->capacity;i++){
    //we get its items and then copy them to their new linear dictionary in the
    //new array using the appropriate index by calling hash
    items = old_array[i]->getItems();
     for (int j=0; j< items.size(); j++){
       index = hash(items[j].first,new_capacity);
       this->array[index]->insert(items[j].first,items[j].second);
     }
   }
   //we delete each of the old linear dictionary in our array
   for  (int i=0; i<this->capacity;i++){
     delete old_array[i];
   }

   //we delete the old array
   delete[] old_array;
   //we update our capcacity in the object
   this->capacity = 2*this->capacity;

}



template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
  //if there is nothing,
  if(this->size==0){
    throw runtime_error("there is nothing in the hash table.");
  }

  //we find the correct index and then update the value
  int index;
  index = hash(key,this->capacity);
  this->array[index]->update(key,value);
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {

  if(this->size==0){//if empty
    throw runtime_error("there is nothing in the hash table.");
  }
  //we find the index of the linear dictionary and then search in that dictionary
  V value;
  int index;
  index = hash(key,this->capacity);
  value=this->array[index]->get(key);
  return value;
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {

  if(this->size==0){//if empty
    return false;
  }

  //we find the appropriate index
  int index;
  index = hash(key,this->capacity);
  //if the linear dictionary at that index in hash table contains the key
  if (this->array[index]->contains(key) == true){
    return true;

    }
  else{
    return false;
    }
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {


  //if empty
  if(this->size==0){
    throw runtime_error("there is nothing in the hash table.");
  }
  //we find the appropriate index
  int index;
  index = hash(key,this->capacity);
  //we go and try to delete the element with key in linear dictionary

  this->array[index]->remove(key);
  this->size--;
  this->load_factor = this->size/this->capacity;
}
template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
  vector<K> keys;
  //if there is nothing, return an empty vector
  if(this->size==0){
    return keys;
  }

  //for each linear dictionary,
  for (int i=0; i < this->capacity;i++){
      //if that is not empty
      if(!this->array[i]->isEmpty()){
      //we get keys for that linear dictionary
      //and return the appropriate vector.
      vector<K> temp_vector;
      temp_vector = this->array[i]->getKeys();
      for (int j=0; j <temp_vector.size();j++){
        keys.push_back(temp_vector[j]);
      }
    }
  }
  //at the end, we return the vector containing our keys
  return keys;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
  vector<pair<K,V>> items;
    //if there is nothing, return an empty vector
    if(this->size==0){
        return items;
    }
    //for each linear dictionary,
    for (int i=0; i < this->capacity;i++){

        //if that particular linear dictionary has something in it
        if(!this->array[i]->isEmpty()){

          //then call get items on that linear dictionary and copy the elements
          vector<pair<K,V>> temp_vector;
          temp_vector = this->array[i]->getItems();

          //copy over each of the elements
          for (int j=0; j <temp_vector.size();j++){
            items.push_back(temp_vector[j]);
          }
        }
    }
    return items;
}
