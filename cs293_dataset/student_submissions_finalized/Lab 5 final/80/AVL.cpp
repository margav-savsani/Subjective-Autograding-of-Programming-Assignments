#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif



bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;//create a greatgrandparent node to check how the subtree is connected to the main tree
  bool isGPRoot;//check if grandparent is already the root
  if (greatGrandParentNode == nullptr){
    isGPRoot=true;
  }
  else{
    isGPRoot=false;
  }
  //check if grandparent is the left child of greatgrandparent
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(!isGPRoot){
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
  }


  TreeNode *T3 = parentNode->right; //a subtree to be moved around according to algorithm



//moves of the algorithms


  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);


  updateAVLParentChild(currNode, parentNode, true);
  

  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);
  if(isGPRoot){
    root = parentNode;
  }

  return true;
}


//similar idea to the above function is implemented 4 times in total.
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{


  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPRoot;
  if (greatGrandParentNode == nullptr){
    isGPRoot=true;
  }
  else{
    isGPRoot=false;
  }
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(!isGPRoot){
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
  if(isGPRoot){
    root = currNode;
  }
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

// Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPRoot;
  if (greatGrandParentNode == nullptr){
    isGPRoot=true;
  }
  else{
    isGPRoot=false;
  }
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(!isGPRoot){
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
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

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
  updateAVLParentChild(parentNode, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);
  
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
  updateAVLParentChild(T2, parentNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  if(isGPRoot){
    root = currNode;
  }
  return true;


}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPRoot;
  if (greatGrandParentNode == nullptr){
    isGPRoot=true;
  }
  else{
    isGPRoot=false;
  }
  bool isGPLeftChild;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(!isGPRoot){
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
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->left;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

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
  updateAVLParentChild(T3, grandParentNode, false);
  if(isGPRoot){
    root = parentNode;
  }
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{


  //cout << getComparisonCost() << endl;
  //cout << getParentChildUpdateCost() << endl;
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



  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

  TreeNode *insertion_node = new TreeNode(jrnyCode, price);//preparing the node to be inserted
  insertion_node->parent=nullptr;
  insertion_node->height=0;
  //cout << "nodes initalized" << endl;


  //searching for position to insert
  while (currNode != nullptr) {
    //cout << "in while loop"<< endl;
    if (AVLLessThan(currNode, insertion_node)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(insertion_node,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      //currNode->height -= 1;
      return false;
    }
  }

  if(parentOfCurrNode==nullptr){//checking if tree was empty earlier and this node is the first
    root=insertion_node;
    root->height = 0;
    //cout << "root assigned" << endl;
    return true;
  }
  //insertion of the node
  if(AVLLessThan(parentOfCurrNode,insertion_node)){
    updateAVLParentChild(insertion_node, parentOfCurrNode, false);
  }
  else{
    updateAVLParentChild(insertion_node, parentOfCurrNode, true);
  }


  //going up the tree to update heights and to solve imbalances
  TreeNode *grandparentNode = parentOfCurrNode->parent;
  if (grandparentNode == nullptr){
    parentOfCurrNode->height=1;
    return true;//check if the tree's height is too small to have a grandparent
  }
  //cout << "here" << endl;
  while(grandparentNode!=nullptr){
    if(parentOfCurrNode->left==nullptr){
      parentOfCurrNode->height= parentOfCurrNode->right->height + 1;
    }
    else if(parentOfCurrNode->right==nullptr){
      parentOfCurrNode->height = parentOfCurrNode->left->height + 1;
    }
    else{
      parentOfCurrNode->height = max(parentOfCurrNode->right->height, parentOfCurrNode->left->height) + 1;//incrementing heights
    }
    int imbalance_param=grandparentNode->check_imbalance();
    if(imbalance_param != 0){//special case with some imbalance. Need rotations
      //cout << "imbalance found " << imbalance_param << endl;
      if(imbalance_param==1){//if imbalance is on left side
        if(parentOfCurrNode->left==insertion_node){
          rotateLeftLeft(insertion_node, parentOfCurrNode, grandparentNode);
          grandparentNode->height-=1;
          grandparentNode=parentOfCurrNode->parent;
          continue;
        }
        else{
          rotateLeftRight(insertion_node, parentOfCurrNode, grandparentNode);
          insertion_node->height+=1;
          parentOfCurrNode->height-=1;
          grandparentNode->height-=1;
          grandparentNode=insertion_node->parent;
          parentOfCurrNode=insertion_node;
          insertion_node=parentOfCurrNode->left;
          continue;
        }
      }
      else{//if imbalance is on right side
        if(parentOfCurrNode->left==insertion_node){
          rotateRightLeft(insertion_node, parentOfCurrNode, grandparentNode);
          insertion_node->height+=1;
          parentOfCurrNode->height-=1;
          grandparentNode->height-=1;
          grandparentNode=insertion_node->parent;
          parentOfCurrNode=insertion_node;
          insertion_node=parentOfCurrNode->left;
          continue;
        }
        else{
          rotateRightRight(insertion_node, parentOfCurrNode, grandparentNode);
          grandparentNode->height-=1;
          grandparentNode=parentOfCurrNode->parent;
          continue;
        }
      }
      //here, rotations were done, heights were alterred and the nodes were suitably adjusted so that the travel up the tree continues.
    }
    insertion_node = insertion_node->parent;
    parentOfCurrNode = parentOfCurrNode->parent;
    grandparentNode = grandparentNode->parent;
  }
  root->height=max(root->right->height, root->left->height) + 1;


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

  TreeNode *find_node = new TreeNode(jrnyCode, 0);//create a new node that contains id of node to be found.
  TreeNode *curr_node = root;
  if(curr_node==nullptr){
    return -1;//return -1 if tree is already empty
  }
  //cout << "here" << endl;
  //go to location where node should be
  while (AVLLessThan(curr_node,find_node) || AVLLessThan(find_node,curr_node)){
    //cout << "bah" << endl;
    if(AVLLessThan(curr_node,find_node)){
      curr_node=curr_node->right;
    }
    else if(AVLLessThan(find_node,curr_node)){
      curr_node=curr_node->left;
    }

    if(curr_node==nullptr){
      return -1;//return -1 if point where node should be is empty
    }

  }
  //cout << "about to return" << endl;
  return curr_node->height;}//return non neg number if found.

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


