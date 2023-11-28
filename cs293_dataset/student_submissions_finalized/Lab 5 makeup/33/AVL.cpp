#ifndef AVL_H 
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <cmath>
#include <stdlib.h>
#endif


int AVLTree::getheight(TreeNode *currnode){
   if(currnode == nullptr){
     return -1 ;
   }
   else if((currnode->left==nullptr)&&(currnode->right==nullptr)){
    currnode->height = 0 ;
    return 0 ;
   }
   
   int left_height = getheight(currnode->left);
   int right_height = getheight(currnode->right); ;

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
      return  1+(a->right)->height ;
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
    else{
      return nearest(x->parent);
    }
  }
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{  

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;

  if(greatGrandParentNode == nullptr){
    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);
    
    updateAVLParentChild(T3, grandParentNode, true);
    
    parentNode->parent = nullptr;   // Now parentNode will become root and and its parent is set to NULL.  
    root = parentNode;
    root->height = getheight(root);
    return true;

   /* root = parentNode;
    root->parent = nullptr;
    root = parentNode;
    TreeNode* node1 = parentNode->right;
    updateAVLParentChild(grandParentNode,parentNode,false);
    updateAVLParentChild(node1,grandParentNode,true);
    return true;*/
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
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  // TreeNode *T3 = parentNode->right;
  updateAVLParentChild(T3, grandParentNode, true);
  root->height = getheight(root) ;
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(greatGrandParentNode == nullptr){
    TreeNode* T3 = currNode->left;
    TreeNode* T2 = currNode->right;
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false);
    updateAVLParentChild(T3,parentNode,false);
    updateAVLParentChild(T2,grandParentNode,true);
    currNode->parent = nullptr;
    root = currNode;
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
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  root->height = getheight(root);
  return true;
}
  
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode == nullptr){
    TreeNode* T3 = currNode->left;
    TreeNode* T2 = currNode->right;
    updateAVLParentChild(parentNode,currNode,false);
    updateAVLParentChild(grandParentNode,currNode,true);
    updateAVLParentChild(T3,grandParentNode,false);
    updateAVLParentChild(T2,parentNode,true);
    currNode->parent = nullptr;
    root = currNode;
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
  TreeNode *T3 = currNode->right;
  TreeNode *T2 = currNode->left;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
 //root->height = getheight(root);
  updateAVLParentChild(grandParentNode, currNode, true);
 // root->height = getheight(root);
  updateAVLParentChild(T2, grandParentNode,false);
 //root->height = getheight(root);
  updateAVLParentChild(T3, parentNode,true);
  root->height = getheight(root);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent ;
  if(greatGrandParentNode == nullptr){
    TreeNode *T3 = parentNode->left;
     updateAVLParentChild(currNode, parentNode,false);
     updateAVLParentChild(grandParentNode,parentNode,true);
     updateAVLParentChild(T3,grandParentNode,false);
     root->parent = nullptr;
     root = parentNode;
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
  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
 //root->height = getheight(root);
  updateAVLParentChild(currNode, parentNode,false);
 //root->height = getheight(root);
  updateAVLParentChild(grandParentNode, parentNode,true);
 //root->height = getheight(root);

  updateAVLParentChild(T3, grandParentNode, false);
  root->height = getheight(root);
  return true;
}



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
    bool z = rotateLeftLeft(n,m,d); 
    return z ;
    // m->height=getheight(m);
   //  n->height=getheight(n);
   //  d->height=getheight(d);
   }
   else if((!x)&&y){
    bool z = rotateRightLeft(n,m,d);
    return z;
    // m->height=getheight(m);
     //n->height=getheight(n);
     //d->height=getheight(d);
   }
   else if(x&&(!y)){
    bool z = rotateLeftRight(n,m,d);
     return z ;
     // m->height=getheight(m);
     //n->height=getheight(n);
     //d->height=getheight(d);
   }
   else{
     bool z = rotateRightRight(n,m,d);
     return z;
     // d->height = getheight(d) ;
     // m->height = getheight(m) ;
     // n->height = getheight(n) ;
   }
   }
  
}


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



