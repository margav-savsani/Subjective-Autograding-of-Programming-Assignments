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

  TreeNode *T3 = parentNode->right;

  if(grandParentNode->parent == NULL){
    parentNode->parent = NULL;
    root = parentNode;
  }
  else {

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);}

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
  updateAVLParentChild(T3, grandParentNode, true);

  currNode->height = cal_height(currNode);
  parentNode->height = cal_height(parentNode);
  grandParentNode->height = cal_height(grandParentNode);

  return true;
  
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  if(grandParentNode->parent == NULL){
    parentNode->parent = NULL;
    root = parentNode;
  }
  else {

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

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
  }

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
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  currNode->height = cal_height(currNode);
  parentNode->height = cal_height(parentNode);
  grandParentNode->height = cal_height(grandParentNode);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *T2 = currNode->left;

  TreeNode *T3 = currNode->right;

  if(grandParent->parent == NULL){
    parent->parent = NULL;
    root = parent;
  }
  else {

  TreeNode *greatGrandParent = grandParent->parent;

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



  updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
  }

  updateAVLParentChild(parent, currNode, false);

  updateAVLParentChild(grandParent, currNode, true);

  updateAVLParentChild(T2, grandParent, false);

  updateAVLParentChild(T3, parent, true);

  currNode->height = cal_height(currNode);
  parent->height = cal_height(parent);
  grandParent->height = cal_height(grandParent);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *T3 = parent->right;

  if(grandParent->parent == NULL){
    parent->parent = NULL;
    root = parent;
  }
  else {

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  bool isGPLeftChild;
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


  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  }

  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T3, grandParent, false);

  currNode->height = cal_height(currNode);
  parent->height = cal_height(parent);
  grandParent->height = cal_height(grandParent);
  
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

void AVLTree::preo(TreeNode *tree){
    if(tree == NULL){
        return;
        }
    else{
        tree->height = cal_height(tree);
        preo(tree->left);
        preo(tree->right);
}
}



bool AVLTree::insert(int jrnyCode, int price)
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

  TreeNode *present = NULL;  //declare a null TreeNode
  TreeNode *search = root;   //root of the tree
   // TreeNode *given;           //node for the given values
   // given->JourneyCode = JourneyCode;  //assign passed journeycode and price to "given" treenode
    //given->price = price;

  TreeNode *given = new TreeNode(jrnyCode,price);
     
    while(search != NULL){   // while root of the tree is not null, repeat the loop. finally "search" will give the correct insertion position for the "given" node.
        present = search;    // stores parent of "search" in "present"
        if(AVLLessThan(given,search)){     //if price of root is greater than the given price
            search = search->left;            //go to the left subtree
        }
        else{                                 //if price of root is less than the given price
            search = search->right;           //go to the right subtree
        }
    }

    given->parent = present;    // make "present" the parent node of the given node. 

    if(present == NULL){   //if "present" is still NULL means our root of the tree was NULL
        root = given;      //store the "given" node into root. insertion complete
        root->height = cal_height(root);
        return true;
    }
    else if(AVLLessThan(given, present)){   //if "present" is not NULL and given price is less than the parent's price
        present->left = given;  // the "given" node will be left node of the parent. inserton complete
        preo(root);
        if(st==0){
          st++;
          return true;
        }
    }
    else if(AVLLessThan(present,given)){    //else the "given" node will be right node of the parent.
        present->right = given; 
        preo(root);  
        if(st==0){
          st++;
          return true;
        }             
    }

  given->parent->parent->height = cal_height(given->parent->parent);

    if(bf(given->parent->parent)>1 && bf(given->parent->parent->left)==1){
            cout << "too" << endl;
            rotateLeftLeft(given,given->parent,given->parent->parent);
             return true;
     }
     else if(bf(given->parent->parent)<-1 && bf(given->parent->parent->right)==-1){
            rotateRightRight(given,given->parent,given->parent->parent);
            return true;
     }
     else if(bf(given->parent->parent)<-1 && bf(given->parent->parent->right)==1){
              rotateRightLeft(given,given->parent,given->parent->parent);
              return true;
     }
     else if(bf(given->parent->parent)>1 && bf(given->parent->parent->left)==-1){
             rotateLeftRight(given,given->parent,given->parent->parent);
             return true;
     }

  return false;
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

  TreeNode *current_root = root;  //store root in TreeNode "current_root"
  TreeNode *now = new TreeNode(jrnyCode, 1);

    while(current_root!=NULL && current_root->getJourneyCode()!=jrnyCode){ //loop till current_root does not contain the given data
        if(current_root < now){
            current_root =  current_root->right;  //if given price is greater than price in current_root, store pointer of current_root->right into current_root 
        }
        else{
            current_root =  current_root->left;  // else store pointer of current_root->left into current_root
        }
    }
    if(current_root==NULL) return false;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(current_root->getJourneyCode()==jrnyCode){  // else ticket is present and return true
        return current_root->getPrice();
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


