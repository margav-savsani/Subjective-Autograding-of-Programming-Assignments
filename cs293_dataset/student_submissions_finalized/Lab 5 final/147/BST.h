#ifndef BST_H
#define BST_H

#include "Tree.h"
using namespace std;

class AbstractBST {
protected:
	TreeNode *root;
	int totalComparisonCost = 0;
	int totalParentChildUpdateCost = 0;
	int perComparisonCost;
	int perParentChildUpdateCost;
public:
	// constructor
	AbstractBST(int perComparisonCost, int perParentChildUpdateCost, TreeNode *root=nullptr): 
	perComparisonCost(perComparisonCost), perParentChildUpdateCost(perParentChildUpdateCost), root(root){}	
	// destructor
	~AbstractBST() { recursiveDelete(root); } // neat!

protected:
	// Recursively deletes all nodes in the binary tree rooted at currNode
	void recursiveDelete(TreeNode *currNode) {
		if (!currNode) return; 

		TreeNode *leftChild = currNode->left;
		TreeNode *rightChild = currNode->right;
		delete currNode;
		recursiveDelete(leftChild);
		recursiveDelete(rightChild);
		return;
	}

	// wrapper functions that also update the costs of comparisons and updations.

	// checks if *leftArg is < *rightArg or not.
	bool LessThan(const TreeNode* leftArg, const TreeNode* rightArg){
		if (leftArg && rightArg) {
			totalComparisonCost += perComparisonCost;
			return leftArg->JourneyCode < rightArg->JourneyCode;
		}
		cerr << "Unexpected exceptional condition!" << endl;
		exit(-1);
	}	
	// sets childNode to be the left/right child of ParentNode.
	void updateParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeft){
		// parent can be nullptr (ie we re-root the tree)
		// child can be nullptr (ie we set one subtree of parent to nullptr)
		// both shouldn't be nullptr though

		if (childNode) childNode->parent = parentNode; // else do nothing.
		
		if (parentNode){
			if (isLeft) parentNode->left = childNode;
			else        parentNode->right= childNode;
		}
		else{
			root = childNode;
		}

		if (childNode) // why is this required? Okay if !childNode half the cost, say.
			totalParentChildUpdateCost += perParentChildUpdateCost;
		return;
	}
	
public:
	// common across all BSTs. At least over usual BSTs and AVL Trees.
	int find(int JourneyCode);
	const TreeNode *getnode(int JourneyCode);
	void updateHeightsOnPath(TreeNode *);
	
	// insert
	virtual bool insert(int JourneyCode, int price) = 0;

	// Optional: Implement "remove" only for bonus marks
	virtual bool remove(int JourneyCode) = 0;

	// accessor fns. Again common across both BST types.
	int getComparisonCost() { return totalComparisonCost; }
	int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
	void print() { printBinaryTree(root, "", true); return;}
};

class BST: public AbstractBST{
public:
	BST(int perComparisonCost, int perParentChildUpdateCost, TreeNode *root=nullptr): 
	AbstractBST(perComparisonCost, perParentChildUpdateCost, root){}
	~BST(){} // ~AbstractBST takes care of memory deallocation.

	bool insert(int JourneyCode, int price);
	bool remove(int JourneyCode);
};

#endif
