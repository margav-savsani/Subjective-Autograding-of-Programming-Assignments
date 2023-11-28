#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  //when greatgrandparent is nullptr you cannot access its left and right hence need
  //to handle that case seperately

  if(greatGrandParentNode!=nullptr){
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

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }

  //need to set parentNode as root too else wouldn't print correctly
  else{
    //true,false dosen't matter here due to the way it is handelled in the fn
    updateAVLParentChild(parentNode,greatGrandParentNode,false);
    root=parentNode;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

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
  if(greatGrandParentNode!=nullptr){
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
  else{
    bool isGPLeftChild=true;//dosen't matter if set true or false;
    root=currNode;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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
  // Implement this yourself
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  else{
    bool isGPLeftChild=true;//dosen't matter if set true or false;

    //updating the root
    root=currNode;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, false);
  
  updateAVLParentChild(grandParentNode, currNode, true);

  updateAVLParentChild(T2, grandParentNode, false);

  updateAVLParentChild(T3, parentNode, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode!=nullptr){
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
  }
  else{
    updateAVLParentChild(parentNode,greatGrandParentNode,true);

    //updating the root
    root=parentNode;
  }

  TreeNode *T3 = parentNode->left;

  updateAVLParentChild(currNode, parentNode, false);
  
  updateAVLParentChild(grandParentNode, parentNode, true);

  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *to_ins = new TreeNode(jrnyCode,price);
  TreeNode *x,*y;
  x=root;
  y=nullptr;

  if(N==0){
    updateAVLParentChild(to_ins,nullptr,true);
    root = to_ins;
    N=1;
    return true;
  }

  else{
    while(x!=nullptr){
      y=x;
      if(AVLLessThan(to_ins,x)){
        x=x->left;
      }
      else if(AVLLessThan(x,to_ins)){
        x=x->right;
      }
      else{
        return false;
      }
    }
    if(AVLLessThan(to_ins,y)){
      updateAVLParentChild(to_ins,y,true);
    }
    else{
      updateAVLParentChild(to_ins,y,false);
    }
    //do not need to update height here as after rotations height of the nodes
    //above the first point of imbalance does not change and hence updating heights of
    //all nodes would make the code inefficient
  }

  //creating two new variables to store what rotations are to be called if found imbalanced
  bool par_curr_left, grand_par_left;
  //grandparent node would be stored here
  TreeNode *current;

  //checking if imbalance is present and the function itself sets the bool and returns the node
  //this function also updates height till the node where the first imbalance is found
  //the parameters are passed by reference and hence their values are changed by the function itself

  bool rotate = to_ins->check_imbalance(par_curr_left,grand_par_left,&current);

  if(rotate){
    if(par_curr_left==true && grand_par_left==true){
      if(rotateLeftLeft((current->left)->left,current->left,current)){
        //changing heights after rotation of the x,y,z nodes as only they need to be changed
        //as we do not go above z in the check_imbalanc function hence we do not need to 
        //worry about their heights 
        (current->decheightby2());
      }
    }
    else if(par_curr_left==true && grand_par_left==false){
      if(rotateRightLeft((current->right)->left,current->right,current)){
        //changing heights after rotation of the x,y,z nodes
        current->decheightby2();
        (current->parent)->incheightby1();
        ((current->parent)->right)->decheightby1();
      }
    }
    else if(par_curr_left==false && grand_par_left==true){
      if(rotateLeftRight((current->left)->right,current->left,current)){
        //changing heights after rotation of the x,y,z nodes
        current->decheightby2();
        (current->parent)->incheightby1();
        ((current->parent)->left)->decheightby1();
      }
    }
    else{
      if(rotateRightRight((current->right)->right,current->right,current)){
        //changing heights after rotation of the x,y,z nodes
        (current)->decheightby2();
      }
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
  TreeNode *to_find = new TreeNode(jrnyCode,0);
  TreeNode *x=root;
  while(x!=nullptr){
    if(AVLLessThan(to_find,x)){
      x = x->left;
    }
    else if(AVLLessThan(x,to_find)){
      x = x->right;
    }
    else{
      return x->getprice();
    }
  }
  
  return -1;
}

bool AVLTree::remove(int jrnyCode)
{
  return true;
}


