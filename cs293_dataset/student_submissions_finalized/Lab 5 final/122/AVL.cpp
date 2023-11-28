#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
int AVLTree::fi(TreeNode *r, TreeNode *s)
{
  if (r == nullptr)
  {
    return -1;
  }
  if (!(AVLLessThan(r, s) || AVLLessThan(s, r)))
  {
    cout << "hello";
    return r->reprise();
  }
  if (AVLLessThan(r, s))
  {
    if (r->right == nullptr)
    {
      return -1;
    }
    TreeNode *pt = r->right;
    return fi(r->right, s);
  }
  else
  {
    if (r->left == nullptr)
    {
      return -1;
    }

    TreeNode *pt = r->left;
    return fi(r->left, s);
  }
}

void AVLTree::upd(TreeNode*ptr){
  if(pos(ptr)==ptr){
    return;
  }
 if(ptr==root){
   return;
 }
 if(ptr->parent->height - ptr->height ==1){
   return;
 }
 else {
 ptr->parent->height +=1;
 return upd(ptr->parent);
 }
} 
TreeNode *AVLTree::pos(TreeNode *pt)
{
  if (pt == nullptr)
  {
    return nullptr;
  }
  
  
  /*else if ((!(pt->right == nullptr)) && (!(pt->left == nullptr)))
    {
      if (abs(pt->right->height - pt->left->height) >= 1)
      {
        cout <<"7";
        return pt;
      }
      else
      {
        pos(pt->parent);
      }
    }
  else if ((pt->right == nullptr && pt->left == nullptr))
    {
      return pos(pt->parent);
    } */
  else if (pt->right == nullptr)
    {
      if (pt->left->height >= 1)
      {
        cout<<"8";
        return pt;
      }
      else
      {
        pos(pt->parent);
      }
    }
  else if(pt->left == nullptr)
    {
      if (pt->right->height >= 1)
      {
        cout <<"hlo";
        return pt;
      }
      else
      {
        pos(pt->parent);
      }
    }
  else {
    return nullptr;
  }
    

  }



/*bool AVLTree::childpos(TreeNode*lik ){
  TreeNode*ris = lik->parent
   if(ris->left == lik) {
    return  = true;
  }
  else(ris->right == lik) {
    return = false;
  } */

TreeNode *AVLTree::function(TreeNode *ptr , TreeNode *r)
{
  if (ptr == nullptr)
  {
    root = new TreeNode(0, 0);
    cout << "in";
    root = r;
    return r;
  }
  else
  {
  
    if (AVLLessThan(ptr,r))
    {cout<<"ris";
      if (ptr->right == nullptr)
      {
        cout << "hi";
        ptr->right = new TreeNode(0,0);
        ptr->right= r;
        r->parent = ptr;
        upd(r);
        return r;
      }
      TreeNode *pt = ptr->right;
      return function(pt,r);
    }
    else
    {
      if (ptr->left == nullptr)
      {
        cout << "h";
      ptr->left = new TreeNode(0,0);
      ptr->left = r;
        r->parent = ptr;
        upd(r);
        return r;}
      TreeNode *pt = ptr->left;
      return function(pt,r);
    }
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

if(greatGrandParentNode==NULL){
  parentNode->parent=NULL;
  root=parentNode;
}
else{
bool isGPLeftChild;
if (greatGrandParentNode->left == grandParentNode)
{
  isGPLeftChild = true;
}
else if (greatGrandParentNode->right == grandParentNode)
{
  isGPLeftChild = false;
}
else
{
  cerr << "Unexpected condition encountered!" << endl;
  return false;
}
updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode

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
  if(greatGrandParentNode==NULL){
    parentNode->parent=NULL;
    root=parentNode;
  }
  else{
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
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

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent){
  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

if(greatGrandParentNode==NULL){
  parent->parent=NULL;
  root=parent;
}
else{
bool isGPLeftChild;
if (greatGrandParentNode->left == grandParent)
{
  isGPLeftChild = true;
}
else if (greatGrandParentNode->right == grandParent)
{
  isGPLeftChild = false;
}
else
{
  cerr << "Unexpected condition encountered!" << endl;
  return false;
}
updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}

  TreeNode *T2 = parent->left;
 
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(currNode, parent, false);
  updateAVLParentChild(T2, grandParent, false);
  // Implement this yourself

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

if(greatGrandParentNode==NULL){
  parent->parent=NULL;
  root=parent;
}
else{
bool isGPLeftChild;
if (greatGrandParentNode->left == grandParent)
{
  isGPLeftChild = true;
}
else if (greatGrandParentNode->right == grandParent)
{
  isGPLeftChild = false;
}
else
{
  cerr << "Unexpected condition encountered!" << endl;
  return false;
}
updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(T2, grandParent, false);
  updateAVLParentChild(T3, parent, true);

  // Implement this yourself

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *a;
  TreeNode *b;
  bool flag;
  bool fla;
  TreeNode * v;
  v = new TreeNode(jrnyCode,price);
  
  TreeNode *npr = function(root,v);
  if(npr ==root){
    return true;
  }
  if(npr->parent== root){
    return true;
  }
  TreeNode * cl = npr ->parent;
  if(pos(cl) == nullptr){
    cout << "ni";
  
    return true;
  }
  else{
    TreeNode *x = pos(cl);
   cout<< x->height;
     cout << "x";

  if((!(x->right ==nullptr) && (!(x->left== nullptr)))){
  if(x->height - x->right->height ==1 ){
    a = x->right;
    flag = false;
    }
  else{
    a = x->left;
    cout <<"he";
    flag = true;
  }}
  else if(x->right ==nullptr){
    a = x->left;
    cout <<"1";
    flag = true;
  }
  else{
    a = x->right;
    cout <<"2";
    flag = false;
  }
  if((!(a->right ==nullptr) && (!(a->left== nullptr)))){
  if(a->height - a->right->height ==1 ){
    b = a->right;
    fla = false;
    }
  else{
    fla = true;
  }}
  else if(a->right ==nullptr){
    b = a->left;
    cout << 10;
;    fla = true;
  }
  else{
    b = a->right;
    cout << 11;
    fla = false;
  }
  
  if(flag == false && fla == false){
    rotateRightRight(b,a,x);
    cout <<"ok";
    x->height  -=2;
  }
  else if(flag == false && fla == true){
    rotateRightLeft(b,a,x);
    x->height -=2;
    b->height +=1;
    a->height -=1;
  
  }
  else if(flag == true && fla == true){
  cout << "say";
    rotateLeftLeft(b,a,x);
    cout <<"lk";
    x->height  -=2;
  }
  else{
    if(flag == true && fla == false){
    rotateLeftRight(b,a,x);
     x->height -=2;
 b->height +=1;
 a->height -=1;
  }
  }
 /* if((!(a->right ==nullptr) && (!(a->left== nullptr)))){
    if(a->right->height > a->left->height){
      a->height = a->right->height +1;
      cout <<"p";
    }
    else {
      a->height = a->left->height +1;
      cout <<"g";
    }
  } */
 /* else if(a->right== nullptr  && a->left == nullptr){
 a->height =0;
 cout <<"e";
}
else if(a->right == nullptr){
 a->height = a->left->height+1;
 cout <<"f";
}
else{
 a->height = a->right->height +1;
 cout << "m";
    }
  
   if((!(b->right ==nullptr) && (!(b->left== nullptr)))){
   if(b->right->height > b->left->height){
     b->height = b->right->height +1;
   }
   else {
  b->height = b->left->height +1;
}}

   else if(b->right== nullptr  && b->left == nullptr){
    b->height =0;
   }
   else if(b->right == nullptr){
    b->height = b->left->height+1;
   }
   else{
    b->height = b->right->height +1;
       } */
 /* if((!(x->right ==nullptr) && (!(x->left== nullptr)))){
if(x->right->height >  x->left->height){
  x->height = x->right->height +1;
}
else {
x->height = x->left->height +1;}}
else if(x->right== nullptr  && x->left == nullptr){
 x->height =0;
}
else if(x->right == nullptr){
 x->height = x->left->height+1;
}
else{
 x->height = x->right->height +1;
    }   */

  }
  return true;
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
// see fit

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  cout << "h";
  TreeNode *d = new TreeNode(jrnyCode, 0);
  cout << "hi";

  int falg = fi(root, d);

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
  if (falg == -1)
  {
    return -1;
  }
  else
    return falg;
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
