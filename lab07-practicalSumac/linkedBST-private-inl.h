/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current==nullptr){
      throw runtime_error("there are no nodes in this tree");
    }else{
      if (current->getKey()== key){
        return current->getValue();
      }
      else if(current->getKey() <key){
        return findInSubtree(current->getRight(),key);
      }else{
        return findInSubtree(current->getLeft(),key);
      }
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
  if (current==nullptr){
     return 0;
  }else{
    if (current->getKey()== key){
      return 1;
    }
    else if(current->getKey() <key){
      return containsInSubtree(current->getRight(),key);
    }else{
      return containsInSubtree(current->getLeft(),key);
    }
  }
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key, V value){
  if (current==nullptr){
    throw runtime_error("there's nothing in the tree");
  }else {
    if (current->getKey()== key){
      return current->setValue(value);
    }
    else if(current->getKey() <key){
      return updateInSubtree(current->getRight(),key,value);
    }else{
      return updateInSubtree(current->getLeft(),key,value);
    }
  }
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {

    int count=0;
    int left_value=0;
    int right_value=0;
    //if there is a right child, this function calls the function on the right child
    if(current->getRight() !=nullptr){
      right_value= getHeightInSubtree(current->getRight());
      count++;
    }
    //if there is a left child, we cal the get height function on the left child
    if(current->getLeft()!=nullptr){
      left_value= getHeightInSubtree(current->getLeft());
      count++;
    }
    //if there are two children and left child's subtree's height is larger
    if(count==2 && left_value>right_value){
        return left_value+1;
    }
    //if there are two children and right child's subtree's height is larger
    else if(count==2 && right_value>left_value){
      return right_value+1;
    }
    //if there is one child
    else if(count==1 ){
      //and that child is left
      if(left_value!=0){
        return left_value+1;

        }
    //else when there is a right child to our current
    return right_value+1;

    }
    //base case
    return 0;

}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
  pair<K,V> min_right;
  pair<K,V> min_left;
  K right_key;
  K left_key;
  K current_key = current->getKey();
  pair<K,V> current_pair(current->getKey(),current->getValue());

  int counter = 0;

  //singleton tree
  if(current->getRight()==nullptr && current->getLeft()==nullptr){
    return current_pair;
  }

  else{
    if (current->getRight() != nullptr){
      min_right = getMinInSubtree(current->getRight());
      right_key = min_right.first;
      counter ++;
    }
    if (current->getLeft() != nullptr){
      min_left = getMinInSubtree(current -> getLeft());
      left_key = min_left.first;
      counter ++;
    }

    //current node has 2 children
    if (counter == 2){
      if(right_key<left_key && right_key<current_key){
          return min_right;
      }
      if (left_key<right_key && left_key<current_key){
        return min_left;
      }
      if (current_key<left_key && current_key<right_key){
        return current_pair;
      }
    }

    //current has only one children
    if (counter == 1){
      if (current->getRight() != nullptr){
        if(right_key<current_key){
          return min_right;
        }
        return current_pair;
      }
      if (left_key<current_key){
        return min_left;
      }
      return current_pair;
    }
  }

  //if tree is empty, throw runtime error
  throw runtime_error("the tree is empty");
}



template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {

  pair<K,V> max_right;
  pair<K,V> max_left;
  K right_key;
  K left_key;
  K current_key = current->getKey();
  pair<K,V> current_pair(current->getKey(),current->getValue());

  int counter = 0;

  //no node in tree
  // if (current==nullptr){
  //   throw runtime_error("the tree is empty");
  // }

  //singleton tree
  if(current->getRight()==nullptr && current->getLeft()==nullptr){
    return current_pair;
  }

  else{
    if (current->getRight() != nullptr){
      max_right = getMaxInSubtree(current->getRight());
      right_key = max_right.first;
      counter ++;
    }
    if (current->getLeft() != nullptr){
      max_left = getMaxInSubtree(current -> getLeft());
      left_key = max_left.first;
      counter ++;
    }

    //current node has 2 children
    if (counter == 2){
      if(right_key>left_key && right_key>current_key){
          return max_right;
      }
      if (left_key>right_key && left_key>current_key){
        return max_left;
      }
      if (current_key>left_key && current_key>right_key){
        return current_pair;
      }
    }

    //current has only one children
    if (counter == 1){
      if (current->getRight() != nullptr){
        if(right_key>current_key){
          return max_right;
        }
        return current_pair;
      }
      if (left_key>current_key){
        return max_left;
      }
      return current_pair;
    }
  }

  //if tree is empty, throw runtime error
  throw runtime_error("the tree is empty");
}


template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
    if (current==nullptr){
      LinkedBSTNode<K, V>* new_node= new LinkedBSTNode<K,V>(key,value);
      return new_node;
    }
    else{
      if (current->getKey()== key){
        throw runtime_error("A key alrady exists of the same value ");
        return nullptr;
      }
      else if(current->getKey() <key){
        current->setRight(insertInSubtree(current->getRight(),key,value));
        return current;
      }else{
        current->setLeft(insertInSubtree(current->getLeft(),key,value));
        return current;
      }
    }
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
    if(current==nullptr){
      throw runtime_error("tree is empty");

    }else{
      if (current->getKey()<key){
        current->setRight(removeFromSubtree(current->getRight(),key));
        return current;
      }else if (current->getKey()>key){
        current->setLeft(removeFromSubtree(current->getLeft(),key));
        return current;
      }
    else{
      if (current->getRight()==nullptr && current->getLeft()==nullptr){
        return nullptr;
      }else if(current->getRight()!=nullptr || current->getLeft()!=nullptr){
          if(current->getLeft()!=nullptr){
            return current->getLeft();
          }
          return current->getRight();
      }else{
        K smallkey = getMinInSubtree(current->getRight()).first;
        V smallvalue = findInSubtree(current->getRight(),smallkey);
        current->setRight(removeFromSubtree(current->getRight(),smallkey));
        current->setKey(smallkey);
        current->setValue(smallvalue);
        return current;
      }
    }
  }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
  // if (current==nullptr){
  //   throw runtime_error("tree is empty");
  // }
  // if(current->getRight() == nullptr && current->getLeft()==nullptr){
  //     delete current;
  // }else{
  //   if (current->getRight() != nullptr){
  //     deleteSubtree(current->getRight());
  //   }
  //   if (current->getLeft() != nullptr){
  //     deleteSubtree(current->getLeft());
  //   }
  // }

  throw runtime_error("boo");
}



template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {
  if (current==nullptr){
    throw runtime_error("three is empty");
  }

  if (current!=nullptr ){
  list.insertFirst(current);
  }

  if(current->getRight()!= nullptr && current->getLeft()!=nullptr){
      buildPreOrderTraversal(current->getLeft(),list);
      buildPreOrderTraversal(current->getRight(),list);
    }
  if(current->getRight()!= nullptr || current->getLeft()!=nullptr){
      if(current->getRight()!= nullptr){
        buildPreOrderTraversal(current->getRight());
      }
      else{
        buildPreOrderTraversal(current->getLeft());
      }

    }

}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildInOrder");
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildPostOrder");
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
