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

  bool isGPLeftChild;
  TreeNode *T3 = parentNode->right;
  int h = -1;

  if (T3 != nullptr)
  {
    h = T3->height;
  }
  if (grandParentNode == root)
  {
    root = parentNode;
    root->parent=nullptr;
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  else
  {
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
  }
  // As rotation happens, heights of the three nodes changes but the height of the sub trees do not change. So used the height of subtree and changed the height of the three nodes.
  currNode->height = h + 1;
  grandParentNode->height = h + 1;
  parentNode->height = h + 2;
  TreeNode* y = parentNode;
  while(y->parent != nullptr){
    if((!isGPLeftChild && y->parent->left == nullptr) ||  (isGPLeftChild && y->parent->right == nullptr)){
      y->parent->height = 1 + y->height;
    }
    
    else if((!isGPLeftChild && y->parent->left->height < y->height) ||  (isGPLeftChild && y->parent->right->height < y->height)){
      y->parent->height = 1+y->height;
    }
    y=y->parent;
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

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  int h = -1;
  if (T2 != nullptr && T3 != nullptr)
  {
    if (T2->height > T3->height)
      h = T2->height;
    else
      h = T3->height;
  }
  else if (T2 != nullptr)
  {
    h = T2->height;
  }
  else if (T3 != nullptr)
  {
    h = T3->height;
  }
  bool isGPLeftChild;
  if (grandParentNode == root)
  {
    root = currNode;
    root->parent=nullptr;
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  else
  {
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
  }
  currNode->height = h + 2;
  grandParentNode->height = h + 1;
  parentNode->height = h + 1;
  TreeNode* y=currNode;
  while(y->parent != nullptr){
    if((!isGPLeftChild && y->parent->left == nullptr) ||  (isGPLeftChild && y->parent->right == nullptr)){
      y->parent->height = 1 + y->height;
    }
    
    else if((!isGPLeftChild && y->parent->left->height < y->height) ||  (isGPLeftChild && y->parent->right->height < y->height)){
      y->parent->height = 1+y->height;
    }
    y=y->parent;
  }
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  // cout<<"rotation"<<endl;
  TreeNode *greatGrandParentNode = grandParent->parent;
  // cout<<"rotation"<<endl;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  TreeNode *T3 = parent->left;
  int h = -1;

  if (T3 != nullptr)
  {
    h = T3->height;
  }
  // grandParent has become root. May be assignment issue
  if (grandParent == root)
  {
    root = parent;
    root->parent=nullptr;
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    updateAVLParentChild(currNode, parent, false);
  }

  // cout<<greatGrandParentNode->right<<endl;
  else
  {
    if (greatGrandParentNode->left == grandParent)
    {
      isGPLeftChild = true;
      // cout<<"1"<<endl;
    }
    else if (greatGrandParentNode->right == grandParent)
    {
      isGPLeftChild = false;
      // cout<<"2"<<endl;
    }
    else
    {

      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    // cout<<h<<endl;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

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
  }
  currNode->height = h + 1;
  grandParent->height = h + 1;
  parent->height = h + 2;
  TreeNode* y = parent;
  while(y->parent != nullptr){
    if((!isGPLeftChild && y->parent->left == nullptr) ||  (isGPLeftChild && y->parent->right == nullptr)){
      y->parent->height = 1 + y->height;
    }
    
    else if((!isGPLeftChild && y->parent->left->height < y->height) ||  (isGPLeftChild && y->parent->right->height < y->height)){
      y->parent->height = 1+y->height;
    }
    y=y->parent;
  }
  // cout<<"rend"<<endl;
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  int h = -1;
  if (T2 != nullptr && T3 != nullptr)
  {
    if (T2->height > T3->height)
      h = T2->height;
    else
      h = T3->height;
  }
  else if (T2 != nullptr)
  {
    h = T2->height;
  }
  else if (T3 != nullptr)
  {
    h = T3->height;
  }
  bool isGPLeftChild;
  if (grandParent == root)
  {
    root = currNode;
    root->parent=nullptr;
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(T3, parent, true);
    updateAVLParentChild(T2, grandParent, false);
  }
  else
  {
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
    updateAVLParentChild(T3, parent, true);

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T2, grandParent, false);
  }
  currNode->height = h + 2;
  grandParent->height = h + 1;
  parent->height = h + 1;
  TreeNode* y = currNode;
  while(y->parent != nullptr){
    if((!isGPLeftChild && y->parent->left == nullptr) ||  (isGPLeftChild && y->parent->right == nullptr)){
      y->parent->height = 1 + y->height;
    }
    
    else if((!isGPLeftChild && y->parent->left->height < y->height) ||  (isGPLeftChild && y->parent->right->height < y->height)){
      y->parent->height = 1+y->height;
    }
    y=y->parent;
  }
  // cout<<"rend"<<endl;
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
  TreeNode *father = nullptr;
  TreeNode *son = root;
  // IMPORTANT- We have to create a new node(dynamic) each and every time to get a different address. If we donot add new, then the node created gets the same address as of root. To overcome this, always create a new node.
  TreeNode *node = new TreeNode(jrnyCode, price);
  bool isLeftChild;
  while (son != nullptr)
  {
    father = son;

    if (AVLLessThan(node, father))
    {
      // cout<<"lesser"<<endl;
      son = father->left;
      isLeftChild = true;
    }
    else if (AVLLessThan(father, node))
    {
      // cout<<"greater"<<endl;
      son = father->right;
      isLeftChild = false;
      // cout<<"end"<<endl;
    }
    else
    {
      return false;
    }
  }
  updateAVLParentChild(node, father, isLeftChild);
  son = node;
  //cout << son << endl;
  while (father != nullptr)
  {
    if (father->height < 1 + son->height)
    {
      father->height = 1 + son->height;
    }

    son = father;
    father = father->parent;
  }
  son = node;
  father = node->parent;

  // cout<<son<<" "<<father<<endl;

  while (true)
  {
    if (father == nullptr)
      break;
    if (father->left != nullptr && father->right != nullptr)
    {
      if (father->left->height - father->right->height <= 1 && father->left->height - father->right->height >= -1)
      {
        //cout << father->left->height << " " << father->right->height << endl;
        son = father;
        father = father->parent;
      }
      else
      {
        //cout << father->left->height << " " << father->right->height << endl;
        //cout << "break1" << endl;
        break;
      }
    }
    else if (father->left != nullptr)
    {
      if (father->left->height <= 0)
      {
        // cout<<father->left->height <<" "<< father->right->height<<endl;
        son = father;
        father = father->parent;
      }
      else
      {
        //cout << "break2" << endl;
        break;
      }
    }
    else if (father->right != nullptr)
    {
      if (father->right->height <= 0)
      {
        // cout<<father->left->height <<" "<< father->right->height<<endl;
        son = father;
        father = father->parent;
        //cout << "scratch" << endl;
      }
      else
      {
        //cout << "break3" << endl;
        break;
      }
    }
  }

  bool isLeft1, isLeft2;
  if (father != nullptr)
  {
    TreeNode *grandParent = father;

    TreeNode *parent = son;
    TreeNode *current;

    if (grandParent->left == parent)
      isLeft1 = true;
    else
      isLeft1 = false;
    if (parent->left != nullptr && parent->right != nullptr)
    {
      if (parent->left->height > parent->right->height)
      {
        current = parent->left;
        isLeft2 = true;
      }
      else
      {
        current = parent->right;
        isLeft2 = false;
      }
      //cout << "1" << endl;
    }
    else if (parent->left != nullptr)
    {
      current = parent->left;
      isLeft2 = true;
      //cout << "2" << endl;
    }

    else if (parent->right != nullptr)
    {
      current = parent->right;
      isLeft2 = false;
      //cout << "3" << endl;
    }
    if (isLeft1)
    {
      if (isLeft2)
        rotateLeftLeft(current, parent, grandParent);
      else
        rotateLeftRight(current, parent, grandParent);
    }
    else
    {
      if (isLeft2)
        rotateRightLeft(current, parent, grandParent);
      else
      {
        rotateRightRight(current, parent, grandParent);
      }
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
  TreeNode *start;
  TreeNode *node = new TreeNode(jrnyCode, 1);
  start = root;
  while (start != NULL)
  {
    // //cout<<"getNode"<<endl;
    if (AVLLessThan(node, start))
    {
      // //cout<<"if"<<endl;
      // //cout<<start->JourneyCode<<" "<<start->price<<endl;
      start = start->left;
    }
    else if (AVLLessThan(start, node))
    {
      start = start->right;
    }
    else
    {
      return 1;
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
