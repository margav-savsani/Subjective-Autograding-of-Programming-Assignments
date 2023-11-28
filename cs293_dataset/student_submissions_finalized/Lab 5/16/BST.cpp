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

  // My code
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  // Checking firstly if element is already present or not
  if (find(jrnyCode))
  {
    return false;
  }

  // Now we know that it surely isn't present
  // Firstly finding the location where we need it to be there, and then adding(inserting at that location)
  TreeNode *finder, *parent = NULL;
  finder = root;
  while (finder != NULL)
  {
    parent = finder;
    if (finder->JourneyCode >= jrnyCode)
    {
      finder = finder->left;
    }
    else if (finder->JourneyCode < jrnyCode)
    {
      finder = finder->right;
    }
  }

  // Handling the case of same journey code but different price too, by putting that in the left tree
  TreeNode *element = new TreeNode(jrnyCode, price);
  if (parent != NULL)
  {
    element->parent = parent;
    if (parent->JourneyCode >= jrnyCode)
    {
      parent->left = element;
    }
    else
    {
      parent->right = element;
    }
  }
  else
  {
    root = element;
    element->parent = NULL;

    // Since no root exist earlier, longest and shortest path for it would be same and that should be zero\
    which default constructor anyhow gives, so no need to change.
  }

  // Changing the path length of all the nodes that were traversed to get here
  // TreeNode *changer = element;
  // while (changer != root)
  // {
  //   if (ch)
  // }

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
  TreeNode *finder;
  finder = root;
  while (finder != NULL)
  {
    if (finder->JourneyCode == jrnyCode)
    {
      if (finder->price == price)
      {
        return 1;
      }
      else
      {
        finder = finder->left;
      }
    }
    else if (finder->JourneyCode > jrnyCode)
    {
      finder = finder->left;
    }
    else if (finder->JourneyCode < jrnyCode)
    {
      finder = finder->right;
    }
  }
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

  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.

  // Firstly checking if given pair exist in the tree or not, if not return false
  if (!find(JourneyCode, price))
  {
    return false;
  }

  // Else first finding the pointer to the pair that is to be deleted
  TreeNode *finder;
  finder = root;
  while (true)
  {
    if (finder->JourneyCode == JourneyCode)
    {
      if (finder->price == price)
      {
        break;
      }
      else
      {
        finder = finder->left;
      }
    }
    else if (finder->JourneyCode > JourneyCode)
    {
      finder = finder->left;
    }
    else if (finder->JourneyCode < JourneyCode)
    {
      finder = finder->right;
    }
  }

  // Now we know that finder is pointing to the node we need to delete
  // Have to implement the different cases of deletion

  // Leaf node
  if (finder->left == NULL && finder->right == NULL)
  {
    // Just making sure that parent is not null, before accessing parent pointer
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = NULL;
      }
      else
      {
        (finder->parent)->left = NULL;
      }
    }
    else
    {
      root = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }

  // Having one child
  else if (finder->left != NULL && finder->right == NULL)
  {
    // Just making sure that parent is not null, before accessing parent pointer
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = finder->left;
        (finder->left)->parent = finder->parent;
      }
      else
      {
        (finder->parent)->left = finder->left;
        (finder->left)->parent = finder->parent;
      }
    }
    // Making sure above that all the pointer reference changes are being done properly, that is parents are pointed correctly \
        parents childs are handled properly etc.
    else
    {
      root = finder->left;
      (finder->left)->parent = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }
  else if (finder->left == NULL && finder->right != NULL)
  {
    // similar case to above else if
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = finder->right;
        (finder->right)->parent = finder->parent;
      }
      else
      {
        (finder->parent)->left = finder->right;
        (finder->right)->parent = finder->parent;
      }
    }
    else
    {
      root = finder->right;
      (finder->right)->parent = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }

  // Having two children
  // using predecessor method
  else
  {
    TreeNode *pred;
    // Here predecessor is forsure the right most element in the left sub-tree, NOTE can be equal to price value of deleted one
    pred = finder->left;
    // cout << "fnder" << finder->JourneyCode << endl;
    // cout << "pred" << pred->JourneyCode << endl;
    while (pred->right != NULL)
    {
      pred = pred->right;
    }
    // cout << "pred" << pred->JourneyCode << endl;
    // Since our pred would be no more after deletion, lets store its inner values in new node
    int jc = pred->JourneyCode;
    int p = pred->price;
    // Need to properly delete elements, can be called recursively
    bool del = remove(jc, p); // No use of this variable, just a placeholder
    finder->JourneyCode = jc;
    finder->price = p;
  }
  return true;
}
