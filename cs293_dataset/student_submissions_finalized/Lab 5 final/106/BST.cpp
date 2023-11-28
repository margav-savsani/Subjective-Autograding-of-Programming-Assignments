#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST


bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* currNode = root;   // currnode is node at which comparision takes place
  TreeNode* parent = NULL;     // parent node of current node
  bool flag = 1;                // to decide whether new node is left or right child
  TreeNode* newNode = new TreeNode(jrnyCode,price);
  while (true) {
    if (currNode == NULL) {
      if (parent == NULL) root = newNode;   // if currnode and parent are both null then currnode is root
      updateBSTParentChild(newNode,parent,flag);
      break;
    }
    if (BSTLessThan(newNode, currNode)) {
      flag = 1; // new node is left child of parent
      parent = currNode;
      currNode = currNode->left;
    }
    else if (BSTLessThan(currNode, newNode)) {
      flag = 0; // new node is right child of parent
      parent = currNode;
      currNode = currNode->right;
    }
  }
  int h = updateH(root); // updates heights after insertion
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  int p = 1;            // price corresponding to jrnycode initialized to 1
  TreeNode* currNode = root;   // currnode is node we are checking currently
  TreeNode* newNode = new TreeNode(jrnyCode, p);
  while(true) {
    if (currNode->getjrnycode () == newNode->getjrnycode ()) {
      p = currNode->getprice();        //if there is node with that jrnycode returns price
      return p;
    }
    if (BSTLessThan(newNode, currNode)) currNode = currNode->left;
    if (BSTLessThan(currNode, newNode)) currNode = currNode->right;
    if (currNode == NULL) return -1;   // if there is no node with that jrnycode returns -1
  }
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


