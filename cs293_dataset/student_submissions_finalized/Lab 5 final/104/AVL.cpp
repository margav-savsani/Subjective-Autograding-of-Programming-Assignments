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

	if (greatGrandParentNode == nullptr)
	{
		TreeNode *T3 = parentNode->right;

		root = parentNode;
		parentNode->parent = nullptr;

		updateAVLParentChild(currNode, parentNode, true);

		updateAVLParentChild(grandParentNode, parentNode, false);

		updateAVLParentChild(T3, grandParentNode, true);

		return true;
	}

	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode

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

	TreeNode *greatGrandParentNode = grandParentNode->parent;

	if (greatGrandParentNode == nullptr)
	{
		// Let T2 be the left child of currNode (i.e. of x)
		TreeNode *T2 = currNode->left;

		// Let T3 be the right child of currNode (i.e. of x)
		TreeNode *T3 = currNode->right;

		root = currNode;
		currNode->parent = nullptr;

		updateAVLParentChild(parentNode, currNode, true);

		updateAVLParentChild(grandParentNode, currNode, false);

		updateAVLParentChild(T2, parentNode, false);

		updateAVLParentChild(T3, grandParentNode, true);

		return true;
	}

	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode

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
	// exact opposite of rotateLeftRight

	TreeNode *greatGrandParentNode = grandParentNode->parent;

	if (greatGrandParentNode == nullptr)
	{
		// Let T2 be the right child of currNode (i.e. of x)
		TreeNode *T2 = currNode->right;

		// Let T3 be the left child of currNode (i.e. of x)
		TreeNode *T3 = currNode->left;

		root = currNode;
		currNode->parent = nullptr;

		updateAVLParentChild(parentNode, currNode, false);

		updateAVLParentChild(grandParentNode, currNode, true);

		updateAVLParentChild(T2, parentNode, true);

		updateAVLParentChild(T3, grandParentNode, false);

		return true;
	}

	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode

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

	TreeNode *T2 = currNode->right;

	TreeNode *T3 = currNode->left;

	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

	updateAVLParentChild(parentNode, currNode, false);

	updateAVLParentChild(grandParentNode, currNode, true);

	updateAVLParentChild(T2, parentNode, true);

	updateAVLParentChild(T3, grandParentNode, false);

	return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{	
	// exact opposite of rotateLeftLeft

	TreeNode *greatGrandParentNode = grandParentNode->parent;

	if (greatGrandParentNode == nullptr)
	{
		TreeNode *T3 = parentNode->left;

		root = parentNode;
		parentNode->parent = nullptr;

		updateAVLParentChild(currNode, parentNode, false);

		updateAVLParentChild(grandParentNode, parentNode, true);

		updateAVLParentChild(T3, grandParentNode, false);

		return true;
	}

	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode

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

	TreeNode *T3 = parentNode->left;

	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

	updateAVLParentChild(currNode, parentNode, false);

	updateAVLParentChild(grandParentNode, parentNode, true);

	updateAVLParentChild(T3, grandParentNode, false);

	return true;
}


// inserts the node as if in BST and returns pointer to inserted node

TreeNode *AVLTree::helperInsert(int jrnyCode, int price)
{

	TreeNode *nd = new TreeNode(jrnyCode, price);

	// if an empty tree then create a root node
	if (root == nullptr)
	{
		root = nd;
		return nd;
	}

	TreeNode *ptr = root;

	// search for required node
	while (true)
	{

		// return false if already present
		if ((!AVLLessThan(nd, ptr)) && (!AVLLessThan(ptr, nd)))
		{
			return nullptr;
		}

		// go left if required key is less than or equal
		if (AVLLessThan(nd, ptr) && ptr->left != nullptr)
		{
			ptr = ptr->left;
		}
		// go right if required key is strictly more
		else if (AVLLessThan(ptr, nd) && ptr->right != nullptr)
		{
			ptr = ptr->right;
		}
		// insert to left
		else if (AVLLessThan(nd, ptr) && ptr->left == nullptr)
		{
			ptr->left = nd;
			ptr->left->parent = ptr;
			return nd;
		}
		// insert to right
		else if (AVLLessThan(ptr, nd) && ptr->right == nullptr)
		{
			ptr->right = nd;
			ptr->right->parent = ptr;
			return nd;
		}
	}
}


// return true if given node is imbalanced, else false
bool checkImbalance(TreeNode *nd)
{
	int l, r;
	if (nd->left == nullptr)
	{
		l = -1;
	}
	else
	{
		l = nd->left->getHeight();
	}

	if (nd->right == nullptr)
	{
		r = -1;
	}
	else
	{
		r = nd->right->getHeight();
	}

	return !(l == r || l - r == 1 || r - l == 1);
}

// sets correct height of the given node
void editHeight(TreeNode *nd)
{
	int l, r;

	if (nd->left == nullptr)
	{
		l = -1;
	}
	else
	{
		l = nd->left->getHeight();
	}

	if (nd->right == nullptr)
	{
		r = -1;
	}
	else
	{
		r = nd->right->getHeight();
	}

	nd->setHeight(max(l, r) + 1);
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{	

	// inserting node naively
	TreeNode *ptr = helperInsert(jrnyCode, price);

	// checking if insertion at root
	if (ptr->parent == nullptr)
	{
		return true;
	}

	TreeNode *currNode = ptr;
	TreeNode *parentNode = currNode->parent;
	TreeNode *grandParentNode = parentNode->parent;

	while (grandParentNode != nullptr)
	{
		// updating height of ancestors
		editHeight(parentNode);

		if (checkImbalance(grandParentNode))
		{	
			// this node will have height less by 1 after rotation, so setting it priorly
			grandParentNode->setHeight(grandParentNode->getHeight() - 1);
			break;
		}
		else
		{
			currNode = currNode->parent;
			parentNode = parentNode->parent;
			grandParentNode = grandParentNode->parent;
		}
	}

	if (grandParentNode == nullptr)
	{
		return true;
	}

	// calling rotate functions appropriately

	if (parentNode == grandParentNode->left && currNode == parentNode->left)
	{
		rotateLeftLeft(currNode, parentNode, grandParentNode);
		return true;
	}

	if (parentNode == grandParentNode->right && currNode == parentNode->right)
	{
		rotateRightRight(currNode, parentNode, grandParentNode);
		return true;
	}

	if (parentNode == grandParentNode->left && currNode == parentNode->right)
	{
		rotateLeftRight(currNode, parentNode, grandParentNode);
		return true;
	}

	if (parentNode == grandParentNode->right && currNode == parentNode->left)
	{
		rotateRightLeft(currNode, parentNode, grandParentNode);
		return true;
	}
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
	TreeNode *nd = new TreeNode(jrnyCode, 0);

	TreeNode *ptr = root;

	// same code as in insert
	while (true)
	{
		if (ptr == nullptr)
		{
			delete nd;
			return -1;
		}
		else if ((!AVLLessThan(nd, ptr)) && (!AVLLessThan(ptr, nd)))
		{
			delete nd;
			return ptr->getJourneyCode();
		}
		else if (AVLLessThan(nd, ptr))
		{
			ptr = ptr->left;
		}
		else
		{
			ptr = ptr->right;
		}
	}
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
	return true;
}
