#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
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

int hyt(TreeNode *head)    // This function has no change with path function 
{
  if (head == nullptr)     // in BST except function name.
    return -1;
  if (head->left == nullptr && head->right == nullptr)
    return 0;
  int left_height = hyt(head->left);

  int right_height = hyt(head->right);

  if (head->left != nullptr)
    head->left->height = left_height;
  if (head->right != nullptr)
    head->right->height = right_height;

  return 1 + max(left_height, right_height);
}
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if (greatGrandParentNode == nullptr)   // This case is when first imbalance doesnt have a parent i.e,
  {                                      // first imbalancing occurs at root.
    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);
    
    updateAVLParentChild(T3, grandParentNode, true);
    
    parentNode->parent = nullptr;   // Now parentNode will become root and and its parent is set to NULL.  
    root = parentNode;
    root->height = hyt(root);
    return true;
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
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

  root->height = hyt(root); // updating height of each node after rotation.
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
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  if (greatGrandParentNode == nullptr)  // Same as in the above case.
  {
    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);

    updateAVLParentChild(T2, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);
    
    currNode->parent = nullptr;
    root = currNode;
    root->height = hyt(root);
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
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)

  // Let T3 be the right child of currNode (i.e. of x)

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

  root->height = hyt(root);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParent->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(parent, currNode, false);

    updateAVLParentChild(grandParent, currNode, true);

    updateAVLParentChild(T2, grandParent, false);

    updateAVLParentChild(T3, parent, true);

    currNode->parent = nullptr;
    root = currNode;
    root->height = hyt(root);
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
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)

  // Let T3 be the right child of currNode (i.e. of x)

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parent, currNode, false);

  updateAVLParentChild(grandParent, currNode, true);

  updateAVLParentChild(T2, grandParent, false);

  updateAVLParentChild(T3, parent, true);

  root->height = hyt(root);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  
  TreeNode *greatGrandParentNode = grandParent->parent;
  TreeNode *T3 = parent->left;

  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(currNode, parent, false);

    updateAVLParentChild(grandParent, parent, true);

    updateAVLParentChild(T3, grandParent, false);

    parent->parent = nullptr;
    root = parent;
    root->height = hyt(root);
    return true;
  }

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
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parent, false);

  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T3, grandParent, false);

  root->height = hyt(root);
  return true;
}

TreeNode *AVLTree::search(TreeNode *T, int JourneyCode)  // This search function has no change with 
{                                                        // search in BST.
  TreeNode *temp = new TreeNode(JourneyCode, 0);
  if (T == nullptr)
  {
    return nullptr;
  }
  if (AVLLessThan(T, temp))
  {
    return search(T->right, JourneyCode);
  }
  else if (AVLLessThan(temp, T))
  {
    return search(T->left, JourneyCode);
  }
  else
    return T;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

TreeNode *AVLTree::get_imb(TreeNode *T)  // This function returns the lowest node at which imbalance occurs.
{
  if (T == nullptr)
  {
    return nullptr;   // if not found return NULL.
  }
  else
  {
    int height_diff = hyt(T->left) - hyt(T->right);
    if (abs(height_diff) > 1)   // If there is an imbalance at current node then return address of node.
      return T;
    else
      return get_imb(T->parent); // else call the function recursively by moving up.
  }
}

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *newnode = new TreeNode(jrnyCode, price);
  if (search(root, jrnyCode) != nullptr)
  {
    return false;
  }
  else
  {
    if (root == nullptr)
    {
      root = new TreeNode(jrnyCode, price);
      root->height = 0;
      return true;
    }
    else
    {
      TreeNode *T = root;
      TreeNode *temp;
      while (T != nullptr)
      {
        temp = T;
        if (AVLLessThan(newnode, T))
        {
          T = T->left;
        }
        else
        {
          T = T->right;
        }
      }
      if (AVLLessThan(newnode, temp))
      {
        updateAVLParentChild(newnode, temp, true);
        root->height = hyt(root);
      }
      else
      {
        updateAVLParentChild(newnode, temp, false);
        root->height = hyt(root);
      }                  
                                        // First insert the node as done in case of BST
      TreeNode *grand = get_imb(newnode); // then check for any imbalance created.
      if (grand == nullptr)
        return true;    // If no imbalance is created the insertion is already done successfully.
      else
      {
        if (AVLLessThan(newnode, grand)) // If child is left
        {
          if (AVLLessThan(newnode, grand->left))  // if grandchild is left
          {
            return rotateLeftLeft(grand->left->left, grand->left, grand);
          }
          else              // else grandchild is right
          {
            return rotateLeftRight(grand->left->right, grand->left, grand);
          }
        }
        else      // else child is right
        {
          if (AVLLessThan(newnode, grand->right))  // if grandchild is left
          {
            return rotateRightLeft(grand->right->left, grand->right, grand);
          }
          else        // if grandchild is right.
          {
            return rotateRightRight(grand->right->right, grand->right, grand);
          }
        }
      }
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
  TreeNode *getnode = search(root, jrnyCode);
  if (getnode != nullptr)
  {
    return getnode->getprice();         // This function works same as it works in BST.
  }
  else
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
