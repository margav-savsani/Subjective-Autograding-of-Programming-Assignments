#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

class AVLTree
{
private:
	TreeNode *root;
	int totalComparisonCost;
	int totalParentChildUpdateCost;
	int perComparisonCost;
	int perParentChildUpdateCost;

	bool rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
	bool rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
	bool rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
	bool rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);

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

	bool AVLLessThan(TreeNode *leftArg, TreeNode *rightArg)
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

	void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
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
			root = childNode;
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
	AVLTree(int perCompCost, int perParntChldUpdCost)
	{
		root = nullptr;
		totalComparisonCost = 0;
		totalParentChildUpdateCost = 0;
		perComparisonCost = perCompCost;
		perParentChildUpdateCost = perParntChldUpdCost;
	}

	AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost)
	{
		root = newRoot;
		totalComparisonCost = 0;
		totalParentChildUpdateCost = 0;
		perComparisonCost = perCompCost;
		perParentChildUpdateCost = perParntChldUpdCost;
	}

	// Destructor
	~AVLTree()
	{
		recursiveDelete(root);
	}

	bool insert(int jrnyCode, int price);		   // Insert Node
	int find(int jrnyCode);						   // Find Node

	// Optional: Implement "remove" only for bonus marks

	bool remove(int jrnyCode);					   // Delete Node

	void updateAVLHeight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode);	// Update Heights of appropriate Nodes
	void updateHeightDel(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode);	// Update Heights on Deletion
	int getComparisonCost() { return totalComparisonCost; }
	int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
	TreeNode *successor(TreeNode *currNode);		// Find Succossor of a Node
	TreeNode *minNode(TreeNode *currNode);			// Find the Node with Minimum Journey Code
	TreeNode *findImbalanceNode(TreeNode *v);		// Find Imbalance Node
	TreeNode *getLargeHeightNode(TreeNode *v);		// Get the child of a Node with larger Height
	TreeNode *searchNode(int jrnyCode);				// Search for a Node and return it
	void print()
	{
		printBinaryTree(root, "", false);
		return;
	}
};

#endif
