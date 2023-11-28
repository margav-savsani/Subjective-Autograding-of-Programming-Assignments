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
  if (grandParentNode != root)
  {
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

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
  else
  {
    TreeNode *T3 = parentNode->right;
    root = parentNode;
    parentNode->parent = nullptr;
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    return true;
  }
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  if (grandParentNode != root)
  {
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

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

    return true;
  }
  else
  {
    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->left;

    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;

    root = currNode;
    currNode->parent = nullptr;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    return true;
  }
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  if (grandParent != root)
  {
    // Implement this yourself
    // Moreover, currNode is the left child of parentNode, and parentNode is the right child of grandParentNode.
    // That's why we are doing a rotateRightLeft

    TreeNode *greatGrandParentNode = grandParent->parent;

    // First find if grandParentNode is the left or right child of greatGrandParentNode.

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
    // We can directly implement the double rotation, instead of doing two
    // rotations sequentially.

    // Let T3 be the left child of currNode (i.e. of x)
    TreeNode *T3 = currNode->left;

    // Let T2 be the right child of currNode (i.e. of x)
    TreeNode *T2 = currNode->right;

    // Make currNode the appropriate child of greatGrandParentNode.
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    // Make parentNode the right child of currNode.
    // The last parameter is "false" to indicate that parentNode should be made the right child of currNode.
    updateAVLParentChild(parent, currNode, false);

    // Make grandParentNode the left child of currNode.
    // The last parameter is "true" to indicate that grandParent should be made the left child of currNode.
    updateAVLParentChild(grandParent, currNode, true);

    // the right subtree of parentNode and left subtree of grandParent stay unchanged after the LeftRight rotation.
    // The only update needed is that the right subtree of currNode should now become the left subtree of parent.
    // Similarly, the left subtree of currNode should now become the right subtree of grandParentNode.
    // Let's implement these updations below.

    // We use "true" as the third argument of the following call to indicate
    // that T2 should become the left child of ParentNode
    updateAVLParentChild(T2, parent, true);

    // We use "false" as the third argument of the following call to indicate
    // that T3 should become the right child of grandParentNode
    updateAVLParentChild(T3, grandParent, false);

    return true;
  }
  else
  {
    // Let T3 be the left child of currNode (i.e. of x)
    TreeNode *T3 = currNode->left;

    // Let T2 be the right child of currNode (i.e. of x)
    TreeNode *T2 = currNode->right;

    root = currNode;
    currNode->parent = nullptr;
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T2, parent, true);
    updateAVLParentChild(T3, grandParent, false);
  }
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  if (grandParent != root)
  {
    // Implement this yourself
    TreeNode *greatGrandParentNode = grandParent->parent;

    // First find if grandParentNode is the left or right child of greatGrandParentNode.

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

    TreeNode *T3 = parent->left;
    // Now replicate the single rotation for rightright as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode the appropriate child of greatGrandParentNode.
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

    // Make currNode the right child of parentNode.
    // The last parameter is "false" to indicate that currNode should be made the right child of parentNode.
    updateAVLParentChild(currNode, parent, false);

    // Make grandParentNode the left child of parentNode.
    // The last parameter is "true" to indicate that grandParentNode should be made the left child of parentNode.
    updateAVLParentChild(grandParent, parent, true);

    // We use "false" as the third argument of the following call to indicate
    // that T3 should become the right child of grandParentNode
    updateAVLParentChild(T3, grandParent, false);

    return true;
  }

  else
  {
    TreeNode *T3 = parent->left;
    root = parent;
    parent->parent = nullptr;
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
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
  // cout<<"hi"<<endl;
  TreeNode *y = nullptr;
  TreeNode *x = root;
  // We need to create z as a pointer so that the same address is not pointed every time when the function is called.
  TreeNode *z = new TreeNode(jrnyCode, price);

  while (x != nullptr)
  {
    y = x;

    if (AVLLessThan(z, x))
    {
      x = x->left;
    }
    else if (AVLLessThan(x, z))
    {
      x = x->right;
    }
    else
    {
      // cout<<"gone"<<endl;
      return false;
    }
  }
  // cout<<"hi1"<<endl;
  z->parent = y;

  if (y == nullptr)
  {
    root = z;
  }
  else if (AVLLessThan(z, y))
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }

  // cout<<"hi2"<<endl;
  TreeNode *w = y;
  // cout<<"hi3"<<endl;
  while (w != nullptr)
  {
    // cout << "hi" << endl;
    //cout << w->get_Journeycode() << w->height << endl;
    w->update_height();
    //cout << w->get_Journeycode() << w->height << endl;
    w = w->parent;
  }

  //cout << "hi4" << endl;
  if (y == nullptr || y == root)
  {
    //cout << "vinay" << endl;
    return true;
  }
  else
  {
    // cout<<"hello1"<<endl;
    w = z;
    TreeNode *w_child;
    TreeNode *w_grandchild;
    while (w->imbalance() == true && w != nullptr && w != root)
    {
      w_grandchild = w_child;
      w_child = w;
      w = w->parent;
      // cout << w->get_Journeycode() << endl;
      // cout << w_child->get_Journeycode() << endl;
      // cout << w_grandchild->get_Journeycode() << endl;
    }
    //cout << "hi5" << endl;
    
    
    if (w->imbalance() == false)
    {
      if (w->left == w_child && w_child->left == w_grandchild)
      {
        // cout << w->get_Journeycode() << endl;
        // cout << w_child->get_Journeycode() << endl;
        // cout << w_grandchild->get_Journeycode() << endl;
        rotateLeftLeft(w_grandchild, w_child, w);
        w->update_height();
        w_child->update_height();
      }
      else if (w->right == w_child && w_child->right == w_grandchild)
      {
        // cout << w->get_Journeycode() << endl;
        // cout << w_child->get_Journeycode() << endl;
        // cout << w_grandchild->get_Journeycode() << endl;
        rotateRightRight(w_grandchild, w_child, w);
        w->update_height();
        w_child->update_height();
      }
      else if (w->left == w_child && w_child->right == w_grandchild)
      {
        // cout << w->get_Journeycode() << endl;
        // cout << w_child->get_Journeycode() << endl;
        // cout << w_grandchild->get_Journeycode() << endl;
        rotateLeftRight(w_grandchild, w_child, w);
        w->update_height();
        w_child->update_height();
        w_grandchild->update_height();
      }
      else if (w->right == w_child && w_child->left == w_grandchild)
      {
        // cout << w->get_Journeycode() << endl;
        // cout << w_child->get_Journeycode() << endl;
        // cout << w_grandchild->get_Journeycode() << endl;
        rotateRightLeft(w_grandchild, w_child, w);
        w->update_height();
        w_child->update_height();
        w_grandchild->update_height();
      }
      //cout << "hifinal" << endl;
      // We use "return true" below to enable compilation.  Change this as you
      // see fit.
      return true;
    }
    else return true;
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

  int found = -1;
  TreeNode *x = root;
  TreeNode *z = new TreeNode(jrnyCode, 0);
  while (x != nullptr)
  {
    if (AVLLessThan(z, x))
    {
      x = x->left;
    }
    else if (AVLLessThan(x, z))
    {
      x = x->right;
    }
    else
    {
      // cout<<"hi"<<endl;
      found = 0;
      break;
    }
  }
  if (found == 0)
    return x->get_price();
  else
    return found;
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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
