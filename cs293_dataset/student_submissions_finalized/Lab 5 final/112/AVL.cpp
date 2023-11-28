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
  grandParentNode->height -= 2; // height modification
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isRoot = greatGrandParentNode == nullptr; // corner case. root is imbalanced
  if (isRoot)
  {
    greatGrandParentNode = new TreeNode(-1); // temp Node
    updateAVLParentChild(grandParentNode, greatGrandParentNode, true);
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

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

  if (isRoot)
  {
    greatGrandParentNode->left->parent = nullptr;
    root = greatGrandParentNode->left;
    delete greatGrandParentNode;
  }

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  grandParentNode->height -= 2; // height modification
  parentNode->height -= 1;      // height modification
  currNode->height += 1;
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isRoot = greatGrandParentNode == nullptr; // corner case. root is imbalanced
  if (isRoot)
  {
    greatGrandParentNode = new TreeNode(-1); // temp Node
    updateAVLParentChild(grandParentNode, greatGrandParentNode, true);
  }

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

  if (isRoot)
  {
    greatGrandParentNode->left->parent = nullptr;
    root = greatGrandParentNode->left;
    delete greatGrandParentNode;
  }

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  grandParentNode->height -= 2; // height modification
  parentNode->height -= 1;      // height modification
  currNode->height += 1;

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isRoot = greatGrandParentNode == nullptr; // corner case. root is imbalanced
  if (isRoot)
  {
    greatGrandParentNode = new TreeNode(-1); // temp Node
    updateAVLParentChild(grandParentNode, greatGrandParentNode, true);
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPRightChild;
  if (greatGrandParentNode == nullptr || greatGrandParentNode->right == grandParentNode)
  {
    isGPRightChild = true;
  }
  else if (greatGrandParentNode->left == grandParentNode)
  {
    isGPRightChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, !isGPRightChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);

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
  updateAVLParentChild(T2, parentNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  if (isRoot)
  {
    greatGrandParentNode->left->parent = nullptr;
    root = greatGrandParentNode->left;
    delete greatGrandParentNode;
  }

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  grandParentNode->height -= 2; // height modification

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isRoot = greatGrandParentNode == nullptr; // corner case. root is imbalanced
  if (isRoot)
  {
    greatGrandParentNode = new TreeNode(-1); // temp Node
    updateAVLParentChild(grandParentNode, greatGrandParentNode, true);
  }

  bool isGPRightChild;
  if (greatGrandParentNode == nullptr || greatGrandParentNode->right == grandParentNode)
  {
    isGPRightChild = true;
  }
  else if (greatGrandParentNode->left == grandParentNode)
  {
    isGPRightChild = false;
  }
  else
  {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->left;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, !isGPRightChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

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
  updateAVLParentChild(T3, grandParentNode, false);

  if (isRoot)
  {
    greatGrandParentNode->left->parent = nullptr;
    root = greatGrandParentNode->left;
    delete greatGrandParentNode;
  }

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode)
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
  return myInsert(jrnyCode, root);
}

void AVLTree::adjust(TreeNode *addedNode)
{
  TreeNode *currNode = addedNode;
  TreeNode *parentNode = addedNode->parent;
  if (parentNode == nullptr)
    return;
  TreeNode *grandParentNode = parentNode->parent;
  if (grandParentNode == nullptr)
    return;
  while (grandParentNode != nullptr)
  {
    int leftHeight, rightHeight;
    if (grandParentNode->left == nullptr)
      leftHeight = 0;
    else
      leftHeight = grandParentNode->left->height;
    if (grandParentNode->right == nullptr)
      rightHeight = 0;
    else
      rightHeight = grandParentNode->right->height;
    if (abs(leftHeight - rightHeight) > 1)
      break;
    else
    {
      currNode = parentNode;
      parentNode = grandParentNode;
      grandParentNode = grandParentNode->parent;
    }
  }
  if (grandParentNode == nullptr)
    return;
  bool first = (grandParentNode->left == parentNode);
  bool second = (parentNode->left == currNode);
  if (first && second)
  {
    rotateLeftLeft(currNode, parentNode, grandParentNode);
  }
  else if (first && !second)
  {
    rotateLeftRight(currNode, parentNode, grandParentNode);
  }
  else if (!first && second)
  {
    rotateRightLeft(currNode, parentNode, grandParentNode);
  }
  else
  {
    rotateRightRight(currNode, parentNode, grandParentNode);
  }
  // modify the hieghts here
  return;
}

// insert in subtree
bool AVLTree::myInsert(int JourneyCode, TreeNode *insertInMe)
{
  if (insertInMe == NULL && root != NULL)
  {
    return false;
  }
  else if (insertInMe == NULL && root == NULL)
  {
    root = new TreeNode(JourneyCode);
    return true;
  }
  TreeNode *compareMe = new TreeNode(JourneyCode);
  if (AVLEqualTo(insertInMe, compareMe))
  {
    delete compareMe;
    return false;
  }
  if (AVLLessThan(compareMe, insertInMe))
  {
    if (insertInMe->left == NULL)
    {
      updateAVLParentChild(compareMe, insertInMe, true);
      TreeNode *modifyMe = insertInMe; // modify the heights after addition
      modifyMe->height += 1;
      modifyMe = modifyMe->parent;
      while (modifyMe != NULL)
      {
        int leftHeight, rightHeight;
        if (modifyMe->left == nullptr)
          leftHeight = 0;
        else
          leftHeight = modifyMe->left->height;
        if (modifyMe->right == nullptr)
          rightHeight = 0;
        else
          rightHeight = modifyMe->right->height;
        modifyMe->height = 1 + max(leftHeight, rightHeight);
        modifyMe = modifyMe->parent;
      }
      adjust(insertInMe->left); // rotate appropriately and modify height againA
      return true;
    }
    else
    {
      delete compareMe;
      return myInsert(JourneyCode, insertInMe->left);
    }
  }
  else
  {
    if (insertInMe->right == NULL)
    {
      updateAVLParentChild(compareMe, insertInMe, false);
      TreeNode *modifyMe = insertInMe; // modify the heights after addition
      modifyMe->height += 1;
      modifyMe = modifyMe->parent;
      while (modifyMe != NULL)
      {
        int leftHeight, rightHeight;
        if (modifyMe->left == nullptr)
          leftHeight = 0;
        else
          leftHeight = modifyMe->left->height;
        if (modifyMe->right == nullptr)
          rightHeight = 0;
        else
          rightHeight = modifyMe->right->height;
        modifyMe->height = 1 + max(leftHeight, rightHeight);
        modifyMe = modifyMe->parent;
      }
      adjust(insertInMe->right); // rotate appropriately and modify height again
      return true;
    }
    else
    {
      delete compareMe;
      return myInsert(JourneyCode, insertInMe->right);
    }
  }
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
  return myFind(jrnyCode) != nullptr;
}

TreeNode *AVLTree::myFind(int jrnyCode)
{
  if (root == nullptr)
  {
    return nullptr;
  }
  TreeNode *compareMe = new TreeNode(jrnyCode);
  if (AVLEqualTo(compareMe, root))
  {
    delete compareMe;
    return root;
  }
  else
  {
    if (AVLLessThan(compareMe, root))
    {
      delete compareMe;
      TreeNode *curr = root;
      root = root->left;
      TreeNode *returnMe = myFind(jrnyCode);
      root = curr;
      return returnMe;
    }
    else
    {
      delete compareMe;
      TreeNode *curr = root;
      root = root->right;
      TreeNode *returnMe = myFind(jrnyCode);
      root = curr;
      return returnMe;
    }
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
