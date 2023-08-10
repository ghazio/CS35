/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedStack.h"

using namespace std;

template <typename T> LinkedStack<T>::LinkedStack() {
}

template <typename T> void LinkedStack<T>::push(T element) {
    stack.insertLast(element);
}

template <typename T> T LinkedStack<T>::pop() {
  T popped = stack.removeLast();
  return popped;
}

template <typename T> void LinkedStack<T>::insert(T element) {
    stack.insertLast(element);
}

template <typename T> T LinkedStack<T>::remove() {
  T popped = stack.removeLast();
  return popped;
}

template <typename T> int LinkedStack<T>::getSize() {
    return stack.getSize();
}

template <typename T> bool LinkedStack<T>::isEmpty() {
    return stack.isEmpty();
}

template <typename T> T LinkedStack<T>::peek() {
    return stack.getLast();
}
