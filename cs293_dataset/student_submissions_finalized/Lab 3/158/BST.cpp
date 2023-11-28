#include <bits/stdc++.h>
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
using namespace std;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root = nullptr; ; }
BST::BST(TreeNode *root){this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
  struct TreeNode* curr= root;
  struct TreeNode* prev= root;
  if (root==nullptr){root = new struct TreeNode;
  	root->price = price;
        root->JourneyCode = JourneyCode;
        return true;
  }
  
  while(curr!=nullptr && curr->JourneyCode!=JourneyCode){
  	if(curr->price < price){
  		prev = curr;
  		curr = prev->right;
  	}
  	else {prev = curr;
  		curr=prev->left;}
  
  
  }
  if(curr==nullptr){
  	curr = new struct TreeNode;
  	curr->parent = prev;
  	if(prev->price < price){
  		curr->price = price;
        curr->JourneyCode = JourneyCode;
  		prev->right=curr;
  		return true;
  	}
  	else {curr->price = price;
        curr->JourneyCode = JourneyCode;
  		prev->left=curr;
  		return true;}
  
  }
  else
  return false;
  }
    

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
	struct TreeNode* curr= root;
  	struct TreeNode* prev= root;
	
	while(curr!=nullptr && curr->JourneyCode!=JourneyCode){
  	if(curr->price < price){
  		prev = curr;
  		curr = prev->right;
  	}
  	else {prev = curr;
  		curr=prev->left;}
  
  
  }
	if(curr->JourneyCode == JourneyCode){return true;}
	else return false;

 }
 
 struct TreeNode* BST::predecessor(struct TreeNode* node){
 	struct TreeNode* pre;
 	
 	
 	if (node->left != nullptr)
        {
            struct TreeNode* tmp = node->left;
            while (tmp->right!=nullptr)
                tmp = tmp->right;
            return tmp ;
        }
       
        
 	
 
 
 
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	TreeNode *curr=root, *prev=nullptr;
	
	
	// If root is not being removed:
	while(curr!=nullptr && curr->JourneyCode!=JourneyCode){
  	if(curr->price < price){
  		prev = curr;
  		curr = prev->right;
  	}
  	else {prev = curr;
  		curr=prev->left;}
  
  
  }
  if(curr->JourneyCode==JourneyCode && curr->price==price){
  	
  	// When Node is a LEAF
  	if (curr->left==nullptr && curr->right==nullptr){
  	
  		if(curr->price > prev->price){
  		
  		 prev->right = nullptr; return true;
  	}
  		else {
  		prev->left=nullptr; return true;
  	}
  	
  	}
  	
  	
  	// When Node has ONLY ONE RIGHT CHILD
  	
  	else if (curr->left==nullptr ){
  	curr->right->parent = prev;
  		if(curr->price > prev->price){
  		
  		 prev->right = curr->right; return true;
  	}
  		else {
  		prev->left=curr->right; return true;
  	}
  	
  	
  	}
  	
  	
  	//When NOde has only ONE LEFT CHILD
  	else if (curr->right==nullptr ){
  	cout<<"delhere";
  		if(curr->price > prev->price){
  			curr->left->parent = prev;
  		 prev->right = curr->left; 
  		 return true;
  	}
  		else {
  		curr->left->parent = prev;
  		prev->left=curr->left; return true;
  	}
  	
  	
  	}
  	
  	else {
  	if(predecessor(curr)!=curr->left){
  		 predecessor(curr)->parent->right = predecessor(curr)->left; 
  		 predecessor(curr)->left->parent =predecessor(curr)->parent->right;}
  		 predecessor(curr)->left=curr->left;
  		 curr->left->parent = predecessor(curr);
  		 curr->right->parent = predecessor(curr);
  		 predecessor(curr)->right = curr->right;
  	  if(curr->price > prev->price){
  		
  		 prev->right = predecessor(curr);
  		 predecessor(curr)->parent = prev;
  		 
  		 
  		 
  		
  		 
  		  return true;
  	}
  		else {
  		prev->left=predecessor(curr);
  		predecessor(curr)->parent = prev; 
  		return true;
  	}
  	
  	
  	}
  	
  	
  	
  	}
	else
		return false;
	
	

 
 }
 
 	void BST::preorder(struct TreeNode *l){
 		if (l==nullptr)return;
 		else{
 			cout<<l->JourneyCode<<" ";
 			preorder(l->left);
 			preorder(l->right);
 		
 		}
 	};
	void BST::postorder(struct TreeNode *l){
	if (l==nullptr)return;
 		else{
 			
 			postorder(l->left);
 			postorder(l->right);
 			cout<<l->JourneyCode<<" ";
 		
 		}
	};
	
	
	void BST::inorder(struct TreeNode *l){
	if (l==nullptr)return;
 		else{
 			
 			inorder(l->left);
 			cout<<l->JourneyCode<<" ";
 			inorder(l->right);
 			
 		
 		}
	
	};
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
if (typeOfTraversal==0)
	preorder(root);
else if (typeOfTraversal==1)
	postorder(root);
else
	inorder(root);
	
	
return;


}

 

// Returns the price of the cheapest journey
int BST::getMinimum() {
	struct TreeNode* curr=root;
	while(curr->left!=nullptr){
		
		curr=curr->left; 
	}
	return curr->price;
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
        root = curr;
        root = root->right;
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
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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

