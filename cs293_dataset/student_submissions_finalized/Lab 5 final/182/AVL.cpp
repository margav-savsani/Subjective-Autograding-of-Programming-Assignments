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
//   y                             parent
//   z                             grandParent
//
// Recall also that z (grandParent) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parent) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the left child of parent, and
  // parent is the left child of grandParent
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParent
  
  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parent (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParent
  updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parent
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of parent
  updateAVLParentChild(grandParent, parent, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParent (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParent doesn't need to be updated at all.
  // The only update needed is that the right subtree of parent (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParent (i.e. of z in Prof. Garg's notes).

  // Let T3 be the right child of parent (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the right child of parent, and
  // parent is the left child of grandParent.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParent

  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent) {
    isGPLeftChild = true;
updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);

  // Make parent (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parent should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parent (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParent (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parent and the right child of grandParent
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parent (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParent (i.e. of z).
       
  // Let's implement these updations below.
       
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of Parent
  updateAVLParentChild(T2, parent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParent

  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent) {
    isGPLeftChild = false;
  }
  else if (greatGrandParent->right == grandParent) {
    isGPLeftChild = true;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParent
   updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parent
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of parent
  updateAVLParentChild(grandParent, parent, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParent (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParent doesn't need to be updated at all.
  // The only update needed is that the right subtree of parent (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParent (i.e. of z in Prof. Garg's notes).

  // Let T3 be the right child of parent (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  
  TreeNode *greatGrandParent = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParent

  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent) {
    isGPLeftChild = false;
  }
  else if (greatGrandParent->right == grandParent) {
    isGPLeftChild = true;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParent
 updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);

  // Make parent (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parent should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parent (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParent (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parent and the right child of grandParent
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parent (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParent (i.e. of z).
       
  // Let's implement these updations below.
       
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of Parent
  updateAVLParentChild(T2, parent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);

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
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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
  return true;
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
  struct TreeNode *currNode = root;
  struct TreeNode *n;
  int price=0;
  n=new TreeNode(jrnyCode,price);
  
  while (currNode != nullptr) {
   // if (currNode->getJourneyCode() < jrnyCode)
   if(AVLLessThan(currNode,n)) {
      currNode = currNode->right;
    }
    else if (AVLLessThan(n,currNode)) {
      currNode = currNode->left;
    }
    else { return currNode->getJourneyCode();
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
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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


