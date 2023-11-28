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
int AVLTree::maxDepth(TreeNode* a){
  if (a == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(a->left);
        int rDepth = maxDepth(a->right);
     
        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
    TreeNode *T3 = parentNode->right;

    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
  
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
      
    updateAVLParentChild(T3, grandParentNode, true);
      // We use "true" as the third argument of the following call to indicate
      // that T3 should become the left child of grandParentNode
    parentNode->parent=nullptr;
    root=parentNode;
    return true;
  }
  else{
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
    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    return true;
  }
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
   if (greatGrandParentNode == nullptr){
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    updateAVLParentChild(T2, parentNode, false);
    currNode->parent =nullptr;root=currNode;
    return true;
  }
  else{
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
    return true;
  }
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
      TreeNode *T2 = currNode->left;
      TreeNode *T3 = currNode->right;
      updateAVLParentChild(parentNode, currNode, false);
      updateAVLParentChild(grandParentNode, currNode, true);
      updateAVLParentChild(T3, parentNode, true);
      updateAVLParentChild(T2, grandParentNode, false);
      currNode->parent=nullptr;root=currNode;
      return true;
    }
  else{
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
    updateAVLParentChild(parentNode, currNode, false);
    updateAVLParentChild(grandParentNode, currNode, true);
    updateAVLParentChild(T3, parentNode, true);
    updateAVLParentChild(T2, grandParentNode, false);
    return true;
  }
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
  TreeNode *T3 = parentNode->left;
    updateAVLParentChild(grandParentNode, parentNode, true);
    updateAVLParentChild(T3, grandParentNode, false);
    parentNode->parent=nullptr;root=parentNode;
  return true;
  }
  else{
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
   updateAVLParentChild(grandParentNode, parentNode, true);
   updateAVLParentChild(T3, grandParentNode, false);
  return true;
  }
}

bool AVLTree::insert(int jrnyCode, int price)
{
  if (find(jrnyCode) != -1){
        return false;
  }
  TreeNode* temp;
  TreeNode* current = root;

  TreeNode* add = new TreeNode(jrnyCode, price);
  if(root == nullptr){
    root = add;
    updateheight(root);
    return true;
  }
  while(current != nullptr){
    temp = current;
    if(AVLLessThan(add, current)){
      current = current->left;
    }
    else{
      current = current->right;
    }
  }
  add->parent = temp;
  if(AVLLessThan(add, temp)){
    //temp->left = add;
    updateAVLParentChild(add, temp, true);
    TreeNode* node = temp->left;
  }
  else{
    //temp->right = add;
    updateAVLParentChild(add, temp, false);
    TreeNode* node = temp->right;
  }
  int i = 0;
  TreeNode* x;
  TreeNode* y;
  TreeNode* z;
  z = add;
  y = add;
  x = add;
  while(true){
    if(z->parent == nullptr){
      break;
    }
    int bal = maxDepth(z->left) - maxDepth(z->right);
    if(bal < -1 || bal > 1){
      break;
    }
    i += 1;
    if(i > 1){
      y = y->parent;
    }
    if(i > 2){
      x = x->parent;
    }
    z = z->parent;
  }
  int bal = maxDepth(z->left) - maxDepth(z->right);
  if(bal >= -1 && bal <= 1){
    updateheight(root);
    return true;
  }
  if(bal > 1 && AVLLessThan(x, y)){
    rotateLeftLeft(x, y, z);
  }
  else if(bal > 1&& AVLLessThan(y, x)){
    rotateLeftRight(x, y, z);
  }
  else if((bal < -1)&&(AVLLessThan(x, y))){
    rotateRightLeft(x, y, z);
  }
  else if((bal < -1)&&(AVLLessThan(y, x))){
    rotateRightRight(x, y, z);
  }
  updateheight(root);
  return true;
}
void AVLTree::updateheight(TreeNode* a){
  a->height = maxDepth(a);
  if(a->left != nullptr){
    updateheight(a->left);
  }
  if(a->right != nullptr){
    updateheight(a->right);
  }
  return;
}
// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode* x;
  TreeNode* y;
  x = root;
  y = new TreeNode(jrnyCode, 0);
  while (x != NULL && x->getjourney() != y->getjourney()){
    if(AVLLessThan(y, x)){     //add in case   || y->getjourney() == x->getjourney()
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  if(x == NULL){
    return -1;
  }
  else{
    return x->getprice();
  }
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


