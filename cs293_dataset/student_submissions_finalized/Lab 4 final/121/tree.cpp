// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<cassert>
using namespace std;

#include "tree.h"

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
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  if (root==nullptr){
    root = new TreeNode(JourneyCode, price);
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
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  assert(parentOfCurrNode!=nullptr);
  currNode=new TreeNode(JourneyCode, price);
  currNode->parent=parentOfCurrNode;
  if (JourneyCode > parentOfCurrNode->JourneyCode){    
    parentOfCurrNode->right=currNode;
    return true;
  }
  if (JourneyCode < parentOfCurrNode->JourneyCode){
    parentOfCurrNode->left=currNode;
    return true;
  }
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
 if(root==NULL) return false; 
 if(root->price==price && root->JourneyCode==JourneyCode){
 return true;
 }
 if(root->price < price){
 BST right_subtree(root->right);
 return right_subtree.find(JourneyCode, price); 
 }
 if(root->price>=price){
 BST left_subtree(root->left);
 return left_subtree.find(JourneyCode, price);
 } 
 return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
	//trivial case
	if(root==nullptr) return false;
	//if ticket is on left of root (if there is)
	if(root->price > price) {
		if (root->left==NULL) return false;
		BST left_subtree(root->left);
		return left_subtree.remove(JourneyCode, price);
	}
	//if ticket is on right of root (if there is)
	if(root->price < price){
		if (root->right == nullptr) return false;
		BST right_subtree(root->right);
		return right_subtree.remove(JourneyCode, price);
	}
	if(root->price==price){
	//if ticket has same price but different JourneyCode, it is in the left subtree (convention of insertion)
		if(root->JourneyCode!=JourneyCode){
		if(root->left==nullptr) return false;
		BST left_subtree(root->left);
		return left_subtree.remove(JourneyCode, price);
 		}
		//this means that current node (root) is the ticket
		else{
		//if root is a leaf
			if((root->left==nullptr) && (root->right==nullptr)){
			if(root->parent==nullptr){ //if we are removing the only node in tree
			root = nullptr;
			return true;
 	}
	//if leaf is on left of parent
	if (root->price <= root->parent->price) {
		root->parent->left = nullptr;
		delete root;
		return true;
		}
	//if leaf is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = nullptr;
	delete root;
	return true;
	}
	}
	//if root has one child
	if(root->left==nullptr){
	//if node is root of tree
	if(root->parent==nullptr){
	root=root->right;
	root->parent=nullptr;
	return true;
	}
	//if node is on left of parent
	if (root->price <= root->parent->price) {
	root->parent->left = root->right;
	root->right->parent=root->parent;
	delete root;
	return true;
	}
	//if node is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = root->right;
	root->right->parent=root->parent;
	delete root;
	return true;
	}
	}
	if(root->right==nullptr){
	//if node is root of tree
	if(root->parent==nullptr){
	root=root->left;
	root->parent=nullptr;
	return true;
	}
	//if node is on left of parent
	if (root->price <= root->parent->price) {
	root->parent->left = root->left;
	root->left->parent=root->parent;
	delete root;
	return true;
	}
	//if node is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = root->left;
	root->left->parent=root->parent;
	delete root;
	return true;
	}
	}
	
	//if root has 2 children
	//locating node in left with highest price
	TreeNode* pred = root->left;
	while(pred->right!=nullptr){
	pred=pred->right;
	}
	//pred is left child of node
	if(pred==root->left){
	//parent of pred
	root->right->parent=pred;
	//updating child of parent
	if (root->parent!=nullptr){
	//root is left child of parent
	if (root->price <= root->parent->price){
	root->parent->left=pred;
	}
	//root is right child of parent
	if (root->price > root->parent->price){
	root->parent->right=pred;
	}
	}
	//parent of right child
	root->right->parent=pred;
	return true; 
	}

	// //if node is root of tree
	// if (root->parent==nullptr);
	// root->right->parent=pred;
	// root->left->parent=pred;

	//now, pred is for sure rightmost point of left subtree
	pred->parent->right=pred->left;
	if(pred->left!=nullptr) pred->left->parent=pred->parent;
	//if root has no parent
	if(root->parent==nullptr){
	if(root->right!=nullptr) root->right->parent=pred;
	root->left->parent=pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=nullptr;
	delete root;
	return true;
	}
	//root is in left of parent
	if(root->price <= root->parent->price){
	root->parent->left = pred;
	root->left->parent = pred;
	if(root->right!=nullptr) root->right->parent = pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=root->parent;
	}
	//root right of parent
	if(root->price > root->parent->price){
	root->parent->right = pred;
	root->left->parent = pred;
	if(root->right!=nullptr) root->right->parent = pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=root->parent;
	}
	delete root;
	return true;
	}
	}
	return true;
}

int BST::MAX(TreeNode* n){
  if (n==nullptr) return -1;
  if (n->right==nullptr && n->left==nullptr){
    return 0;
  }
  int r_max, l_max;
  r_max = MAX(n->right);
  l_max = MAX(n->left);
  if(r_max>=l_max){
    return r_max+1;
  }
  else return l_max+1;
}

int BST::MIN(TreeNode* n){
  if (n==nullptr) return -1;
  if (n->right==nullptr && n->left==nullptr){
    return 0;
  }
  int r_min, l_min;
  r_min = MIN(n->right);
  l_min = MIN(n->left);
  if(r_min<=l_min){
    return r_min+1;
  }
  else return l_min+1;
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

