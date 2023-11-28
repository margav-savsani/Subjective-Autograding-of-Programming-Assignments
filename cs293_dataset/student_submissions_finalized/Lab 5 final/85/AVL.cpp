#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
#endif


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    parentNode->parent = nullptr;
    root = parentNode;
    root->height = Height(root);
    return true;
  }
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

 
  updateAVLParentChild(T3, grandParentNode, true);
  root->height = Height(root);
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);

    updateAVLParentChild(T2, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    root = currNode;
    root->height = Height(root);
    return true;
  }
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);

 
  // Let's implement these updations below.

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  root->height = Height(root);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(parentNode, currNode, false);

    updateAVLParentChild(grandParentNode, currNode, true);

    updateAVLParentChild(T2, grandParentNode, false);

    updateAVLParentChild(T3, parentNode, true);

    root = currNode;
    root->height = Height(root);
    return true;
  }
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parentNode, true);
  root->height = Height(root);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = parentNode->left;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(currNode, parentNode, false);

    updateAVLParentChild(grandParentNode, parentNode, true);

    updateAVLParentChild(T2, grandParentNode, false);

    parentNode->parent = nullptr;
    root = parentNode;
    root->height = Height(root);
    return true;
  }
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  root->height = Height(root);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::Height(TreeNode *head)
{
  if (head == NULL)
    return -1;
  if (head->left == NULL && head->right == NULL)
    return 0;
  int left_height = Height(head->left);

  int right_height = Height(head->right);

  if (head->left != NULL)
    head->left->height = left_height;
  if (head->right != NULL)
    head->right->height = right_height;
  if (left_height < right_height)
  {
    return 1 + right_height;
  }
  else
  {
    return 1 + left_height;
  }
}
TreeNode *AVLTree::balance(TreeNode *N)
{

  if (N == NULL)
  {
    return NULL;
  }
  int h = (Height(N->left) - Height(N->right));
  if (abs(h) > 1)
  {
    return N;
  }
  else
  {
    return balance(N->parent);
  }
}
int length(TreeNode *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.
  if (find(jrnyCode) == jrnyCode)
  {
    return false;
  }
  else
  {
    TreeNode *T = new TreeNode(jrnyCode, price);
    TreeNode *t = new TreeNode(0, 0);

    t = root;

    if (root == NULL)
    {
      
      root = new TreeNode(jrnyCode, price);
      root->height = 1;
      return true;
    }
    while (t != NULL)
    {
      if (AVLLessThan(t, T))
      {
        if (t->right == NULL)
        {
          updateAVLParentChild(T, t, false);
          t->right = T;

          T->parent = t;
          T->JourneyCode = jrnyCode;
          T->price = price;
          root->height = Height(root);
          break;
        }
        else
        {
          t = t->right;
        }
      }
      else if (AVLLessThan(T, t))
      {
        if (t->left == NULL)
        {
          updateAVLParentChild(T, t, true);
          root->height = Height(root);
          break;
        }
        else
        {
          t = t->left;
        }
      }
    }

    TreeNode *node = balance(T);
    if (node == nullptr)
      return true;
    else
    {
      if (AVLLessThan(T, node))
      {
        if (AVLLessThan(T, node->left))
        {
          return rotateLeftLeft(node->left->left, node->left, node);
        }
        else
        {
          return rotateLeftRight(node->left->right, node->left, node);
        }
      }
      else
      {
        if (AVLLessThan(T, node->right))
        {
          return rotateRightLeft(node->right->left, node->right, node);
        }
        else
        {
          return rotateRightRight(node->right->right, node->right, node);
        }
      }
    }
  }
}
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

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.
  TreeNode *t = new TreeNode(0, 0);
  t->JourneyCode = jrnyCode;
  TreeNode *T = root;
  while (T != NULL)
  {
    if (T->JourneyCode == jrnyCode)
    {
      return jrnyCode;
    }
    else if (AVLLessThan(t, T))
    {
      T = T->left;
    }
    else if (AVLLessThan(T, t))
    {
      T = T->right;
    }
    else
    {
      return -1;
    }
  }
  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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
