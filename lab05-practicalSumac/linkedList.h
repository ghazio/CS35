#pragma once
/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "adts/list.h"

// This file declares two classes: a LinkedListNode class (which represents a
// single node in a linked list) and a LinkedList class (which represents a
// full linked list as an implementation of the List ADT).

/**
 * This class represents a single node in a linked list.  It contains
 * one list element as well as pointers to the nodes which follow it
 * (or NULL when those nodes don't exist).
 * @tparam T The type of data stored in the list.
 */
template <typename T> class LinkedListNode {

  public:
    /**
     * Constructs a new node.
     * @param val The value to store in the node.
     * @param next An optional pointer to the following node.
     *             If unspecified next will be set to nullptr.
     */
    LinkedListNode<T>(T val, LinkedListNode<T>* next);

    // public data members:
    T value;
    LinkedListNode<T>* next;
};

/**
 * This class implements this list ADT as a linked list.
 * @tparam T The type of data stored in the list.
 */
template <typename T> class LinkedList : public List<T> {
  public:
    LinkedList();
    ~LinkedList();

    /**
     * Confirms that there are this->size elements in the list.
     * @throws runtime_error if the invariant does not hold.
     */
    void checkInvariants();

    /**
     * Returns the size of the linked list
     */
    int getSize();
    /**
     * checks if the linked list is empty or not
     * Returns a 0 boolean value if the list is not empty and 1 if it is empty
     */
    bool isEmpty();
    /**
     * Returns the value stored in the first node of our linked list
     * Throws a runtime error if there is nothing in our list
     */
    T getFirst();
    /**
     * Returns the value stored in the last node of our linked list
     * Throws a runtime error if there is nothing in our list
     */
    T getLast();
    /**
     * It takes in an index of a node in our list which must be positive or 0
     * Returns the value stored in a particular node of the list
     * Throws a runtime error if you are trying to access a wrong memory address
     */
    T get(int index);
    /**
     * Takes in a value for a new node
     * this method inserts a new node as the first on the linked list and adjusts the
     *  data structure correctly
     * Returns nothing
     */
    void insertFirst(T value);
    /**
     * Takes in a value for a new node
     * this method inserts a new node as the last one on the linked list and adjusts the
     * data structure correctly
     * Returns nothing
     */
    void insertLast(T value);
    /**
     * Takes in no inputs
     * this method deletes the first node of the linked list and adjusts the
     * structure properly.
     * Returns the value of the deleted node of the appropriate time
     * Throws a runtime error if the list is of size 0
     */
    T removeFirst();
    /**
     * Takes in no inputs
     * this method deletes the last node of the linked list and adjusts the
     * structure properly
     * Returns the value of the deleted node of the appropriate time
     * Throws a runtime error if the list is of size 0
     */
    T removeLast();
  private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;
};

#include "linkedList-inl.h"
