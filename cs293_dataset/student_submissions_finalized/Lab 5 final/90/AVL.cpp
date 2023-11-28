#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// The correspondence between the terminology in Prof. Garg's lectures and
// my terminology in this code is as follows:
//
// Prof. Garg's lectures           my code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //x is *currNode, y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild = false;
  if(greatGrandParentNode!=NULL){//Added this new condition to avoid null pointer errors.
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if(greatGrandParentNode->right != grandParentNode){
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

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
  return true;
}


bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //x is *currNode, y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateRightRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild = false;
  if(greatGrandParentNode!=NULL){//Added this new condition to avoid null pointer errors.
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if(greatGrandParentNode->right != grandParentNode){
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T3 be the left child of parentNode (i.e. of y)
  TreeNode *T3 = parentNode->left;

  // Make parentNode (y) the appropriate child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);


  // Make grandParentNode (z) the right child of parentNode (y)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

  // The left and right subtrees of currNode (i.e. x) stay unchanged after
  // the RightRight rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e., z) stays unchanged.  
  // Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y) should now become the right
  // child of grandParentNode (i.e. of z ).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);  
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

  bool isGPLeftChild = false;
  if(greatGrandParentNode!=NULL){//Added this new condition to avoid null pointer errors.
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if(greatGrandParentNode->right != grandParentNode){
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
  return true;
}


bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // x is *currNode, y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild = false;
  if(greatGrandParentNode!=NULL){//Added this new condition to avoid null pointer errors.
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if(greatGrandParentNode->right != grandParentNode){
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

  // Now replicate the double rotation for RightLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation  and arrive at that from the original tree.

  // Making currNode (x) the appropriate child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y) the right child of currNode (x)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z) the right child of currNode (x)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);

  // The right subtree of parentNode (i.e. y) and left subtree of 
  // grandParentNode (i.e. z ) stay unchanged
  // after the RightLeft rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x) should now become the right subtree of
  // grandparentNode (z).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // ParentNode (i.e. of y).

  // We use "true" as the third argument of the following call to indicate
  // that T2 should NOT become the right child of ParentNode
  updateAVLParentChild(T2, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}


// This function updates the height of the treenode
// by iterating from given TreeNode all the way to the root
// and updating all the nodes along the way.
void AVLTree::updateHeights(TreeNode* parentOfCurrNode){

  // exit the loop when node reaches the nullptr, which means 
  // it has already surpassed the root, and there is no
  // node left to be updated
  while(parentOfCurrNode!=nullptr){
      int heightL, heightR; 
      //heightL and heightR correspond to height of left child and right child respectively.
      if(parentOfCurrNode->right == nullptr){
        //height is zero for a nullpointer as there is nothing
        heightR = 0;
      } 
      else{
        heightR = parentOfCurrNode->right->height;
      }
      if(parentOfCurrNode->left == nullptr){
        //height is zero for a nullpointer as there is nothing
        heightL = 0;
      } 
      else{
        heightL = parentOfCurrNode->left->height;
      }

      //parent of the current node has maximum of heights of children nodes incremented by a 1
      parentOfCurrNode->height = max(heightL,heightR)+1;
      parentOfCurrNode = parentOfCurrNode->parent;
  }
}


//This function restores the balance in the tree, by doing 
//appropriate rotations and updating heights accordingly
void AVLTree::restore_balance(TreeNode* node){
  // Prof. Garg's lectures           My code
  // ---------------------           --------
  //   x                             currNode
  //   y                             parentNode
  //   z                             grandParentNode
  TreeNode* grandParentNode = node;
  TreeNode* parentNode = nullptr;
  TreeNode* currNode = nullptr;

  // We iteratively search for imbalance at the grandParentNode(i.e., z)
  // When grandparentNode becomes null pointer, that means it has crossed
  // the root, and there are no more nodes above it, hence there is no inbalance.
  while(grandParentNode!=nullptr){
    int diff; // stores the imbalance 
    //When grandParentNode(i.e., z) has no children, then imbalance = 0-0 = 0
    //This case shall never happen, but we have written this for the sake of 
    //understanding.
    if(grandParentNode->left == nullptr && grandParentNode->right == nullptr) diff = 0;
    //If grandParentNode(i.e., z) has only one child, then imbalance is equal to the 
    //height of the only child of z
    else if(grandParentNode->left == nullptr && grandParentNode->right != nullptr) diff = grandParentNode->right->height;
    else if(grandParentNode->left != nullptr && grandParentNode->right == nullptr) diff = grandParentNode->left->height;
    //When the grandparentNode(i.e., z)has two children, then imbalance is absolute difference
    //of the two heights
    else diff = abs(grandParentNode->right->height - grandParentNode->left->height);
    if(diff > 1) break;

    //updating the pointers to one step above in the path.
    currNode = parentNode;
    parentNode = grandParentNode;
    grandParentNode = grandParentNode->parent;
  }

  // If grandparentNode(i.e., z) is nullptr, it means that there is no imbalance,
  // so balance hadn't been disturbed.
  // If z is not nullptr then balance has been disturbed and now it shall be restored
  if(grandParentNode!=nullptr){

    //True when parentNode is to the left of grandparentNode, otherwise false
    bool y_z_lessthan = AVLLessThan(parentNode,grandParentNode);
    //True when currNode is to the left of parentNode, otherwise false
    bool x_y_lessthan = AVLLessThan(currNode,parentNode);

    // Prof. Garg's lectures           My code
    // ---------------------           --------
    //   x                             currNode
    //   y                             parentNode
    //   z                             grandParentNode

    //If x is to the left of y which is to the left of z
    //then perform a LL rotation
    //Also the height of grandparentNode reduces by 2
    if(y_z_lessthan && x_y_lessthan){
      rotateLeftLeft(currNode,parentNode,grandParentNode);
      grandParentNode->height -= 2;
    }

    //If x is to the right of y which is to the left of z
    //then perform a LR rotation
    //Also the height of grandparentNode reduces by 2
    //Height of currentNode increases by 1
    //And that of parent node reduces by 1
    else if(y_z_lessthan && !x_y_lessthan){
      rotateLeftRight(currNode,parentNode,grandParentNode);
      currNode->height++;
      parentNode->height--;
      grandParentNode->height -= 2;
    }

    //If x is to the left of y which is to the right of z
    //then perform a RL rotation
    //Also the height of grandparentNode reduces by 2
    //Height of currentNode increases by 1
    //And that of parent node reduces by 1
    else if(!y_z_lessthan && x_y_lessthan){
      rotateRightLeft(currNode,parentNode,grandParentNode);
      currNode->height++;
      parentNode->height--;
      grandParentNode->height -= 2;
    }

    //If x is to the right of y which is to the right of z
    //then perform a RR rotation
    //Also the height of grandparentNode reduces by 2
    else{
      rotateRightRight(currNode,parentNode,grandParentNode);
      grandParentNode->height -= 2;
    }
    updateHeights(grandParentNode->parent);
  }
  return;
}


// Returns true on successful insertion in AVLTree. Returns false otherwise.
// Also keeping in mind that no two nodes can have the same
// journey code
bool AVLTree::insert(int jrnyCode, int price){

  // Creating a new node named "SearchNode" containing the journey code
  // to be searched along with price set to some value(say 0), as the price
  // doesn't affect our code, as comparing journeycodes would itself suffice.
  // This is in accordance to the assumption, that no two nodes have the 
  // same journey code.  
  TreeNode* SearchNode = new TreeNode(jrnyCode,price);

  // Current Node is set to root, we start iterative search for the required node
  // by comparing the currNode with the SearchNode in every iteration and accordingly
  // chosing which path to follow down.
  // We additionally maintain a parent pointer to the current Node so that 
  // when the currNode becomes NULL, we do know what was the node, that gave
  // rise to the currNode=NULL
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    
  // Exit the looop when currNode is nullptr, this means that currNode travelled all the
  // way from root to a nullptr, which means that it did not find the required node
  while (currNode != nullptr) {

    // If JourneyCode of the Current Node is less than required
    // then travel along the right path from the current node.
    // Also update the parentOfCurrNode
    if (AVLLessThan(currNode, SearchNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }

    // If JourneyCode of the Current Node is greater than required
    // then travel along the left path from the current node.
    // Also update the parentOfCurrNode
    else if (AVLLessThan(SearchNode, currNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }

    // If both the above conditions fail, that means the journey code
    // of the current node and the required node are the same
    // In that case, the node we are aiming to insert has already
    // been inserted earlier, so return false.
    else {
      return false;
    }
  }

  // When the while loop ends the moment it begins, that means the tree
  // is empty, hence insert at the root position itself.
  if(parentOfCurrNode == nullptr){
    root = new TreeNode(jrnyCode,price);
  }
  else{
    bool isLeft; //true if SearchNode is to the left of parentOfCurrNode

    // If the journeyCode to be inserted is greated than parentOfCurrNode,
    // then insert to its right
    if(AVLLessThan(parentOfCurrNode, SearchNode)){
      isLeft = false;
      updateAVLParentChild(SearchNode,parentOfCurrNode,false);
    }

    // If the journeyCode to be inserted is greated than parentOfCurrNode,
    // then insert to its left
    else{
      isLeft = true;
      updateAVLParentChild(SearchNode,parentOfCurrNode,true);
    }

    // Update all nodes starting from parent of Current Node till the root.
    updateHeights(parentOfCurrNode);

    // Finally restoring the balance, by starting from left of inserted Node towards the root, 
    // and finding where is the imbalance occuring, and then performing appropriate rotations
    // and making necessary updations in height.
    if(isLeft){
      restore_balance(parentOfCurrNode->left);
    }
    else restore_balance(parentOfCurrNode->right);
  }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// Also keeping in mind that no two nodes can have the same
// journey code
int AVLTree::find(int jrnyCode)
{
  // Creating a new node named "SearchNode" containing the journey code
  // to be searched along with price set to some value(say 0), as the price
  // doesn't affect our code, as comparing journeycodes would itself suffice.
  // This is in accordance to the assumption, that no two nodes have the 
  // same journey code.  
  TreeNode* SearchNode = new TreeNode(jrnyCode,0);
  
  // Current Node is set to root, we start iterative search for the required node
  // by comparing the currNode with the SearchNode in every iteration and accordingly
  // chosing which path to follow down
  TreeNode *currNode = root;
    
  // Exit the looop when currNode is nullptr, this means that currNode travelled all the
  // way from root to a nullptr, which means that it did not find the required node 
  while (currNode != nullptr) {

    // If JourneyCode of the Current Node is less than required
    // then travel along the right path from the current node.
    if (AVLLessThan(currNode, SearchNode)){
      currNode = currNode->right;
    }

    // If JourneyCode of the Current Node is greater than required
    // then travel along the left path from the current node.
    else if (AVLLessThan(SearchNode, currNode)){
      currNode = currNode->left;
    }

    // If both the above conditions fail, that means the journey code
    // of the current node and the required node are the same
    // In that case, this is the node we are searching for, hence return
    // the price of the node
    else {
      return currNode->getPrice();
    }
  }

  // If execution comes out of the loop without returning, that implies
  // required node has not been found, hence return -1.
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
  TreeNode* SearchNode = new TreeNode(jrnyCode,0);
  TreeNode *currNode = root;
    
  while (currNode != nullptr) {
    if (AVLLessThan(currNode, SearchNode)){
      currNode = currNode->right;
    }
    else if (AVLLessThan(SearchNode, currNode)){
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      break;
    }
  }

  if(currNode == nullptr) return false;

  bool isLeft = false;
  if(currNode!=root){
    if(currNode->parent->left == currNode) isLeft = true;
  }

  if(currNode->right == nullptr && currNode->left == nullptr){
    if(currNode == root){
      root = nullptr;
    }
    else{
      if(currNode->parent->right == currNode) currNode->parent->right = nullptr;
      else currNode->parent->left = nullptr; 
    }
    updateHeights(currNode->parent); //height updation
  }
  else if(currNode->right != nullptr && currNode->left == nullptr){
    updateAVLParentChild(currNode->right,currNode->parent, isLeft);
    updateHeights(currNode->parent);
  }
  else if(currNode->left != nullptr && currNode->right == nullptr){
    updateAVLParentChild(currNode->left, currNode->parent, isLeft);
    updateHeights(currNode->parent);
  }
  else{ //That is when currNode has two children
    TreeNode* succNode = currNode->right;
    while(succNode->left != NULL){
      succNode = succNode->left;
    }

    if(succNode->parent == currNode){
      updateAVLParentChild(currNode->left,succNode,true);
      updateAVLParentChild(succNode,currNode->parent, isLeft);
      updateHeights(succNode);
    }
    else{
      TreeNode* parentOfSuccNode = succNode->parent;
      updateAVLParentChild(succNode->right,succNode->parent, true);
      updateAVLParentChild(currNode->right, succNode, false);
      updateAVLParentChild(currNode->left, succNode, true);
      updateAVLParentChild(succNode, currNode->parent, isLeft);
      updateHeights(parentOfSuccNode);
    }
  }
  return true;
}


