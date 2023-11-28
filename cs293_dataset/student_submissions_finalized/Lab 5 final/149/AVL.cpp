#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

/// @brief rotate the nodes when the node succeeding the node with imbalance are in the left direction.
/// @param currNode grandchild of the node with imbalance
/// @param parentNode child of the node with imbalance.
/// @param grandParentNode node with imbalance
/// @return true if all the actions are performed correctly
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // node above the grandparent node
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;

  // if greatgrandparent node doesn't exists, make the parent node root. Attach the right node of the parent to the left of grandparent. Attach granparent node to parent's right.
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(parentNode, nullptr, 1);
    root = parentNode;
    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(T3, grandParentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, 0);
    grandParentNode->updateHeight();
    return true;
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

  // Do the same except making the parentnode root, attach it to left of the greatgrandparent node.
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(T3, grandParentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);

  return true;
}

/// @brief rotate the nodes of the tree when first node succeeding the node with imbalance is in the left direction and the next node is in the right direction.
/// @param currNode node to left and then right to the grandparent node.
/// @param parentNode node to the left of grandparent. child of the grandparent.
/// @param grandParentNode node with imbalance.
/// @return true if all the functions are carried out correctly without any major errors.
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // node above the grandparent node
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;

  // if greatgrandparent node doesn't exists, make the current node root. Attach the left node of the current node to the right of parent node and attch thr right node of the current node to the left of granparentnode. then attach parent node to left of current node and grandparentnode to the right of currentnode.
  if (greatGrandParentNode == nullptr)
  {
    root = currNode;
    updateAVLParentChild(currNode, nullptr, 1);
    TreeNode *T1 = currNode->left;
    TreeNode *T2 = currNode->right;
    updateAVLParentChild(T1, parentNode, false);
    updateAVLParentChild(T2, grandParentNode, true);
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    return true;
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

  // perform similar function except instead of making the current node rrot, make it the left child of the greatgrandparent node.
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  return true;
}

/// @brief rottate the nodes of the tree when the node succeding the node with imbalne are in right and left direction respectively.
/// @param currNode grandchild of the node with imbalnce
/// @param parentNode child of the node with imbalance
/// @param grandParentNode node with imbalance
/// @return true if all the functions are carried out error free.
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // parent of the node with imbalance
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;

  // similar to rotateleftright except left and rights are interchanged
  if (greatGrandParentNode == nullptr)
  {
    root = currNode;
    updateAVLParentChild(currNode, nullptr, 0);
    TreeNode *T1 = currNode->right;
    TreeNode *T2 = currNode->left;
    updateAVLParentChild(T1, parentNode, true);
    updateAVLParentChild(T2, grandParentNode, false);
    updateAVLParentChild(parentNode, currNode, false);
    updateAVLParentChild(grandParentNode, currNode, true);
    return true;
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

  // again similar!!
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  return true;
}

/// @brief node succeding the node with imbalance are in the right to the node with imbalance
/// @param currNode grandchild of the node with imbalance
/// @param parentNode child of the node with imbalance
/// @param grandParentNode node with imbalance
/// @return true if all the functions are carried out pretty well.
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // parent of the node with imbalance
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;

  // simailar to thet of rortateleftleft
  if (greatGrandParentNode == nullptr)
  {
    updateAVLParentChild(parentNode, nullptr, 0);
    root = parentNode;
    TreeNode *T3 = parentNode->left;
    updateAVLParentChild(T3, grandParentNode, false);
    updateAVLParentChild(grandParentNode, parentNode, 1);
    grandParentNode->updateHeight();
    return true;
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

  // again silmilar!!
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(T3, grandParentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);

  return true;
}

/// @brief check if the the tree is balance after a new node is added to the tree. If not balanced, call related function to make the tree balanced again
/// @param t parent of the node just inserted
/// @param y the node just inserted
void AVLTree::balance(TreeNode *t, TreeNode *y)
{
  if (t->parent == nullptr)
    return;
  else
  {
    int bal = getBal(t->parent);

    if (abs(bal) > 1)
    {
      if (bal > 1 && AVLLessThan(y, t))
      {
        rotateLeftLeft(y, t, t->parent);
      }
      else if (bal > 1 && AVLLessThan(t, y))
      {
        rotateLeftRight(y, t, t->parent);
      }
      else if (bal < -1 && AVLLessThan(y, t))
      {
        rotateRightLeft(y, t, t->parent);
      }
      else if (bal < -1 && AVLLessThan(t, y))
      {
        rotateRightRight(y, t, t->parent);
      }
    }
    else
    {
      balance(t->parent, t);
    }
  }
}

/// @brief recursive function to add node in the avl tree. It is pretty much ssimilar to the bst counterpart
/// @param t supposedly ht parent of the node to be inserted
/// @param jrnycode journeycode of the node to be inserted. used for comparision purpose in the avl tree.
/// @param price price of the journey. just for symbolic presence. no roll in the insertion of the node
/// @return true if node is inserted successfully
bool AVLTree::addNode(TreeNode *t, int jrnycode, int price)
{
  // construct a node for the given journeycode and price. to be used for doing future comparisions.
  TreeNode *y;
  y = new TreeNode(jrnycode, price);

  if (AVLLessThan(y, t))
  {
    if (t->left == nullptr)
    {
      updateAVLParentChild(y, t, 1);
      balance(t, y);
      return true;
    }
    else
    {
      return addNode(t->left, jrnycode, price);
    }
  }
  else if (AVLLessThan(t, y))
  {
    if (t->right == nullptr)
    {
      updateAVLParentChild(y, t, 0);
      balance(t, y);
      return true;
    }
    else
    {
      return addNode(t->right, jrnycode, price);
    }
  }
}

/// @brief main insert function called to insert nodes. If root is empty, it creates the root. then finds if the node with given journeycode alredy exists or not. if it does not, calls addnode recursive function to add the node.
/// @param jrnyCode journeycode of the function to be inserted
/// @param price price of the journey
/// @return true if the node is inserted successfully. if a similar node is found, returns false.
bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *y;
  y = new TreeNode(jrnyCode, price);
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
  }
  else if (find(jrnyCode) != 0)
    return false;
  else
  {
    addNode(root, jrnyCode, price);
  }
  return true;
}

/// @brief recursive function to find the node
/// @param t the node where th efunction has reached till now finding the node
/// @param code journeycode of the node to be found
/// @return return the node if found. else return nullptr
TreeNode *AVLTree::findNode(TreeNode *t, int code)
{
  TreeNode *y = new TreeNode();
  y->JourneyCode = code;
  if (t == nullptr)
  {
    return t;
  }
  else if (t->JourneyCode == code)
  {
    return t;
  }
  else if (AVLLessThan(y, t))
  {
    return findNode(t->left, code);
  }
  else
  {
    return findNode(t->right, code);
  }
}

/// @brief find function. acalls a recursive function to find the node
/// @param jrnyCode journeycode of the journey to be found
/// @return true if found else false
int AVLTree::find(int jrnyCode)
{
  TreeNode *t = findNode(root, jrnyCode);
  if (t == nullptr)
    return false;
  else
    return t->price;
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
