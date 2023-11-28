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


//updates the height of the AVL tree from parent of given node to the root.
TreeNode *AVLTree::updateheight(TreeNode *z)
{
  TreeNode *x; // the current node to be found whose grand father is imbalanced
  TreeNode *y = z->parent;
  TreeNode *sendnode = nullptr; // the default nullpointer to be sent if no imbalance found
  while (y != nullptr) //
  {
    int temp; // temporary height stored so that even after insertion if the height remains same no need to go further upwards
    temp = y->height;

    //updating heights in various cases and sending the current node whose grandfather is imbalanced if such a node is found
    if (y->left == nullptr && y->right == nullptr)
      y->height = 0;
    else if (y->left != nullptr && y->right == nullptr)
    {
      y->height = y->left->height + 1;
      if (y->left->height >= 1 )
      {
        return x;
      }
    }
    else if (y->right != nullptr && y->left == nullptr)
    {
      y->height = y->right->height + 1;
      if (y->right->height >= 1)
      {
        return x;
      }
    }
    else
    {
      y->height = max(y->right->height, y->left->height) + 1;
      if (abs(y->left->height - y->right->height) > 1 )
      {
        return x;
      }
    }
    if (temp == y->height) // discussed in above comment
      break;
    x = z;
    z = y; // z becomes the father of x
    y = y->parent; // y becomes the grandfather of x
  }
  return sendnode; // default nullpointer to be sent if no imbalance found
}

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

  bool isGPLeftChild = false;
  if (greatGrandParentNode != nullptr) // this condition is added by me for the case when grandparent is the root otherwise will show seg fault due to accessing nullptr
  {
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

  grandParentNode->height -= 2;

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

  bool isGPLeftChild = false;
  if (greatGrandParentNode != nullptr) // this condition is added by me for the case when grandparent is the root otherwise will show seg fault due to accessing nullptr
  {
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

  grandParentNode->height -= 2;
  parentNode->height--;
  currNode++;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild = false;
  if (greatGrandParentNode != nullptr) // this condition is added by me for the case when grandparent is the root otherwise will show seg fault due to accessing nullptr
  {
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
  }

  // Let T1 be the left child of currNode (i.e. of x)
  TreeNode *T1 = currNode->left;

  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  //updating the current node as the child of the greatGrandParent node using isGPLleftchild boolean to find the place to be added
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T2 should become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T1, grandParentNode, false);

  grandParentNode->height -= 2;
  parentNode->height--;
  currNode++;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateRightRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild = false;
  if (greatGrandParentNode != nullptr)
  {
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
  }

  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->left;

  // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parentNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  grandParentNode->height -= 2;

  return true;
}

////When provided the current node, checks which rotation to perform on it(like leftleft or leftright etc) and does it
//current node was found during update height.
void AVLTree::dorotation(TreeNode *x)
{
  TreeNode *y = x->parent;
  TreeNode *z = y->parent;
  if (z->left == y && y->left == x)
  {
    rotateLeftLeft(x, y, z);
  }
  else if (z->left == y && y->right == x)
  {
    rotateLeftRight(x, y, z);
  }
  else if (z->right == y && y->left == x)
  {
    rotateRightLeft(x, y, z);
  }
  else
  {
    rotateRightRight(x, y, z);
  }
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

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

  //if already found the journey code in the insertion return false
  if (find(jrnyCode) != -1)
    return false;

  TreeNode *z = new TreeNode(jrnyCode, price); // new treenode to be inserted is created
  //This 2 pointers will go through the tree to find the insertion location of the new treenode as parent and child
  TreeNode *y = nullptr;
  TreeNode *x = root;
  while (x != nullptr)
  {
    y = x;
    if (AVLLessThan(z, x))
    {
      x = x->left;
    }
    else
      x = x->right;
  }
  //y is going to be the parent of the inserted node
  //if y is nullptr then z must be the root
  if (y == nullptr)
    root = z;
  else if (AVLLessThan(z, y)) // comparing journeycodes to decide if z is the left or right child of y.
  {
    updateAVLParentChild(z, y, true);
  }
  else
    updateAVLParentChild(z, y, false);

  //updating the height of the tree above the inserted element to the root and return the first element whose grandfather has imbalance
  TreeNode *current_node = updateheight(z);

  //if such a current node is found do the required rotation to remove the imbalance
  if (current_node != nullptr)
    dorotation(current_node);

  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
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

  TreeNode *z = new TreeNode(jrnyCode, 0); //a treenode created with the given journey code and arbitrary price 

  TreeNode *x = root;
  while (x != nullptr && (AVLLessThan(x, z) || AVLLessThan(z, x))) //the condition after && actually checks for equality of the journeys
  {
    if (AVLLessThan(z, x))
      x = x->left;
    else
    {
      x = x->right;
    }
  }
  if (x == nullptr) // if no such journey found
    return -1;
  else
    return x->getprice(); //otherwise return the price

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
