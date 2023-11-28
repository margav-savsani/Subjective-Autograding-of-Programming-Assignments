#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{ 
  if(grandParentNode->right==NULL){
  grandParentNode->height = 1+(grandParentNode->left->height);}
  else{
    grandParentNode->height = 1+max(grandParentNode->left->height,grandParentNode->right->height);
  }
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  // Updating the Heights
  if(grandParentNode->right==NULL && grandParentNode->left==NULL){
    grandParentNode->height=0;
  }
  else if(grandParentNode->right==NULL){
  grandParentNode->height = 1+(grandParentNode->left->height);}
  else if(grandParentNode->left==NULL){
    grandParentNode->height = 1+(grandParentNode->right->height);
  }
  else{
    grandParentNode->height = 1+max(grandParentNode->left->height,grandParentNode->right->height);
  }
  root = parentNode; // changing the root
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  // Updating the Heights
  currNode->height += 1;
  parentNode->height -= 1;
  grandParentNode->height -= 2;
  root = currNode; // changing the root
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  // Updating the Heights
  currNode->height += 1;
  parent->height -= 1;
  grandParent->height -= 2;
  root = currNode; // changing the root
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *T3 = parent->left;
  updateAVLParentChild(currNode, parent, false);
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  // Updating the Heights
  grandParent->height -= 2;
  root = parent; // changing the root
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{

  TreeNode *temp = new TreeNode(jrnyCode, price);
  if (root == NULL) // Base case for recursion
  {
    root = temp;
    return true;
  }
  else if (AVLLessThan(root, temp))
  {
    AVLTree *right = new AVLTree(root->right, perComparisonCost, perParentChildUpdateCost);
    bool x = right->insert(jrnyCode, price); // Inserts function Recursively
    updateAVLParentChild(right->root, root, false);
    root->height = max(root->height, 1 + right->root->height);
    totalComparisonCost = totalComparisonCost + right->getComparisonCost();
    totalParentChildUpdateCost = totalParentChildUpdateCost + right->getParentChildUpdateCost();

    if (!x)
    {
      return x; //returns false is x is false
    }
  }
  else
  {
    AVLTree *left = new AVLTree(root->left, perComparisonCost, perParentChildUpdateCost);
    bool x = left->insert(jrnyCode, price); // Inserts function Recursively
    updateAVLParentChild(left->root, root, true);
    root->height = max(root->height, 1 + left->root->height);
    totalComparisonCost = totalComparisonCost + left->getComparisonCost();
    totalParentChildUpdateCost = totalParentChildUpdateCost + left->getParentChildUpdateCost();

    if (!x)
    {
      return x;  //returns false is x is false
    }
  }
  // CHECKS PROPER ROTATION CONDITIONS ->
  
  if (root->left != NULL && root->right != NULL)
  {
    if (root->left->height - root->right->height > 1)
    {
      if (root->left->left != NULL && root->left->right != NULL)
      {
        if (root->left->left->height > root->left->right->height)
        {
          rotateLeftLeft(root->left->left, root->left, root);
          return true;
        }
        else
        {
          rotateLeftRight(root->left->right, root->left, root);
          return true;
        }
      }
      if (root->left->right == NULL)
      {
        rotateLeftLeft(root->left->left, root->left, root);
        return true;
      }
      else if (root->left->left == NULL)
      {
        rotateLeftRight(root->left->right, root->left, root);
        return true;
      }
    }
    if (root->right->height -root->left->height > 1)
    {
      if (root->right->left != NULL && root->right->right != NULL)
      {
        if (root->right->right->height > root->right->left->height)
        {
          rotateRightRight(root->right->right, root->right, root);
          return true;
        }
        else 
        {
          rotateRightLeft(root->right->left, root->right, root);
          return true;
        }
        if (root->right->right == NULL)
        {
          rotateRightLeft(root->right->left, root->right, root);
          return true;
        }
        else if (root->right->left == NULL)
        {
          rotateRightRight(root->right->right, root->right, root);
          return true;
        }
      }
    }
  }
  if (root->left == NULL && root->right != NULL)
  {
    if (root->height > 1)
    {
      if (root->right->left == NULL)
      {
        rotateRightRight(root->right->right, root->right, root);
        return true;
      }
      else
      {
        rotateRightLeft(root->right->left, root->right, root);
        return true;
      }
    }
  }
  if (root->right == NULL && root->left != NULL)
  {
    if (root->height > 1)
    {
      if (root->left->right == NULL)
      {
        rotateLeftLeft(root->left->left, root->left, root);
        return true;
      }
      else
      {
        rotateLeftRight(root->left->right, root->left, root);
        return true;
      }
    }
  }
  
  return true;
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *Tosearch = new TreeNode(jrnyCode, -100);
  TreeNode *temp = new TreeNode();
  temp = root;
  while (temp != NULL)
  {
    if (temp->getJourneyCode() == Tosearch->getJourneyCode())
    {
      return temp->getPrice();
    }
    else if (AVLLessThan(temp, Tosearch))
    {
      temp = temp->right;
    }
    else if(AVLLessThan(Tosearch,temp))
    {
      temp = temp->left;
    }
    else break;
  }
  return -1;

  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}
