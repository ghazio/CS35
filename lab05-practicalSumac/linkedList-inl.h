/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

using namespace std;
using std::runtime_error;

// This file defines the methods for two classes: LinkedListNode and LinkedList.
// The LinkedListNode methods have been defined for you.  You are responsible
// for defining the LinkedList methods.

// //////// LinkedListNode /////////////////////////////////////////////////////

template <typename T>
LinkedListNode<T>::LinkedListNode(T val, LinkedListNode<T>* next) {
    this->value = val;
    this->next = next;
}

// //////// LinkedList /////////////////////////////////////////////////////////

template <typename T> LinkedList<T>::LinkedList() {
    this->size = 0;
    this->head=nullptr;
    this->tail=nullptr;
}

template <typename T> LinkedList<T>::~LinkedList() {
  LinkedListNode<T>* pointer_node=this->head;
  LinkedListNode<T>* placekeeper=this->head;
  for(int i = 0; i < this->size;i++){
    pointer_node = pointer_node->next;
    delete placekeeper;
    placekeeper=pointer_node;
  }
}

template <typename T> void LinkedList<T>::checkInvariants() {
  int count = 0;
  LinkedListNode<T>* pointer_node=this->head;
  while(pointer_node != nullptr){
    // cout<<pointer_node ->value<<endl;
    pointer_node = pointer_node->next;
    count += 1;
  }
  // cout<<count<<this->size<<endl;

  if (this->size != count){
    throw runtime_error("Node count does not match size");
  }
}

template <typename T> int LinkedList<T>::getSize() {

    return this->size;
}

template <typename T> bool LinkedList<T>::isEmpty() {
    if(this->head == nullptr){
      return 1;
    }
    else{
      return 0;
    }
}

template <typename T> T LinkedList<T>::getFirst() {
    if (this->head == nullptr){
      throw runtime_error("there is no element in this list");
    }
    else{
      T first_value=(this->head->value);
      return first_value;
    }
}

template <typename T> T LinkedList<T>::getLast() {

  if (this->head == nullptr){
    throw runtime_error("there is no element in this list");
  }
  else{
    T last_value=(this->tail->value);
    return last_value;
  }
}

template <typename T> T LinkedList<T>::get(int index) {
    if (index <0){
      throw runtime_error("negative index ");
    }
    else if(index>((this->size)-1)){
      throw runtime_error("Wrong index outside range");
    }
    else{
      LinkedListNode<T>* pointer_node=this->head;
      for(int i=0;i<index;i++){
          pointer_node=pointer_node->next;
      }

      return pointer_node->value;
    }
}

template <typename T> void LinkedList<T>::insertFirst(T value) {
  LinkedListNode<T>* new_node= new LinkedListNode<T>(value, this->head);
    if(this->size==0){
        this->tail=new_node;
    }
  this->head=new_node;
  this->size += 1;
}

template <typename T> void LinkedList<T>::insertLast(T value) {
  LinkedListNode<T>* new_node = new LinkedListNode<T>(value, nullptr);

  if(this->size==0){
      this->head=new_node;
  }

  else if(this->size==1){
    this->head->next=new_node;
  }

  else{
    this->tail->next=new_node;
  }

  this->tail=new_node;
  this->size += 1;
}

template <typename T> T LinkedList<T>::removeFirst() {
  if (this->head == nullptr){
    throw runtime_error("there is no element in this list");
  }
  else{
    LinkedListNode<T>* pointer_n1 = (this->head);
    LinkedListNode<T>* pointer_n2 = (this->head)->next;

    this -> head = pointer_n2;
    T value = pointer_n1->value;
    delete pointer_n1;
    this->size -= 1;

    if(this->size == 0){
      this->head = nullptr;
      this->tail = nullptr;
    }

    return value;
  }
}

template <typename T> T LinkedList<T>::removeLast() {

  if (this->head == nullptr){
    throw runtime_error("there is no element in this list");
  }

  else{
      LinkedListNode<T>* pointer_node = this -> head;
      LinkedListNode<T>* current_tail = this -> tail;
       for(int i = 1; i < this->size-1;i++){
          pointer_node = pointer_node->next;
       }
   this->tail = pointer_node;
   T value = current_tail->value;
   delete current_tail;
   this->size -= 1;

   if(this->size!=0){
     this->tail->next = nullptr;
   }

   if(this->size == 0){
     this->head = nullptr;
     this->tail = nullptr;
   }
   return value;
}
}
