#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int AVLTree::getImbalance(TreeNode *root)
{
  if (root->left == nullptr && root->right == nullptr)
  {
    return 0;
  }
  else if (root->left == nullptr)
  {
    return root->right->height + 1;
  }
  else if (root->right == nullptr)
  {
    return -1 - root->left->height;
  }
  else
  {
    return root->right->height - root->left->height;
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

  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T3 = parentNode->right;

    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    root = parentNode;
    root->parent = nullptr;

    return true;
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
    cerr << "1 Unexpected condition encountered!" << endl;
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

  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T2 = currNode->left;

    TreeNode *T3 = currNode->right;

    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);

    updateAVLParentChild(T2, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);
    root = currNode;
    root->parent = nullptr;

    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentN

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
    cerr << "2 Unexpected condition encountered!" << endl;
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

  // Recall from Prof. Garg's lectures that the // left subtree of
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

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  TreeNode *greatGrandParentNode = grandParent->parent;

  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T2 = currNode->left;

    TreeNode *T3 = currNode->right;

    updateAVLParentChild(parent, currNode, false);

    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T2, grandParent, false);

    updateAVLParentChild(T3, parent, true);

    root = currNode;
    root->parent = nullptr;

    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

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
    cerr << "3 Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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
  updateAVLParentChild(parent, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);

  // the right subtree of  parentNode (i.e. y in Prof. Garg's lectures) and left subtree of
  //  grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  //  after the RightLeft rotation.  So do don't need to update the
  //  right child of parentNode and the left child of grandParentNode
  //  at all.
  //  The only update needed is that the left subtree of currNode (i.e.
  //  x in Prof. Garg's notes) should now become the right subtree of
  //  grandParentNode (z in Prof. Garg's notes).  Similarly, the right subtree
  //  of currNode (i.e. of x) should now become the left subtree of
  //  ParentNode (i.e. of y).

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, grandParent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, parent, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParent->parent;

  if (greatGrandParentNode == nullptr)
  {
    TreeNode *T3 = parent->left;

    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);

    updateAVLParentChild(T3, grandParent, false);
    root = parent;
    root->parent = nullptr;

    return true;
  }

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

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
    cerr << "4 Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->left;

  // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should NOT be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parent, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, true);

  // the left and right subtrees of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the RightRight rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  return true;
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

  if (jrnyCode < 0 || price < 0)
    return false;

  if (root == nullptr) // When we initialize a BST using BST(), the JourneyCode of root node is 0. This makes sure that root is inserted before moving ahead.
  {
    // root->JourneyCode = JourneyCode;
    // root->price = price;
    // root->longestPathLength = 0;
    // root->shortestPathLength = 0;
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  TreeNode insrt(jrnyCode, price);
  if (AVLLessThan(root, &insrt))
  {
    if (root->right == nullptr) // When the right child of root doesn't exist, we create a new one and join them.
    {
      TreeNode *right = new TreeNode(jrnyCode, price);
      updateAVLParentChild(right, root, false);

      // if(root->left == nullptr) root->shortestPathLength = 0; //Since the node doesn't have a left child, that is the shortest path to a leaf node.
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;//As we go up the treewhile exiting recursion, we update the shortestPathLength of each node we encounter. It is the minimum of ShortestPathLength of both its child +1

      // As we go up the tree while exiting recursion, we update the longestPathLength of each node we encounter. It is the maximum of longestPathLength of both its child +1
      if (root->left == nullptr)
        root->height = root->right->height + 1;
      else
        root->height = std::max(root->left->height, root->right->height) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                       // stores the value of our root
      root = root->right;                          // changes root to root->right. This makes our RST the BST
      bool val = AVLTree::insert(jrnyCode, price); // recurses until the upper condition is reached.
      root = curr;                                 // This changes our BST from RST to BST.

      if (root->left == nullptr)
        root->height = root->right->height + 1;
      else
        root->height = std::max(root->left->height, root->right->height) + 1;

      int imbal = getImbalance(root);
      if (abs(imbal) > 1)
      {
        TreeNode *grandParent = root, *parent, *child;
        if (imbal < 0)
        {
          parent = grandParent->left;
          int pImbal = getImbalance(parent);
          if (pImbal < 0)
          {
            child = parent->left;
            rotateLeftLeft(child, parent, grandParent);
          }
          else
          {
            child = parent->right;
            rotateLeftRight(child, parent, grandParent);
          }
        }
        else
        {
          parent = grandParent->right;
          int pImbal = getImbalance(parent);
          if (pImbal < 0)
          {
            child = parent->left;
            rotateRightLeft(child, parent, grandParent);
          }
          else
          {
            child = parent->right;
            rotateRightRight(child, parent, grandParent);
          }
        }
          if (grandParent->left == nullptr)
          {
            if(grandParent->right==nullptr) grandParent->height=0;
            else grandParent->height = grandParent->right->height + 1;
          }
          else
          {
            if(grandParent->right==nullptr) grandParent->height = grandParent->left->height + 1;
            else grandParent->height = std::max(grandParent->left->height, grandParent->right->height) + 1;
          }

          if (parent->left == nullptr)
          {
            if(parent->right==nullptr) parent->height=0;
            else parent->height = parent->right->height + 1;
          }
          else
          {
            if(parent->right==nullptr) parent->height = parent->left->height + 1;
            else parent->height = std::max(parent->left->height, parent->right->height) + 1;
          }

          if (child->left == nullptr)
          {
            if(child->right==nullptr) child->height=0;
            else child->height = child->right->height + 1;
          }
          else
          {
            if(child->right==nullptr) child->height = child->left->height + 1;
            else child->height = std::max(child->left->height, child->right->height) + 1;
          }
      }

      return val;
    }
  }

  else if (AVLLessThan(&insrt, root))
  {
    if (root->left == nullptr) // When the left child of root doesn't exist, we create a new one and join them.
    {
      TreeNode *left = new TreeNode(jrnyCode, price);
      updateAVLParentChild(left, root, true);

      // if(root->right == nullptr) root->shortestPathLength = 0;
      // else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      if (root->right == nullptr)
        root->height = root->left->height + 1;
      else
        root->height = std::max(root->left->height, root->right->height) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                       // stores the value of our root
      root = root->left;                           // changes root to root->left. This makes our LST the BST
      bool val = AVLTree::insert(jrnyCode, price); // recurses until the upper condition is reached.
      root = curr;                                 // This changes our BST from LST to BST.

      if (root->right == nullptr)
        root->height = root->left->height + 1;
      else
        root->height = std::max(root->left->height, root->right->height) + 1;

      int imbal = getImbalance(root);
      if (abs(imbal) > 1)
      {
        TreeNode *grandParent = root, *parent, *child;
        if (imbal < 0)
        {
          parent = grandParent->left;
          int pImbal = getImbalance(parent);
          if (pImbal < 0)
          {
            child = parent->left;
            rotateLeftLeft(child, parent, grandParent);
          }
          else
          {
            child = parent->right;
            rotateLeftRight(child, parent, grandParent);
          }
        }
        else
        {
          parent = grandParent->right;
          int pImbal = getImbalance(parent);
          if (pImbal < 0)
          {
            child = parent->left;
            rotateRightLeft(child, parent, grandParent);

          }
          else
          {
            child = parent->right;
            rotateRightRight(child, parent, grandParent);
          }
        }

        if (grandParent->right == nullptr)
          {
            if(grandParent->left==nullptr) grandParent->height=0;
            else grandParent->height = grandParent->left->height + 1;
          }
          else
          {
            if(grandParent->left==nullptr) grandParent->height = grandParent->right->height + 1;
            else grandParent->height = std::max(grandParent->left->height, grandParent->right->height) + 1;
          }

          if (parent->right == nullptr)
          {
            if(parent->left==nullptr) parent->height=0;
            else parent->height = parent->left->height + 1;
          }
          else
          {
            if(parent->left==nullptr) parent->height = parent->right->height + 1;
            else parent->height = std::max(parent->left->height, parent->right->height) + 1;
          }

          if (child->right == nullptr)
          {
            if(child->left==nullptr) child->height=0;
            else child->height = child->left->height + 1;
          }
          else
          {
            if(child->left==nullptr) child->height = child->right->height + 1;
            else child->height = std::max(child->left->height, child->right->height) + 1;
          }
      }

      return val;
    }
  }
  else
    return false;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  if (root == nullptr)
    return -1;

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

  TreeNode tmp(jrnyCode, 0);
  bool a = AVLLessThan(&tmp, root), b = AVLLessThan(root, &tmp);
  if (!a && !b)
  {
    return root->getPrice(); // Base Condition
  }

  if (AVLLessThan(&tmp, root))
  {
    // if (root->right == nullptr)
    //   return false; // Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
    // else
    {
      TreeNode *curr = root;             // stores value of current root
      root = root->left;                 // Changes root to point to right child to recurse in RST
      int val = AVLTree::find(jrnyCode); // recurses until a Base condition is satisfied.
      root = curr;                       // We come back to our original BST
      return val;
    }
  }

  else
  {
    // if (root->left == nullptr)
    //   return false; // Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
    // else
    {
      TreeNode *curr = root;             // stores value of current root
      root = root->right;                // Changes root to point to left child to recurse in LST
      int val = AVLTree::find(jrnyCode); // recurses until a Base condition is satisfied.
      root = curr;                       // We come back to our original BST
      return val;
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
