#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif



int TreeNode::insert_in_BST(int val, int price)
{
	// inserts a value in the binary search tree at the appropriate location
	// this does not move any of the existing elements
	// Insertion happens in the whole tree
	// returns 10*(number of comparisons that happen during insertion)+(number of parent-child updates)
	int num_comp = 0, num_updates = 1;
	TreeNode *temp = this;
	while (temp->parent)
	{
		temp = temp->parent;
	}
	temp = temp->insert_in_subtree(val, price, num_comp); // store the location of the new node in temp
	// update heights in the tree
	temp->update_heights_of_ancestors();
	return 10 * num_comp + num_updates; // since the number of updates is always less than 6, we can use this scheme to pass both
}

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

	// We use "return true" below to enable compilation.  Change this as you
	// see fit.
	if (!root)
	{
		root = new TreeNode(jrnyCode, price);
		totalComparisonCost += perComparisonCost;
		return true;
	}
	int num_comp = (root->insert_in_BST(jrnyCode, price));
	int num_update = num_comp % 10;
	num_comp /= 10;
	totalComparisonCost += perComparisonCost * num_comp;
	totalParentChildUpdateCost += perParentChildUpdateCost * num_update;
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

	// We use "return -1" below to enable compilation.  Change this as you
	// see fit.
	TreeNode* dummy = new TreeNode{jrnyCode, 0};   
    TreeNode* temp1{root};
    while(temp1){
		if(BSTLessThan(dummy, temp1))
            temp1 = temp1->left;
        else if(BSTEqualTo(dummy, temp1))
            return temp1->price;
        else
            temp1 = temp1->right;
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

	// REMEMBER to update the height of appropriate nodes in the tree
	// after a successful deletion.

	// We use "return true" below to enable compilation.  Change this as you
	// see fit.

	return true;
}
