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

  // Ensure no node is nullptr
  if(currNode == nullptr || parentNode == nullptr || grandParentNode == nullptr){
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode if greatGrandParentNode exists
  
  bool isGPLeftChild = 0;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
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

  // Ensure no node is nullptr
  if(currNode == nullptr || parentNode == nullptr || grandParentNode == nullptr){
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode if greatGrandParentNode exists

  bool isGPLeftChild = 0;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
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

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  // Ensure no node is nullptr
  if(currNode == nullptr || parentNode == nullptr || grandParentNode == nullptr){
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode if greatGrandParentNode exists

  bool isGPLeftChild = 0;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;
  
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

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

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should NOT be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // right child of parentNode and the left child of grandParentNode
  // at all.
  // The only update needed is that the right subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the left subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the left subtree
  // of currNode (i.e. of x) should now become the right subtree of
  // grandParentNode (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "true" as the third argument of the following call to indicate
  // that T2 should become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);


  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Ensure no node is nullptr
  if(currNode == nullptr || parentNode == nullptr || grandParentNode == nullptr){
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode if greatGrandParentNode exists
  
  bool isGPLeftChild = 0;
  if(greatGrandParentNode != nullptr){
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }

  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->left;

  // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parentNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
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
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}



// Balances the given node by rotations
// Returns true if height remains unchanged after balancing (No need to continue up)
// Returns false if height get changed (Need to check above too)
bool AVLTree::balanceNode(TreeNode* imbalanced){
  int initialHeight = imbalanced->height;

  if(imbalanced->getImbalance() > 0){   // Left
    if(imbalanced->left->getImbalance() >= 0){  // LeftLeft
      rotateLeftLeft(imbalanced->left->left, imbalanced->left, imbalanced);
    }
    else{                               // LeftRight
      rotateLeftRight(imbalanced->left->right, imbalanced->left, imbalanced);
    }
  }
  else{                                 // Right
    if(imbalanced->right->getImbalance() > 0){  // RightLeft
      rotateRightLeft(imbalanced->right->left, imbalanced->right, imbalanced);
    }
    else{                               // RightRight
      rotateRightRight(imbalanced->right->right, imbalanced->right, imbalanced);
    }
  }

  imbalanced->parent->updateHeight();
  imbalanced->parent->left->updateHeight();
  imbalanced->parent->right->updateHeight();

  int finalHeight = imbalanced->parent->height;

  if(initialHeight == finalHeight){
    return 1;
  }
  else{
    return 0;
  }
}



// Returns true on successful insertion in AVL tree. Returns false otherwise.
// No two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
  // New node for insertion
  TreeNode *newNode = new TreeNode(jrnyCode, price);

	TreeNode *currNode = root;
	TreeNode *parentOfCurrNode = nullptr;
	while (currNode != nullptr)
	{
		if (AVLLessThan(currNode, newNode))
		{
			parentOfCurrNode = currNode;
			currNode = currNode->right;
		}
		else if (AVLLessThan(newNode, currNode))
		{
			parentOfCurrNode = currNode;
			currNode = currNode->left;
		}
		else
		{ // currNode->JourneyCode == JourneyCode
			return false;
		}
	}
	// JourneyCode is not present in the AVL tree.  We must now
	// insert an appropriate child of parentOfCurrNode.

	if (parentOfCurrNode == nullptr){
		root = newNode;
    return true;
	}
	else{
		if (AVLLessThan(newNode, parentOfCurrNode)){
			updateAVLParentChild(newNode, parentOfCurrNode, 1);
		}
		else{
			updateAVLParentChild(newNode, parentOfCurrNode, 0);
		}
	}
  // Node added
	
  // Travel up the path to check for imbalance
	TreeNode *y = parentOfCurrNode;
	while (y != nullptr)
	{
    // if y is not balanced balance it and break
    if(!y->isBalanced()){
      balanceNode(y); // Balance it
      if(root == y){  // If root is pointing to node at y then root needs to be updated
        root = y->parent; // New root
      }
      break;  // No need to check anymore above
    }
    
		if (y->updateHeight()) // if height gets updated to a new value then go up
			y = y->parent;
		else                   // Else no need to go up anymore
			break;
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

  // New node for comparison
  TreeNode* key = new TreeNode(jrnyCode, -1);

	TreeNode* x = root;

	while(x!= nullptr){
		if(AVLLessThan(key, x)){
			x = x->left;
		}
		else if(AVLLessThan(x, key)){
			x = x->right;
		}
		else{ // Return price if found
			return x->getPrice();
		}
	}

  // Return -1 if not found
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// No two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::remove(int jrnyCode)
{
  // New node for comparison
  TreeNode * key = new TreeNode(jrnyCode, -1);

  if (root == nullptr) {
    return false;
  }

  TreeNode * updateFrom = nullptr;

  // Special case for root
  if (!AVLLessThan(key, root) && !AVLLessThan(root, key)) {
    TreeNode * x = root;
    // Case 1: Both child are null
    if (x -> left == nullptr && x -> right == nullptr) {
      root = nullptr;
      delete x;
    }
    // Case 2: Left child is null
    else if (x -> left == nullptr) {
      root = x -> right;
      updateAVLParentChild(x -> right, nullptr, 0);
      delete x;
    }
    // Case 3: Right child is null
    else if (x -> right == nullptr) {
      root = x -> left;
      updateAVLParentChild(x -> left, nullptr, 0);
      delete x;
    }
    // Case 4: No child is null
    else {
      // Get successor
      TreeNode * z = x -> right;
      while (z -> left != nullptr) {
        z = z -> left;
      }

      updateFrom = z -> parent;

      // Replace at root
      x -> setJourneyCode(z -> getJourneyCode());
      x -> setPrice(z -> getPrice());

      // Delete successor
      if (z -> left == nullptr && z -> right == nullptr) {
        if (z -> parent -> left == z) updateAVLParentChild(nullptr, z -> parent, 1);
        else if (z -> parent -> right == z) updateAVLParentChild(nullptr, z -> parent, 0);
        delete z;
      } else {
        if (z -> parent -> left == z) updateAVLParentChild(z -> right, z -> parent, 1);
        else if (z -> parent -> right == z) updateAVLParentChild(z -> right, z -> parent, 0);

        delete z;
      }

    }

  }

  else{
    TreeNode * x = root;
    // Find the node with matching journeyCode
    while (x != nullptr) {
      if (AVLLessThan(key, x)) {
        x = x -> left;
      } else if (AVLLessThan(x, key)) {
        x = x -> right;
      } else {
        break;
      }
    }
    if (x == nullptr) return false;
    else {
      TreeNode * y = x -> parent;
      // Case 1: Both child are null
      if (x -> left == nullptr && x -> right == nullptr) {
        if (y -> left == x) updateAVLParentChild(nullptr, y, 1);
        else if (y -> right == x) updateAVLParentChild(nullptr, y, 0);
        delete x;
        updateFrom = y;
      }
      // Case 2: Left child is null
      else if (x -> left == nullptr) {
        if (y -> left == x) updateAVLParentChild(x -> right, y, 1);
        else if (y -> right == x) updateAVLParentChild(x -> right, y, 0);
        delete x;
        updateFrom = y;
      }
      // Case 3: Right child is null
      else if (x -> right == nullptr) {
        if (y -> left == x) updateAVLParentChild(x -> left, y, 1);
        else if (y -> right == x) updateAVLParentChild(x -> left, y, 0);
        delete x;
        updateFrom = y;
      }
      // Case 4: No child is null
      else {
        // Get successor
        TreeNode * z = x -> right;
        while (z -> left != nullptr) {
          z = z -> left;
        }

        updateFrom = z -> parent;

        // Replace at current node
        x -> setJourneyCode(z -> getJourneyCode());
        x -> setPrice(z -> getPrice());

        // Delete successor
        if (z -> left == nullptr && z -> right == nullptr) {
          if (z -> parent -> left == z) updateAVLParentChild(nullptr, z -> parent, 1);
          else if (z -> parent -> right == z) updateAVLParentChild(nullptr, z -> parent, 0);
          delete z;
        } else {
          if (z -> parent -> left == z) updateAVLParentChild(z -> right, z -> parent, 1);
          else if (z -> parent -> right == z) updateAVLParentChild(z -> right, z -> parent, 0);

          delete z;
        }

      }

    }
  }

  TreeNode* y = updateFrom;
	while (y != nullptr)
	{
    // If imbalanced then balance it and break if height remains unchanged else continue up
    if(!y->isBalanced()){ // if not balanced
      bool done = balanceNode(y); // balance and see if done
      if(root == y){      // if root is node at y then need to update root
        root = y->parent;
      }
      if(done){
        break;
      }
      else{
        y = y->parent->parent;
        continue;
      }
    }
    
		if (y->updateHeight())
			y = y->parent;
		else
			break;
	}

  return true;
}


