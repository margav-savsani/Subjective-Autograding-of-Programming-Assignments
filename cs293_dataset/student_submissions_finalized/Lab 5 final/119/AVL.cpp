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
void update(TreeNode* v){
  int l = -1, r = -1;
  if(v->left != NULL) l = v->left->height;
  if(v->right != NULL) l = v->right->height;

  v->height = 1 + std::max(l, r);
}


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  /*
           z                                      y 
          / \                                   /   \
         y   T4      Right Rotate (z)          x      z
        / \          - - - - - - - - ->      /  \    /  \ 
       x   T3                               T1  T2  T3  T4
      / \
    T1   T2

  */

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild = 0;
  if (greatGrandParentNode != NULL){
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
  }

  else{
    root = parentNode;
  }

  TreeNode *T1 = currNode->left;
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = parentNode->right;
  TreeNode *T4 = grandParentNode->right;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  
  update(grandParentNode);
  update(currNode);
  update(parentNode);
  // int t3=-1,t4=-1,a1=-1,a2=-1;
  // if (T3 != NULL) t3 = T3->height;
  // if (T4 != NULL) t4 = T4->height;
  // if (currNode != NULL) a1 = currNode->height;
  // if (grandParentNode != NULL) a2 = grandParentNode->height;
  // grandParentNode->height = 1 + max(t3,t4);
  // parentNode->height = 1 + max(a1,a2);

  // TreeNode *q = parentNode;

  // while (q->parent != NULL){
  //   int hl=-1,hr=-1;
  //   if (q->parent->left!=NULL) hl = q->parent->left->height;
  //   if (q->parent->right!=NULL) hr = q->parent->right->height;
  //   q->parent->height = 1 + max(hl,hr);
  //   q = q->parent;
  // }

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{   
  /*
       z                               z                           x
      / \                            /   \                        /  \ 
     y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
    / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
  T1   x                          y    T3                    T1  T2 T3  T4
      / \                        / \
    T2   T3                    T1   T2

  */

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild = 0;
  if (greatGrandParentNode != NULL){
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
  }
  else{
    root = currNode;
  }
  TreeNode *T1 = parentNode->left;  
  TreeNode *T2 = currNode->left;  
  TreeNode *T3 = currNode->right;
  TreeNode *T4 = grandParentNode->right;  

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  update(grandParentNode);
  update(parentNode);
  update(currNode);

  // int t1=0,t2=0,t3=0,t4=0,a1=0,a2=0;
  // if (T1 != NULL) t1 = T1->height;
  // if (T2 != NULL) t2 = T2->height;
  // if (T3 != NULL) t3 = T3->height;
  // if (T4 != NULL) t4 = T4->height;
  // if (parentNode != NULL) a1 = parentNode->height;
  // if (grandParentNode != NULL) a2 = grandParentNode->height;
  // parentNode->height = 1 + max(t1,t2);
  // grandParentNode->height = 1 + max(t3,t4);
  // currNode->height = 1 + max(a1,a2);

  // TreeNode *q = currNode;

  // while (q->parent != NULL){
  //   int hl=0,hr=0;
  //   if (q->parent->left!=NULL) hl = q->parent->left->height;
  //   if (q->parent->right!=NULL) hr = q->parent->right->height;
  //   q->parent->height = 1 + max(hl,hr);
  //   q = q->parent;
  // }

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  /*
     z                            z                            x
    / \                          / \                          /  \ 
  T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
      / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
     x   T4                      T2   y                  T1  T2  T3  T4
    / \                              /  \
  T2   T3                           T3   T4
  
  */

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild = 0;
  if (greatGrandParentNode != NULL){
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
  }

  else{
    root = currNode;
  }

  TreeNode *T1 = grandParentNode->left;  
  TreeNode *T2 = currNode->left;  
  TreeNode *T3 = currNode->right;
  TreeNode *T4 = parentNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parentNode, true);

  update(grandParentNode);
  update(parentNode);
  update(currNode);

  // int t1=0,t2=0,t3=0,t4=0,a1=0,a2=0;
  // if (T1 != NULL) t1 = T1->height;
  // if (T2 != NULL) t2 = T2->height;
  // if (T3 != NULL) t3 = T3->height;
  // if (T4 != NULL) t4 = T4->height;
  // if (parentNode != NULL) a1 = parentNode->height;
  // if (grandParentNode != NULL) a2 = grandParentNode->height;
  // parentNode->height = 1 + max(t3,t4);
  // grandParentNode->height = 1 + max(t1,t2);
  // currNode->height = 1 + max(a1,a2);

  // TreeNode *q = currNode;

  // while (q->parent != NULL){
  //   int hl=0,hr=0;
  //   if (q->parent->left!=NULL) hl = q->parent->left->height;
  //   if (q->parent->right!=NULL) hr = q->parent->right->height;
  //   q->parent->height = 1 + max(hl,hr);
  //   q = q->parent;
  // }

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  /*
    z                                y
   /  \                            /   \ 
  T1   y     Left Rotate(z)       z      x
      /  \   - - - - - - - ->    / \    / \
     T2   x                     T1  T2 T3  T4
         / \
       T3  T4

  */

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild = 0;
  if (greatGrandParentNode != NULL){
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
  }

  else{
    root = parentNode;
  }
  
  TreeNode *T1 = grandParentNode->left;
  TreeNode *T2 = parentNode->left;
  TreeNode *T3 = currNode->left;
  TreeNode *T4 = currNode->right;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);

  update(grandParentNode);
  update(currNode);
  update(parentNode);

  // int t1=0,t2=0,a1=0,a2=0;
  // if (T1 != NULL) t1 = T1->height;
  // if (T2 != NULL) t2 = T2->height;
  // if (currNode != NULL) a1 = currNode->height;
  // if (grandParentNode != NULL) a2 = grandParentNode->height;
  // grandParentNode->height = 1 + max(t1,t2);
  // parentNode->height = 1 + max(a1,a2);

  // TreeNode *q = grandParentNode;

  // while (q->parent != NULL){
  //   int hl=0,hr=0;
  //   if (q->parent->left!=NULL) hl = q->parent->left->height;
  //   if (q->parent->right!=NULL) hr = q->parent->right->height;
  //   q->parent->height = 1 + max(hl,hr);
  //   q = q->parent;
  // }

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // the scratch case
  if(root == NULL){
    root = new TreeNode(jrnyCode,price);
    root->height = 0;
    return true;
  }
  // if already present
  if (find(jrnyCode)!=-1) return false;
  
  // now to search a spot, insert there
  TreeNode* curr = root;
  TreeNode* t = new TreeNode(jrnyCode,price);

  while(true){
      if(AVLLessThan(curr, t)){
          if(curr->right!=NULL) curr = curr->right;
          else {
              updateAVLParentChild(t,curr,false);
              t->height = 0; curr->height = 1;
              // cout << "early" << endl;
              print();
              break;    
          }
      }
      else{
          if(curr->left!=NULL) curr = curr->left;
          else {
              updateAVLParentChild(t,curr,true);
              t->height = 0; curr->height = 1;
              // cout << "early" << endl;
              print();
              break;
          }
      }
  }

  // now to locate x,y,z, and update height simultaneously
  TreeNode *x, *y, *z;
  
  if (curr->parent == NULL){
    // cout << "curr has no parent" << endl;      
    return true;
  }
  
  x = t; 
  y = curr; 
  z = curr->parent; 
  //curr = curr->parent;

  while(true){
    if (z == NULL) {
      // cout << "here" << endl;
      return true;
    }

    int hl=-1,hr=-1;
    if (z->left!=NULL) hl = z->left->height;
    if (z->right!=NULL) hr = z->right->height;
    z->height = 1 + max(hl,hr);
    
    if (abs(hl-hr)<=1){
      x = y; 
      y = z;
      z = z->parent;
    }
    else break;
  }
  
  // now to figure out the right rotation
  if (y->left == x && z->left == y) {rotateLeftLeft(x,y,z);}
  if (y->left == x && z->right == y) rotateRightLeft(x,y,z);
  if (y->right == x && z->left == y) rotateLeftRight(x,y,z);
  if (y->right == x && z->right == y) rotateRightRight(x,y,z);

  // cout << "post" << endl;
  print();
  return true; 
}

int AVLTree::find(int jrnyCode)
{
  TreeNode* curr = root;
  TreeNode* temp = new TreeNode(jrnyCode,0);

  while(true){
    if (curr == NULL) return -1;
    if (AVLLessThan(temp, curr)){ curr = curr->left; }
    else if (AVLLessThan(curr, temp)) { curr = curr->right; }
    else {
      delete temp;
      return curr->retP(); 
    }
  }
  delete temp;
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

void AVLTree::updateHeight(TreeNode *v, int offset){
    if (v == NULL) return;
    v->height += offset;
    updateHeight(v->left,offset);
    updateHeight(v->right,offset);
}