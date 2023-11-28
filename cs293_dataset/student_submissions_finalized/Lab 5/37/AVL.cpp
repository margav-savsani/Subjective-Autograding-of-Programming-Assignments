#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
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
  int get_im(TreeNode *To_be_ins){
    if(To_be_ins->right!=NULL && To_be_ins->left!=NULL){    
      return abs(To_be_ins->right->height - To_be_ins->left->height);
    }
    else if(To_be_ins->right!=NULL)return To_be_ins->right->height;
    else if(To_be_ins->left!=NULL)return To_be_ins->left->height;
    else return 0;
  }

void height_reset_ins(TreeNode* To_be_ins ){
    while(To_be_ins!=NULL){
      if(To_be_ins->right!=NULL && To_be_ins->left!=NULL){
        if((To_be_ins->right)->height < (To_be_ins->left)->height )
          To_be_ins->height = (To_be_ins->left)->height +1;
        else  
          To_be_ins->height = (To_be_ins->right)->height +1;
      }

      else if(To_be_ins->right!=NULL || To_be_ins->left!=NULL){
        if(To_be_ins->right!=NULL){
          To_be_ins->height = (To_be_ins->right)->height +1;

        }
       else{
          To_be_ins->height = (To_be_ins->left)->height +1;

        }
      }
      else{

        To_be_ins->height = 0;
      }
      To_be_ins=To_be_ins->parent;
     
    }
    return;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right,*x=NULL;
  if( greatGrandParentNode == NULL){
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root=parentNode;

    updateAVLParentChild(parentNode, x, false);
    return true;

  }
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  

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

  TreeNode *greatGrandParentNode = grandParentNode->parent,*x=NULL;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  //in case when grandparent is the root of the tree
  if (greatGrandParentNode == NULL){

    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    updateAVLParentChild(currNode, x, false);
    root=currNode;
    
    return true;
  } 
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

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent,*x=NULL;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  //in case when grandparent is the root of the tree
  if (greatGrandParentNode == NULL){

    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T2, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    updateAVLParentChild(currNode, x, false);
    root=currNode;
    
    return true;
  }
  


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


  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parent, currNode, false);
  

  updateAVLParentChild(grandParent, currNode, true);
  
  updateAVLParentChild(T3, parent, true);


  updateAVLParentChild(T2, grandParent, false);



  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{


  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->left,*x=NULL;
  if( greatGrandParentNode == NULL){
    updateAVLParentChild(grandParentNode, parentNode, true);
    updateAVLParentChild(T3, grandParentNode, false);
    root=parentNode;

    updateAVLParentChild(parentNode, x, false);
    
    return true;
  }
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


  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);


  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(currNode, parentNode, false);
  

  
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
  
  
}



bool AVLTree::insert(int jrnyCode, int price)
{ 
  
  TreeNode *req=new TreeNode(jrnyCode,price);
  TreeNode *x=root;
  TreeNode *y=NULL;
  TreeNode *z=NULL;
   
  while (x != NULL)
  { 
        y = x;
        
        if (AVLLessThan(req,x))  x = x->left;
        else if(AVLLessThan(x, req)) x = x->right;
        else return false;

  }
   if( root==NULL ){
    root=req;

    return true;
  }

  x=root;

  req->parent=y;
  bool is_left_of_y=false,is_left_of_z=false;
  if (AVLLessThan(req,y)){
    updateAVLParentChild(req, y, true);
    is_left_of_y=true;
  }
  else{
    updateAVLParentChild(req, y, false);
    is_left_of_y=false;
  }
  if (AVLLessThan(y,z)) is_left_of_z=true;
  height_reset_ins(req);
  z=y->parent;
  x=req;
  
  while(z!=NULL){
    if(get_im(z)>1){
      if(is_left_of_y && is_left_of_z){
        rotateLeftLeft(x,y,z);
        z->height-=2; //in the nptel lecture the height of z decreases by 2 after rotation
        break;
      }

      else if(!is_left_of_y && !is_left_of_z){
        rotateRightRight(x,y,z);
        z->height-=2; //in the nptel lecture the height of z decreases by 2 after rotation
        break;
      }

      else if(!is_left_of_y && is_left_of_z){
        rotateLeftRight(x,y,z);
        z->height-=2; //in the nptel lecture the height of z decreases by 2 after rotation
        y->height-=1;
        x->height+=1;
        break;
      }

      else if(is_left_of_y && !is_left_of_z){
        rotateRightLeft(x,y,z);
        z->height-=2; //in the nptel lecture the height of z decreases by 2 after rotation
        y->height-=1;
        x->height+=1;
        break;
      }


    }
    



    x=y;
    y=z;
    z=z->parent;
  }
  
  height_reset_ins(req);
        
 
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
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int JourneyCode)
{
  class TreeNode *currNode = root,*req=new TreeNode(JourneyCode,69);
  if(root==NULL){
   
    return -1;
  }
  while (currNode != NULL) {
    if (AVLLessThan(currNode,req)) {
      
      currNode = currNode->right;
    }
    else if (AVLLessThan(req ,currNode)) {
       std::cout<<"oo\n";
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return 1;
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

  return true;
}


