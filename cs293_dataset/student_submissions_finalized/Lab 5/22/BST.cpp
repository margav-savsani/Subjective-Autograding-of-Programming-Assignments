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
  // if (root->JourneyCode == JourneyCode)
  //   return false;

  if (root == nullptr) // When we initialize a BST using BST(), the JourneyCode of root node is 0. This makes sure that root is inserted before moving ahead.
  {
    // root->JourneyCode = JourneyCode;
    // root->price = price;
    // root->longestPathLength = 0;
    // root->shortestPathLength = 0;
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  TreeNode* insrt = new TreeNode(jrnyCode, price);
  if (BSTLessThan(root, insrt))
  {
    if (root->right == nullptr) // When the right child of root doesn't exist, we create a new one and join them.
    {
      // TreeNode *right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
      // (*root).right = insrt;
      updateBSTParentChild(insrt, root, false);

      // if(root->left == nullptr) root->shortestPathLength = 0; //Since the node doesn't have a left child, that is the shortest path to a leaf node.
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;//As we go up the treewhile exiting recursion, we update the shortestPathLength of each node we encounter. It is the minimum of ShortestPathLength of both its child +1

      //As we go up the tree while exiting recursion, we update the longestPathLength of each node we encounter. It is the maximum of longestPathLength of both its child +1
      if(root->left==nullptr) root->height = root->right->height + 1;
      else root->height = std::max(root->left->height, root->right->height) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                      // stores the value of our root
      root = root->right;                         // changes root to root->right. This makes our RST the BST
      bool val = BST::insert(jrnyCode, price); // recurses until the upper condition is reached.
      root = curr;                                // This changes our BST from RST to BST.

      // if(root->left == nullptr) root->shortestPathLength = 0;//Since the node doesn't have a left child, that is the shortest path to a leaf node.

      //As we go up the treewhile exiting recursion, we update the shortestPathLength of each node we encounter. It is the minimum of ShortestPathLength of both its child +1
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      //As we go up the tree while exiting recursion, we update the longestPathLength of each node we encounter. It is the maximum of longestPathLength of both its child +1

      if(root->left==nullptr) root->height = root->right->height + 1;
      else root->height = std::max(root->left->height, root->right->height) + 1;

      return val;
    }
  }

  else
  {
    if (root->left == nullptr) // When the left child of root doesn't exist, we create a new one and join them.
    {
      // TreeNode *left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
      root->left = insrt;
      updateBSTParentChild(insrt, root, true);

      // if(root->right == nullptr) root->shortestPathLength = 0;
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      if(root->right==nullptr) root->height = root->left->height + 1;
      else root->height = std::max(root->left->height, root->right->height) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                      // stores the value of our root
      root = root->left;                          // changes root to root->left. This makes our LST the BST
      bool val = BST::insert(jrnyCode, price); // recurses until the upper condition is reached.
      root = curr;                                // This changes our BST from LST to BST.

      // if(root->right == nullptr) root->shortestPathLength = 0;
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      if(root->right==nullptr) root->height = root->left->height + 1;
      else root->height = std::max(root->left->height, root->right->height) + 1;

      return val;
    }
  }
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
  return -1;
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


