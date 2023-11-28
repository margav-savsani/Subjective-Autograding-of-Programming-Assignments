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

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild=true;

  //Checking if the grandparent node is the root of the tree
  if(greatGrandParentNode != nullptr){
      if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  //Updating the root if the grandparent node is the root of the tree
  if(greatGrandParentNode == nullptr)root = parent;

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, false);

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
  updateAVLParentChild(T3, grandParent, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild=true;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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
  if(greatGrandParentNode == nullptr)root = currNode;

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
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
  updateAVLParentChild(T2, parent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  bool isGPLeftChild=true;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  TreeNode *T2 = currNode->right;
  
  TreeNode *T3 = currNode->left;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  if(greatGrandParentNode == nullptr)root = currNode;

  updateAVLParentChild(parent, currNode, false);

  updateAVLParentChild(grandParent, currNode, true);

  updateAVLParentChild(T2, parent, true);

  updateAVLParentChild(T3, grandParent, false);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
 
  bool isGPLeftChild=true;
  if(greatGrandParentNode != nullptr){
      if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  
  TreeNode *T3 = parent->left;

  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  if(greatGrandParentNode == nullptr)root = parent;

  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T3, grandParent, false);

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
  if(find(jrnyCode) != -1)false;

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

  TreeNode *noden=new TreeNode(jrnyCode, price);
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (AVLLessThan(currNode,noden)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(noden, currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->jrnyCode == jrnyCode
      return false;
    }
  }
  bool var=true;
  if(parentOfCurrNode != nullptr){
    var = AVLLessThan(noden,parentOfCurrNode);
  }
  
  //Inserting the node at appropriate position
  updateAVLParentChild(noden, parentOfCurrNode, var);
  if(root == nullptr)root=noden;


  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  TreeNode *x=noden, *y=noden , *z=noden->parent;
  int i = 1;
  //Checking whether the insertion causes any imbalance and changing the heights accordingly
  while(true){
    int hr=-1,hl=-1;
    bool yzl;
    if(z==nullptr)break;
    if(z->height > y->height)break;
    if(y == z->right){
      yzl = false;
      hr = y->height;
      if(z->left != nullptr){
        hl = z->left->height;
      }
      else hl=-1;
    }
    else{
      yzl = true;
      hl = y->height;
      if(z->right != nullptr){
        hr = z->right->height;
      }
      else hr = -1;
    }
    if((hl-hr)*(hr-hl)<-1){
      //handling the rotations after the imbalance is found.
      bool xyl;
      if( x == y->right)xyl=false;
      else xyl = true;

      if(xyl && yzl){
        rotateLeftLeft(x, y, z);
        z->height -= 1;
      }
      else if( !xyl && yzl){
        rotateLeftRight(x, y, z);
        x->height += 1;
        y->height -= 1;
        z->height -= 1;
      }
      else if( xyl && !yzl){
        rotateRightLeft(x, y, z);
        x->height += 1;
        y->height -= 1;
        z->height -= 1;
      }
      else if( !xyl && !yzl){
        rotateRightRight(x, y, z);
        z->height -= 1;
      }
      break;
    }
    //Updating the heights and pointers when no imbalance is found
    z->height += 1;
    z = z->parent;
    y = y->parent;
    if(i==0)x=x->parent;
    i=0;
  }
  
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
  TreeNode *cmp = new TreeNode(jrnyCode,0);
  TreeNode *currNode = root;
  while( currNode != nullptr){
    bool v1 = AVLLessThan(currNode, cmp);
    if(v1){
      currNode = currNode->right;
      continue;}
    bool v2 = AVLLessThan(cmp, currNode);
    if(v2){
      currNode = currNode->left;
      continue;}
    if(!(v1 || v2))return currNode->getprice();
  }

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


