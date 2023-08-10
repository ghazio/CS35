/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
    this -> size = 0;
    this -> root = nullptr;
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    // To do: implement the destructor
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    if (this->root == nullptr){
      return 1;
    }
    return 0;
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
  LinkedBSTNode<K, V>* check=  insertInSubtree(this->root,key,value);
  this->root = check;
  if (check!=nullptr){
    this->size ++;
  }


}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
  updateInSubtree(this->root,key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
  V value_found= findInSubtree(this->root,key);
  return value_found;
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    bool result= containsInSubtree(this->root, key);
    return result;
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    removeFromSubtree(this->root,key);
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
  throw runtime_error("Not yet implemented: LinkedBST<K,V>::getItems");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getItems");
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
     int height= getHeightInSubtree(this->root);
     return height;
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
     pair<K,V> max= getMaxInSubtree(this->root);
     return max.first;
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
  pair<K,V> min= getMinInSubtree(this->root);
  return min.first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
  List<pair<K, V>>* list= new List<pair<K, V>>;
  buildPreOrderTraversal(this->root,list);
  vector<pair<K,V>> vector1;
  for(i=list->getSize();i>0;i--){
    vector1.push_back(list->get(i));
  }
  return vector1;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::traverseInOrder");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::traversePostOrder");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::traverseLevelOrder");
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false arguments
        // indicate that they do not apply.  But we need a value of type K to
        // fill this parameter since we don't have globally min/max K values
        // generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
