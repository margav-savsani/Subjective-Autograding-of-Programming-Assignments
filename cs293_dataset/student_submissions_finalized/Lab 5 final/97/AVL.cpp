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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if(greatGrandParentNode == nullptr){
    root = parentNode;
    grandParentNode->parent = parentNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
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
  TreeNode *T3 = parentNode->right;

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

  grandParentNode->height = 1 + max(height(grandParentNode->left), height(grandParentNode->right));
  parentNode->height = 1 + max(height(parentNode->left), height(parentNode->right));
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
 if(greatGrandParentNode == nullptr){
    root = currNode;
    grandParentNode->parent = currNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
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

  grandParentNode->height = 1 + max(height(grandParentNode->left), height(grandParentNode->right));
  parentNode->height = 1 + max(height(parentNode->left), height(parentNode->right));
  currNode->height = 1 + max(height(currNode->left), height(currNode->right));
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  if(greatGrandParentNode == nullptr){
    root = currNode;
    grandParentNode->parent = currNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->right;

  TreeNode *T3 = currNode->left;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, false);

  updateAVLParentChild(grandParentNode, currNode, true);

  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  grandParentNode->height = 1 + max(height(grandParentNode->left), height(grandParentNode->right));
  parentNode->height = 1 + max(height(parentNode->left), height(parentNode->right));
  currNode->height = 1 + max(height(currNode->left), height(currNode->right));
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;
  if(greatGrandParentNode == nullptr){
    root = parentNode;
    grandParentNode->parent = parentNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
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

  updateAVLParentChild(currNode, parentNode, false);

  updateAVLParentChild(grandParentNode, parentNode, true);

  updateAVLParentChild(T3, grandParentNode, false);

  grandParentNode->height = 1 + max(height(grandParentNode->left), height(grandParentNode->right));
  parentNode->height = 1 + max(height(parentNode->left), height(parentNode->right));
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::height(TreeNode *n) {
  if(n == nullptr)
    return -1;
  return n->height;
}

int AVLTree::balance_factor(TreeNode *n) {
  if(n == nullptr)
    return 0;
  return(height(n->left) - height(n->right));
}

bool AVLTree::insert(int jrnyCode, int price)
{ 
  TreeNode* n = new TreeNode(jrnyCode, price);
  TreeNode *y = nullptr;
  TreeNode *temp = root;
  while(temp != nullptr) {
    y = temp;
    if(AVLLessThan(n, temp))
      temp = temp->left;
    else
      temp = temp->right;
  }
  n->parent = y;

  if(y == nullptr) //newly added node is root
    root = n;
  else if(AVLLessThan(n, y))
    updateAVLParentChild(n, y, true);
  else
    updateAVLParentChild(n, y, false);
  TreeNode *z = n;

  while(y != nullptr) {
    y->height = 1 + max(height(y->left), height(y->right));

    TreeNode *x = y->parent;
    if(x == nullptr)
      break;
    if(balance_factor(x) <= -2 || balance_factor(x) >= 2) {//grandparent is unbalanced
      if(y == x->left) {
        if(z == x->left->left){ //case 1
            rotateLeftLeft(z, y, x);
        }
        else if(z == x->left->right) {//case 3
            rotateLeftRight(z, y, x);
        }
      }
      else if(y == x->right) {
        if(z == x->right->right){ //case 2
          rotateRightRight(z, y, x);
        }
        else if(z == x->right->left) {//case 4
          rotateRightLeft(z, y, x);
        }
      }
      break;
    }
    y = y->parent;
    z = z->parent;
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
  TreeNode* x = root;
  TreeNode* z = new TreeNode(jrnyCode, jrnyCode);
    while(x != nullptr && (AVLLessThan(x, z) || AVLLessThan(z, x))){
        if(AVLLessThan(z, x))
            x = x->left;
        else
            x = x->right;
    }
    if(x != nullptr){
        return x->getPrice();
    }
    else
        return -1;
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

// updates parent pointers
void AVLTree::transplant(TreeNode *u, TreeNode *v){
  if(u->parent == nullptr) //u is root
    root = v;
  else if(u == u->parent->left) //u is left child
    updateAVLParentChild(v, u->parent, true);
  else //u is right child
    updateAVLParentChild(v, u->parent, false);

  if(v != nullptr)
    v->parent = u->parent;
}

// does the rotations for delete
void AVLTree::avl_delete_fixup(TreeNode *n) {
  TreeNode *p = n;

  while(p != nullptr) {
    p->height = 1 + max(height(p->left), height(p->right));

    if(balance_factor(p) <= -2 || balance_factor(p) >= 2) { //grandparent is unbalanced
      TreeNode *z = p, *y = nullptr, *x = nullptr;

      //taller child of z will be y
      if(z->left->height > z->right->height)
        y = z->left;
      else
        y = z->right;

      //taller child of y will be x
      if(y->left->height > y->right->height) {
        x = y->left;
      }
      else if(y->left->height < y->right->height) {
        x = y->right;
      }
      else{ //same height, go for single rotation
        if(y == z->left)
          x = y->left;
        else
          x = y->right;
      }

      if(y == z->left) {
        if(x == z->left->left) //case 1
          rotateLeftLeft(z, y, x);

        else if(x == z->left->right) {//case 3
          rotateLeftRight(z, y, x);
        }
      }
      else if(y == z->right) {
        if(x == z->right->right) //case 2
          rotateRightRight(z, y, x);

        else if(x == z->right->left) {//case 4
          rotateRightLeft(z, y, x);
        }
      }
  }
  p = p->parent;
  }
}

// finds minimum in the AVL tree
TreeNode* AVLTree::minimum(TreeNode *x) {
  while(x->left != nullptr)
    x = x->left;
  return x;
}

bool AVLTree::remove(int jrnyCode)
{
  TreeNode* z = root;
  TreeNode* temp = new TreeNode(jrnyCode, jrnyCode);
    while(z != nullptr && (AVLLessThan(temp, z) || AVLLessThan(z, temp))){
        if(AVLLessThan(temp, z))
            z = z->left;
        else
            z = z->right;
    }
  delete temp;
  if(z == nullptr){
    return false;
  }
  if(z->left == nullptr) {
    transplant(z, z->right);
    if(z->right != nullptr)
      avl_delete_fixup(z->right);
    delete z;
  }
  else if(z->right == nullptr) {
    transplant(z, z->left);
    if(z->left != nullptr)
      avl_delete_fixup(z->left);
    delete z;
  }
  else {
    TreeNode *y = minimum(z->right); //minimum element in right subtree
    if(y->parent != z) {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
  }
  transplant(z, y);
  y->left = z->left;
  y->left->parent = y;
  if(y != nullptr)
    avl_delete_fixup(y);
  delete z;
  }
  return true;
}