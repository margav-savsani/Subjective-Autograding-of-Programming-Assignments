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
  if (greatGrandParentNode != nullptr)
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
  }
  else{
    root = parentNode;
    
  }
  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild


  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;
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
  grandParentNode->height = grandParentNode->height - 2; // from lectures it goes from h+4(unbalanced) to h+2
  parentNode = parentNode->parent;
    while(parentNode!=nullptr){
      parentNode->height--;//heights of all nodes had been updated previouosly so to counter that now we have to reduce the values above the point of imabalance
      parentNode = parentNode->parent;
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

  bool isGPLeftChild;
  // Grandparent is root case should be handled otherwise this block creates a segment fault

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if (greatGrandParentNode != nullptr)
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
  }
  else{
    root = currNode;
    
  }

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.
    // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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

  // height updation
  currNode->height = currNode->height + 1;               // h+2 to h+3
  parentNode->height = parentNode->height - 1;           // h+3 to h+2
  grandParentNode->height = grandParentNode->height - 2; // h+4 (unbalanced) to h+2 -- these values are from lectures after double rotation
  currNode = currNode->parent;
    while(currNode!=nullptr){
      currNode->height--;//heights of all nodes had been updated previouosly so to counter that now we have to reduce the values above the point of imabalance
      currNode = currNode->parent;
    }
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
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
  }
  else{
    root = currNode;
    
  }
  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.


  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);

  // Let's implement these updations below.


  // We use "false" as the third argument of the following call to indicate
  // that T2 should become the right child of GrandParentNode
  updateAVLParentChild(T2, grandParentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of ParentNode
  updateAVLParentChild(T3, parentNode, true);

  currNode->height = currNode->height + 1;               // h+2 to h+3
  parentNode->height = parentNode->height - 1;           // h+3 to h+2
  grandParentNode->height = grandParentNode->height - 2; // h+4 (unbalanced) to h+2 -- these values are from lectures after double rotation

   currNode = currNode->parent;
    while(currNode!=nullptr){//heights of all nodes had been updated previouosly so to counter that now we have to reduce the values above the point of imabalance
      currNode->height--;
      currNode = currNode->parent;
    }

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr)
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
  }
  else{
    root = parentNode;
    
  }
    // Now replicate the single rotation for RightRight as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

        // Let T3 be the left child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->left;
    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    // Make currNode (x in Prof. Garg's lectures) the left child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that currNode should be
    // made the right child of parentNode
    updateAVLParentChild(currNode, parentNode, false);

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that grandParentNode
    // should be made the left child of parentNode
    updateAVLParentChild(grandParent, parentNode, true);



    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the right child of grandParentNode
    updateAVLParentChild(T3, grandParent, false);

    // Height updation
    grandParent->height = grandParent->height - 2; // from lectures it goes from h+4(unbalanced) to h+2
    parentNode = parentNode->parent;//heights of all nodes had been updated previouosly so to counter that now we have to reduce the values above the point of imabalance
    while(parentNode!=nullptr){
      parentNode->height--;
      parentNode = parentNode->parent;
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

    if (find(jrnyCode) != -1)
    { // if journey code already exists return false
      return false;
    }
    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke BSTLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.
    TreeNode *insertnode = new TreeNode(jrnyCode, price);
    TreeNode *curr = root;
    TreeNode *parentNode = nullptr;
    TreeNode *grandparent = nullptr;
    bool isLeftChild;
    while (curr != nullptr)
    {
      grandparent = parentNode;
      parentNode = curr; // so that parent and grandparent is always stored
      if (AVLLessThan(insertnode, curr))
      { // go left if node to be inserted is less than current node curr
        curr = curr->left;
        isLeftChild = true;
      }
      else
      { // go right if node to be inserted is more than current node curr
        curr = curr->right;
        isLeftChild = false;
      }
    }
    TreeNode *temp1;
    TreeNode *temp;
    // root case
    if (parentNode == nullptr)
    {

      root = insertnode;
      updateAVLParentChild(insertnode, nullptr, isLeftChild);
    }
    else
    {
      curr = insertnode;
      updateAVLParentChild(insertnode, parentNode, isLeftChild);

      temp = curr;
      temp = temp->parent;
      while (temp != nullptr)
      { // this is condition for root's parent where this loop must stop
        if (temp->left == nullptr && temp->right != nullptr)
        {
          temp->height = 1 + temp->right->height;
        }
        else if (temp->right == nullptr && temp->left != nullptr)
        {
          temp->height = 1 + temp->left->height;
        }
        else
        { // two children case
          temp->height = 1 + max(temp->left->height, temp->right->height);
        }
        temp = temp->parent; // update height of all ancestors of our inserted node
      }

      // calling rotate functions
      while (grandparent != nullptr)
      {
        // one child cases
        if (grandparent->right == nullptr && grandparent->left->height >= 1)
        {
          if (parentNode->left == curr)
          { // left left config
            rotateLeftLeft(curr, parentNode, grandparent);
            break;
          }
          else
          { // left right config
            rotateLeftRight(curr, parentNode, grandparent);
            break;
          }
        }
        else if (grandparent->left == nullptr && grandparent->right->height >= 1)
        {
          if (parentNode->right == curr)
          { // right right config
            rotateRightRight(curr, parentNode, grandparent);
            break;
          }
          else
          { // right left config
            rotateRightLeft(curr, parentNode, grandparent);
            break;
          }
        }

        // two child cases
        else if (grandparent->left->height - grandparent->right->height >= 2)
        {
          if (parentNode->left == curr)
          { // left left config
            rotateLeftLeft(curr, parentNode, grandparent);
            break;
          }
          else
          { // left right config
            rotateLeftRight(curr, parentNode, grandparent);
            break;
          }
        }
        else if (grandparent->right->height - grandparent->left->height >= 2)
        {
          if (parentNode->right == curr)
          { // right right config
            rotateRightRight(curr, parentNode, grandparent);
            break;
          }
          else
          { // right left config
            rotateRightLeft(curr, parentNode, grandparent);
            break;
          }
        }

        grandparent = grandparent->parent;
        parentNode = parentNode->parent;
        curr = curr->parent;
      }
    
    }
    

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
    // Implement find in AVL tree.
    // This is really no different from finding in a binary search tree.
    // This operation cannot cause any balance factor disturbances.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    TreeNode *findnode = new TreeNode(jrnyCode, 0);
    TreeNode *curr = root;
    while (curr != nullptr)
    {
      if (findnode->getJourneyCode() == curr->getJourneyCode())
        return curr->getprice();

      if (AVLLessThan(findnode, curr))
      {
        curr = curr->left;
      }
      else
      {
        curr = curr->right;
      }
    }

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
