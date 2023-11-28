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

// Function to check whether there is an imbalance in the given node in the tree.
//Note that we call this function for any non-leaf (i.e internal) nodes present in our path.
bool AVLTree::checkimbalance(TreeNode *given)
{
  TreeNode *l = given->left; //Left child
  TreeNode *r = given->right; //Right child
  int imbl = 0; //variable that determines the imbalance
  if (l != NULL && r != NULL) //For both subtrees present for the given node
                              //It is the difference in their heights.
  {
    imbl = (l->height - r->height);
  }
  else //If any one of the node is absent then it is given as 1 + the height of present node.
       //Since given is not a leaf hence atleast one of l or r is non-NULL
  {
    if (l != NULL)
    {
      imbl = (1 + l->height);
    }
    else
    {
      imbl = (1 + r->height);
    }
  }
  // IF imbl greater than 1 or less than -1 then imbalance
  if (imbl > 1 || imbl < -1)
  {
    return true;
  }
  // For the case of no imbalance.
  return false;
}

//Function checks which child is the given child of parent (i.e right or left)
//returns 0 for left, 1 for right
int AVLTree::checkchild(TreeNode *child, TreeNode *parent)
{
  int t; // Turn
  // t=0 <=> left
  // t=1 <=> right
  if (parent->left == child)
  {
    t = 0;
  }
  else
  {
    t = 1;
  }
  return t;
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParent = grandParent->parent;

  if (greatGrandParent == NULL)
  { // Case when z would be the root of the tree.
    TreeNode *T3 = parent->right;
    updateAVLParentChild(grandParent, parent, false);
    updateAVLParentChild(T3, grandParent, true);
    parent->parent = NULL;  //when parent becomes the root
    root = parent;
    return true;
  }
  // When gGP is not NULL
  // First find if grandParent is the left or right child of
  // greatGrandParent
  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T3 = parent->right;
  updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);
  updateAVLParentChild(grandParent, parent, false);
  updateAVLParentChild(T3, grandParent, true);
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParent = grandParent->parent;

  if (greatGrandParent == NULL)
  { // Case when z is the root itself.
    // Let T2 be the left child of curr (i.e. of x)
    TreeNode *T2 = currNode->left;
    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parent, currNode, true);
    updateAVLParentChild(grandParent, currNode, false);
    updateAVLParentChild(T2, parent, false);
    updateAVLParentChild(T3, grandParent, true);
    currNode->parent = NULL;
    root = currNode;
    return true;
  }
  // First find if grandParent is the left or right child of
  // greatGrandParent
  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  // Let T2 be the left child of curr (i.e. of x)
  TreeNode *T2 = currNode->left;
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
  updateAVLParentChild(parent, currNode, true);
  updateAVLParentChild(grandParent, currNode, false);
  updateAVLParentChild(T2, parent, false);
  updateAVLParentChild(T3, grandParent, true);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParent = grandParent->parent;

  if (greatGrandParent == NULL)
  {
    // Case when z is the root itself.
    // Let T2 be the left child of curr (i.e. of x)
    TreeNode *T2 = currNode->right;
    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->left;
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T2, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    currNode->parent = NULL;
    root = currNode;
    return true;
  }
  // First find if grandParent is the left or right child of
  // greatGrandParent
  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  // Let T3 be the left child of curr (i.e. of x)
  TreeNode *T3 = currNode->left;
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParent = grandParent->parent;

  if (greatGrandParent == NULL)
  { // Case when z would be the root of the tree.
    TreeNode *T3 = parent->left;
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    parent->parent = NULL;
    root = parent;
    return true;
  }
  // First find if grandParent is the left or right child of
  // greatGrandParent
  bool isGPLeftChild;
  if (greatGrandParent->left == grandParent)
  {
    isGPLeftChild = true;
  }
  else if (greatGrandParent->right == grandParent)
  {
    isGPLeftChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T3 = parent->left;
  updateAVLParentChild(parent, greatGrandParent, isGPLeftChild);
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  return true;
}

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *comparisonnode = new TreeNode(jrnyCode, price); //Creating a comparison node for comparison.
  
  TreeNode *currNode = root;
  TreeNode *parentOfCurrNode = nullptr;
  if (root == NULL) // For root not present yet.
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  while (currNode != nullptr)
  {
    if (this->AVLLessThan(currNode, comparisonnode))
    {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else
    {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
  //Assigning the parent of currNode.
  if (this->AVLLessThan(comparisonnode, parentOfCurrNode))
  {
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    updateAVLParentChild(currNode, parentOfCurrNode, true);
  }
  else
  {
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    updateAVLParentChild(currNode, parentOfCurrNode, false);
  }
  delete (comparisonnode); // Deleting the temporary node made.

  // Now we need to check whether there is some imbalance at any point.
  TreeNode *x = currNode;
  TreeNode *y = x->parent;
  if (y == NULL)
  {              // Case when x is the root itself.
    return true; // Do nothing in this case.
  }
  TreeNode *z = y->parent;
  if (z == NULL)
  { // if y is the root of the tree, then x is added as a child of y and hence height of y is 1.
    y->height = 1;
    return true;
  }
  parentOfCurrNode->height = 1; // After addition of a leaf
                                // The height of its parent is always 1.
  while (z != root)             // Checking untill z is not 'root'.
  {
    if (checkimbalance(z))
    {
      break; // imbalace in z hence break.
    }
    if((z->height - y->height) == 1 || (z->height - y->height) == 2){ 
      //Since if the height is 1 or 2 greater then no need to check.
      //For imbalance and return true height
      return true;
    }
    // else we continue, In this case height of z is equal height of y.
    z->height = 1 + y->height; // Since heights of x,y are already updated.
    x = y;
    y = z;
    z = z->parent;
  }
  //Making choice according to 00, 01, 10, 11 as (ll,lr,rl,rr) resp.
  int choice = 10*checkchild(y, z) + checkchild(x, y);
  if (!checkimbalance(z)) // Case when z is root and imbalance is not present.
  {
    z->height = max(1+y->height,z->height); // If no imbalance in tree then just increment height of z
    return true;
  }
  else
  { // Else z is the node with the first imbalance. (Z may or may not be root)
    if (choice == 00)
    {
      z->height--; // Changing the height.
      rotateLeftLeft(x, y, z); //Updating rotate function
    }
    else if (choice == 01)
    {
      z->height--;
      x->height++;
      y->height--;
      rotateLeftRight(x, y, z); //Updating rotate function
    }
    else if (choice == 11)
    {
      z->height--; // changing height.
      rotateRightRight(x, y, z); //Updating rotate function
    }
    else if (choice == 10)
    {
      z->height--;
      x->height++;
      y->height--;
      rotateRightLeft(x, y, z); //Updating rotate function
    }
    return true;
  }
}

int AVLTree::find(int jrnyCode)
{
  //Dummy node for comparison
  TreeNode *comparisonnode = new TreeNode(jrnyCode, 0);

  TreeNode *x = root; // STARTING FROM ROOT NODE
  while (x != NULL && ((this->AVLLessThan(x, comparisonnode) || this->AVLLessThan(comparisonnode, x))))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (this->AVLLessThan(comparisonnode, x))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  if (x == NULL)
  { // IF NO SUCH NODE
    return -1;
  }
  else
  {
    return 1; //return 1 instead of price
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
