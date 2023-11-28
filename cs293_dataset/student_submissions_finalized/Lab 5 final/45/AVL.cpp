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

bool balanced(TreeNode* x){
  if(x->left==nullptr and x->right==nullptr){return true;}
  if(x->left==nullptr and x->right!=nullptr){
    if(x->right->height==0){return true;}
  }
  if(x->left!=nullptr and x->right==nullptr){
    if(x->left->height==0){return true;}
  }
  if(x->left!=nullptr and x->right!=nullptr){
    if(abs((x->left->height)-(x->right->height))<=1){return true;}
  }
  return false;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // if greatgrandparent is null
  if(grandParentNode->parent==NULL) {
    TreeNode* T2 = parentNode->right;
    updateAVLParentChild(grandParentNode,parentNode,false);
    updateAVLParentChild(T2,grandParentNode,true); 
    grandParentNode->height -= 2; 
    parentNode->parent=NULL; 
    root=parentNode; 
    return true;
  }
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
  TreeNode *T3 = parentNode->right; // storing the address of left child of parent

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true); //updating nodes
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
  updateAVLParentChild(T3, grandParentNode, true);
  grandParentNode->height -= 2; // after the rotation, height of grandparent will be decreased by 2
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //if greatgrandparent is null
  if(grandParentNode->parent==NULL) { 
    TreeNode* T2 = currNode->left;
    TreeNode* T3 = currNode->right; 
    currNode->parent=NULL; 
    parentNode->right=NULL;
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    currNode->height +=1;
    grandParentNode->height -=2; 
    parentNode->height--; 
    root=currNode; 
    return true;
  }
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
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
       
  // Let T2 be the left child of currNode (i.e. of x)
  // Let T3 be right child of currNode
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  currNode->height++;
  grandParentNode->height-=2;
  parentNode->height--;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //if greatgrandparent is null
  if(grandParentNode->parent==NULL) { 
    TreeNode* T2 = currNode->left; 
    TreeNode* T3 = currNode->right; 
    currNode->parent=NULL; 
    parentNode->right=NULL;
    updateAVLParentChild(parentNode,currNode,false);
    updateAVLParentChild(grandParentNode,currNode,true);
    updateAVLParentChild(T3, parentNode, true);
    updateAVLParentChild(T2, grandParentNode, false);
    currNode->height +=1; 
    grandParentNode->height -=2; 
    parentNode->height--; 
    root=currNode; 
    return true;
  }
  TreeNode *greatGrandParentNode = grandParentNode->parent;

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

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
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
       
  // Let T2 be the left child of currNode (i.e. of x)
  // Let T3 be right child of currNode
  updateAVLParentChild(T3, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);

  currNode->height++;
  grandParentNode->height-=2;
  parentNode->height--;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  //if greatgrandparent is null
  if(grandParentNode->parent==NULL) {
    TreeNode* T2 = parentNode->left; 
    updateAVLParentChild(grandParentNode,parentNode,true);
    updateAVLParentChild(T2,grandParentNode,false); 
    grandParentNode->height -= 2; 
    parentNode->parent=NULL; 
    root=parentNode; 
    return true;
  }
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
  TreeNode *T3 = parentNode->left; // storing the address of left child of parent
  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false); //updating nodes
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  updateAVLParentChild(T3, grandParentNode, false);
  grandParentNode->height -= 2; // after the rotation, height of grandparent will be decreased by 2
  return true;
}


bool AVLTree::insert(int jrnyCode, int price)
{
  /* solution-1st check if root is null,if it is,then isert node.
            -now take x=root,check if T(node to insert) is less or more than x,
            -if it is less,do x=x->left,and continue this till u get x->left / x-right is null.
            -now insert a node
            for heights-
                -first take y=inserted node and set its heigt to 0.
                now do a while loop,y=y->parent and y->height=1+max(left->height,right->height)
                if y is imbalanced, now break.
                as there is no need to increase heights after this,since 
                if we increase them now,we should decrese them again after rotation
  */
  TreeNode* T=new TreeNode(jrnyCode,price);
  TreeNode* inserted;
  if(find(jrnyCode)==0){ return false;}

  
  if(root==nullptr){
    root=T;
    inserted=root;
  }
  else{
    TreeNode* x=root;

    while(true){
      if(AVLLessThan(x,T)){
        if(x->right==nullptr){
          T->parent=x;
          x->right=T;
          inserted=T;
          break;
        }
        else{
          x=x->right;
        }
      }
      else if(AVLLessThan(T,x)){
        if(x->left==nullptr){
          T->parent=x;
          x->left=T;
          inserted=T;
          break;
        }
        else{
          x=x->left;
        }
      }
    }
  }
  

  TreeNode* y=inserted;

  while(y!=nullptr){
    if(y->left==nullptr and y->right==nullptr){y->height=0;}
    else if(y->left!=nullptr and y->right==nullptr){y->height=1+y->left->height;}
    else if(y->left==nullptr and y->right!=nullptr){y->height=1+y->right->height;}
    else if(y->left!=nullptr and y->right!=nullptr)
    {
      y->height=1+max(y->left->height,y->right->height);
    }
    if(!balanced(y)){
      break;
    }
    else{
      y=y->parent;
    }
  }
  

  TreeNode* z=inserted;
  
  while(z!=nullptr and z->parent!=nullptr and z->parent->parent!=nullptr){
    if(!balanced(z->parent->parent))
    {
      break;
    }
    else
    {
      z=z->parent;
    }
  }
  TreeNode* cn=z;
  if(z->parent!=nullptr){
    TreeNode* pn=z->parent;
    if(pn->parent!=nullptr){
      TreeNode* gpn=pn->parent;

      if(gpn->left==pn and pn->left==cn){ rotateLeftLeft(cn,pn,gpn);}
      else if(gpn->left==pn and pn->right==cn){ rotateLeftRight(cn,pn,gpn);}
      else if(gpn->right==pn and pn->left==cn){ rotateRightLeft(cn,pn,gpn);}
      else if(gpn->right==pn and pn->right==cn){ rotateRightRight(cn,pn,gpn);}
    }
  }
  return true;
}


int AVLTree::find(int jrnyCode)
{
  TreeNode* x=root;
  TreeNode* y=new TreeNode(jrnyCode,1);
  while(x!=NULL and (AVLLessThan(x,y) or AVLLessThan(y,x))){
      if(AVLLessThan(y,x)){
          x=x->left;
      }
      else{
          x=x->right;
      }
  }
  if(x!=NULL and !(AVLLessThan(x,y) or AVLLessThan(y,x))){
      return 0;
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


