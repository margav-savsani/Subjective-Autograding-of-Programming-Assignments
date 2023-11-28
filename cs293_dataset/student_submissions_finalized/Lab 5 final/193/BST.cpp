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
  //Creating a dummy node for the comparison of journeycode
  TreeNode *comparisonnode = new TreeNode(jrnyCode, price);

  TreeNode *currNode = root;
  TreeNode *parentOfCurrNode = nullptr;
  if (root == NULL)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  while (currNode != nullptr)
  {
    if (this->BSTLessThan(currNode, comparisonnode))
    {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else
    {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
  //NODE LEFT CHILD OF PARENT
  if (this->BSTLessThan(comparisonnode, parentOfCurrNode))
  {
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    updateBSTParentChild(currNode, parentOfCurrNode, true);
  }
  //NODE RIGHT CHILD OF PARENT
  else
  {
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    updateBSTParentChild(currNode, parentOfCurrNode, false);
  }
  delete (comparisonnode); //Deleting the comparison node

  int currht = 1; //TRAVERSING BACK FROM BELOW AND UPDATING HEIGHT
  TreeNode *p = parentOfCurrNode; //Parent node 

  while (p != NULL)
  {
    if (p->height <= currht) //comparison with the current height
    {
      p->height = currht;
    }
    else
    {
      break; //break for the case when heights are correct.
    }
    p = p->parent;
    currht++;
  }
  return true;
}

int BST::find(int jrnyCode)
{
  //Creating an arbitrary comparison node
  TreeNode *comparisonnode = new TreeNode(jrnyCode, 0);

  TreeNode *x = root; // STARTING FROM ROOT NODE
  while (x != NULL && ((this->BSTLessThan(x, comparisonnode) || this->BSTLessThan(comparisonnode, x))))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (this->BSTLessThan(comparisonnode, x))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  if (x == NULL)
  { // IF NO SUCH NODE
    return -1;
  }
  else // CASE WHEN THE EXACT LOCATION OF THE NODE HAS BEEN FOUND
  {
    return 1; //RETURN 1 as is convinient.
  }
  return -1; //RETURN -1 for any other
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
