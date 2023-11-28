#ifndef AVL_H 
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include<cmath>
#include <stdlib.h>
#endif


int AVLTree::getheight(TreeNode *currnode){
   if(currnode == nullptr){
     return -1 ;
   }
   if((currnode->left==nullptr)&&(currnode->right==nullptr)){
    return 0 ;
   }
   
   int left_height = getheight(currnode->left);
   int right_height = getheight(currnode->right);

   if(currnode->left != nullptr){
    (currnode->left)->height = left_height ;
   }
   if(currnode->right != nullptr){
    (currnode->right)->height = right_height ;
   }
    return (1+max(left_height,right_height));
   
}
int AVLTree::imbalance(TreeNode* a){
  if(a == nullptr)return -1 ;
  else{
    if((a->right!=nullptr)&&(a->left!=nullptr)){
      if((a->right)->height > (a->left)->height)return ((a->right)->height - (a->left)->height) ;
      else return ((a->left)->height - (a->right)->height );
    }
    else if((a->right!=nullptr)&&(a->left==nullptr)){
      return 1+(a->right)->height ;
    }
    else if((a->left!=nullptr)&&(a->right==nullptr)){
      return 1+(a->left)->height ;
    }
    else return 0 ;
  }
}

TreeNode* AVLTree::nearest(TreeNode* x){
  if (x == nullptr)
  {
    return nullptr;
  }
  else
  {
    if (imbalance(x) > 1)
      return x;
    else
      return nearest(x->parent);
  }
}

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
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if(greatGrandParentNode == nullptr){
    root = parentNode;
    root->parent = nullptr;
    TreeNode* node1 = parentNode->right;
    updateAVLParentChild(grandParentNode,parentNode,false);
    updateAVLParentChild(node1,grandParentNode,true);
    return true;
  }
  
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
 // root->height = getheight(root);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
 // root->height = getheight(root);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);
 // root->height = getheight(root);

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
  TreeNode *T3 = parentNode->right;

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  //root->height = getheight(root);

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

  if(greatGrandParentNode == nullptr){
    root = currNode;
    root->parent = nullptr;
    TreeNode* T3 = currNode->left;
    TreeNode* T2 = currNode->right;
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false);
    updateAVLParentChild(T3,parentNode,false);
    updateAVLParentChild(T2,grandParentNode,true);
    return true;
  }

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
 // root->height = getheight(root);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);
 // root->height = getheight(root);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
 // root->height = getheight(root);
  
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
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);
 // root->height = getheight(root);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
 // root->height = getheight(root);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode == nullptr){
    root = currNode;
    root->parent = nullptr;
    TreeNode* T3 = currNode->left;
    TreeNode* T2 = currNode->right;
    updateAVLParentChild(parentNode,currNode,false);
    updateAVLParentChild(grandParentNode,currNode,true);
    updateAVLParentChild(T3,grandParentNode,false);
    updateAVLParentChild(T2,parentNode,true);
    return true;
  }
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
  root->height = getheight(root);
  updateAVLParentChild(parentNode, currNode, false);
 root->height = getheight(root);
  updateAVLParentChild(grandParentNode, currNode, true);
  root->height = getheight(root);
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(T2, parentNode,true);
 root->height = getheight(root);
  updateAVLParentChild(T3, grandParentNode,false);
  root->height = getheight(root);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent ;
  TreeNode *T3 = parentNode->left;
  if(greatGrandParentNode == nullptr){
     updateAVLParentChild(currNode, parentNode,false);
     updateAVLParentChild(grandParentNode,parentNode,true);
     updateAVLParentChild(T3,grandParentNode,false);
     root = parentNode;
     root->parent = nullptr;
     root->height = getheight(root);
          return true;
  }
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
 root->height = getheight(root);
  updateAVLParentChild(currNode, parentNode,false);
 root->height = getheight(root);
  updateAVLParentChild(grandParentNode, parentNode,true);
 root->height = getheight(root);
  updateAVLParentChild(T3, grandParentNode, false);
  root->height = getheight(root);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{ 
  TreeNode* a;
   a = new TreeNode(jrnyCode,price);
   TreeNode* c;
   TreeNode* b;
   b = nullptr;
   c = root ;
  while(c != nullptr){
      b = c;
      if(AVLLessThan(a,c)){
        c = c->left ;
      }
      else if(AVLLessThan(c,a)){
        c = c->right ;
      }
      else{
        return false ;
      }
    }
    a->parent = b ;
    if(b == nullptr){
      root = a ; 
    }
    else if(AVLLessThan(a,b)) {
      updateAVLParentChild(a,b,true);
      root->height = getheight(root);
    }
    else if(AVLLessThan(b,a)){
      updateAVLParentChild(a,b,false);
      root->height = getheight(root);
    }
  TreeNode* d;
  d = nearest(a);
  if(d==nullptr){return true ;}
  else{ 
   TreeNode* m;
   TreeNode*n;
   bool x,y ;
   if(AVLLessThan(a,d)){
    m = d->left ;
    x = true ;
   }
   else { 
    m = d->right ;
    x = false ;
   }
   if(AVLLessThan(a,m)){
      n = m->left ;
      y = true ;
   }
   else{
    n = m->right ;
    y = false ;
   }
   if(x&&y){
     rotateLeftLeft(m,n,d);
     m->height=getheight(m);
     n->height=getheight(n);
     d->height=getheight(d);
   }
   else if((!x)&&y){
     rotateRightLeft(m,n,d);
     m->height=getheight(m);
     n->height=getheight(n);
     d->height=getheight(d);
   }
   else if(x&&(!y)){
     rotateLeftRight(m,n,d);
     m->height=getheight(m);
     n->height=getheight(n);
     d->height=getheight(d);
   }
   else{
     rotateRightRight(m,n,d);
     d->height = getheight(d) ;
     m->height = getheight(m) ;
     n->height = getheight(n) ;
   }
   return true ;
   }
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
  // see fit return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{  TreeNode* d ;
    d = root ;
    TreeNode* e ;
    e = new TreeNode(jrnyCode,0);
    while( d != nullptr &&  (AVLLessThan(d,e) || AVLLessThan(e,d)) ){
       if(AVLLessThan(e,d)){
         d = d->left ;
       }
       else if(AVLLessThan(d,e)){ d = d->right ;}
    }
    if(d == nullptr){return -1 ;}
    else return 1 ;


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
  // return -1;
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



