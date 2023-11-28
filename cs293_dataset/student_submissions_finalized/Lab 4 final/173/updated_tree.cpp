// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "updated_tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  int depth=0;
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    	//cout << "going to right    depth: " << ++depth << endl;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      //cout << "going to left    depth: " << ++depth << endl;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  //cout << "inserting leaf...\n";
  if (parentOfCurrNode != nullptr) {
  	currNode = new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
  	if (parentOfCurrNode->JourneyCode > JourneyCode)
  		parentOfCurrNode->left=currNode;
		else if (parentOfCurrNode->JourneyCode < JourneyCode)
			parentOfCurrNode->right=currNode;
  	//cout << "leaf successfully added\n";                       // Inserts a new node/leaf to the BST
  }
  else
  	root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);

  // Below, I wrote the code to find shortestPath and longestPath from a node to its leaves.
  // It works on recursion. if short(node->leftChild) < short(node->rightChild) then
  // short(node)=short(node->leftChild)+1; and if long(node->leftChild) < long(node->rightChild)
  // then long(node)=long(node->leftChild)+1; if node->leftChild or node->rightChild=nullptr; then
  // short(thatChild)=long(thatChild)=0; If a new node/leaf is inserted then the efficient way to 
  // update the shortestPath and longestPath is to update the values only for the direct ancestors of 
  // the inserted node/leaf. but this is slightly tricky (think why?). So, I'll just go with updating
  // the values for all nodes in BST with the new node/leaf added. Uh-oh! seems like I need to implement
  // tree traversal to do this. but I didn't solve lab03. So, I'll just go with the ancestor method. but
  // this uses iteration instead of recursion. I really don't know this is efficient or not :-)
  
  while(parentOfCurrNode != nullptr) {
  	//cout << parentOfCurrNode->JourneyCode << endl;
  	if (parentOfCurrNode->left==nullptr && parentOfCurrNode->right==nullptr) {
  		//cout << "entered this0\n";
  		parentOfCurrNode->shortestPathLength=0;
  		parentOfCurrNode->longestPathLength=0;
  	}
  	else if (parentOfCurrNode->left==nullptr && parentOfCurrNode->right!=nullptr)
  	{
  		//cout << "entered this1\n";
  		parentOfCurrNode->shortestPathLength=0;
  		parentOfCurrNode->longestPathLength=(parentOfCurrNode->right->longestPathLength)+1;
  	}
  	else if (parentOfCurrNode->left!=nullptr && parentOfCurrNode->right==nullptr)
  	{
  		//cout << "entered this2\n";
  		parentOfCurrNode->shortestPathLength=0;
  		parentOfCurrNode->longestPathLength=(parentOfCurrNode->left->longestPathLength)+1;
  	}
  	else {
  		if(parentOfCurrNode->left->shortestPathLength < parentOfCurrNode->right->shortestPathLength) 
				parentOfCurrNode->shortestPathLength = parentOfCurrNode->left->shortestPathLength+1;
			else
				parentOfCurrNode->shortestPathLength = parentOfCurrNode->right->shortestPathLength+1;
			
			if(parentOfCurrNode->left->longestPathLength < parentOfCurrNode->right->longestPathLength)
				parentOfCurrNode->longestPathLength = parentOfCurrNode->right->longestPathLength+1;
			else
				parentOfCurrNode->longestPathLength = parentOfCurrNode->left->longestPathLength+1;
  	}
  	parentOfCurrNode=parentOfCurrNode->parent;
  }
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  struct TreeNode* curr=root;
  while (curr != nullptr) {
		if (curr->JourneyCode < JourneyCode)
			curr=curr->right;
		else if (curr->JourneyCode > JourneyCode)
			curr=curr->left;
		else if ((curr->JourneyCode == JourneyCode) && (curr->price == price))
			return true;
  }
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
	
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
        cout << root->JourneyCode << /*" S-" << root->shortestPathLength << " L-" << root->longestPathLength <<*/  endl;
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

