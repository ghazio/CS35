/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <UnitTest++/UnitTest++.h>

#include "adts/BST.h"
#include "adts/list.h"
#include "linkedBST.h"
#include "linkedBSTNode.h"

using namespace std;

/**
 * This helper function will build a small BST on which we can perform
 * experiments.  We can call the methods of the BST
 * in a specific order to make sure it puts the nodes where we want them
 * (assuming, of course, that the insert and get functions work correctly).
 * Our tree will look like this:
 * @verbatim
 *         6
 *        / \
 *       /   \
 *      2     7
 *     / \     \
 *    1   4     9
 *       /
 *      3
 * @endverbatim
 * @return An example BST.  The caller is responsible for deleting this BST.
 */
LinkedBST<int, string>* makeExampleBST() {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    bst->insert(6, "6");
    bst->insert(2, "2");
    bst->insert(7, "7");
    bst->insert(1, "1");
    bst->insert(4, "4");
    bst->insert(9, "9");
    bst->insert(3, "3");
    bst->checkInvariants();
    return bst;
}

TEST(emptyBST) {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    CHECK_EQUAL(0, bst->getSize());
    CHECK(bst->isEmpty());
    bst->checkInvariants();
    delete bst;
}

TEST(exampleBST) {
    // Since we have to respect the BST interface -- we can't look directly at
    // the BST nodes -- we have to test the example BST to make sure that it
    // behaves like we'd think.  If this test fails, then either the insert or
    // the get method is broken and it's hard to tell which.
    // The upside is that we test both the insert and get functions with this
    // test.
    LinkedBST<int, string>* bst = makeExampleBST();
    for (int i = 1; i <= 9; i++) {
        if (i != 5 && i != 8) {
            CHECK_EQUAL(to_string(i), bst->get(i));
        }
    }
    delete bst;
}

TEST(exampleBSTSize) {
    LinkedBST<int, string>* bst = makeExampleBST();
    cout<<bst->getSize()<<endl;
    CHECK_EQUAL(7, bst->getSize());
    CHECK(!bst->isEmpty());
    delete bst;
}


TEST(example_insert){
  LinkedBST<int,string>* bst = new LinkedBST<int, string>();
  bst->insert(9, "9");
  bst->checkInvariants();
  CHECK_EQUAL("9",bst->get(9));
  delete bst;
}

// NOTE: Be sure to make frequent use of the checkInvariants method
// which verifies that your BST contains the correct number of nodes
// and has properly implemented the BST property.

TEST(update){
  LinkedBST<int,string>* bst = makeExampleBST();
  bst->update(4, "10");
  CHECK_EQUAL("10",bst->get(4));
  delete bst;
}

TEST(contains){
  LinkedBST<int,string>* bst = makeExampleBST();
  CHECK_EQUAL(1,bst->contains(4));
  CHECK_EQUAL(0,bst->contains(20));
  delete bst;
}

TEST(remove_key){
  LinkedBST<int,string>* bst = makeExampleBST();
  bst->remove(3);
  CHECK_EQUAL(0,bst->contains(3));
  delete bst;
}

// TEST(delete){
//   LinkedBST<int,string>* bst = makeExampleBST();
//   bst->delete(3,"3");
//   CHECK_EQUAL(0,bst->contains(3));
//   delete bst;
// }
// TODO: test LinkedBST<K,V>::getKeys

// TODO: test LinkedBST<K,V>::getItems


TEST(getHeight){
  LinkedBST<int,string>* bst = makeExampleBST();
  CHECK_EQUAL(3,bst->getHeight());
  delete bst;
}

TEST(getMax){
  LinkedBST<int,string>* bst = makeExampleBST();
  CHECK_EQUAL(9,bst->getMaxKey());
  delete bst;
}

TEST(getMin){
  LinkedBST<int,string>* bst = makeExampleBST();
  CHECK_EQUAL(1,bst->getMinKey());
  delete bst;
}

TEST(examplePreOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePreOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

// TODO: test LinkedBST<K,V>::getInOrder

// TODO: test LinkedBST<K,V>::getPostOrder

// TODO: test LinkedBST<K,V>::getLevelOrder

int main() {
    return UnitTest::RunAllTests();
}
