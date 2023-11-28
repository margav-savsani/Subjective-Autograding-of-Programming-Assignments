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
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T3 = parentNode->right;
    // parentNode->parent = nullptr;
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root = parentNode;
    parentNode->parent = nullptr;
  }
  else
  {
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
    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  parentNode->height = max(parentNode->right->height, parentNode->left->height) + 1;
  grandParentNode->height = max(grandParentNode->right->height, grandParentNode->left->height) + 1;
  return true;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).
  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    // currNode->parent = nullptr;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root = currNode;
    currNode->parent = nullptr;
  }
  else
  {
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
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  parentNode->height = max(parentNode->right->height, parentNode->left->height) + 1;
  grandParentNode->height = max(grandParentNode->right->height, grandParentNode->left->height) + 1;
  currNode->height = max(currNode->left->height, currNode->right->height) + 1;
  return true;
  // Let T2 be the left child of currNode (i.e. of x)
  // Let T3 be the right child of currNode (i.e. of x)
  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.
  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  // Recall from Prof. Garg's lectures that the left subtree of
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
  // Let's implement these updations below.
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParent = grandParent->parent;
  if (greatGrandParent == nullptr)
  {
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T3, parent, true);
    updateAVLParentChild(T2, grandParent, false);
    root = currNode;
    currNode->parent = nullptr;
  }
  else
  {
    bool isGPLeftChild;
    if (greatGrandParent->left == grandParent)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParent->right == grandParent)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T3, parent, true);
    updateAVLParentChild(T2, grandParent, false);
  }
  parent->height = max(parent->right->height, parent->left->height) + 1;
  grandParent->height = max(grandParent->right->height, grandParent->left->height) + 1;
  currNode->height = max(currNode->left->height, currNode->right->height) + 1;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParent = grandParent->parent;
  if (greatGrandParent == nullptr)
  {
    TreeNode *T3 = parent->left;
    // parent->parent = nullptr;
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    root = parent;
    parent->parent = nullptr;
  }
  else
  {
    bool isGPLeftChild;
    if (greatGrandParent->left == grandParent)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParent->right == grandParent)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    TreeNode *T3 = parent->right;
    updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
  }
  parent->height = max(parent->right->height, parent->left->height) + 1;
  grandParent->height = max(grandParent->right->height, grandParent->left->height) + 1;
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.
  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
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
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  TreeNode *ptr = new TreeNode(jrnyCode, price);
  if (AVLLessThan(ptr, root))
  {
    if (root->left == nullptr)
    {
      TreeNode *newNode = new TreeNode(jrnyCode, price);
      updateAVLParentChild(newNode, root, true);
      if (root->right == nullptr)
      {
        root->height = root->left->height + 1;
      }
      else
      {
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return true;
    }
    else
    {
      TreeNode *temp = root;
      root = root->left;
      bool sol = AVLTree::insert(jrnyCode, price);
      root = temp;
      if (root->right == nullptr)
      {
        root->height = root->left->height + 1;
      }
      else
      {
        root->height = max(root->right->height, root->left->height) + 1;
      }
      TreeNode *parent = root, *currNode = root->left, *grandParent = parent->parent;
      int bf = grandParent->getImbalance();
      if (grandParent == nullptr)
      {
        return sol;
      }
      else
      {
        if (bf > 1 && grandParent->left == root)
        {
          rotateLeftLeft(currNode, parent, grandParent);
        }
        if (bf < -1 && grandParent->right == root)
        {
          rotateRightLeft(currNode, parent, grandParent);
        }
      }
      return sol;
    }
  }
  else if (AVLLessThan(root, ptr))
  {
    if (root->right == nullptr)
    {
      TreeNode *newNode = new TreeNode(jrnyCode, price);
      updateAVLParentChild(newNode, root, false);
      if (root->left == nullptr)
      {
        root->height = root->right->height + 1;
      }
      else
      {
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return true;
    }
    else
    {
      TreeNode *temp = root;
      root = root->right;
      bool sol = AVLTree::insert(jrnyCode, price);
      root = temp;
      if (root->left == nullptr)
      {
        root->height = root->right->height + 1;
      }
      else
      {
        root->height = max(root->right->height, root->left->height) + 1;
      }
      TreeNode *parent = root, *currNode = root->left, *grandParent = parent->parent;
      if (grandParent == nullptr)
      {
        return sol;
      }
      else
      {
        int bf = grandParent->getImbalance();
        if (bf < -1 && grandParent->right == root)
        {
          rotateLeftLeft(currNode, parent, grandParent);
        }
        if (bf > 1 && grandParent->left == root)
        {
          rotateLeftRight(currNode, parent, grandParent);
        }
      }

      return sol;
    }
  }
}

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
  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode *ptr = new TreeNode(jrnyCode, 0); //node to be found
  if (root == nullptr) //if root == nullptr, return -1
  {
    return -1;
  }
  if (AVLLessThan(ptr, root))
  {
    if (root->left == nullptr) //if root->left == nullptr, return -1
    {
      return -1;
    }
    AVLTree *leftTree = new AVLTree(root->left, perComparisonCost, perParentChildUpdateCost);
    leftTree->find(jrnyCode);
  }
  else if (AVLLessThan(root, ptr))
  {
    if (root->right == nullptr) //if root->right == nullptr, return -1
    {
      return -1;
    }
    AVLTree *rightTree = new AVLTree(root->right, perComparisonCost, perParentChildUpdateCost);
    rightTree->find(jrnyCode);
  }
  else
  {
    return root->getPrice();
  }
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
