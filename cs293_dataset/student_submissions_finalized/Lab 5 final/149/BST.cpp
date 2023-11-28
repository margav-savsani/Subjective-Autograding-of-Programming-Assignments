#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

/// @brief recursively add node to the tree
/// @param t node at which the new node might get inserted, otherwise used for recursion
/// @param code Journeycode of the node to be inserted
/// @param price price of the journey
/// @return true if all the functions are carried out successfully
bool BST::addNode(TreeNode *t, int code, int price)
{
  TreeNode *y;
  y = new TreeNode(code, price);
  if (t->JourneyCode == 0)
  {
    t = y;
    return true;
  }
  else if (BSTLessThan(y, t))
  {
    if (t->left == nullptr)
    {
      updateBSTParentChild(y, t, 1);
      return true;
    }
    else
    {
      return addNode(t->left, code, price);
    }
  }
  else if (BSTLessThan(t, y))
  {
    if (t->right == nullptr)
    {
      updateBSTParentChild(y, t, 0);
      return true;
    }
    else
    {
      return addNode(t->right, code, price);
    }
  }
}

/// @brief main function called to insert node, adds root if its a nullptr, checks if the node already exist in the tree and then calls the recursive function addnode to add the node to the tree.
/// @param JourneyCode Journeycode of the node to be inserted
/// @param price price of the journey
/// @return true if the node is inserted successfully
bool BST::insert(int JourneyCode, int price)
{
  if (root == nullptr)
  {
    root = new TreeNode(JourneyCode, price);
    root->parent = nullptr;
    return true;
  }
  else if (find(JourneyCode) != 0)
  {
    return false;
  }
  else
    return addNode(root, JourneyCode, price);
  return true;
}

/// @brief recursive function to find a specific node
/// @param t treenode used for recursion
/// @param code journeycode of the journey to be found
/// @return the node of found else return nullptr
TreeNode *BST::findNode(TreeNode *t, int code)
{
  TreeNode *y = new TreeNode();
  y->JourneyCode = code;
  if (t == nullptr)
  {
    return t;
  }
  else if (t->JourneyCode == code)
  {
    return t;
  }
  else if (BSTLessThan(y, t))
  {
    return findNode(t->left, code);
  }
  else
  {
    return findNode(t->right, code);
  }
}

/// @brief find the journey using code and return its price
/// @param JourneyCode code of the journey to be found
/// @return price of the journey
int BST::find(int JourneyCode)
{
  TreeNode *t = findNode(root, JourneyCode);
  if (t == nullptr)
    return false;
  else
    return t->price;
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
