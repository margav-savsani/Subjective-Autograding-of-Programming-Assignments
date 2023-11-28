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

// ====================================================

void AVLTree::heightUpdater(TreeNode *(*currentNode))
{
  TreeNode *temp;
  temp = *currentNode;
  if(temp == nullptr) cout << "temp\n";
  if (temp->parent == nullptr)
  {
    if (temp->left == nullptr && temp->right != nullptr)
    {
      temp->height = temp->right->height + 1;
    }
    else if (temp->left != nullptr && temp->right == nullptr)
    {
      temp->height = temp->left->height + 1;
    }
    else
    {
      temp->height = max(temp->left->height, temp->right->height) + 1;
    }
    return;
  }
  else
  {
    if (temp->left == nullptr && temp->right != nullptr)
    {
      temp->height = temp->right->height + 1;
    }
    else if (temp->left != nullptr && temp->right == nullptr)
    {
      temp->height = temp->left->height + 1;
    }
    else if (temp->left == nullptr && temp->right == nullptr)
    {
      temp->height++;
    }
    else
    {
      temp->height = max(temp->left->height, temp->right->height) + 1;
    }
    TreeNode *otherChild;
    if (temp->parent->parent != nullptr)
    {
      if (temp->parent == temp->parent->parent->left)
      {
        otherChild = temp->parent->parent->right;
      }
      else
      {
        otherChild = temp->parent->parent->left;
      }

      // cout<<"this "<<temp->parent->JourneyCode<<endl;
      if (otherChild == nullptr && temp->parent->height >= 1)
      {
        if (temp == temp->parent->left && temp->parent->parent != nullptr && temp->parent == temp->parent->parent->left)
        {

          temp->parent->height++;
          temp->parent->parent->height--;
          rotateLeftLeft(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->right && temp->parent->parent != nullptr && temp->parent == temp->parent->parent->right)
        {
          temp->parent->parent->height--;
          temp->parent->height++;
          rotateRightRight(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->left && temp->parent->parent != nullptr && temp->parent == temp->parent->parent->right)
        {

          temp->height++;
          temp->parent->parent->height--;
          rotateLeftRight(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->right && temp->parent->parent != nullptr && temp->parent == temp->parent->parent->left)
        {

          temp->height++;
          temp->parent->parent->height--;
          rotateRightLeft(temp, temp->parent, temp->parent->parent);
        }
      }
      else if (otherChild != nullptr && temp->parent->parent != nullptr && abs(temp->parent->height - otherChild->height) >= 1)
      {
        if (temp == temp->parent->left && temp->parent == temp->parent->parent->left)
        {

          temp->parent->height++;
          temp->parent->parent->height--;
          rotateLeftLeft(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->right && temp->parent == temp->parent->parent->right)
        {

          temp->parent->height++;
          temp->parent->parent->height--;
          rotateRightRight(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->left && temp->parent == temp->parent->parent->right)
        {

          temp->height++;
          temp->parent->parent->height--;
          rotateLeftRight(temp, temp->parent, temp->parent->parent);
        }
        else if (temp == temp->parent->right && temp->parent == temp->parent->parent->left)
        {

          temp->height++;
          temp->parent->parent->height--;
          rotateRightLeft(temp, temp->parent, temp->parent->parent);
        }
      }
    }
    temp = (*currentNode)->parent;
    return heightUpdater(&temp);
  }
}

bool AVLTree::actualInsert(int JourneyCode, int price, TreeNode *(*currentNode), TreeNode *(*currentParent))
{
  // Has to create a recursion to check and update height,,,

  TreeNode *temp = new TreeNode(JourneyCode, price);
  // cout<<"Reached checkpoint 2 \n";
  if (*currentNode == nullptr)
  {
    // cout<<"Address:"<<&*currentNode<<endl;
    *currentNode = new TreeNode(JourneyCode, price);
    //, nullptr, nullptr, (*currentParent));
    (*currentNode)->parent = *currentParent;
    if ((*currentNode)->parent->parent != nullptr)
    {
      cout << (*currentNode)->parent->parent->left->JourneyCode << endl;
    }
    heightUpdater(&(*currentNode));
    return true;
  }
  //(*currentNode)->price > price && (*currentNode)->price != 0
  else if (AVLLessThan(temp, (*currentNode)))
  {
    // cout<<"Going left in insert \n";
    return actualInsert(JourneyCode, price, &((*currentNode)->left), &(*currentNode));
  } //
  else if (AVLLessThan((*currentNode), temp))
  {
    // cout<<"Going right in insert \n";
    return actualInsert(JourneyCode, price, &((*currentNode)->right), &(*currentNode));
  }
  else
  {
    return false;
  }
};

bool AVLTree::actualFind(int JourneyCode, TreeNode *currentNode, TreeNode *currentParent)
{
  // cout<<"Reached checkpoint 4 \n";
  TreeNode *temp = new TreeNode(JourneyCode, 0);
  if (currentNode == nullptr)
  {
    return false;
  }
  else if (currentNode->JourneyCode == JourneyCode)
  {
    return true;
    // actualInsert(JourneyCode,price,currentNode->left,currentNode);
  }
  else if (AVLLessThan((currentNode), temp))
  {
    // cout<<"Going right in find \n";
    return actualFind(JourneyCode, currentNode->right, currentNode);
  }
  else if (AVLLessThan(temp, (currentNode)))
  {
    // cout<<"Going left in find \n";
    return actualFind(JourneyCode, currentNode->left, currentNode);
  }
}

// ====================================================

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft
  TreeNode *T3 = parentNode->right;
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if (greatGrandParentNode != nullptr)
  {
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
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    root = parentNode;
    parentNode->parent = nullptr;
  }

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
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if (greatGrandParentNode != nullptr)
  {
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
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else
  {
    root = currNode;
    currNode->parent = nullptr;
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

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

  if (greatGrandParentNode != nullptr)
  {
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
  }
  else
  {
    root = currNode;
    currNode->parent = nullptr;
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

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);

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
  updateAVLParentChild(T2, parent, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft
  TreeNode *T3 = parent->left;
  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if (greatGrandParentNode != nullptr)
  {
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
  }
  else
  {
    root = parent;
    parent->parent = nullptr;
  }

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
  updateAVLParentChild(currNode, parent, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, true);

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
  updateAVLParentChild(T3, grandParent, false);

  return true;
}

// ==========================================================

// Has to implement balance function , using different rotations

// ==========================================================

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
  if (find(jrnyCode) != -1)
  {
    return false;
  }
  // cout<<"Reached checkpoint 1 \n";
  if (root == nullptr)
  {
    // cout<<"here\n";
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  return actualInsert(jrnyCode, price, &root, nullptr);
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
  if (actualFind(jrnyCode, root, nullptr))
  {
    return 1;
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
