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
  TreeNode *T3 = parentNode->right;
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild = false;
  if (greatGrandParentNode != nullptr){
    if (greatGrandParentNode -> left == grandParentNode){
      isGPLeftChild = true;
    } else if (greatGrandParentNode -> right == grandParentNode){
      isGPLeftChild = false;
    } else {
      return false;
    }
  } else {
    this->root = parentNode;
  }
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures

  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);
  grandParentNode->height = grandParentNode->height - 1;

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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (grandParentNode != nullptr){
    if (greatGrandParentNode -> left == grandParentNode){
      isGPLeftChild = true;
    } else if (greatGrandParentNode -> right == grandParentNode){
      isGPLeftChild = false;
    } else {
      return false;
    }
  } else {
    this->root = currNode;
  }
  // leftChild of currNode
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  
  updateAVLParentChild(currNode, grandParentNode, true); // make currNode child of grandparent

  updateAVLParentChild(parentNode, currNode, true); //make parent node child of current node

  updateAVLParentChild(T2, parentNode, false); //make left child of currNode to right child of parent node

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild); //make the new parent node the child of great grand parent.

  

  updateAVLParentChild(grandParentNode, currNode, false); //make grandparent node the right child of the new parent node.

  updateAVLParentChild(T3, grandParentNode, true); //make the right subtree of currNode the left subtree of grandParentNode.


  //updating heights to new values.
  currNode->height = grandParentNode->height;
  parentNode->height = parentNode->height - 1;
  grandParentNode->height = grandParentNode->height -1;



  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  TreeNode * greatGrandParent = grandParent->parent;

  bool isGPLeftChild;


  //do not greatGrandParents if it doesnt exists
  if (greatGrandParent != nullptr){
    if (greatGrandParent -> left == grandParent){
      isGPLeftChild = true;
    } else if (greatGrandParent -> right == grandParent){
      isGPLeftChild = false;
    } else {
      return false;
    }
  } else {
    this->root = currNode;
  }

  TreeNode * T2 = currNode -> right;
  TreeNode * T3 = currNode -> left;
  updateAVLParentChild(currNode, grandParent, false); //make the currNode child of grnadparent node

  updateAVLParentChild(parent, currNode, false); //make the old parent node child of the old current node

  updateAVLParentChild(T2, parent, true); //make right subtree of currNode the leftsubtree of parentNode

  updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild); //make new parent node the child of grandParent node.

  

  updateAVLParentChild(grandParent, currNode, true); //make grandparentNode the child of the currNode.

  updateAVLParentChild(T3, grandParent, false); //make make the left subtree of currNode the right subtree of grandparent node. 


  //updating heights to new values.
  currNode->height = grandParent->height;
  parent->height = parent->height - 1;
  grandParent->height = grandParent->height -1;




  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  TreeNode * greatGrandParent = grandParent->parent;

  bool isGPLeftChild;
  
  if (greatGrandParent != nullptr){ //if greatGrandParent is a nullptr then dont check for left of right childs.
    if (greatGrandParent -> left == grandParent){
      isGPLeftChild = true;
    } else if (greatGrandParent -> right == grandParent){
      isGPLeftChild = false;
    } else {
      return false;
    }
  } else {
    this->root = parent;
  }

  //pointer updates corresponding to rotations.
  updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);



  updateAVLParentChild(currNode, parent, false);
  TreeNode* T3 = parent->left;

  updateAVLParentChild(grandParent, parent, true);
  
  
  //updating heights to new values.
  grandParent->height = grandParent->height - 1;


  updateAVLParentChild(T3, grandParent, false);




  





  
  return true;
}

void AVLTree::Rotate(TreeNode * curr, TreeNode * parent, TreeNode * grandParent){
  
  //check if parent and child are leftchild or rightchild of their parents
  bool pleft = false;
  bool cleft = false;


  //call appropriate rotate function.
  if (grandParent->left == parent){
      pleft = true;
  } else pleft = false ;

  if (parent->left == curr){
    cleft = true;
  } else cleft = false;

  if (pleft && cleft){
    this->rotateLeftLeft(curr, parent, grandParent);
  } else if (pleft && !cleft){
    this->rotateLeftRight(curr, parent, grandParent);
  } else if (!pleft && cleft){
    this->rotateRightLeft(curr, parent, grandParent);
  } else {
    this->rotateRightRight(curr, parent, grandParent);
  }
}

//consider height of nullptr to be -1
//Imbalance returns the difference of heights of its two trees.
int getImabalance(TreeNode * currNode){
  
  if (currNode -> left == nullptr){

    return -1 -currNode->right->height;

  } else if (currNode -> right == nullptr ){
    return currNode->left->height + 1;
  } else {
    return currNode->left->height - currNode->right->height;
  }
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
  TreeNode* toInsert = new TreeNode(jrnyCode, price);
  TreeNode *currNode = root;

  bool inserted = false;

  if (currNode == nullptr) { 
    root = toInsert;
    return true;
  }

  //Insert implemented like a normal BST
  while (!inserted){
    if (AVLLessThan(toInsert, currNode)){
      if (currNode->left == nullptr){
        updateAVLParentChild(toInsert, currNode, true);
        inserted = true;

      
      } else {
        currNode = currNode -> left;
      }
    } else if (AVLLessThan(currNode, toInsert)) {
      if (currNode -> right == nullptr){
        updateAVLParentChild(toInsert, currNode, false);
        inserted = true;
      } else {
        currNode = currNode -> right;
      }

    } else {
        return false;
    }

    

  }


  //Traverse up the path from leaf to the root and search for imbalance
  TreeNode * gparent = currNode;
  TreeNode * parent = toInsert;
  TreeNode * child = nullptr;
  //TreeNode * child = nullptr;

  while (currNode != nullptr){

    //if imbalance not found, update the heights.
    if (getImabalance(currNode) <= 1 && getImabalance(currNode) >= -1){
      if (currNode->left == nullptr){
        currNode->height = currNode->right->height + 1;
      } else if (currNode->right == nullptr){
        currNode->height = currNode->left->height + 1;
      } else {
        if (currNode->left->height > currNode->right->height){
          currNode->height = currNode->left->height + 1;
        } else {
          currNode->height = currNode->right->height + 1;
        }
      }

      

      currNode = currNode -> parent;
      child = parent;
      parent = gparent;
      gparent = currNode;

      
      
      

    } else {
      //if imbalance is found at the node, then rotate.
      Rotate(child, parent, gparent);
      break;
    }
  }




  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode * currNode = root;
  TreeNode * toFind = new TreeNode(jrnyCode, 9999);
  //if node less than currnode, if greater go right, otherwise we have found the element.
  while (currNode != nullptr){
    if (AVLLessThan(toFind, currNode)){
      currNode = currNode -> left;
    } else if (AVLLessThan(currNode, toFind)) {
      currNode = currNode -> right;
    } else {
      return currNode->getPrice();
    } 


  }
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


