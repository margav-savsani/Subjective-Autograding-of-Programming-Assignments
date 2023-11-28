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
	if (find(jrnyCode) >= 0)		// Return false if the new Node to be inserted is already present
		return false;

	TreeNode *newNode = new TreeNode(jrnyCode, price);		// The new Node to be inserted
	TreeNode *y = nullptr; 									// Using 2 pointers x and y to keep track
	TreeNode *x = root;	   									// of current Node and its parent
	while (x != nullptr)
	{
		y = x;
		if (BSTLessThan(newNode, x))
			x = x->left;
		else
			x = x->right;
	}

	bool isLeft = false;
	if (y == nullptr)
	{
		root = newNode;					// If y is Null, make newNode as Root
		return true;
	}
	else if (BSTLessThan(newNode, y))
	{
		isLeft = true;
	}

	updateBSTParentChild(newNode, y, isLeft);			// make new node as appropriate Child of y

	updateHeights(newNode->parent);						// Update the Heights of the ancestors

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
	TreeNode *x = new TreeNode(0, 100);
	TreeNode *y = new TreeNode(jrnyCode, 200);
	x = root;					// Start searching for the Node from Root
	while (x != nullptr && jrnyCode != x->getJourneyCode())
	{
		if (BSTLessThan(y, x))
			x = x->left;
		else
			x = x->right;
	}
	if (x != nullptr)
		return x->getPrice();	// Reutrning the price of the Node, if it is found
	else
		return -1;				// else returning -1

	// We use "return -1" below to enable compilation.  Change this as you
	// see fit.
}

// Update the Heights of the appropriate Nodes
void BST::updateHeights(TreeNode *father)
{
	if (father == nullptr)
		return;
	if (father->right == nullptr && father->left != nullptr)
	{
		father->height = 1 + father->left->height;
	}
	else if (father->left == nullptr && father->right == nullptr)
	{
		father->height = 0;
	}
	else if (father->left == nullptr && father->right != nullptr)
	{
		father->height = 1 + father->right->height;
	}
	else
	{
		father->height = 1 + max(father->left->height, father->right->height);
	}
	updateHeights(father->parent);		// Using Recursion
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
	if (find(jrnyCode) == -1)		// return false if Node to be deleted is not Present
		return false;

	TreeNode *y = new TreeNode(jrnyCode, 100);
	TreeNode *x = new TreeNode(jrnyCode, 200);
	TreeNode *deleteNode = searchNode(jrnyCode);

	bool successorCase = false;		// check if the Successor is being deleted

	if (deleteNode->left == nullptr || deleteNode->right == nullptr)
	{
		y = deleteNode;
	}
	else
	{
		y = successor(deleteNode);
		successorCase = true;
	}
	if (y->left != nullptr)
		x = y->left;
	else
		x = y->right;
	if (x != nullptr)
		x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != deleteNode)
	{
		*(deleteNode->changeJourneyCode()) = y->getJourneyCode();
		*(deleteNode->changePrice()) = y->getPrice();
	}

	if (successorCase)
		updateHeights(y->parent);
	else
		updateHeights(deleteNode->parent);

	return true;
}

// Find successor of a given Node
TreeNode *BST::successor(TreeNode *v)
{
	if (v->right != nullptr)
	{
		return minNode(v->right);
	}
	TreeNode *y = v->parent;
	while (y != nullptr && v == y->right)
	{
		v = y;
		y = y->parent;
	}
	return y;
}

// Returns the Node with minimum price
TreeNode *BST::minNode(TreeNode *v)
{
	while (v->left != nullptr)
	{
		v = v->left;
	}
	return v;
}

// Searches for a Node and returns it
TreeNode *BST::searchNode(int jrnyCode)
{
	TreeNode *x = new TreeNode(0, 100);
	TreeNode *y = new TreeNode(jrnyCode, 200);
	x = root;
	while (x != nullptr && jrnyCode != x->getJourneyCode())
	{
		if (BSTLessThan(y, x))
			x = x->left;
		else
			x = x->right;
	}
	if (x != nullptr)
		return x;
	else
		return nullptr;
}
