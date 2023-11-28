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

int get_Imbalance(TreeNode* a){                               //calculating imbalance
  if(a->left==NULL && a->right==NULL) return 0;
  else if(a->left==NULL) return ((-1)-(a->right->height));
  else if(a->right==NULL) return ((a->left->height)+1);
  else return((a->left->height)-(a->right->height));
}

int max(int a,int b){                                         //calculating max of a and b
  if(a>b) return a;
  else return b;
}

void update_height(TreeNode* a){                              //function to update height
  if(a->left==NULL && a->right==NULL) a->height=0;
  else if(a->left==NULL) a->height=1+a->right->height;
  else if(a->right==NULL) a->height=1+a->left->height;
  else a->height=1+max(a->left->height,a->right->height);
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

  if(grandParentNode==root){
    root=parentNode;
    root->parent=NULL;
  }

  else{
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
    updateAVLParentChild(parentNode,greatGrandParentNode,isGPLeftChild);
  }

  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  update_height(grandParentNode);
  update_height(parentNode);

  return true;
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
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(grandParentNode==root){                    //case when grandparent is root
    root=currNode;
    root->parent=NULL;
  }
  else{
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
    updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  update_height(parentNode);                          //updating heights
  update_height(grandParentNode);
  update_height(currNode);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  if(grandParent==root){                          //case that grandparent is root
    root=currNode;
    root->parent=NULL;
  }
  else{
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
    updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);
  }
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(grandParent,currNode,true);          
  updateAVLParentChild(parent,currNode,false);
  updateAVLParentChild(T2,grandParent,false);
  updateAVLParentChild(T3,parent,true);
  
  update_height(grandParent);                     //updating heights
  update_height(parent);
  update_height(currNode);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  if(grandParent==root){          //case that grandparent is root
    root=parent;
    root->parent=NULL;
  }

  else{
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
    updateAVLParentChild(parent,greatGrandParentNode,isGPLeftChild);
  }

  TreeNode* t=parent->left;
  updateAVLParentChild(t,grandParent,false);
  updateAVLParentChild(grandParent,parent,true);

  update_height(grandParent);           //updating heights
  update_height(parent); 

  return true;
}

bool AVLTree::insert(int jrnyCode, int price)
{
    // if(find(jrnyCode)!=-1){
    //     return false;
    // }
    TreeNode* tra;
    TreeNode* par;
    TreeNode* nw;
    TreeNode d(jrnyCode,price);
    nw=new TreeNode(jrnyCode, price);       //creating a new treenode
    tra=root;
    par=NULL;
    while (tra != NULL){
        par=tra;
        if(AVLLessThan(&d,tra)){
            tra = tra->left;
        }
        else if(AVLLessThan(tra,&d)){
            tra = tra->right;
        }
        else{
            return false;                   //return false if found in tree
        }
    }
    tra=nw;
    tra->parent=par;
    if(par==NULL){                      //inserting root
        root=tra;
        return true;
    }

    updateAVLParentChild(tra,par,AVLLessThan(tra,par));

    TreeNode* pretra=NULL;

    while(par!=NULL){                   //updating heights and checking for imbalances
      if((par->left==NULL || par->right==NULL)){
        par->height=1+tra->height;
      }
      else{
        update_height(par);
      }

      if(get_Imbalance(par)>1){   
        if(pretra==tra->left){                    //left left case
          rotateLeftLeft(pretra,tra,par);
          par=tra->parent;
          continue;
        }
        else{
          rotateLeftRight(pretra,tra,par);        //left right case
          pretra=tra;
          tra=pretra->parent;
          par=tra->parent;
          continue;
        }
      }

      if(get_Imbalance(par)<-1){
        if(pretra==tra->left){
          rotateRightLeft(pretra,tra,par);        //right left case
          pretra=tra;
          tra=pretra->parent;
          par=tra->parent;
          continue;
        }
        else{
          rotateRightRight(pretra,tra,par);       //right right case
          par=tra->parent;
          continue;
        }
      }
      pretra=tra;
      tra=par;
      par=par->parent;
    }
    return true; 
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

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

int AVLTree::find(int jrnyCode)
{
  TreeNode* tra;
  TreeNode d(jrnyCode, 5);
  tra=root;
    while (tra != NULL){
        if(AVLLessThan(&d,tra)){
            tra = tra->left;
        }
        else if(AVLLessThan(tra, &d)){
            tra = tra->right;
        }
        else{
            return tra->getprice();       //return price of treenode with given journey code if found
        }
    }
  return -1;
}

bool AVLTree::remove(int jrnyCode){
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