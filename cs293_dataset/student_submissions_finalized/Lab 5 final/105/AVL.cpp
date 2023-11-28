#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;TreeNode *T3 = parentNode->right;
  if(grandParentNode!=root){                                                        //IN THE CASE WHICH GRANDPARENT NODE DOES HAVE A PARENT
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

    updateAVLParentChild(grandParentNode, parentNode, false);
  }
  else{                                                                       //IN THE CASE WHICH GRANDPARENT NODE DOESN'T HAVE A PARENT
    root=parentNode;
    updateAVLParentChild(grandParentNode,root,false);
  }

  updateAVLParentChild(T3,grandParentNode,true);
  
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left; TreeNode *T3 = currNode->right;
  if(grandParentNode!=root){                                                   //IN THE CASE WHICH GRANDPARENT NODE DOES HAVE A PARENT
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
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);
  }
  else{                                                                        //IN THE CASE WHICH GRANDPARENT NODE DOESN'T HAVE A PARENT
    root=currNode;
    updateAVLParentChild(grandParentNode,root,false);
    updateAVLParentChild(parentNode,root,true);  
  }

  updateAVLParentChild(T2,parentNode,false);
  updateAVLParentChild(T3,grandParentNode,true);
  return true;

}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->right;TreeNode *T3 = currNode->left;
  if(grandParentNode!=root){                                                           //IN THE CASE WHICH GRANDPARENT NODE DOES HAVE A PARENT
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
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(parentNode, currNode, false);

    updateAVLParentChild(grandParentNode, currNode, true);
  }
  else{                                                                             //IN THE CASE WHICH GRANDPARENT NODE DOESN'T HAVE A PARENT
    root=currNode;
    updateAVLParentChild(grandParentNode,root,true);
    updateAVLParentChild(parentNode,root,false);  
  }
  updateAVLParentChild(T2,parentNode,true);
  updateAVLParentChild(T3,grandParentNode,false);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;TreeNode *T3 = parentNode->left;
  if(grandParentNode!=root){                                                 //IN THE CASE WHICH GRANDPARENT NODE DOES HAVE A PARENT
    bool isGPRightChild;

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
  }
  else{                                                                   //IN THE CASE WHICH GRANDPARENT NODE DOESN'T HAVE A PARENT
    root=parentNode;
    updateAVLParentChild(grandParentNode,root,true);
  }
  updateAVLParentChild(T3,grandParentNode,false);
  return true;
}


bool AVLTree::insert(int jrnyCode, int price)
{
  if(root==NULL){
    root = new TreeNode(jrnyCode,price);
    return true;
  }
  TreeNode *x=new TreeNode(jrnyCode,price);
  TreeNode *y=NULL;
  TreeNode *r=root,*a=NULL,*c,*d;
  int b;bool i,j;
  
  while(r!=NULL){
    if(AVLEqualTo(r,x))return false;                                //the case where the inserted element is already present in the tree
    else if(AVLLessThan(x,r)){
      y=r;
      b=1;
      r=r->left;
    }
    else{
      y=r;
      b=2;
      r=r->right;
    }
    }
  if(b==1) updateAVLParentChild(x,y,true);
  else if(b==2) updateAVLParentChild(x,y,false);
  while(true){
    if(root->getheight(root)==1)break;                              //in case the height of tree is 1 rotation need not take place
    d=a;
    a=x;                                                            //d and x are made to store the previous value of the the updated node
    x=a->parent;
    if(x->left==a)i=true;
    else i=false;                                                 //to know whether the parent node is in left position or right position
    if(a->left==d)j=true;
    else j=false;                                                   //to know whether the current node is in left position or right position
    if(x->left!=NULL && x->right!=NULL && d!=NULL){
      c=x->left;
      if(c==a)c=x->right;
      if(root->getheight(a)-root->getheight(c)>1){                  //case in which the a and c have imbalance 
                                                                    //since the getheight function written in tree.h is not accessible directly root(TreeNode) is called
        if(i==1 && j==1)rotateLeftLeft(d,a,x);
        if(i==0 && j==0)rotateRightRight(d,a,x);
        if(i==1 && j==0)rotateLeftRight(d,a,x);
        if(i==0 && j==1)rotateRightLeft(d,a,x); 
        break;      
      }
    }

    else if((x->left==NULL || x->right==NULL) && d!=NULL){
      if(root->getheight(a)>=1){                                    //case in which imbalance occurs when one of the child of x is null
        if(i==1 && j==1)rotateLeftLeft(d,a,x);
        if(i==0 && j==0)rotateRightRight(d,a,x);
        if(i==1 && j==0)rotateLeftRight(d,a,x);
        if(i==0 && j==1)rotateRightLeft(d,a,x);
        break;
      }
    }  
    else{;}
    if(x==root)break;                                             //the loop terminates when x becomes the root 
  }
  return true;
}

int AVLTree::find(int jrnyCode)
{
  TreeNode *x=new TreeNode(jrnyCode,0);
  TreeNode *r=root;
    if(r==NULL)return false;
    while(r!=NULL){
        if(AVLEqualTo(r,x)) return r->getprice();
        else if(AVLLessThan(x,r)){
            r=r->left;   
        }
        else{
            r=r->right;
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


