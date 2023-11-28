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

class BST {
private:
	TreeNode *root;
	int totalComparisonCost = 0;
	int totalParentChildUpdateCost = 0;
	int perComparisonCost;
	int perParentChildUpdateCost;
	
	// Recursively deletes all nodes in the binary tree rooted at currNode
	
	void recursiveDelete(TreeNode *currNode) {
		if (currNode != nullptr) {
		TreeNode *leftChild = currNode->left;
		TreeNode *rightChild = currNode->right;
		
		delete currNode;
		recursiveDelete(leftChild);
		recursiveDelete(rightChild);
		}
		return;
	}

	// checks if *leftArg is < *rightArg or not.
	bool BSTLessThan(const TreeNode* leftArg, const TreeNode* rightArg){
		if (leftArg && rightArg) {
			totalComparisonCost += perComparisonCost;
			return *leftArg < *rightArg;
		}
		cerr << "Unexpected exceptional condition!" << endl;
		// exit(-1);
	}
	
	void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
	{
		if (childNode && parentNode) {
			childNode->updateParentChild(parentNode, isLeftChild);
			totalParentChildUpdateCost += perParentChildUpdateCost;
		}

		else if (parentNode) {
			if (isLeftChild) parentNode->left = nullptr;
			else parentNode->right = nullptr;
		} // No updating of totalParentChildUpdateCost needed here - why? There are updates.
		
		else if (childNode) {
			childNode->parent = nullptr;
		} // No updating of totalParentChildUpdateCost needed here

		// both childNode and parentNode are nullptr
		else {
			// Nothing to do really
			// No updating of totalParentChildUpdateCost needed here
		;}
	}
		
public:
	// Constructors
	BST(int perComparisonCost, int perParentChildUpdateCost): 
	perComparisonCost(perComparisonCost), perParentChildUpdateCost(perParentChildUpdateCost), root(nullptr){}
	
	BST(TreeNode *root, int perCompCost, int perParntChldUpdCost): 
	perComparisonCost(perComparisonCost), perParentChildUpdateCost(perParentChildUpdateCost), root(root){}
		
	// Destructor
	~BST() { recursiveDelete(root); } // neat!

	bool insert(int jrnyCode, int price);
	int find(int jrnyCode);
	const TreeNode *getnode(int JourneyCode);

	// Optional: Implement "remove" only for bonus marks
	
	bool remove(int jrnyCode);

	// accessor fns
	int getComparisonCost() { return totalComparisonCost; }
	int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
	void print() { printBinaryTree(root, "", false); return;}
};

#endif
