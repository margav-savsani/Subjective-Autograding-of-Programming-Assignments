#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
	if(root == nullptr){
		root = new TreeNode(JourneyCode,price);
		return true;
	}
	// root is not empty
	struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
	// check for currect place
	while (currNode != nullptr) {
    if(currNode->JourneyCode == JourneyCode) return false;
		if (BSTLessThan(currNode->JourneyCode,JourneyCode)) {
			parentOfCurrNode = currNode;
			currNode = currNode->right;
		}
		else{
			parentOfCurrNode = currNode;
			currNode = currNode->left;
		}
	}
	// is Journeycode is not found then
	currNode = new TreeNode(JourneyCode,price);
	if(parentOfCurrNode->JourneyCode < JourneyCode) updateBSTParentChild(currNode,parentOfCurrNode,false);
	else  updateBSTParentChild(currNode,parentOfCurrNode,true);
  //update heights
  while (currNode->height+1 > parentNode->height){
    parentNode->height++;
    currNode=parentNode;
    parentNode=currNode->parent;
  }
	return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  BST temp(jrnyCode,0);
  if (root == NULL) return 1;
	if(root->JourneyCode == JourneyCode) return -1;
	if(BSTLessThan(root,*temp))return BST(root->right).find(JourneyCode, price);
	else return BST(root->left).find(JourneyCode, price);
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


