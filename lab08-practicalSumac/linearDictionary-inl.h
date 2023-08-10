    /*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
  this->size=0;
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    //if nothing exists in the dictionary
    if(this->size ==0){
      //we return 1
      return true;
    }
    //otherwise we return 0
    return false;
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {

    int i=0;
    while(i<this->size){
      //if the key already exists, throw a runtime error
      if(this->vector1[i].first == key){
        throw std::runtime_error("Key already exists in our dictionary");
        return ;
      }
      i++;
    }
    //add the new element to our list if we are sure that the key does not
    //already exist
    pair<K,V> addition= pair<K,V> (key,value) ;
    this->vector1.push_back(addition);
    this->size++;
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    int i=0;
    //if there is no element in the list, throw a runtime error
    if(this->size==0){
      throw std::runtime_error("There is nothing in the dictionary");
    }
    //while we do not reach our required key
    while(!(this->vector1[i].first == key)){
      i++;
      //if we reach end of our dictionary,
      if(i==this->size){
        //we know that the key was not in and we throw a runtime error
        throw std::runtime_error("Key was not in our dictionary");
      }
    }

    this->vector1[i].second=value;
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {

  int i =0;
  //if there is no element in the list, throw a runtime error
  if(this->size==0){
    throw std::runtime_error("There is nothing in the dictionary");
  }
  //until we reach the required key
  while(!(this->vector1[i].first == key)){
    i++;
    //if we reach end of our dictionary,
    if(i==this->size){
      //we know that the key was not in and we throw a runtime error
      throw std::runtime_error("Key was not in our dictionary");
    }
  }
  return this->vector1[i].second;

}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {

  int i =0;
  //if there is no element in the vector, then we know the item is not in there
  if(this->size==0){
    return false;
  }
  //until we reach the required key
  while(!(this->vector1[i].first == key)){
    i++;
    //if it reaches the end, then we return 0
    if(i==this->size){
      return false;
    }
  }
  //if we break out of the loop, we return 1 because we know the key exists
  return true;

}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {

  int i =0;
  //if there is no element in the list, throw a runtime error
  if(this->size==0){
    throw std::runtime_error("There is nothing to remove in the dictionary");
  }
  //until we reach the required key
  while(!(this->vector1[i].first == key)){
    i++;
    //if it reaches the end,
    if(i==this->size){
      //throw runtime error
      throw std::runtime_error("We do not have the key in our dictiionary");
    }
  }
  //we delete the appropriate element
  this->vector1.erase(this->vector1.begin() + i, this->vector1.begin() + i + 1);
  this->size--;
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {

   vector<K> keys;
   int i=0;
   //until we reach the end of the list
   while(i != this->getSize()){
     //store the key
     keys.push_back(this->vector1[i].first);
     i++;
   }
   return keys;

}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {

  vector<pair<K,V>> items;
  int i=0;
  //until we reach the end of the list
  while(i != this->getSize()){
    //add the item to our vector
    items.push_back(this->vector1[i]);
    i++;
  }
  return items;
}
