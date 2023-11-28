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

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;

  if(greatGrandParentNode == NULL)
  {
    updateAVLParentChild(currNode, parentNode, true);
  
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    parentNode->parent=NULL;
    root = parentNode;
    root->height = updateheight(root);
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures

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

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  root->height = updateheight(root);
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
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  
  if(greatGrandParentNode == NULL)
  {
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root = currNode;
    root->height = updateheight(root);
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

  // Let T2 be the left child of currNode (i.e. of x)

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
  root->height = updateheight(root);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{

 TreeNode *greatGrandParentNode = grandParent->parent;
 TreeNode *T2 = currNode->right;
 TreeNode *T3 = currNode->left;

  if(greatGrandParentNode == NULL)
  {
    updateAVLParentChild(parent, currNode,false);
    updateAVLParentChild(grandParent, currNode,true);
    updateAVLParentChild(T2, parent,true);
    updateAVLParentChild(T3, grandParent,false); 
    root = currNode;
    root->height = updateheight(root);
    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
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
  updateAVLParentChild(parent, currNode,false);
  updateAVLParentChild(grandParent, currNode,true);
  updateAVLParentChild(T2, parent,true);
  updateAVLParentChild(T3, grandParent,false); 
  root->height = updateheight(root);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  TreeNode *T3 = parent->left;
  
  if(greatGrandParentNode == NULL)
  {
    updateAVLParentChild(currNode, parent, false);
  
    updateAVLParentChild(grandParent, parent, true);

    updateAVLParentChild(T3, grandParent, false);
    parent->parent=NULL;
    root = parent;
    root->height = updateheight(root);
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
  
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T3, grandParent, false);
  root->height = updateheight(root);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

TreeNode *AVLTree::imbnode(TreeNode *x)
{
  if (x!=NULL)
  {
    int a = abs(updateheight(x->right) - updateheight(x->left));
    if (a>1)
      return x;
    else
      return imbnode(x->parent);
  }
  return NULL;
}

int AVLTree::updateheight(TreeNode *x)
{
 if(x == NULL) return -1;
  if (x->left == NULL)
  {
    if (x->right == NULL)
    {
      x->height=0;
      return 0;
    }
    else{
      x->height = updateheight(x->right) + 1;
      return x->height;}
  }
  if (x->right == NULL)
  {
    x->height = updateheight(x->left) + 1;
    return x->height;
  }
  x->height = (max(updateheight(x->left),updateheight(x->right)) + 1);
  return x->height;
}


bool AVLTree::insert(int jrnyCode, int price)
{
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
if (find(jrnyCode)!=-1) return false;
if (root==NULL) 
{
  root=new TreeNode(jrnyCode,price);
  root->height=0;
  return true;
}
TreeNode* x = new TreeNode(0,0);
TreeNode* z = new TreeNode(jrnyCode,price);
x=root;
while(x!=NULL)
{
  if (AVLLessThan(z,x) ){
    if (x->left==NULL){ 
     updateAVLParentChild(z,x,true);
      break;}
    x=x->left;}
  if (AVLLessThan(x,z)){
    if (x->right==NULL){ 
      updateAVLParentChild(z,x,false);
      break; }
    x=x->right;
    }
}
updateheight(root);
TreeNode* Z;
Z = imbnode(z);
if(Z == NULL) return true;
TreeNode* X;
TreeNode* Y;
if (AVLLessThan(z,Z)){
     Y=Z->left;
  if(AVLLessThan(z,Y)){
     X=Y->left;
     rotateLeftLeft(X,Y,Z);
     }
  else {
     X=Y->right;
     rotateLeftRight(X,Y,Z);
     }
}
else if (AVLLessThan(Z,z)){
     Y=Z->right;
  if(AVLLessThan(z,Y)){
     X=Y->left;
     rotateRightLeft(X,Y,Z);}
  else {
     X=Y->right;
     rotateRightRight(X,Y,Z);}
}
updateheight(root);
return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode* y=new TreeNode(jrnyCode,0);
  TreeNode *x=new TreeNode(0,0);
  x=root;
  while (x!=NULL){
    if ((!AVLLessThan(x,y))&&(!AVLLessThan(y,x))){return x->getprice();} 
    if (AVLLessThan(y,x)){x=x->left;}
    else if (AVLLessThan(x,y)) {x=x->right;}
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


