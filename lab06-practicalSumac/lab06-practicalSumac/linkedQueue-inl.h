/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedQueue.h"

using namespace std;

template <typename T> LinkedQueue<T>::LinkedQueue() {
}

template <typename T> void LinkedQueue<T>::enqueue(T element) {
    queue.insertFirst(element);
}

template <typename T> T LinkedQueue<T>::dequeue() {
  T deleted=queue.removeLast();
   return deleted;
}

template <typename T> void LinkedQueue<T>::insert(T element) {
    queue.insertLast(element);
}

template <typename T> T LinkedQueue<T>::remove() {
   T deleted=queue.removeFirst();
   return deleted;
}

template <typename T> int LinkedQueue<T>::getSize() {
    return queue.getSize();
}

template <typename T> bool LinkedQueue<T>::isEmpty() {
    return queue.isEmpty();
}

template <typename T> T LinkedQueue<T>::peek() {
    return queue.getFirst();
}
