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
	TreeNode *T3 = parentNode->right;

	// First find if grandParentNode is the left or right child of
	// greatGrandParentNode

	bool isGPLeftChild = true;
	if (greatGrandParentNode == nullptr)	
	{
		isGPLeftChild = true;
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
	grandParentNode->height = grandParentNode->height - 1;
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
	bool isGPLeftChild;
	if (greatGrandParentNode == nullptr)
	{
		isGPLeftChild = true;
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

	// Update heights of the nodes that were rearranged
	currNode->height = currNode->height + 1;
	parentNode->height = parentNode->height - 1;
	grandParentNode->height = grandParentNode->height - 1;

	return true;
}

// Rotate Right Left
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	TreeNode *greatGrandParentNode = grandParentNode->parent;		// Find the parent of Imablanced Node
	bool isGPLeftChild;												// check if it is left child or right chlid
	if (greatGrandParentNode == nullptr)
	{
		isGPLeftChild = true;
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
	}

	// Let T2 be the left child of currNode (i.e. of x)
	TreeNode *T2 = currNode->left;

	// Let T3 be the right child of currNode (i.e. of x)
	TreeNode *T3 = currNode->right;

	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);	// make currNode as appropriate child of greatgrandParent

	updateAVLParentChild(parentNode, currNode, false);						// make parentNode as right child of currNode

	updateAVLParentChild(grandParentNode, currNode, true); 					// make grandParentNode as left child of currNode

	updateAVLParentChild(T2, grandParentNode, false);						// T2 becomes right child of grandParentNode

	updateAVLParentChild(T3, parentNode, true);								// T3 becomes left child of parentNode

	// Update minute changes in heights after rotation 
	currNode->height = currNode->height + 1;
	parentNode->height = parentNode->height - 1;
	grandParentNode->height =  grandParentNode->height - 1;

	return true;
}

// Rotate Right Right
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	TreeNode *greatGrandParentNode = grandParentNode->parent;				// find parent of grandParentNode
	TreeNode *T3 = parentNode->left;										// T3 be the left Tree of parentNode

	bool isGPLeftChild;								// Check if grandParentNode is left or right child of greatGrandParent
	if (greatGrandParentNode == nullptr)
	{
		isGPLeftChild = true;
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
	}

	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);	// Make parentNode as appropriate child of greatGrandParent	

	updateAVLParentChild(currNode, parentNode, false);						// Make currNode as right child of parentNode

	updateAVLParentChild(grandParentNode, parentNode, true);				// Make grandParentNode as left child of parentNode

	updateAVLParentChild(T3, grandParentNode, false);						// Make T3 as right subTree of grandParent Node

	grandParentNode->height = grandParentNode->height - 1;					// Decrease Height of grandparent Node by 1

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

	if (find(jrnyCode) >= 0) return false;		// If JourneyCode is already present, return false

	TreeNode *newNode = new TreeNode(jrnyCode, price);		// New Node to be inserted
	TreeNode *y = nullptr; 									// Using 2 pointers x and y to keep track
	TreeNode *x = root;	   									// of current Node and its parent
	while (x != nullptr)
	{
		y = x;
		if (AVLLessThan(newNode, x))
			x = x->left;
		else
			x = x->right;
	}
	
	bool isLeft = false;
	if(y == nullptr)
	{ 
		root = newNode;				// y being NULL implies newNode is root
		return true;				
	}
    else if(AVLLessThan(newNode,y))
	{
    	isLeft = true;
    }

    updateAVLParentChild(newNode,y,isLeft);		// Make New Node as appropriate child of y

	updateAVLHeight(newNode, y, y->parent);		// Update Heights of all the ancestors and Balance the tree

	// You MUST use only AVLLessThan to compare two journey codes.  You
	// can create a new node containing the journey code to be inserted
	// and invoke AVLLessThan on the current node in the tree that you
	// are inspecting and the new node to do your comparison.

	// REMEMBER to update the heights of appropriate nodes in the tree
	// after an insertion.

	// We use "return true" below to enable compilation.  Change this as you
	// see fit.
	return true;
}

// To Update Heights of all the ancestors of a Node
void AVLTree::updateAVLHeight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	if (parentNode->right == nullptr && parentNode->left != nullptr)
	{
		parentNode->height = 1 + parentNode->left->height;
	}
	else if (parentNode->left == nullptr && parentNode->right != nullptr)
	{
		parentNode->height = 1 + parentNode->right->height;
	}
	else
	{
		parentNode->height = 1 + max(parentNode->left->height, parentNode->right->height);
	}
	if (grandParentNode == nullptr)								// Base case, if grandParent is null 
		return;
	else if (abs(grandParentNode->getBalance()) == 2)			// else if Imbalance found, Rotate the tree accordingly
	{
		if (grandParentNode->getBalance() == 2 && currNode == parentNode->left)
			rotateLeftLeft(currNode, parentNode, grandParentNode);			// Rotate Left Left
		else if (grandParentNode->getBalance() == 2 && currNode == parentNode->right)
			rotateLeftRight(currNode, parentNode, grandParentNode);			// Rotate Left Right
		else if (grandParentNode->getBalance() == -2 && currNode == parentNode->left)
			rotateRightLeft(currNode, parentNode, grandParentNode);			// Rotate Right Left
		else if (grandParentNode->getBalance() == -2 && currNode == parentNode->right)
			rotateRightRight(currNode, parentNode, grandParentNode);		// Rotate Right Right
		return;
	}

	updateAVLHeight(parentNode, grandParentNode, grandParentNode->parent);	// Else, search recursively Up the Tree

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

	TreeNode *x = new TreeNode(0, 100);
	TreeNode *y = new TreeNode(jrnyCode, 200);
	x = root;									// Search the whole Tree starting from Root
	while (x != nullptr && jrnyCode != x->getJourneyCode())
	{
		if (AVLLessThan(y, x))
			x = x->left;
		else
			x = x->right;
	}
	if (x != nullptr)
		return x->getPrice();			// Returning Price of the Node found
	else
		return -1;						// Else returning -1

	// We use "return -1" below to enable compilation.  Change this as you
	// see fit.
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
	if (find(jrnyCode) == -1)	// If element is not present, return false
		return false;

	TreeNode *y = new TreeNode(jrnyCode, 100);
	TreeNode *x = new TreeNode(jrnyCode, 200);
	TreeNode *deleteNode = searchNode(jrnyCode);		// The node to be deleted

	bool caseSuccessor = false;							// To Check if the successor is deleted

	if (deleteNode->left == nullptr || deleteNode->right == nullptr)
	{
		y = deleteNode;
	}
	else
	{
		y = successor(deleteNode);
		caseSuccessor = true;
	}
	if (y->left != nullptr)
		x = y->left;
	else
		x = y->right;
	if (x != nullptr)
		x->parent = y->parent;
	if (y->parent == nullptr)
	{
		root = x;
		return true;
	}
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != deleteNode)
	{
		*(deleteNode->changeJourneyCode()) = y->getJourneyCode();
		*(deleteNode->changePrice()) = y->getPrice();
	}

	TreeNode *z = new TreeNode(0, 0);		// Find the Imabalance Node (z)
	if (caseSuccessor)
		z = findImbalanceNode(y);
	else
		z = findImbalanceNode(deleteNode);

	if (z == nullptr)						// Return if z is NULL
		return true;

	TreeNode *y1 = getLargeHeightNode(z);	// Else y1 be the child of z with larger Height
	TreeNode *x1 = getLargeHeightNode(y1);  // And x1 be the child of y1 with larger Height

	updateHeightDel(x1, y1, z);				// Update the Heights and Rotate accordingly

	return true;
}

// To Update Heights and Rotate the Tree when Imbalance is found
void AVLTree::updateHeightDel(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	if (grandParentNode == nullptr)				// Return if grandParent is NULL
		return;
	else if (abs(grandParentNode->getBalance()) == 2)			// Rotate appropriately if Imabalance is found
	{
		if (grandParentNode->getBalance() == 2 && currNode == parentNode->left)
			rotateLeftLeft(currNode, parentNode, grandParentNode);			// Rotate Left left
		else if (grandParentNode->getBalance() == 2 && currNode == parentNode->right)
			rotateLeftRight(currNode, parentNode, grandParentNode);			// Rotate Left Right
		else if (grandParentNode->getBalance() == -2 && currNode == parentNode->left)
			rotateRightLeft(currNode, parentNode, grandParentNode);			// Rotate Right Left
		else if (grandParentNode->getBalance() == -2 && currNode == parentNode->right)
			rotateRightRight(currNode, parentNode, grandParentNode);		// Rotate Right Right
	}

	TreeNode *z = findImbalanceNode(grandParentNode);			// Again travel Up the Tree to balance
	if (z == nullptr)											// and repeat the same procedure
		return;
	TreeNode *y1 = getLargeHeightNode(z);
	TreeNode *x1 = getLargeHeightNode(y1);
	updateHeightDel(x1, y1, z);
}

// To get child of a Node with larger Height 
TreeNode *AVLTree::getLargeHeightNode(TreeNode *currNode)
{
	if (currNode->left == nullptr)
	{
		return currNode->right;
	}
	else if (currNode->right == nullptr)
	{
		return currNode->left;
	}
	else
	{
		if (currNode->left->height >= currNode->right->height)
			return currNode->left;
		else
			return currNode->right;
	}
}

// Function to find the least ancestor of a Node at which Imbalance occured
// As well as update the Heights while traversing up from the Node
TreeNode *AVLTree::findImbalanceNode(TreeNode *v)
{
	if (v == nullptr)
	{
		return nullptr;
	}
	if (v->left == nullptr && v->right == nullptr)
	{
		v->height = 0;
	}
	else if (v->left == nullptr && v->right != nullptr)
	{
		v->height = 1 + v->right->height;
	}
	else if (v->left != nullptr && v->right == nullptr)
	{
		v->height = 1 + v->left->height;
	}
	else
	{
		v->height = 1 + max(v->left->height, v->right->height);
	}

	if (abs(v->getBalance()) == 2)		// Return the Node at which Imbalance is detected
	{
		return v;
	}
	return findImbalanceNode(v->parent);
}

// To find successor of a Node
TreeNode *AVLTree::successor(TreeNode *v)
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
TreeNode *AVLTree::minNode(TreeNode *v)
{
	while (v->left != nullptr)
	{
		v = v->left;
	}
	return v;
}

// Searches the Node and returns the Node
// Similar to find function, but it return the Node
// instead of Price
TreeNode *AVLTree::searchNode(int jrnyCode)
{
	TreeNode *x = new TreeNode(0, 100);
	TreeNode *y = new TreeNode(jrnyCode, 200);
	x = root;
	while (x != nullptr && jrnyCode != x->getJourneyCode())
	{
		if (AVLLessThan(y, x))
			x = x->left;
		else
			x = x->right;
	}
	if (x != nullptr)
		return x;
	else
		return nullptr;
}


