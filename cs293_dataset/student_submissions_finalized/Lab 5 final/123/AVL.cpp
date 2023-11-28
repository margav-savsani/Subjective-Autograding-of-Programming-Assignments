#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);

  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, true);

  updateAVLParentChild(grandParentNode, currNode, false);
  
  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, false);

  updateAVLParentChild(grandParentNode, currNode, true);
  
  updateAVLParentChild(T3, parentNode, true);

  updateAVLParentChild(T2, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->left;
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);

  updateAVLParentChild(grandParentNode, parentNode, true);

  updateAVLParentChild(T3, grandParentNode, false);

  
  return true;
}


bool AVLTree::insert(int JourneyCode, int price)
{
  TreeNode* newnode = new TreeNode(JourneyCode,price);
        TreeNode *y = NULL;
        TreeNode *x = root;
        bool left;
        if(find(JourneyCode) == 1){
            return false;
        }
        while(x != NULL){
            y = x;
            if(AVLLessThan(newnode,x)){
                x = x->left;
                left = true;
            }
            else{
                x = x->right;
                left = false;
            }
            }
        updateAVLParentChild(newnode, y , left);
            cout<<"Kusal"<<endl;
        x=newnode;
        while (y != nullptr)
        {
            if (y->height < 1 + x->height)
            {
                y->height = 1 + x->height;
            }
            x = y;
            y = y->parent;
        }
  
  while (true)
  {
    if (y == nullptr)
      break;
    if (y->left != nullptr && y->right != nullptr)
    {
      if (y->left->height - y->right->height <= 1 && y->left->height - y->right->height >= -1)
      {
        //cout << y->left->height << " " << y->right->height << endl;
        x = y;
        y = y->parent;
      }
      else
      {
        //cout << y->left->height << " " << y->right->height << endl;
        //cout << "break1" << endl;
        break;
      }
    }
    else if (y->left != nullptr)
    {
      if (y->left->height <= 0)
      {
        // cout<<y->left->height <<" "<< y->right->height<<endl;
        x = y;
        y = y->parent;
      }
      else
      {
        //cout << "break2" << endl;
        break;
      }
    }
    else if (y->right != nullptr)
    {
      if (y->right->height <= 0)
      {
        // cout<<y->left->height <<" "<< y->right->height<<endl;
        x = y;
        y = y->parent;
        //cout << "scratch" << endl;
      }
      else
      {
        //cout << "break3" << endl;
        break;
      }
    }
  }

  bool isLeft1, isLeft2;
  if (y != NULL)
  {
    TreeNode *grandParent = y;

    TreeNode *parent = x;
    TreeNode *current;

    if (grandParent->left == parent)
      isLeft1 = true;
    else
      isLeft1 = false;
    if (parent->left != nullptr && parent->right != nullptr)
    {
      if (parent->left->height > parent->right->height)
      {
        current = parent->left;
        isLeft2 = true;
      }
      else
      {
        current = parent->right;
        isLeft2 = false;
      }
    }
    else if (parent->left != nullptr)
    {
      current = parent->left;
      isLeft2 = true;
    }

    else if (parent->right != nullptr)
    {
      current = parent->right;
      isLeft2 = false;
    }
    if (isLeft1)
    {
      if (isLeft2)
        rotateLeftLeft(current, parent, grandParent);
      else
        rotateLeftRight(current, parent, grandParent);
    }
    else
    {
      if (isLeft2)
        rotateRightLeft(current, parent, grandParent);
      else
      {
        rotateRightRight(current, parent, grandParent);
      }
    }
  }
  return true;
}


int AVLTree::find(int JourneyCode)
{
  TreeNode *x;
    x = root;
    TreeNode* newnode = new TreeNode(JourneyCode,1);
    if(x == NULL){
        return -1;
    }
    if(!(AVLLessThan(x,newnode) || AVLLessThan(newnode,x))){
        return 1;
    }
    else{
        if(AVLLessThan(newnode,x)){
            x = x->left;
            AVLTree* leftTree = new AVLTree(x);
            return leftTree->find(JourneyCode);
        }
        else{
            x = x->right;
            AVLTree* rightTree = new AVLTree(x);
            return rightTree->find(JourneyCode);
        }
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


