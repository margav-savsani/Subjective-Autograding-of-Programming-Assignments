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

  if (greatGrandParentNode != nullptr)
  {
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
  }

  else
  {
    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->right;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // As no greatgrandparent exist parent node now will be the new root of the\
    the tree as earlier grandparent node was the root.
    root = parentNode;
    parentNode->parent = nullptr;

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

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // If greatgrandparent exist
  if (greatGrandParentNode != nullptr)
  {

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
  }

  // If greatgrandparent does not exist that is grandparent is root
  else
  {
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

    // For the case when greatgrandparent is NULL
    root = currNode;
    currNode->parent = nullptr;

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

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // If greatgrandparent exist
  if (greatGrandParentNode != nullptr)
  {

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
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

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
  }

  // If greatgrandparent does not exist that is grandparent is root
  else
  {
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

    // For the case when greatgrandparent is NULL
    root = currNode;
    currNode->parent = nullptr;

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

  if (greatGrandParentNode != nullptr)
  {
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
    TreeNode *T3 = parentNode->left;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

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
  }

  else
  {
    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->left;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // As no greatgrandparent exist parent node now will be the new root of the\
    the tree as earlier grandparent node was the root.
    root = parentNode;
    parentNode->parent = nullptr;

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
  }

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

  // Creating a temporary temp node for comparisons
  TreeNode *element = new TreeNode(jrnyCode, price);

  TreeNode *finder;
  TreeNode *parent = nullptr;
  finder = root;
  while (finder != nullptr)
  {
    parent = finder;
    // Updating the comparison cost by 1 as equality was checked
    totalComparisonCost = totalComparisonCost + perComparisonCost;
    if (*finder == *element)
    {
      break;
    }
    else if (AVLLessThan(finder, element))
    {
      finder = finder->right;
    }
    else
    {
      finder = finder->left;
    }
  }

  // finder as null indicates that the given journey code doesn't exist already and hence we can \
  perform the addition of node
  if (finder == nullptr)
  {
    // indicates that addition is not being done at the root position
    if (parent != nullptr)
    {
      element->parent = parent;
      if (AVLLessThan(parent, element))
      {
        updateAVLParentChild(element, parent, false);
        // parent->right = element;
      }
      else
      {
        updateAVLParentChild(element, parent, true);
        // parent->left = element;
      }
    }

    // for the case when addition is at root position that is the added element is the \
    very first element of the Tree.
    else
    {
      root = element;
      updateAVLParentChild(element, parent, false);
      // element->parent = nullptr;
    }

    // Updating the height of all the elements up the path until we find a node where insertion don't result in height change\
    and that would be after we find the first unbalanced node or find the first node where addition hasn't changed the height\
    essentially meaning that no unbalanced node was created

    // Creating x, y and z now itself
    TreeNode *x = element;
    TreeNode *y = element->parent;
    TreeNode *z;
    if (y == nullptr)
    {
      return true;
    }
    else
    {
      z = y->parent;
      if (y->right == nullptr || y->left == nullptr)
      {
        y->height = x->height + 1;
      }
      else
      {
        // og_height stores height before insertion of new node
        int og_height = y->height;

        // new_height stores new proposed height post insertion of new node
        // int new_height = max((y->left)->height, (y->right)->height) + 1;
        int new_height = x->height + 1;

        // If new and old are same that means we basically are at the node from which\
        any node above it won't have any height change
        if (new_height <= og_height)
        {
          return true;
        }
        else
        {
          y->height = new_height;
        }
      }
    }
    while (z != nullptr)
    {
      if (z->right == nullptr || z->left == nullptr)
      {
        // Not checking the case of unbalance here,
        // og_height stores height before insertion of new node
        int og_height = z->height;

        // new_height stores new proposed height post insertion of new node
        int new_height = y->height + 1;

        // For the case when height has been changed, here we must also check if\
        imbalance has been there or not
        // Need to do rotation here, to balance the tree
        if (y->height > 0)
        {
          // Need to check which rotation has to be called
          if (z->right == y && y->right == x)
          {
            // cout << "M here RR z special" << endl;
            rotateRightRight(x, y, z);
            z->height = z->height - 1;
          }
          else if (z->right == y && y->left == x)
          {
            // cout << "M here RL zspecial" << endl;
            rotateRightLeft(x, y, z);
            x->height = x->height + 1;
            y->height = y->height - 1;
            z->height = z->height - 1;
          }
          else if (z->left == y && y->right == x)
          {
            // cout << "M here LR zspecial" << endl;
            rotateLeftRight(x, y, z);
            x->height = x->height + 1;
            y->height = y->height - 1;
            z->height = z->height - 1;
          }
          else
          {
            // cout << "M here LL zspecial" << endl;
            rotateLeftLeft(x, y, z);
            z->height = z->height - 1;
          }

          // Post-rotation we don't need to change anymore heights
          break;
        }

        // Tree balanced yet, simply update the height and move up as possibility\
          of unbalanced node occuring has not yet been reduced to zero.
        else
        {
          z->height = new_height;
          x = y;
          y = z;
          z = z->parent;
          continue;
        }
      }
      else
      {
        // og_height stores height before insertion of new node
        int og_height = z->height;

        // new_height stores new proposed height post insertion of new node
        int new_height = max((z->left)->height, (z->right)->height) + 1;

        // If new and old are same that means we basically are at the node from which\
        any node above it won't have any height change
        if (new_height <= og_height)
        {
          break;
        }

        // For the case when height has been changed, here we must also check if\
        imbalance has been there or not
        else
        {
          // Need to do rotation here, to balance the tree
          if (abs((z->left)->height - (z->right)->height) > 1)
          {
            // Need to check which rotation has to be called
            if (z->right == y && y->right == x)
            {
              // cout << "M here RR " << endl;
              rotateRightRight(x, y, z);
              z->height = z->height - 1;
            }
            else if (z->right == y && y->left == x)
            {
              // cout << "M here RL" << endl;
              rotateRightLeft(x, y, z);
              x->height = x->height + 1;
              y->height = y->height - 1;
              z->height = z->height - 1;
            }
            else if (z->left == y && y->right == x)
            {
              // cout << "M here LR" << endl;
              rotateLeftRight(x, y, z);
              x->height = x->height + 1;
              y->height = y->height - 1;
              z->height = z->height - 1;
            }
            else
            {
              // cout << "M here LL" << endl;
              rotateLeftLeft(x, y, z);
              z->height = z->height - 1;
            }

            // Post-rotation we don't need to change anymore heights
            break;
          }

          // Tree balanced yet, simply update the height and move up as possibility\
          of unbalanced node occuring has not yet been reduced to zero.
          else
          {
            z->height = new_height;
            x = y;
            y = z;
            z = z->parent;
            continue;
          }
        }
      }
    }
    return true;
  }
  // Returning false as something was found with the same journey code and that is not allowed.
  return false;
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
  TreeNode *temp = new TreeNode(jrnyCode, 50);

  TreeNode *finder;
  finder = root;
  while (finder != NULL)
  {
    // Updating the comparison cost by 1 as equality is being checked
    totalComparisonCost = totalComparisonCost + perComparisonCost;
    if (*finder == *temp)
    {
      return finder->get_price();
    }
    else if (AVLLessThan(finder, temp))
    {
      finder = finder->right;
    }
    else
    {
      finder = finder->left;
    }
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
