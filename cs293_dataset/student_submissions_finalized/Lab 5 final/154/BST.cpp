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

	// node to be inserted and used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, price);

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
		else { // curr->JourneyCode == JourneyCode
			delete search_node;
			return false;
		}
  	}

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parent.

    // inserting the node
	curr = search_node;
	updateBSTParentChild(curr, parent, BSTLessThan(search_node, parent));
	// curr->updateParentChild(parent, BSTLessThan(search_node, parent));

	// updating the height
	unsigned int new_height; // stores the new height to update
	while(parent!=nullptr){
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

	// node used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, 0);

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
		else { // curr->JourneyCode == JourneyCode
			delete search_node;
			return curr->getPrice();
		}
  	}

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

	// empty tree
	if(root == nullptr){
		return false;
	}

	// node to be used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, 0);

    // finding that node
	struct TreeNode *curr = root;

	while (curr != nullptr) {
		if (BSTLessThan(curr, search_node)) {
			curr = curr->right;
		}
		else if (BSTLessThan(search_node, curr)) {
			curr = curr->left;
		}
		else { // curr->JourneyCode == JourneyCode
			break;
		}
  	}
	delete search_node;

	if(curr == nullptr){
		// element not found 
		return false;
	}

	TreeNode* delNode; // it has 1/0 child
	if(curr->left == nullptr || curr->right == nullptr){
		// 0 or 1 child
		delNode = curr;
	}
	else{
		// 2 childs, so find succesor
		TreeNode* successor = curr->right;
            while(successor->left != nullptr){
                successor = successor->left;
			}
		delNode = successor;
		// update the values
		curr->reset(delNode);
	}

	// child of delNode
	TreeNode* delChild = (delNode->left != nullptr)?(delNode->left):(delNode->right);

	if(delChild != nullptr){
		// 1 child case
		delChild->parent = delNode->parent;
	}
	
	if (delNode->parent == nullptr){
		// delNode is root with 1/0 child
		root = delChild;
		return true;
		// no more updates required anywhere
	}
	else{
		updateBSTParentChild(delChild, delNode->parent, delNode == delNode->parent->left);
	}

	// updating heights
	TreeNode* parent = delNode->parent; // parent of the delNode
	delete delNode; // deleting the delNode

	if(parent->left == nullptr && parent->right == nullptr){
		// handling this case as parent is assumed to have atleast 1 children
		parent->height = 0;
		parent = parent->parent;
	}

	unsigned int new_height; // stores the new height to update
	while(parent!=nullptr){
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
