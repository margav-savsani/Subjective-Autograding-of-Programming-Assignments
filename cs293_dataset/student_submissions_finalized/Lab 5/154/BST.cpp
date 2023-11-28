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
	// Implement insertion in BST

	// You MUST use only BSTLessThan to compare two journey codes.  You
	// can create a new node containing the journey code to be inserted
	// and invoke BSTLessThan on the current node in the tree that you
	// are inspecting and the new node to do your comparison.

	// REMEMBER to update the heights of appropriate nodes in the tree
	// after an insertion.

    // base case handling
	if(root == nullptr){
		root = new TreeNode(jrnyCode, price);
		return true;
	}
	TreeNode* search_node = new TreeNode(jrnyCode, 0);

    // finding place to insert
	struct TreeNode *curr = root, *parent = nullptr;

	while (curr != nullptr) {
		if (BSTLessThan(curr, search_node)) {
			parent = curr;
			curr = curr->right;
		}
		else if (BSTLessThan(search_node, curr)) {
			parent = curr;
			curr = curr->left;
		}
		else { // currNode->JourneyCode == JourneyCode
			return false;
		}
  	}

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parent.

    // inserting the node
	curr = new TreeNode(jrnyCode, price);
	if(BSTLessThan(search_node, parent)){
		curr->updateParentChild(parent, true);
	}
	else{
		curr->updateParentChild(parent, false);
	}

	// updating the height
	while(parent!=nullptr){
        unsigned int new_height;
		if(parent->left == nullptr ){
			new_height = parent->right->height + 1;
		}
		else if(parent->right == nullptr ){
			new_height = parent->left->height + 1;
		}
		else{
			new_height = max(parent->left->height, parent->right->height) + 1;
		}
        if(new_height == parent->height){
            // no need to go up if not changed at this node
            return true;
        }
        parent->height = new_height;
		parent = parent->parent;
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

	    //similar to insert
    if(root == nullptr){
        return -1;
    }

	TreeNode* search_node = new TreeNode(jrnyCode, 0);

    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    while (currNode != nullptr) {
		if (BSTLessThan(currNode, search_node)) {
			parentOfCurrNode = currNode;
			currNode = currNode->right;
		}
		else if (BSTLessThan(search_node, currNode)) {
			parentOfCurrNode = currNode;
			currNode = currNode->left;
		}
		else { // currNode->JourneyCode == JourneyCode
			return true;
		}
  	}

	// We use "return -1" below to enable compilation.  Change this as you
	// see fit.
    // if not found above
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
