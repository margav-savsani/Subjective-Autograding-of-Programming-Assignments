#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct TreeNode{
    int JourneyCode = -1;	// Train Number
    int price = -1;			// Price
    TreeNode *left = nullptr;		// Left Child of this Node (NULL, if None)
    TreeNode *right = nullptr;	// Right Child of this Node (NULL, if None)
    TreeNode *parent = nullptr;	// The Parent Node, NULL in case of Root
	int height = 0;     // Height of the tree rooted at this node. A leaf has height 0. 

public:
	// Constructors
    TreeNode(){}
	TreeNode(int JourneyCode): JourneyCode(JourneyCode){}
    TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode){}
	TreeNode(int jrnyCode, int jrnyPrice, TreeNode *parent): price(jrnyPrice), JourneyCode(jrnyCode), parent(parent){}
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent){}

	// Destructor: Define this as per your requirements
	~TreeNode() {}

	// Print information about tree node on cout
	void printInfo() const{
		cout << "(" << JourneyCode << ", " << price << "), h: " << height;
	}
	bool isLeaf() const{ return !left && !right; }
	bool isLeftChild() const{
		if (!parent){
			std::cerr << "Cannot check for left child if parent is nullptr" << endl; throw 2;
		}
		return (parent->left == this);
	}
	bool isbalanced() const{
		return abs(((left) ? left->height: -1) - ((right) ? right->height : -1)) <= 1;
	}

	// updates height of node in the tree and returns whether the node is now balanced or not.
	bool updateHeight(){
		height = 1 + std::max((left) ? left->height: -1, (right) ? right->height: -1);
		return isbalanced();
	}
	
	// Makes THIS node the left child of parentNode if
	// isLeftChild is set to true; otherwise, it makes current node
	// the right child of parentNode.  In either case, the function
	// returns true.
	// If parentNode is NULL, the function returns false.
	// bool updateParentChild(TreeNode *parentNode, bool isLeftChild){
	// 	if (!parentNode)
	// 		return false;

	// 	parent = parentNode;
		
	// 	if (isLeftChild) parentNode->left = this; 
	// 	else 			 parentNode->right= this;
	// 	return true;
	// }
	
	// Note that if parentNode already had a left child, say x, and if
	// you are setting current node to be the new left child of
	// parentNode, then x will no longer be the left child of parentNode.
};

// The following function is effectively the same as printBST used in earlier labs.  The only difference is that this is not a member function of any class, and hence the root must be explicitly supplied as a parameter

void printBinaryTree(TreeNode *root, const string& prefix="", bool isLeft=true){
    if(root){
		cout << prefix;
		
		cout << (isLeft ? "|--" : "|__" );
		
		// print the value of the node
		root->printInfo();
		cout << endl;
		TreeNode *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
    }
}

#endif
