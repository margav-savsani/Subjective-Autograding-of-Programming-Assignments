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
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  TreeNode *T3 = parentNode->right;

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode

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

  root = parentNode; // updating root

  if (T3 != NULL && grandParentNode->right != NULL) // children of grandparent
  {
    grandParentNode->height = 1 + max(T3->height, grandParentNode->right->height); // updating height of grand parent node
  }
  else if (T3 != NULL) // if only one child exists
  {
    grandParentNode->height = 1 + T3->height; // updating height of grand parent node
  }
  else if (grandParentNode->right != NULL) // if only one child exists
  {
    grandParentNode->height = 1 + grandParentNode->right->height;
  }
  else
  {
    grandParentNode->height = 0; // updating height of grand parent node
  }
  parentNode->height = 1 + max(currNode->height, grandParentNode->height); // updating height of parent node
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
  currNode->height += 1;         // changed height as per lecture  slides
  parentNode->height += -1;      // changed height as per lecture  slides
  grandParentNode->height += -2; // changed height as per lecture  slides
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
  root = currNode;
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(parentNode, currNode, false);     // symetric case of rotateLeftLeft just changing true to false
  updateAVLParentChild(grandParentNode, currNode, true); // symetric case of rotateLeftLeft just changing false to true
  updateAVLParentChild(T2, parentNode, true);            // symetric case of rotateLeftLeft just changing false to true
  updateAVLParentChild(T3, grandParentNode, false);      // symetric case of rotateLeftLeft just changing true to false
  currNode->height += 1;                                 // changed height as per lecture  slides
  parentNode->height += -1;                              // changed height as per lecture  slides
  grandParentNode->height += -2;                         // changed height as per lecture  slides
  root = currNode;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *T3 = parentNode->left; // symetric case of rotateLeftLeft just changing  right to left

  updateAVLParentChild(currNode, parentNode, false);       // symetric case of rotateLeftLeft just changing true to false
  updateAVLParentChild(grandParentNode, parentNode, true); // symetric case of rotateLeftLeft just changing false to true
  updateAVLParentChild(T3, grandParentNode, false);        // symetric case of rotateLeftLeft just changing true to false
  root = parentNode;                                       // updating parent node
  if (T3 != NULL && grandParentNode->left != NULL)         // children of grandparent
  {
    grandParentNode->height = 1 + max(T3->height, grandParentNode->left->height); // updating height of grand parent node
  }
  else if (T3 != NULL) // if only one child exists
  {
    grandParentNode->height = 1 + T3->height; // updating height of grand parent node
  }
  else if (grandParentNode->right != NULL) // if only one child exists
  {
    grandParentNode->height = 1 + grandParentNode->left->height; // updating height of grand parent node
  }
  else
  {
    grandParentNode->height = 0; // updating height of grand parent node
  }
  parentNode->height = 1 + max(currNode->height, grandParentNode->height); // updating height of parent node
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *t = new TreeNode(jrnyCode, price);
  if (root == NULL)
  {
    root = t;
    return true; // adds at root if its null
  }
  AVLTree *T1 = new AVLTree(root->left, perComparisonCost, perParentChildUpdateCost);  // new left sub tree
  AVLTree *T2 = new AVLTree(root->right, perComparisonCost, perParentChildUpdateCost); // new right subtree

  if (AVLLessThan(t, root)) // if it belongs to left subtree
  {
    if (!T1->insert(jrnyCode, price)) // if it doesnt insert
    {
      return false;
    }
    totalComparisonCost += T1->getComparisonCost();               // adding comparison cost
    totalParentChildUpdateCost += T1->getParentChildUpdateCost(); // adding parentchild update cost
    updateAVLParentChild(T1->root, root, true);                   // updating the left child into tree
  }
  else if (AVLLessThan(root, t)) // if it belongs to right subtree
  {
    if (!T2->insert(jrnyCode, price)) // if it doesnt insert
    {
      return false;
    }
    totalComparisonCost += T2->getComparisonCost();               // adding comparison cost
    totalParentChildUpdateCost += T2->getParentChildUpdateCost(); // adding parentchild update cost
    updateAVLParentChild(T2->root, root, false);                  // updating the right child into tree
  }
  else
    return false; // if it doesnt belong to either left or right

  if (root->right != NULL && root->left != NULL) // if both childs are present
  {
    root->height = 1 + max(root->right->height, root->left->height); // maximum of height
  }
  else if (root->right != NULL) // if only right child exists
  {
    root->height = 1 + root->right->height; // updating the height
  }
  else if (root->left != NULL) // if only left child exists
  {
    root->height = 1 + root->left->height; // updating the height
  }
  else
    root->height = 0; // if no child height to 0

  if (root->left != NULL) // if left child exists
  {
    if (root->left->left != NULL) // if left to left exists
    {
      if (root->right != NULL) // if right exists
      {
        if (root->left->height - root->right->height > 1) // if left tree is having more height
        {
          rotateLeftLeft(root->left->left, root->left, root); // rotate left-left
        }
      }
      if (root->left->height >= 1 && root->right == NULL) // if right doesnt exist and left is more than 1
      {
        rotateLeftLeft(root->left->left, root->left, root); // rotate left-left
      }
    }
  }

  if (root->right != NULL) // if right exists
  {
    if (root->right->right != NULL) // if right-right exists
    {
      if (root->left != NULL) // if left exists
      {
        if (root->right->height - root->left->height > 1) // if right tree has more height
        {
          rotateRightRight(root->right->right, root->right, root); // rotate-right-right
        }
      }
      if (root->right->height >= 1 && root->left == NULL) // if left doesnt exist and right is more than 1
      {
        rotateRightRight(root->right->right, root->right, root); // rotate-right-right
      }
    }
  }

  if (root->left != NULL) // if left exists
  {
    if (root->left->right != NULL) // if left-right exists
    {
      if (root->right != NULL) // if right exists
      {
        if (root->left->height - root->right->height > 1) // if left tree height has more height
        {
          rotateLeftRight(root->left->right, root->left, root); // rotate-left-right
        }
      }
      if (root->left->height >= 1 && root->right == NULL) // if right doesnt exist and left has height more than 1
      {
        rotateLeftRight(root->left->right, root->left, root); // rotate-left-right
      }
    }
  }

  if (root->right != NULL) // if right exists
  {
    if (root->right->left != NULL) // if right-left exists
    {
      if (root->left != NULL) // if left exists
      {
        if (root->right->height - root->left->height > 1) // if right side has more height
        {
          rotateRightLeft(root->right->left, root->right, root); // rotate-right-left
        }
      }
      if (root->right->height >= 1 && root->left == NULL) // if left is null and right has more than 1
      {
        rotateRightLeft(root->right->left, root->right, root); // rotate-right-left
      }
    }
  }

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
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *temp = root;
  TreeNode *t = new TreeNode(jrnyCode, 0);
  while (temp != NULL)
  {
    if (AVLLessThan(t, temp))
    {
      temp = temp->left; // check in left tree if price is less than root's
    }
    else if (AVLLessThan(temp, t))
    {
      temp = temp->right; // check in right subtree if price is more than root's
    }
    else
      return temp->getprice(); // if found returns get price
  }
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
