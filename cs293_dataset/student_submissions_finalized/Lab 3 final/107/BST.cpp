#include <algorithm>
#include <cmath>
#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()  //If root not passed then set it to nullptr
{
	root=nullptr;
}
BST::BST(TreeNode *root)  //If root passed then set it to passed node
{
	this->root=root;
}

// Returns true, if given JourneyCode is present in the BST
// Returns false otherwise
bool BST::findJourneyCode(int JourneyCode)
{
	// Since BST is according to price, for JourneyCode we have to search all
	// nodes, we go according to PRE_ORDER, if we find the JourneyCode,
	// we return true, else we return false
	if(root==nullptr)	// If we have empty tree
		return false;
	if(root->JourneyCode==JourneyCode)	// If JourneyCode matches
		return true;
	BST LTree(root->left);
	if(LTree.findJourneyCode(JourneyCode))	// Left subtree search
		return true;
	BST RTree(root->right);
	if(RTree.findJourneyCode(JourneyCode))  // Right subtree search
		return true;
	return false;
}

// Returns pointer to TreeNode having corresponding JourneyCode and Price
TreeNode* BST::getTreeNode(int JourneyCode, int price)
{
	// We search for price according to BST rule, if the element with matched price also
	// matches JourneyCode, then we return that node else continue the search
	// If not found, it returns nullptr
	if(root==nullptr)	// Not found
		return nullptr;
	if((root->price)==price && (root->JourneyCode)==JourneyCode)
		return root;	// Found
	else if((root->price)>price)
	{
		// Left subtree search
		BST LTree(root->left);
		return LTree.getTreeNode(JourneyCode, price);
	}
	else
	{
		// Right subtree search
		BST RTree(root->right);
		return RTree.getTreeNode(JourneyCode, price);
	}
	return nullptr;
}


// Returns node with minimum price in the BST whose root is passed
TreeNode* BST::getMinimumNode(TreeNode* curr)
{
	// Minimum price node is the leftmost node in the BST
	if(curr==nullptr)
		return nullptr;
	if(curr->left==nullptr)
		return curr;	// This will be leftmost node
	return getMinimumNode(curr->left);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
	// Insert if not present at its location
	if(findJourneyCode(JourneyCode))	// If JourneyCode already present
		return false;
	if(root==nullptr)	// Root set
	{
		TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
		root= newnode;
	}
	else if(root->price>price)
	{
		if(root->left==nullptr)
		{
			// Left child set
			TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, root);
			root->left=newnode;
		}
		else
		{
			// Continue search
			BST LTree(root->left);
			return LTree.insert(JourneyCode, price);
		}
	}
	else
	{
		if(root->right==nullptr)
		{
			// Right child set
			TreeNode *newnode= new TreeNode(JourneyCode, price, nullptr, nullptr, root);
			root->right=newnode;
		}
		else
		{
			// Continue search
			BST RTree(root->right);
			return RTree.insert(JourneyCode, price);
		}
	}
	return true;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
	// Find according to BST property
	if(root==nullptr) // Not found
		return false;
	if((root->price)==price && root->JourneyCode==JourneyCode)	// Found
		return true;
	else if((root->price)>price)
	{
		// Left Subtree search
		BST LTree(root->left);
		return LTree.find(JourneyCode, price);
	}
	else
	{
		// Right Subtree search
		BST RTree(root->right);
		return RTree.find(JourneyCode, price);
	}
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
	// Remove if found according to rules discussed in Lecture

	if(!find(JourneyCode, price))	// Not found
		return false;
	TreeNode *toremove= getTreeNode(JourneyCode, price); // Node to remove

	// Root remove cases
	if(toremove==root && root->right==nullptr && root->left==nullptr) // No child
	{
		root=nullptr;
		return true;
	}
	else if(toremove==root && root->right==nullptr)  // Only left child
	{
		root=toremove->left;
		root->parent=nullptr;
		return true;
	}
	else if(toremove==root && root->left==nullptr)	// Only right child
	{
		root=toremove->right;
		root->parent=nullptr;
		return true;
	}
	else if(toremove==root)	// Both left and right child
	{
		TreeNode* successor= getMinimumNode(toremove->right); // This will replace root's parameters
		int jc= successor->JourneyCode;
		int pc= successor->price;
		this->remove(jc, pc);
		root->JourneyCode= jc;
		root->price= pc;
		return true;
	}

	// Not root remove cases
	if(toremove->right==nullptr && toremove->left==nullptr) // No child
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
	else if(toremove->right==nullptr)  // Only left child
	{
		if((toremove->parent)->right == toremove)
			(toremove->parent)->right = toremove->left;
		else
			(toremove->parent)->left = toremove->left;
		(toremove->left)->parent = toremove->parent;
		return true;
	}
	else if(toremove->left==nullptr)  // Only right child
	{
		if((toremove->parent)->right == toremove)
			(toremove->parent)->right = toremove->right;
		else
			(toremove->parent)->left = toremove->right;
		(toremove->right)->parent = toremove->parent;
		return true;
	}
	else  // Both left and right child
	{
		TreeNode* successor= getMinimumNode(toremove->right); // This will replace root's parameters
		int jc= successor->JourneyCode;
		int pc= successor->price;
		this->remove(jc, pc);
		toremove->JourneyCode= jc;
		toremove->price= pc;
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
	// Traverse according to typeOfTraversal

	if(root==nullptr)	// Tree is empty
		return;
	if(typeOfTraversal==PRE_ORDER)
	{
		// PRE_ORDER : root, leftChild, rightChild
		cout<<root->JourneyCode<<" "<<root->price<<endl;
		BST LTree(root->left);
		LTree.traverse(typeOfTraversal);
		BST RTree(root->right);
		RTree.traverse(typeOfTraversal);
	}
	else if(typeOfTraversal==POST_ORDER)
	{
		// POST_ORDER: leftChild, rightChild, root
		BST LTree(root->left);
		LTree.traverse(typeOfTraversal);
		BST RTree(root->right);
		RTree.traverse(typeOfTraversal);
		cout<<root->JourneyCode<<" "<<root->price<<endl;
	}
	else if(typeOfTraversal==IN_ORDER)
	{
		// IN_ORDER: leftChild, root, rightChild
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
	// Cheapest journey is the leftmost node in our tree
	if(root==nullptr)	// If tree is empty
		return 0;
	if(root->left==nullptr) // This is cheapest
		return root->price;
	BST LTree(root->left);
	return LTree.getMinimum();
}

// Part II


void BST::helperCountJourneysInPriceBound(int& total, int lowerPriceBound, int upperPriceBound)
{
	// stores total count in total
	if(root==nullptr)
		return;
	if(root->price > lowerPriceBound) // Go to left child only if price at root is greater than lowerPriceBound
	{
		// Go to left subtree
		BST LTree(root->left);
		LTree.helperCountJourneysInPriceBound(total, lowerPriceBound, upperPriceBound);
		if(root->price <= upperPriceBound)	// This means that root falls under bounds
			total++;
		else	// This means we have crossed upperPriceBound... so no need to preocess BST further
			return;
	}
	else if(root->price == lowerPriceBound)
		total++;
	// Go to right subtree
	BST RTree(root->right);
	RTree.helperCountJourneysInPriceBound(total, lowerPriceBound, upperPriceBound);
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
	// calls helperCountJourneysInPriceBound
	int total=0;
	helperCountJourneysInPriceBound(total, lowerPriceBound, upperPriceBound);
	return total;
}

// Helper to customStore, stores the BST in filename
void BST::helperCustomStore(string filename)
{
	ofstream outfile;
	outfile.open(filename, std::ios::app); // Append mode
	if(root==nullptr)
	{
		outfile<<"!"<<endl;  // Marker to empty tree
		outfile.close();
		return;
	}
	outfile<<root->JourneyCode<<" "<<root->price<<endl;  // Write to outfile
	if (root->left!=nullptr)
	{
		// Left subtree store
		BST LTree(root->left);
		LTree.helperCustomStore(filename);
	}
	if (root->right!=nullptr)
	{
		// Right subtree store
		BST RTree(root->right);
		RTree.helperCustomStore(filename);
	}
	outfile<<"!S"<<endl;  // Marker to end of subtree
	outfile.close();
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
	// delete filename content and calls helperCustomStore
	ofstream outfile;
	outfile.open(filename);
	outfile.close();
	helperCustomStore(filename);
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
	ifstream infile;
	infile.open(filename);
	string nextInLine;	// Will store in it a line of infile
	TreeNode* curr=root;	// curr represents node at which all operations will be done
	while (getline(infile, nextInLine))
	{
		if(nextInLine=="!")	// Empty tree
			return;
		else if(nextInLine=="!S")	// End of subtree, move curr to its parent
		{
			if(curr->parent==nullptr)	// This part is added for LOAD_LEFT_SUBTREE part
				return;
			curr=curr->parent;
		}
		else
		{
			if(flag==LOAD_LEFT_SUBTREE)
			{
				istringstream robj(nextInLine);
				string rstr1, rstr2;
				robj >> rstr1;	// root JourneyCode
				robj >> rstr2; // root price
				getline(infile, nextInLine);
				if (nextInLine=="!S")	// tree has only root in it
					return;
				istringstream nobj(nextInLine);
				string nstr1, nstr2;
				nobj >> nstr1;	// next JourneyCode
				nobj >> nstr2; // next price
				if(stoi(rstr2) <= stoi(nstr2))//Left subtree is not there
					return;
				TreeNode *newNode = new TreeNode();	// newNode to be added
				newNode->JourneyCode=stoi(nstr1);
				newNode->price=stoi(nstr2);
				root=newNode;
				curr=root;
				flag=LOAD_FULL_BST;	// Now we will load full tree of left child
			}
			else
			{
			TreeNode *newNode = new TreeNode();	// newNode to be added
			istringstream obj(nextInLine);
			string str1, str2;
			obj >> str1;	// JourneyCode
			obj >> str2; // price
			newNode->JourneyCode=stoi(str1);
			newNode->price=stoi(str2);
			if(root==nullptr)	// If root is not added yet
			{
				root=newNode;
				curr=root;
			}
			else if(newNode->price < curr->price)
			{
				curr->left=newNode;	// newNode will be left child of curr
				newNode->parent=curr;
				curr=newNode;	// Move curr to newNode
			}
			else
			{
				curr->right=newNode; // newNode will be right child of curr
				newNode->parent=curr;
				curr=newNode; // Move curr to newNode
			}
			}
	 	}
	}
}


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
				string str= to_string(root->JourneyCode);
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
