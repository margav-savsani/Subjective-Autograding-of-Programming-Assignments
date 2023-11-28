#include <algorithm>
#include <cmath>
#include <set>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()
{
	root=nullptr;
}
BST::BST(TreeNode *root)
{
	this->root=root;
}

// Returns true, if given JourneyCode is present in the BST
// Returns false otherwise
bool BST::findJourneyCode(int JourneyCode)
{
	if(root==nullptr)
		return false;
	if(root->JourneyCode==JourneyCode)
		return true;
	BST RTree(root->right);
	if(RTree.findJourneyCode(JourneyCode))
		return true;
	BST LTree(root->left);
	if(LTree.findJourneyCode(JourneyCode))
		return true;
	return false;
}

// Returns pointer to TreeNode having corresponding JourneyCode and Price
TreeNode* BST::getTreeNode(int JourneyCode, int price)
{
	if(root==nullptr)
		return nullptr;
	if((root->price)==price && (root->JourneyCode)==JourneyCode)
		return root;
	else if((root->price)>price)
	{
		BST LTree(root->left);
		return LTree.getTreeNode(JourneyCode, price);
	}
	else
	{
		BST RTree(root->right);
		return RTree.getTreeNode(JourneyCode, price);
	}
	return nullptr;
}

// Returns node with minimum price in the BST whose root is passed
TreeNode* BST::getMinimumNode(TreeNode* curr)
{
	if(curr==nullptr)
		return nullptr;
	if(curr->left==nullptr)
		return curr;
	return getMinimumNode(curr);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
	if(findJourneyCode(JourneyCode))
		return false;
	if(root==nullptr)
	{
		TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
		root= newnode;
	}
	else if(root->price>price)
	{
		if(root->left==nullptr)
		{
			TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, root);
			root->left=newnode;
		}
		else
		{
			BST LTree(root->left);
			LTree.insert(JourneyCode, price);
		}
	}
	else
	{
		if(root->right==nullptr)
		{
			TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, root);
			root->right=newnode;
		}
		else
		{
			BST RTree(root->right);
			RTree.insert(JourneyCode, price);
		}
	}
	return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
	if(root==nullptr)
		return false;
	if((root->price)==price && root->JourneyCode==JourneyCode)
		return true;
	else if((root->price)>price)
	{
		BST LTree(root->left);
		return LTree.find(JourneyCode, price);
	}
	else
	{
		BST RTree(root->right);
		return RTree.find(JourneyCode, price);
	}
	return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
	if(!find(JourneyCode, price))
		return false;
	TreeNode *toremove= getTreeNode(JourneyCode, price);
	if(toremove==root && root->right==nullptr && root->left==nullptr)
	{
		root=nullptr;
		return true;
	}
	else if(toremove==root && root->right==nullptr)
	{
		root=toremove->left;
		return true;
	}
	else if(toremove==root && root->left==nullptr)
	{
		root=toremove->right;
		return true;
	}
	else if(toremove==root)
	{
		TreeNode* successor= getMinimumNode(toremove->right);
		int jc= successor->JourneyCode;
		int pc= successor->price;
		TreeNode* toinsert;
		if(toremove->right==successor)
			toinsert= new TreeNode(jc, pc, toremove->left, nullptr, nullptr);
		else
		  toinsert= new TreeNode(jc, pc, toremove->left, toremove->right, nullptr);
		remove(jc, pc);
		(toremove->right)->parent = toinsert;
		(toremove->left)->parent = toinsert;
		return true;
	}
	if(toremove->right==nullptr && toremove->left==nullptr)
	{
		if((toremove->parent)->right == toremove)
		{
			(toremove->parent)->right = nullptr;
			return true;
		}
		else
		{
			(toremove->parent)->left = nullptr;
			return true;
		}
	}
	else if(toremove->right==nullptr)
	{
		if((toremove->parent)->right == toremove)
		{
			(toremove->parent)->right = toremove->left;
			return true;
		}
		else
		{
			(toremove->parent)->left = toremove->left;
			return true;
		}
	}
	else if(toremove->left==nullptr)
	{
		if((toremove->parent)->right == toremove)
		{
			(toremove->parent)->right = toremove->right;
			return true;
		}
		else
		{
			(toremove->parent)->left = toremove->right;
			return true;
		}
	}
	else
	{
		TreeNode* successor= getMinimumNode(toremove->right);
		int jc= successor->JourneyCode;
		int pc= successor->price;
		TreeNode* toinsert;
		if(toremove->right==successor)
			toinsert= new TreeNode(jc, pc, toremove->left, nullptr, toremove->parent);
		else
		  toinsert= new TreeNode(jc, pc, toremove->left, toremove->right, toremove->parent);
		remove(jc, pc);
		if((toremove->parent)->right == toremove)
		{
			(toremove->parent)->right = toinsert;
		}
		else
		{
			(toremove->parent)->left = toinsert;
		}
		(toremove->right)->parent = toinsert;
		(toremove->left)->parent = toinsert;
		return true;
	}
	return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
	if(root==nullptr)
		return;
	if(typeOfTraversal==PRE_ORDER)
	{
		cout<<root->JourneyCode<<" "<<root->price<<endl;
		BST LTree(root->left);
		LTree.traverse(typeOfTraversal);
		BST RTree(root->right);
		RTree.traverse(typeOfTraversal);
	}
	else if(typeOfTraversal==POST_ORDER)
	{
		BST LTree(root->left);
		LTree.traverse(typeOfTraversal);
		BST RTree(root->right);
		RTree.traverse(typeOfTraversal);
		cout<<root->JourneyCode<<" "<<root->price<<endl;
	}
	else if(typeOfTraversal==IN_ORDER)
	{
		BST LTree(root->left);
		LTree.traverse(typeOfTraversal);
		cout<<root->JourneyCode<<" "<<root->price<<endl;
		BST RTree(root->right);
		RTree.traverse(typeOfTraversal);
	}
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
	if(root==nullptr)
		return 0;
	if(root->left==nullptr)
		return root->price;
	BST LTree(root->left);
	return LTree.getMinimum();
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }

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

void BST::customLoad (int flag, string filename) { return; }


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
				string str= to_string(root->JourneyCode );
        result.push_back(str + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}
