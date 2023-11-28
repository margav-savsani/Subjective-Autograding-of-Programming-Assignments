#ifndef BST_H
#define BST_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

class BST
{
private:
	TreeNode *root;
	int totalComparisonCost;
	int totalParentChildUpdateCost;
	int perComparisonCost;
	int perParentChildUpdateCost;

	// Recursively deletes all nodes in the binary tree rooted at currNode

	void recursiveDelete(TreeNode *currNode)
	{
		if (currNode != nullptr)
		{
			TreeNode *leftChild = currNode->left;
			TreeNode *rightChild = currNode->right;

			delete currNode;
			recursiveDelete(leftChild);
			recursiveDelete(rightChild);
		}
		return;
	}

	bool BSTLessThan(TreeNode *leftArg, TreeNode *rightArg)
	{
		if ((leftArg != nullptr) && (rightArg != nullptr))
		{
			bool result = (*leftArg < *rightArg);
			totalComparisonCost += perComparisonCost;
			return result;
		}
		else
		{
			cerr << "Unexpected exceptional condition!" << endl;
			exit(-1);
		}
	}

	void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
	{
		if ((childNode != nullptr) && (parentNode != nullptr))
		{
			childNode->updateParentChild(parentNode, isLeftChild);
			totalParentChildUpdateCost += perParentChildUpdateCost;
		}
		else if ((childNode == nullptr) && (parentNode != nullptr))
		{
			if (isLeftChild)
			{
				parentNode->left = nullptr;
			}
			else
			{
				parentNode->right = nullptr;
			}
			// No updating of totalParentChildUpdateCost needed here
		}
		else if ((childNode != nullptr) && (parentNode == nullptr))
		{
			childNode->parent = nullptr;
			// No updating of totalParentChildUpdateCost needed here
		}
		else
		{
			// both childNode and parentNode are nullptr
			// Nothing to do really
			// No updating of totalParentChildUpdateCost needed here
			;
		}
		return;
	}

public:
	// Constructors
	BST(int perCompCost, int perParntChldUpdCost)
	{
		root = nullptr;
		totalComparisonCost = 0;
		totalParentChildUpdateCost = 0;
		perComparisonCost = perCompCost;
		perParentChildUpdateCost = perParntChldUpdCost;
	}

	BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost)
	{
		root = newRoot;
		totalComparisonCost = 0;
		totalParentChildUpdateCost = 0;
		perComparisonCost = perCompCost;
		perParentChildUpdateCost = perParntChldUpdCost;
	}

	// Destructor
	~BST()
	{
		recursiveDelete(root);
	}

	bool insert(int jrnyCode, int price);		// Insert Node
	int find(int jrnyCode);						// Find Node

	// Optional: Implement "remove" only for bonus marks

	bool remove(int jrnyCode);					// Delete Node

	void updateHeights(TreeNode *v);			// Update Heights of required Nodes

	int getComparisonCost() { return totalComparisonCost; }
	int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
	TreeNode *successor(TreeNode *currNode);	// Find successor of a Node
	TreeNode *minNode(TreeNode *currNode);		// Find node with minimum value
	TreeNode *searchNode(int jrnyCode);			// Search for a Node and return it
	void print()								// Print the Tree
	{
		printBinaryTree(root, "", false);
		return;
	}
};

#endif
