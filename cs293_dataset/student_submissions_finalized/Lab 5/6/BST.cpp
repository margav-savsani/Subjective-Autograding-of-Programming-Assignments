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
/*
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
  return true;
}
*/
{

	TreeNode *dummy = nullptr;
	TreeNode *start = root;
	if (root->price == 0 && root->JourneyCode == 0)
	{
		root->price = price;
		root->JourneyCode = JourneyCode;

	}
	else
	{
		while (start != nullptr)
		{
			dummy = start;
			if ((start->JourneyCode) > JourneyCode)
			{
				start = start->left;
			}
			else
				start = start->right;
		}
		bool right_change;
		if (JourneyCode < dummy->JourneyCode)
		{
			TreeNode *newnode = new TreeNode;
			dummy->left = newnode;
			dummy->left->price = price;
			dummy->left->JourneyCode = JourneyCode;
			(dummy->left->parent) = dummy;
			right_change = false;
		}
		else
		{
			TreeNode *newnode = new TreeNode;
			dummy->right = newnode;
			dummy->right->price = price;
			dummy->right->JourneyCode = JourneyCode;
			(dummy->right->parent) = dummy;
			right_change = true;
		}
	}
	
	TreeNode* leaf = dummy;
	while(true)
	{
		if(dummy==nullptr)
		{
			break;
		}
		else if(dummy->right==nullptr || dummy->left==nullptr && dummy==leaf)
		{
			dummy->longestPathLength++;
			//dummy->shortestPathLength--;
		}
		else if(dummy==leaf)
		{
		    dummy->shortestPathLength++;
		}
		else
		{
			int l = dummy->longestPathLength;
			int s = dummy->shortestPathLength;
			int rl=0,rs=0,ll=0,ls=0;
			if(dummy->right!=nullptr)
			{
			    rl = dummy->right->longestPathLength;
			    rs = dummy->right->shortestPathLength;
			}
			if(dummy->left!=nullptr)
			{
			    ll = dummy->left->longestPathLength;
			    ls = dummy->left->shortestPathLength;
			}
			dummy->longestPathLength = max(rl, ll) + 1;
			dummy->shortestPathLength = min(rs, ls) + 1;
			if(l==dummy->longestPathLength && s==dummy->shortestPathLength)
			{
				break;
			}
		}
		dummy=dummy->parent;
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


