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
//   y                             parent
//   z                             grandParent
//
// Recall also that z (grandParent) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parent) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the left child of parent, and
  // parent is the left child of grandParent
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if(greatGrandParentNode==NULL) isGPLeftChild=true;
  else if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the right child of parent (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parent (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parent
  updateAVLParentChild(currNode, parent, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // parent (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of parent
  updateAVLParentChild(grandParent, parent, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParent (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParent doesn't need to be updated at all.
  // The only update needed is that the right subtree of parent (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParent (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);
  grandParent->height=parent->height-1;
  while(parent->parent!=NULL){
      parent->parent->height=parent->parent->height-1;
      parent = parent->parent;
  }
  if(greatGrandParentNode==NULL) root=parent;
  
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parent and z is *grandParent

  // Moreover, currNode is the right child of parent, and
  // parent is the left child of grandParent.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParent is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(greatGrandParentNode==NULL) isGPLeftChild=true;
  else if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
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

  // Make parent (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parent should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, true);
  
  // Make grandParent (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParent
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parent (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParent (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parent and the right child of grandParent
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parent (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParent (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParent
  updateAVLParentChild(T3, grandParent, true);
  currNode->height=currNode->height+1;
  parent->height=parent->height-1;
  grandParent->height=grandParent->height-2;
  while((currNode->parent)!=NULL){
      (currNode->parent)->height=(currNode->parent)->height-1;
      currNode = (currNode->parent);
  }
  
  if(greatGrandParentNode==NULL) root=currNode;
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{  TreeNode *greatGrandParentNode = grandParent->parent;
   bool isGPLeftChild;
   if(greatGrandParentNode==NULL) isGPLeftChild=true;
  else if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
   TreeNode *T2 = currNode->right; //left child of x
   TreeNode *T3 = currNode->left; //right child of x
   updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
   updateAVLParentChild(parent, currNode, false);//y should be right child of x
   updateAVLParentChild(grandParent, currNode, true);//z should be left child of x
   updateAVLParentChild(T2, parent, true); //t2 should become the left child of y
   updateAVLParentChild(T3, grandParent, false); //t3 should become the right child of z
  // Implement this yourself
  currNode->height=currNode->height+1;
  parent->height=parent->height-1;
  grandParent->height=grandParent->height-2;
  while((currNode->parent)!=NULL){
      (currNode->parent)->height=(currNode->parent)->height-1;
      currNode = (currNode->parent);
  }
  if(greatGrandParentNode==NULL) root=currNode;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{  
   TreeNode *greatGrandParentNode = grandParent->parent;
    bool isGPLeftChild;
  if(greatGrandParentNode==NULL) isGPLeftChild=true;
  else if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode *T3 = parent->left; //as the child of y is leftchild
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parent, false); //changing true to false
  updateAVLParentChild(grandParent, parent, true); // z should be left child of y so change false to true
  updateAVLParentChild(T3, grandParent, false); // as t3 should become the right child of grandparentnode
  // Implement this yourself
  grandParent->height=parent->height-1;
  while(parent->parent!=NULL){
      parent->parent->height=parent->parent->height-1;
      parent = parent->parent;
  }
  
  if(greatGrandParentNode==NULL) root=parent;
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::getbalance(TreeNode *k){
  return (k->right->height)-(k->left->height); //function that returns balance factor
}
bool AVLTree::insert(int jrnyCode, int price)
{ if(find(jrnyCode)!=-1){return false;} 
  else{
   
    TreeNode *N;
    N=new TreeNode(jrnyCode,price);
    TreeNode *x=root;
    TreeNode *T=NULL;
    while(x!=NULL){ 
     T=x;          
     if(AVLLessThan(N,x)) x=x->left;
     else x=x->right;
     
      }
    N->parent=T;
    TreeNode *a;
    if(T==NULL){
            root=N;
            a=root;
            return true;
          }
    else {
          if(AVLLessThan(T,N)){
             T->right=N;
             TreeNode *p=T->right;
              a=T->right;
             if(T->left==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){   
                   (p->parent)->height=p->height+1;            //updating the height of all nodes after insertion
                   p=p->parent;
                }
             } 
          }
          else{
              T->left=N;
              TreeNode *p=T->left;
              a=T->left;
              if(T->right==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){   
                   (p->parent)->height=p->height+1;             //updating the height of all nodes after insertion
                   p=p->parent;
                }
              }
          }
         }
      
     TreeNode *b=a;         //child
     TreeNode *y=a->parent;   //parent
     TreeNode *z=y->parent;  //grand parent
    if(z==NULL) {return true;}
    while(z!=NULL && z->right!=NULL && z->left!=NULL){
      
      int bal=getbalance(z);
     
      if(bal<-1 || bal>1){
         break;               //if balancefactor no in [-1,1] breaks the while
        }
        else {
          b=y;
          y=z;
          if(z->parent!=NULL) z=z->parent;
          else return true;        //if it reavhes to root the return true
        }
    }

    if(z->left==y && y->left==b) return rotateLeftLeft(b,y,z);   //rotate LL
    else if(z->right==y && y->right==b) { return rotateRightRight(b,y,z);}  //rotate RR
    else if(z->left==y && y->right==b) return rotateLeftRight(b,y,z);      //rotate LR
    else return rotateRightLeft(b,y,z);        //rotate RL
  
  }
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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
  //return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{  TreeNode *x=root;
   TreeNode *N;
  
    N=new TreeNode(jrnyCode,99);
     while(x != nullptr ){
         if (AVLLessThan(N,x )) {
             if(x->left!= NULL) x=x->left;
             else break;
          }
         else if (AVLLessThan(x,N)){
            if(x->right!= NULL) x=x->right;
            else break;
          } 
          else return x->getprice();    //returns the price of the corresponding journeycode
         }
  return -1;
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
  //return -1;
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
{ if(!(find(jrnyCode))) return false;
  else{

    return true;  
  }
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parent, grandParent in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parent, grandParent) following Prof. Garg's lectures
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


