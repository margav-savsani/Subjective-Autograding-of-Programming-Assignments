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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  // storing T3 before parentNode->right gets updated.
  TreeNode *T3 = parentNode->right;

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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
  // decrementing height of grandParentNode by 1.
  grandParentNode->height -= 1;

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // storing T2,T3 before their parent's left and right subtrees get updated.
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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

  // updating heights accordingly.
  grandParentNode->height -= 1;
  parentNode->height -= 1;
  currNode->height += 1;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // storing T2,T3 before its parent's left subtree and right subtree gets updated.
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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

  // Now replicate the double rotation for RightLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);

  // Recall from Prof. Garg's lectures that the right subtree of
  // parentNode (i.e. y in Prof. Garg's lectures) and left subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the RightLeft rotation.  So do don't need to update the
  // right child of parentNode and the left child of grandParentNode
  // at all.
  // The only update needed is that the right subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the left subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the left subtree
  // of currNode (i.e. of x) should now become the right subtree of
  // grandParentNode (i.e. of z).

  // Let's implement these updations below.

  // We use "true" as the third argument of the following call to indicate
  // that T2 should NOT become the right child of ParentNode
  updateAVLParentChild(T2, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  // updating heights accordingly.
  grandParentNode->height -= 1;
  parentNode->height -= 1;
  currNode->height += 1;

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Let T3 be the left child of parentNode
  // storing T3 before parentNode->left gets updated.
  TreeNode *T3 = parentNode->left;

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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
  // should NOT be made the right child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the rightright rotation.  So do don't need to update the children of
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

  // updating height of grandParentNode (decrementing by 1)
  grandParentNode->height -= 1;

  return true;
}

// Returns balance of the given node.
int AVLTree::getbalance(TreeNode *node)
{
  if (node == nullptr /* if nullptr, then return 0 as there exists no node */)
    return 0;
  if (node->left == nullptr && node->right == nullptr /* If node has no children hence, balance is 0. */)
    return 0;
  else if (node->left == nullptr && node->right != nullptr /* If there exists right child, then height of left subtree is 0. */)
    return 0 - node->right->height;
  else if (node->right == nullptr && node->left != nullptr /* If there exists left child, then height of right subtree is 0. */)
    return node->left->height;

  // returning difference of heights of left subtree and right subtree.
  return node->left->height - node->right->height;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
  // this part contains 3 impotant steps:
  // 1.Regular insertion as per BST(just inserting):
  TreeNode *y = nullptr;
  TreeNode *x = this->root;
  // constructing a dummy node with given journey code and price
  TreeNode *temp = new TreeNode(jrnyCode, price);
  // traversing through the tree (x as the place about to be inserted, y as parent of the x).
  while (x != nullptr)
  {
    y = x;
    // if both are equal
    if (!AVLLessThan(x, temp) && !AVLLessThan(temp, x))
    {
      return false;
    }
    if (AVLLessThan(temp, x))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  // constructing new element:
  TreeNode *about_to_insert = new TreeNode(jrnyCode, price);
  about_to_insert->parent = y;
  // first element to be added(root even not defined, we have to insert root).
  if (y == nullptr)
  {
    this->root = about_to_insert;
    return true;
  }
  // else,adding new element depending upon parent node
  updateAVLParentChild(about_to_insert, y, !(AVLLessThan(y, about_to_insert)));

  // 2.Searching for Z(aka GrandparentNode, first node at which inbalance occurs when we traverse upwards from the newly inserted node) and update heights of every node we come across accordingly:
  // traversing through the tree begining from the newly inserted node until we reach root.
  TreeNode *Z = about_to_insert;
  while (/* Condition : We go to its parent node only when the current node is balanced */ getbalance(Z) <= 1 && getbalance(Z) >= -1)
  {
    // basecase : If we reached the root, the tree is balanced , hence break the loop.
    if (Z == this->root)
      break;
    // Traversing to parent
    Z = Z->parent;
    // if left child dosent exits, height must be increased by one of the right child's height
    if (Z->left == nullptr && Z->right != nullptr)
    {
      Z->height = Z->right->height + 1;
      continue;
    }
    // if right child dosent exits, height must be increased by one of the left child's height
    if (Z->right == nullptr && Z->left != nullptr)
    {
      Z->height = Z->left->height + 1;
      continue;
    }

    // updating the height of node ny taking max of both children's height and adding 1 to it.
    Z->height = max(Z->left->height, Z->right->height) + 1;
  }

  // 3. after finding Z, then we need to find appropriate X,Y(parentNode, currNode respectively) and invoke appropriate rotation for balancing the AVLTree.
  TreeNode *X, *Y;
  if (getbalance(Z) > 1)
  {
    // if balance(Z) > 1, then , insertion occured in left subtree of Z. so, we make Y as left child of Z.
    Y = Z->left;
    if (getbalance(Y) > 1)
    {
      // if balance(Y) > 1, then , insertion occured in left subtree of Y. so, we make X as left child of Y.
      X = Y->left;
      // invoking LeftLeft rotation
      rotateLeftLeft(X, Y, Z);
    }
    else if (getbalance(Y) < -1)
    {
      // if balance(Y) < -1, then , insertion occured in right subtree of Y. so, we make X as right child of Y.
      X = Y->right;
      // invoking LeftRight rotation
      rotateLeftRight(X, Y, Z);
    }
  }
  else if (getbalance(Z) < -1)
  {
    // if balance(Z) < -1, then , insertion occured in right subtree of Z. so, we make Y as right child of Z.
    Y = Z->right;
    if (getbalance(Y) > 1)
    {
      // if balance(Y) > 1, then , insertion occured in left subtree of Y. so, we make X as left child of Y.
      X = Y->left;
      // invoking RightLeft rotation
      rotateRightLeft(X, Y, Z);
    }
    else if (getbalance(Y) < -1)
    {
      // if balance(Y) < -1, then , insertion occured in right subtree of Y. so, we make X as right child of Y.
      X = Y->right;
      // invoking RightRight rotation
      rotateRightRight(X, Y, Z);
    }
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
  TreeNode *node = this->root;
  // dummy node for comparision
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  //  traversing through the tree:
  while (node != nullptr)
  {
    // if both are equal, then returning a positive value.
    if (!AVLLessThan(node, temp) && !AVLLessThan(temp, node))
      return 1;
    else
    {
      if (AVLLessThan(node, temp))
        node = node->left;
      else
        node = node->right;
    }
  }
  // if not found, returning negative value(-1).
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
