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
	if (root == nullptr) {
		root = new TreeNode(jrnyCode, price);
		return true;
	}
	// root is not empty
	bool isLeft = true;
	struct TreeNode *newNode = new TreeNode(jrnyCode, price), *currNode = root, *parentOfCurrNode = nullptr;
	// check for currect place
	while (currNode != nullptr) {
		if (BSTLessThan(currNode, newNode)) {
			parentOfCurrNode = currNode;
			currNode = currNode->right;
			isLeft = false;
		}
		else if (BSTLessThan(newNode, currNode)) {
			parentOfCurrNode = currNode;
			currNode = currNode->left;
			isLeft = true;
		}
		else return false;
	}
	// is Journeycode is not found then
	// currNode = new TreeNode(JourneyCode,price);
	updateBSTParentChild(newNode, parentOfCurrNode, isLeft);
	currNode = newNode;
	//update heights
	while (currNode->height + 1 > parentOfCurrNode->height) {
		parentOfCurrNode->height++;
		currNode = parentOfCurrNode;
		parentOfCurrNode = currNode->parent;
		if (parentOfCurrNode == nullptr) return true;
	}
	return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
	// Implement find in AVL tree.
	// This is really no different from finding in a binary search tree.
	// This operation cannot cause any balance factor disturbances.
	TreeNode *current = root;
	TreeNode temp(jrnyCode, 0);
	while (current != nullptr) {
		if (BSTLessThan(current, &temp))current = current->right;
		if (BSTLessThan(&temp, current))current = current->left;
		else return current->getPrice();
	}
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
	TreeNode DNode(jrnyCode, 0);
	TreeNode *currNode = root;
	TreeNode * balanceHeight;
	while (true) {
		if (currNode == nullptr) return false;
		if (BSTLessThan(currNode, &DNode)) currNode = currNode->right;
		else if (BSTLessThan(&DNode, currNode)) currNode = currNode->left;
		else break;
	}
	if (currNode->left == nullptr) {
		if (currNode->right == nullptr) {
			if (currNode->parent == nullptr) root = nullptr;
			else updateBSTParentChild(nullptr, currNode->parent, (currNode->parent->left == currNode));
			balanceHeight = currNode->parent;
			delete currNode;

		}
		else {
			if (currNode->parent == nullptr) {
				root = currNode->right;
			}
			else updateBSTParentChild(currNode->right, currNode->parent, (currNode->parent->left == currNode));
			balanceHeight = currNode->parent;
			delete currNode;
		}
	}
	else {
		TreeNode * pre = currNode->left;
		while (pre->right != nullptr) pre = pre->right;
		updateBSTParentChild(pre->left, pre->parent, (pre->parent->left == pre));
		currNode->Exchange(pre);
		balanceHeight = pre->parent;
		delete pre;
	}

	while (balanceHeight != nullptr) {
		int previousHeight = balanceHeight->height;
		UpdateHeight(balanceHeight);
		if (previousHeight == balanceHeight->height) break;
		balanceHeight = balanceHeight->parent;
	}
	return true;
}

// REMEMBER to update the height of appropriate nodes in the tree
// after a successful deletion.

// We use "return true" below to enable compilation.  Change this as you
// see fit.



