#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

#include <cmath>

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
  TreeNode* T3 = parentNode->right;
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  grandParentNode->height -= 2;
  root = parentNode; 
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode* T2 = currNode->left; 
  TreeNode* T3 = currNode->right; 

  currNode->height += 1;
  grandParentNode->height -= 2;
  parentNode->height -= 1;

  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  
  root = currNode;
  
  return true; 
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode* T2 = currNode->left; 
  TreeNode* T3 = currNode->right; 

  currNode->height += 1;
  grandParentNode->height -= 2;
  parentNode->height -= 1;

  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  root = currNode;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode* T3 = parentNode->left;
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  grandParentNode->height -= 2;
  root = parentNode; 
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int JourneyCode, int price)
{
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
  bool x = false;
  TreeNode *node = new TreeNode(JourneyCode, price);
  
  if (root == nullptr){
    root = node;
    root->height = 0;
    return true;
  }


  
  else if (AVLLessThan(node, root)){
      
      AVLTree* leftchild = new AVLTree(root->left, perComparisonCost, perParentChildUpdateCost);
      
      x = leftchild->insert(JourneyCode, price);
      updateAVLParentChild(leftchild->root, root, true);

      if (root->height >= leftchild->root->height + 1){}
      else {root->height = leftchild->root->height + 1;}
      // after this point, current stack frame goes from bottom to up. 
      // Hence, location of insertion is irrelevant until the imbalance arrives. 

      totalComparisonCost+= leftchild->totalComparisonCost;
      totalParentChildUpdateCost += leftchild->totalParentChildUpdateCost;
      
  }  

  else {
    AVLTree* rightchild = new AVLTree(root->right, perComparisonCost, perParentChildUpdateCost);

    x = rightchild->insert(JourneyCode, price);
    updateAVLParentChild(rightchild->root, root, false);

    if (root->height >= rightchild->root->height + 1){}
    else {root->height = rightchild->root->height + 1;}
    
    totalComparisonCost+= rightchild->totalComparisonCost;
    totalParentChildUpdateCost += rightchild->totalParentChildUpdateCost;

    // NODE INSERTED. 
  }

  // Now, keep terminating stack frames until imbalance is found. 

 
  if ((root->left == nullptr) || (root->right == nullptr)){
   
    if (root->height <= 1){return true; }

    if (root->left == nullptr){
      if (AVLLessThan(node, root->right)){rotateRightLeft(root->right->left, root->right, root);}
      else {rotateRightRight(root->right->right, root->right, root);}
      
    }
    else if (root->right == nullptr){
      if (AVLLessThan(node, root->left)){rotateLeftLeft(root->left->left, root->left, root);}
      else {rotateLeftRight(root->left->right, root->left, root);}
    }
    return true; 
  }

  if (abs(root->right->height - root->left->height) <= 1){return true;}
  else {
    /* Check which case of rotation */

    if (AVLLessThan(node, root)){
  
      // imbalance in left part
      if (AVLLessThan(node, root->left)){rotateLeftLeft(root->left->left, root->left, root);}
      else {rotateLeftRight(root->left->right, root->left, root);}
    }
    else {
      if (AVLLessThan(node, root->right)){rotateRightLeft(root->right->left, root->right, root);}
      else {rotateRightRight(root->right->right, root->right, root);}
    }
    return true;
  }
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int JourneyCode)
{
  TreeNode *node = new TreeNode(JourneyCode, 0);
  // Implement find in BST
  if (root == nullptr){
    return -1;
  }
  if (!AVLLessThan(root, node) && !AVLLessThan(node, root)){
    return root->price;
  }
  else if (AVLLessThan(node, root)){
    AVLTree* leftchild = new AVLTree(root->left, perComparisonCost, perParentChildUpdateCost);    
    int x = leftchild->find(JourneyCode);

    totalComparisonCost+= leftchild->totalComparisonCost;
    totalParentChildUpdateCost += leftchild->totalParentChildUpdateCost;

    return x;
  }
  else {
    AVLTree* rightchild = new AVLTree(root->right, perComparisonCost, perParentChildUpdateCost);    
    int x = rightchild->find(JourneyCode);

    totalComparisonCost+= rightchild->totalComparisonCost;
    totalParentChildUpdateCost += rightchild->totalParentChildUpdateCost;

    return x;
  }

  return -1;
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


