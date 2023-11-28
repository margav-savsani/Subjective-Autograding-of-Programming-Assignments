// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <set>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

TreeNode::TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}


BST::BST()
{
  root=nullptr;
}

BST::BST(TreeNode *curr_root)
{
  root = curr_root;
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
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
	else if((root->JourneyCode)>JourneyCode)
	{
		// Left subtree search
		BST LTree(root->left);
		return LTree.getTreeNode(JourneyCode, price);
	}
	else if((root->JourneyCode)<JourneyCode)
	{
		// Right subtree search
		BST RTree(root->right);
		return RTree.getTreeNode(JourneyCode, price);
	}
  else
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

void BST::updatelengths(TreeNode *parentOfCurrNode)
{
  while (parentOfCurrNode!=nullptr)
  {
    // moving up to root... updating shortestPathLength and longestPathLength
    if(parentOfCurrNode->left==nullptr)
    {
      // only right child is present
      parentOfCurrNode->shortestPathLength=0;
      parentOfCurrNode->longestPathLength=((parentOfCurrNode->right)->longestPathLength) + 1;
    }
    else if(parentOfCurrNode->right==nullptr)
    {
      // only left child is present
      parentOfCurrNode->shortestPathLength=0;
      parentOfCurrNode->longestPathLength=((parentOfCurrNode->left)->longestPathLength) + 1;
    }
    else
    {
      // both left and right children are present
      parentOfCurrNode->shortestPathLength=min((parentOfCurrNode->left)->shortestPathLength, (parentOfCurrNode->right)->shortestPathLength) + 1;
      parentOfCurrNode->longestPathLength=max((parentOfCurrNode->left)->longestPathLength, (parentOfCurrNode->right)->longestPathLength) + 1;
    }
    parentOfCurrNode=parentOfCurrNode->parent;  // move control up the tree
  }
}

bool BST::insert(int JourneyCode, int price)
{
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;

  if(root==nullptr)
  {
    // no root present
    root= new TreeNode(JourneyCode, price);
    root->shortestPathLength=0;
    root->longestPathLength=0;
    return true;
  }

  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  if(parentOfCurrNode->JourneyCode > JourneyCode)
  {
    // left insert
    parentOfCurrNode->left= new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    (parentOfCurrNode->left)->shortestPathLength=0;
    (parentOfCurrNode->left)->longestPathLength=0;
  }
  else
  {
    // right insert
    parentOfCurrNode->right= new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    (parentOfCurrNode->right)->shortestPathLength=0;
    (parentOfCurrNode->right)->longestPathLength=0;
  }
  updatelengths(parentOfCurrNode);  // Update shortestPathLength and longestPathLength
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
	else if((root->JourneyCode)>JourneyCode)
	{
		// Left Subtree search
		BST LTree(root->left);
		return LTree.find(JourneyCode, price);
	}
	else if((root->JourneyCode)<JourneyCode)
	{
		// Right Subtree search
		BST RTree(root->right);
		return RTree.find(JourneyCode, price);
	}
  else
  {
    return false;
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
		}
		else
		{
			(toremove->parent)->left = nullptr;
		}
    updatelengths(toremove->parent);  // Update shortestPathLength and longestPathLength
    return true;
	}
	else if(toremove->right==nullptr)  // Only left child
	{
		if((toremove->parent)->right == toremove)
			(toremove->parent)->right = toremove->left;
		else
			(toremove->parent)->left = toremove->left;
		(toremove->left)->parent = toremove->parent;
    updatelengths(toremove->parent);  // Update shortestPathLength and longestPathLength
		return true;
	}
	else if(toremove->left==nullptr)  // Only right child
	{
		if((toremove->parent)->right == toremove)
			(toremove->parent)->right = toremove->right;
		else
			(toremove->parent)->left = toremove->right;
		(toremove->right)->parent = toremove->parent;
    updatelengths(toremove->parent);  // Update shortestPathLength and longestPathLength
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

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
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
