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

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // CHECK IF GGP IS NULL ACCORDINGLY SET THE ROOT IN THAT CASE

  bool isGPLeftChild;
  if (greatGrandParentNode == nullptr)
  {
    root = parentNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode)
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
  grandParentNode->height--;
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

  bool isGPLeftChild;
  if (greatGrandParentNode == nullptr)
  {
    root = currNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode)
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
  currNode->height++;
  parentNode->height--;
  grandParentNode->height--;
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // CHECK IF GGP IS NULL ACCORDINGLY SET THE ROOT IN THAT CASE
  bool isGPLeftChild;
  if (greatGrandParentNode == nullptr)
  {
    root = currNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode)
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
  // taking out t2 and t3 to store since x will be the new connection between top tree and lower part so when we assign y and z as
  // child of x the info of t2 and t3 will otherwise be lost.
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  // making x as link instead of z from above tree
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  // making y as right child of x
  updateAVLParentChild(parentNode, currNode, false);
  // making z as left child of y
  updateAVLParentChild(grandParentNode, currNode, true);
  // updating left of x earlier t2 now to the right of z.
  updateAVLParentChild(T2, grandParentNode, false);
  // updating right of x earlier t3 now to the left of y.
  updateAVLParentChild(T3, parentNode, true);
  // since x height is increased by one during the rearrangement of trees so updating it
  currNode->height++;
  // height of y and z decrease by one when we rearrange so updating there value accordingly after we have done the rotation.
  parentNode->height--;
  grandParentNode->height--;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // CHECK IF GGP IS NULL ACCORDINGLY SET THE ROOT IN THAT CASE
  if (greatGrandParentNode == nullptr)
  {
    root = parentNode;
    isGPLeftChild = false;
  }
  else if (greatGrandParentNode->left == grandParentNode)
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
  // Taking out t3 pointer out to reassign after restructring x,y,z.
  TreeNode *T3 = parentNode->left;
  // setting up the new connection with above tree as parent node (y) which was z since y is at highest level
  //  after rotation
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  // making x right child of y though its not required since its already the right but just update it.
  updateAVLParentChild(currNode, parentNode, false);
  // updating z as left child of y making y as top level of this part of tree
  updateAVLParentChild(grandParentNode, parentNode, true);
  // finally setting t3 as right child of z which was left child of y earlier.
  updateAVLParentChild(T3, grandParentNode, false);
  // z height decrease due to the rearrangement so updating it accordingly.
  grandParentNode->height--;
  return true;

  // Returns true on successful insertion in AVL tree. Returns false otherwise.
  // You may assume that no two elements being inserted have the same journey
  // code, and journey code is the key for insertion and finding in the AVL
  // tree.
}

bool AVLTree::insert(int jrnyCode, int price)
{
  // Checking for the case when root is null no imbalance possible 
  // updating roots parent to nullptr,
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    root->height=1;
    root->parent = nullptr;
    return true;
  }
  // making the node a to insert and assisgning x and y as pointer to travel down the tree 
  //to find the position of insertion
  // when x will point to nullptr y will be the parent of newly assigned node
  TreeNode *a = new TreeNode(jrnyCode, price);
  TreeNode *x = root;
  TreeNode *y = nullptr;

  // travelling down the tree as per the rule of BST while comparing with the AVLLESSTHAN FUNCTION.
  // IF THERE is already a node with same jrncycode it returns false.
  // This will also be increasing the comparison cost.
  while (x != nullptr)
  {
    if (AVLLessThan(x, a))
    {
      y = x;
      x = x->right;
    }
    else if (AVLLessThan(a, x))
    {
      y = x;
      x = x->left;
    }

    else
    {
      return false;
    }
  }
  // the loop will be exited after finding position to insert now making a as 
  //left or right child of y again just by comparing it with the value of y. 
  if (AVLLessThan(a, y))
  {
    updateAVLParentChild(a, y, true);
  }
  else
  {
    updateAVLParentChild(a, y, false);
  }
  // setting up height of newly inserted node as 1.
  a->height = 1;
  // updating the height of parent of newly inserted a
  // according to the various possibilities of nullptr etc.
  if (y->left == nullptr)
  {
    y->height = 1 + y->right->height;
  }
  else if (y->right == nullptr)
  {
    y->height = 1 + y->left->height;
  }
  else
  {
    y->height = 1 + max(y->left->height, y->right->height);
  }
  // now we move up the tree updating the height accordingly till we reach
  // a point of imbalance otherwise this will go straight up to the root 
  // that is indicated by z becoming null without being point of imbalnce
  // in that case no imbalance is there so we can simply return. // in case of 
  // imbalance reached we just check the location of y wrt z and x wrt y 
  // to know the type of pointer movement required.// we call the required movement 
  // function of pointers with also updating height of x,y,z inside that function. 
  x = a;
  y = a->parent;
  TreeNode *z = y->parent;
  while (z != nullptr)
  {
    int lh, rh;
    // lh and rh denote left child and right child height of z which are 0 
    // in the case pointers being null
    if (z->left != nullptr)
    {
      lh = z->left->height;
    }
    else
      lh = 0;
    if (z->right != nullptr)
    {
      rh = z->right->height;
    }
    else
      rh = 0;
    if (abs(lh - rh) <= 1)
    {
      x = y;
      y = z;
      z = z->parent;
      if (y->left == nullptr)
      {
        y->height = 1 + y->right->height;
      }
      else if (y->right == nullptr)
      {
        y->height = 1 + y->left->height;
      }
      else
      {
        y->height = 1 + max(y->left->height, y->right->height);
      }
    }
    else
    {
      bool isparentLeft = (AVLLessThan(y, z));
      bool ischildLeft = (AVLLessThan(x, y));
      if (isparentLeft)
      {
        if (ischildLeft)
          rotateLeftLeft(x, y, z);
        else
          rotateLeftRight(x, y, z);
      }
      else
      {
        if (ischildLeft)
          rotateRightLeft(x, y, z);
        else
          rotateRightRight(x, y, z);
      }
      return true;
    }
  }
  // if we reach the point where z is a null so the above loop gets over 
  //so in that height of y isn't updated so updating it accordingly.
  if (z == nullptr)
  {
    if (y->left == nullptr)
    {
      y->height = 1 + y->right->height;
    }
    else if (y->right == nullptr)
    {
      y->height = 1 + y->left->height;
    }
    else
    {
      y->height = 1 + max(y->left->height, y->right->height);
    }
  }
  return true;
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
{ // FIND is simply a BST tree walk 
  // just checking the suitable jrncycode acc. to
  // rule of bst by AVLLessThan function.
  // use !(a>x) && !(a<x) => a=x
  TreeNode *a = new TreeNode(jrnyCode, 0);
  TreeNode *x = root;
  while (x != nullptr)
  {
    if (AVLLessThan(x, a))
    {
      x = x->right;
    }
    else if (AVLLessThan(a, x))
    {
      x = x->left;
    }
    else
    {
      return x->getprice();
    }
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
