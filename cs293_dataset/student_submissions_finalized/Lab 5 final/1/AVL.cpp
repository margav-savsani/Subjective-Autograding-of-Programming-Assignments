#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode != NULL){
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
  }
  else{
    //handles the case when it is the root node.
    root = parentNode;
    parentNode->parent = NULL;
  }
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode != NULL){
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
  }
  else{
    root = currNode;
    currNode->parent = NULL;
  }
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParentNode)
{
  //similar implementation
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //handles the case when the grandparent node is the root.
  if(greatGrandParentNode != NULL){
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
  }
  else{
    root = currNode;
    currNode->parent = NULL;
  }
  TreeNode* T2 = currNode->left;
  TreeNode* T3 = currNode->right;
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parent, true);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
 TreeNode *greatGrandParentNode = grandParent->parent;
  if(greatGrandParentNode != NULL){
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
  }
  else{
    root = parent;
    parent->parent = NULL;
  }
  TreeNode *temp = parent->left;
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(temp, grandParent, false);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{ 
  TreeNode *to_insert = new TreeNode(jrnyCode, price);
  if(root == NULL){root = to_insert; return true;}
  TreeNode *curr = root;
  //move according to codes, to locate the insertion location
  while(true){
    if(AVLLessThan(to_insert, curr)){
      if(curr->left == NULL){
        updateAVLParentChild(to_insert, curr, true);
        break;
      }
      curr = curr->left;
    }
    else if(AVLLessThan(curr, to_insert)){
      if(curr->right == NULL){
        updateAVLParentChild(to_insert, curr, false);
        break;
      }
      curr = curr->right;
    }
    else return false;
  }
  //here curr stands for the parent of the newly inserted leaf.
  //2 addresses to indicate the preceding 2 nodes along the path to the root.
  TreeNode *g_child = NULL;
  TreeNode *child = to_insert;
  while(curr != NULL){
    int x = curr->left != NULL ? curr->left->height : -1;
    int y = curr->right != NULL ? curr->right->height : -1;
    //if imbalance condition found, break.
    if(abs(x-y) > 1) break;
    //update the height, the 2 nodes if not broken
    curr->height = max(x, y) + 1;
    g_child = child;
    child = curr;
    curr = curr->parent;
  }
  if(curr == NULL) return true;
  //now, curr is the earliest node of imbalance.
  bool left1 = true, left2 = true;
  //to check which rotation to invoke.
  if(curr->right == child) left1 = false;
  if(child->right == g_child) left2 = false;
  //call the rotation along with proper height updates.
  curr->height--;
  if(left1 && left2) rotateLeftLeft(g_child, child, curr);
  else if(left1 && !left2){
    rotateLeftRight(g_child, child, curr);
    g_child->height++;
    child->height--;
  }
  else if(!left1 && left2){
    rotateRightLeft(g_child, child, curr);
    g_child->height++;
    child->height--;
  }
  else rotateRightRight(g_child, child, curr);
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  TreeNode *curr = root;
  //move according to the code, until the code found or a nullptr encountered.
  while(true){
    if(AVLLessThan(temp, curr)) curr = curr->left;
    else if(AVLLessThan(curr, temp)) curr = curr->right;
    else{ 
      delete temp;
      return curr->price;
    }
    if(curr == NULL) break;
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
  if(find(jrnyCode) < 0) return false;
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  //pair doesn't exist
  TreeNode *node = root;
  //find the node to be removed
  while(true){
    if(AVLLessThan(temp, node)) node = node->left;
    else if(AVLLessThan(node, temp)) node = node->right;
    else break;
  }
  delete temp;
  TreeNode *z;
  //now node points to the node to be deleted.
  if(node->left == NULL && node->right == NULL){
      if(node == root){
        delete root;
        root = NULL; //empty tree now
        return true;
      }
      else{
        bool isLeft;
        if(node->parent->left == node) isLeft = true;
        else isLeft = false;
        updateAVLParentChild(NULL, node->parent, isLeft);
        z = node->parent;
        delete node;
      }
  }
  //if only one of the node's subtrees is non-empty, make its parent point to it.
  //if node is root, set the sub-tree's root as root
  else if(node->right == NULL){
    if(node == root){
      root = node->left;
      root->parent = NULL;
      node->left = NULL;
      delete node;
      return true;
    }
    else{
      bool isLeft;
      if(node->parent->left == node) isLeft = true;
      else isLeft = false;
      updateAVLParentChild(node->left, node->parent, isLeft);
      z = node->parent;
      delete node;
    }
  }
  else if(node->left == NULL){
    if(node == root){
      root = node->right;
      root->parent = NULL;
      node->right = NULL;
      delete node;
      return true;
    }
    else{
      bool isLeft;
      if(node->parent->left == node) isLeft = true;
      else isLeft = false;
      updateAVLParentChild(node->right, node->parent, isLeft);
      z = node->parent;
      delete node;
    }
  }
  else{
  //find the successor, (leftmost of right subtree (non-empty))
    TreeNode *succ = node->right;
    while(succ->left != NULL) succ = succ->left;
    //copy the values of the successor
    int price_succ = succ->price;
    int code_succ = succ->JourneyCode;
    //remove the successor node
    //cases based on if it has a parent (of whom it is a left child)
    //or if it is the right child of the node itself
    if(succ->left == NULL && succ->right == NULL){
      if(node->right == succ){
        updateAVLParentChild(NULL, node, false);
      }
      else updateAVLParentChild(NULL, succ->parent, true);
      z = succ->parent;
      delete succ;
    }
    else{
      if(node->right == succ){
        updateAVLParentChild(succ->right, node, false);
      }
      else{
        updateAVLParentChild(succ->right, succ->parent, true);
      }
      z = succ->parent;
      delete succ;
    }
    //a less efficient way to do it
    //remove(code_succ, price_succ);
    //replace node with the successor
    node->price = price_succ;
    node->JourneyCode = code_succ;
  }
  //now, z points to the last affected node, wrt height.
  while(true){
    while(z != NULL){
      int x = z->left != NULL ? z->left->height : -1;
      int y = z->right != NULL ? z->right->height : -1;
      z->height = max(x, y) + 1;
      if(abs(x-y) > 1) break;
      z = z->parent;
    }
    if(z == NULL){return true;}
    //now z points to the last imbalanced node.
    TreeNode *x, *y;
    //find the x, y nodes which are descendant of z with the larger heights.
    bool yIsLeft = true, xIsLeft;
    //bools to find which rotate to call
    int a = z->left != NULL ? z->left->height : -1;
    int b = z->right != NULL ? z->right->height : -1;
    if(b > a){
      yIsLeft = false;
      y = z->right;
    }
    else y = z->left;
    a = y->left != NULL ? y->left->height : -1;
    b = y->right != NULL ? y->right->height : -1;
    if(b == a){
      if(yIsLeft){xIsLeft = true; x = y->left;}
      else{xIsLeft = false; x = y->right;}
    }
    else if(b > a){xIsLeft = false; x = y->right;}
    else{xIsLeft = true; x = y->left;}
    //call the appropriate rotate with height updates for x, y, z
    if(yIsLeft && !xIsLeft){
      rotateLeftRight(x, y, z);
      z->height -= 2;
      y->height -= 1;
      x->height += 1;
      z = x;
    }
    else if(!yIsLeft && xIsLeft){
      rotateRightLeft(x, y, z);
      z->height -= 2;
      y->height -= 1;
      x->height += 1;
      z = x;
    } 
    else if(yIsLeft && xIsLeft){
      int initial_h = z->height;
      int h = y->right != NULL ? y->right->height : -1;
      rotateLeftLeft(x, y, z);
      z->height = h + 1;
      y->height = z->height + 1;
      z = y;
      if(z->height == initial_h) return true;
    }
    else{
      int initial_h = z->height;
      int h = y->left != NULL ? y->left->height : -1;
      rotateRightRight(x, y, z);
      z->height = h + 1;
      y->height = z->height + 1;
      z = y;
      if(z->height == initial_h) return true;
    }
    //after each block, z is set to point to the new "grandparent" node.
    //its height is used to compute the new heights of upper nodes, and to check
    //for further imbalance, which is handled similarly, until z becomes NULL.
  }
}


