#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4
#define LEFT -1	 // left sentinel
#define RIGHT -2 // right sentinel

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()
{
	root = nullptr;
}
BST::BST(TreeNode *root)
{
	this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise.
bool BST::insert(int JourneyCode, int price)
{
	return myInsert(JourneyCode, price, root);
}

bool BST::myInsert(int JourneyCode, int price, TreeNode *insertInMe)
{
	if (insertInMe == nullptr)
	{
		root = new TreeNode(JourneyCode, price);
		return true;
	}
	if (insertInMe->JourneyCode == JourneyCode)
	{
		return false;
	}
	if (insertInMe->price > price)
	{
		if (journeyExists(insertInMe->right, JourneyCode))
		{
			return false;
		}
		if (insertInMe->left == nullptr)
		{
			insertInMe->left = new TreeNode(JourneyCode, price);
			insertInMe->left->parent = insertInMe;
			return true;
		}
		return myInsert(JourneyCode, price, insertInMe->left);
	}
	else
	{
		if (journeyExists(insertInMe->left, JourneyCode))
		{
			return false;
		}
		if (insertInMe->right == nullptr)
		{
			insertInMe->right = new TreeNode(JourneyCode, price);
			insertInMe->right->parent = insertInMe;
			return true;
		}
		return myInsert(JourneyCode, price, insertInMe->right);
	}
}

bool BST::journeyExists(TreeNode *searchMe, int JourneyCode)
{
	if (searchMe == nullptr)
	{
		return false;
	}
	if (searchMe->JourneyCode == JourneyCode)
	{
		return true;
	}
	return journeyExists(searchMe->left, JourneyCode) || journeyExists(searchMe->right, JourneyCode);
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
	return myFind(JourneyCode, price, root) != nullptr;
}

TreeNode *BST::myFind(int JourneyCode, int price, TreeNode *searchMySubtree)
{
	if (searchMySubtree == nullptr)
	{
		return nullptr;
	}
	if (searchMySubtree->price == price && searchMySubtree->JourneyCode == JourneyCode)
	{
		return searchMySubtree;
	}
	if (price < searchMySubtree->price)
	{
		return myFind(JourneyCode, price, searchMySubtree->left);
	}
	else
	{
		return myFind(JourneyCode, price, searchMySubtree->right);
	}
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
	TreeNode *deleteMe = myFind(JourneyCode, price, root);
	if (deleteMe == nullptr)
	{
		return false;
	}
	bool hasLeftChild = (deleteMe->left != nullptr);
	bool hasRightChild = (deleteMe->right != nullptr);
	int children = int(hasLeftChild) + int(hasRightChild);
	if (children == 0)
	{
		if (deleteMe == root)
		{
			delete deleteMe;
			root = nullptr;
			return true;
		}
		bool isLeftChild = deleteMe->parent->left == deleteMe;
		if (isLeftChild)
		{
			deleteMe->parent->left = nullptr;
			delete deleteMe;
			return true;
		}
		else
		{
			deleteMe->parent->right = nullptr;
			delete deleteMe;
			return true;
		}
	}
	else if (children == 1)
	{
		if (deleteMe == root)
		{
			bool hasLeftChild = deleteMe->right == nullptr;
			if (hasLeftChild)
			{
				root = deleteMe->left;
				delete deleteMe;
				return true;
			}
			else
			{
				root = deleteMe->right;
				delete deleteMe;
				return true;
			}
		}
		bool hasLeftChild = deleteMe->right == nullptr;
		if (hasLeftChild)
		{
			TreeNode *parent = deleteMe->parent;
			bool isLeftChild = parent->left == deleteMe;
			if (isLeftChild)
			{
				parent->left = deleteMe->left;
				deleteMe->left->parent = parent;
				delete deleteMe;
				return true;
			}
			else
			{
				parent->right = deleteMe->left;
				deleteMe->left->parent = parent;
				delete deleteMe;
				return true;
			}
		}
		else
		{
			TreeNode *parent = deleteMe->parent;
			parent = deleteMe->parent;
			bool isLeftChild = parent->left == deleteMe;
			if (isLeftChild)
			{
				parent->left = deleteMe->right;
				deleteMe->right->parent = parent;
				delete deleteMe;
				return true;
			}
			else
			{
				parent->right = deleteMe->right;
				deleteMe->right->parent = parent;
				delete deleteMe;
				return true;
			}
		}
	}
	else
	{
		TreeNode *successor = deleteMe->right;
		while (successor->left != nullptr)
		{
			successor = successor->left;
		}
		int successorPrice = successor->price;
		int successorCode = successor->JourneyCode;
		remove(successorCode, successorPrice);
		deleteMe->price = successorPrice;
		deleteMe->JourneyCode = successorCode;
		return true;
	}
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
	myTraverse(typeOfTraversal, root);
}

void BST::myTraverse(int typeOfTraversal, TreeNode *traverseMe)
{
	if (traverseMe == nullptr)
	{
		return;
	}
	if (typeOfTraversal == IN_ORDER)
	{
		myTraverse(IN_ORDER, traverseMe->left);
		cout << traverseMe->JourneyCode << endl;
		myTraverse(IN_ORDER, traverseMe->right);
		return;
	}
	else if (typeOfTraversal == PRE_ORDER)
	{
		cout << traverseMe->JourneyCode << endl;
		myTraverse(PRE_ORDER, traverseMe->left);
		myTraverse(PRE_ORDER, traverseMe->right);
		return;
	}
	else
	{
		myTraverse(POST_ORDER, traverseMe->left);
		myTraverse(POST_ORDER, traverseMe->right);
		cout << traverseMe->JourneyCode << endl;
		return;
	}
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
	TreeNode *returnMe = root;
	while (returnMe->left != nullptr)
	{
		returnMe = returnMe->left;
	}
	return returnMe->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
	return myCount(lowerPriceBound, upperPriceBound, root);
}

int BST::myCount(int lowerPriceBound, int upperPriceBound, TreeNode *countMe)
{
	if (countMe == nullptr)
	{
		return 0;
	}
	if (countMe->price <= lowerPriceBound)
	{
		return myCount(lowerPriceBound, upperPriceBound, countMe->right) + int(countMe->price == lowerPriceBound); // the typecast part adds 1 to the count if root of subtree is in range
	}
	if (countMe->price > upperPriceBound)
	{
		return myCount(lowerPriceBound, upperPriceBound, countMe->left);
	}
	return 1 + myCount(lowerPriceBound, upperPriceBound, countMe->left) + myCount(lowerPriceBound, upperPriceBound, countMe->right);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
	ofstream outfile;
	outfile.open(filename);
	myCustomStore(outfile);
}

void BST::myCustomStore(ofstream &outfile)
{
	if (root == nullptr)
	{
		return;
	}
	outfile << root->JourneyCode << ' ' << root->price << endl;
	TreeNode *curr = root;
	root = curr->left;
	myCustomStore(outfile);
	outfile << LEFT << LEFT << endl;
	root = curr->right;
	myCustomStore(outfile);
	outfile << RIGHT << RIGHT << endl;
	root = curr;
	return;
}

// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
void BST::customLoad(int flag, string filename)
{
	root = nullptr;
	ifstream infile;
	infile.open(filename);
	vector<TreeNode *> pendingNodes; // a stack of nodes pending to be loaded
	vector<bool> insertOnleft;
	int rootJourneyCode, rootPrice;
	infile >> rootJourneyCode >> rootPrice;
	root = new TreeNode(rootJourneyCode, rootPrice);
	pendingNodes.push_back(root);
	insertOnleft.push_back(true);
	myCustomLoad(infile, pendingNodes, insertOnleft, flag);
}

void BST::myCustomLoad(ifstream &infile, vector<TreeNode *> pendingNodes, vector<bool> insertOnLeft, int flag)
{
	if (flag == LOAD_LEFT_SUBTREE && pendingNodes.size() == 1 && insertOnLeft[0] == false)
	{
		root = root->left;
		return;
	}
	if (pendingNodes.size() == 0)
	{
		return;
	}
	int journeyCode, price;
	infile >> journeyCode >> price;
	if (journeyCode == RIGHT)
	{
		pendingNodes.pop_back();
		insertOnLeft.pop_back();
		myCustomLoad(infile, pendingNodes, insertOnLeft, flag);
		return;
	}
	if (journeyCode == LEFT)
	{
		insertOnLeft[insertOnLeft.size() - 1] = false;
		myCustomLoad(infile, pendingNodes, insertOnLeft, flag);
		return;
	}
	if (insertOnLeft[pendingNodes.size() - 1])
	{
		pendingNodes[pendingNodes.size() - 1]->left = new TreeNode(journeyCode, price);
		pendingNodes[pendingNodes.size() - 1]->left->parent = pendingNodes[pendingNodes.size() - 1];
		pendingNodes.push_back(pendingNodes[pendingNodes.size() - 1]->left);
		insertOnLeft.push_back(true);
		myCustomLoad(infile, pendingNodes, insertOnLeft, flag);
		return;
	}
	if (!insertOnLeft[pendingNodes.size() - 1])
	{
		pendingNodes[pendingNodes.size() - 1]->right = new TreeNode(journeyCode, price);
		pendingNodes[pendingNodes.size() - 1]->right->parent = pendingNodes[pendingNodes.size() - 1];
		pendingNodes.push_back(pendingNodes[pendingNodes.size() - 1]->right);
		insertOnLeft.push_back(true);
		myCustomLoad(infile, pendingNodes, insertOnLeft, flag);
		return;
	}
	cout << "CATCH ME" << endl;
}

// Made a late submission at around 615 pm because I forgot to patch BST.
//  ************************************************************
//  DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
	if (root != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		cout << root->JourneyCode << endl;
		TreeNode *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		printBST(prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		printBST(prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
	if (root != nullptr)
	{
		result.push_back(prefix);

		result.push_back(isLeft ? "|--" : "|__");

		// print the value of the node
		result.push_back(root->JourneyCode + "\n");
		TreeNode *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		getBST(prefix + (isLeft ? "│   " : "    "), true);
		root = curr->right;
		getBST(prefix + (isLeft ? "│   " : "    "), false);
		root = curr;
	}
}

void BST::clearResult()
{
	result.clear();
}

vector<string> BST::getResult()
{
	return result;
}