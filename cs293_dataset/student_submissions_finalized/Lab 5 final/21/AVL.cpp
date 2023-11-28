#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// function to be called when the child as well as grandchild are to the left of their respective parent
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // will be rlinked with parent node
  TreeNode *greatGrandParentNode = grandParentNode->parent;  
  bool isGPLeftChild=true; 
  if (greatGrandParentNode != NULL && greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode != NULL && greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else root = parentNode;

  TreeNode *T3 = parentNode->right; // will be linked with grandparent node

  //four exchanges involved in LeftLeft Rotations
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild); 
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

// function to be called when the child is to left and the grandchild is to the right of their respective parent
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  // will be linked with currentnode
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild=true;
  if (greatGrandParentNode != NULL && greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode != NULL && greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else root = currNode;

  TreeNode *T2 = currNode->left; //will be linkd with parent node
  TreeNode *T3 = currNode->right;//will be linkd with grandparent node

  //five exchanges involved in LeftRight Rotations
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

// function to be called when the child is to right and the grandchild is to the left of their respective parent
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // will be linked with current node
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild=true;
  if (greatGrandParentNode != NULL && greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode != NULL && greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else root = currNode;

  TreeNode *T2 = currNode->right; //will be linkd with parent node
  TreeNode *T3 = currNode->left; //will be linkd with grandparent node

  //five exchanges involved in RightLeft Rotations
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //will be linked with the parent node
  TreeNode *greatGrandParentNode = grandParentNode->parent;  
  bool isGPLeftChild=true;
  if (greatGrandParentNode != NULL && greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode != NULL && greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else root = parentNode;

  TreeNode *T3 = parentNode->left; //will be linked with grandparent node

  //four exchanges involved in RightRight Rotations
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}


// Returns true on successful insertion in AVL tree. Returns false otherwise.
// Also performs the necessary rotations when the balance exceeds 1
bool AVLTree::insert(int jrnyCode, int price)
{
  // currNode and parentOfCurrNode track the position where the new node is to be inserted
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr; 

  TreeNode* new_node = new TreeNode(jrnyCode,price); // new node that is to be inserted

  //base cases : when there is no root just make the new node as root
  if( root == nullptr ){
    root = new_node;
    return true;
  }
  
  //loop untill the tracker reaches NULL pointer
  //basic principle/algorithm of binary insertion is followed
  while (currNode != nullptr) {
    if (AVLLessThan(currNode,new_node)) { 
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(new_node,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
  //inserting the node
  currNode = new_node; 
  if(AVLLessThan(currNode,parentOfCurrNode)) updateAVLParentChild(currNode,parentOfCurrNode,true); 
  else if(AVLLessThan(parentOfCurrNode,currNode)) updateAVLParentChild(currNode,parentOfCurrNode,false);
  else return false; 
  // now the new node is inserted into the tree as per normal binary insertion

  //required when we are performing rotation
  TreeNode* requiredChild = nullptr; 
  TreeNode* requiredGrandChild = nullptr;
  bool exit = false;

  // updation of height starts down from the inserted node
  while (currNode != nullptr){

    updateHeight(currNode); //height of tracker node is updated
    
    //when the balance of a node reaches 2 i.e exceeds one rotation is to be performed
    if (currNode->balance() == 2 && !exit ){
      //rotations are performed based on the cases as mentioned earlier
      if (requiredChild == currNode->left && requiredGrandChild == requiredChild->left) {
        rotateLeftLeft(requiredGrandChild,requiredChild,currNode);
        //after rotation the height of the three nodes are updated
        updateHeight(requiredGrandChild);
        updateHeight(currNode);
        updateHeight(requiredChild);
        currNode = requiredChild;
      }
      else if (requiredChild == currNode->right && requiredGrandChild == requiredChild->right) {
        rotateRightRight(requiredGrandChild,requiredChild,currNode);
        //after rotation the height of the three nodes are updated
        updateHeight(requiredGrandChild);
        updateHeight(currNode);
        updateHeight(requiredChild);
        currNode = requiredChild;
      }
      else if (requiredChild == currNode->left && requiredGrandChild == requiredChild->right) {
        rotateLeftRight(requiredGrandChild,requiredChild,currNode);
        //after rotation the height of the three nodes are updated
        updateHeight(requiredChild);
        updateHeight(currNode);
        updateHeight(requiredGrandChild);
        currNode = requiredGrandChild;
      }
      else if (requiredChild == currNode->right && requiredGrandChild == requiredChild->left) {
        rotateRightLeft(requiredGrandChild,requiredChild,currNode);
        //after rotation the height of the three nodes are updated
        updateHeight(requiredChild);
        updateHeight(currNode);
        updateHeight(requiredGrandChild);
        currNode = requiredGrandChild;
      }
      exit = true; //rotation needs to be done only once, the remaining automatically get balanced
    }

     //child,grandchild are updated in every loop
     requiredGrandChild = requiredChild;
     requiredChild = currNode;
     currNode=currNode->parent;

  }
  
  return true;
  
}

//updates the height of a node based on the height of its children nodes
void AVLTree::updateHeight(TreeNode* currNode){
  if(currNode->left==NULL && currNode->right==NULL) {
      currNode->height = 0; 
    }
    else if (currNode->left!=NULL && currNode->right==NULL ){
      currNode->height = currNode->left->height+1;
    }
    else if (currNode->left==NULL && currNode->right!=NULL ){
      currNode->height = currNode->right->height+1;
    }
    else{
      currNode->height = max(currNode->left->height+1,currNode->right->height+1);
    }
}


// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
int AVLTree::find(int jrnyCode)
{
  //algorithm is the exact same as find in normal BST

  TreeNode *search = root; //iterator node
  TreeNode *new_node = new TreeNode(jrnyCode,0); //new node with same journey code for comparison
    while (search != NULL){
        if (AVLLessThan(search,new_node)){
                search = search->right;
        }
        else if (AVLLessThan(new_node,search)){
                search = search->left;
        }
        else{
            return (search->getPrice());
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


