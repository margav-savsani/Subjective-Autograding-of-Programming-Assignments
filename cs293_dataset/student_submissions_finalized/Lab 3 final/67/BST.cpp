#include <bits/stdc++.h>
#include <fstream>
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

BST::BST(){ // Initializing empty BST
	root=NULL;
}
BST::BST(TreeNode *root){
	this->root=root;
}
// Returns the node with minimum price in the tree after node
TreeNode* BST::getMinimum(TreeNode* node){
	if(node->left==NULL)	return node;
	return getMinimum(node->left);// Recursion
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
	TreeNode* curr=root;
	while(curr){
		if(curr->JourneyCode==JourneyCode && curr->price==price)	return false; // if curr is same as to be inserted
		if(price<=curr->price && curr->left){//if insertion is to be done on left
			curr=curr->left;
			continue;
		}
		if(price>curr->price && curr->right){// if insertion is to be done on right
			curr=curr->right;
			continue;
		}
		// if node to be inserted is child of node
		if(price>curr->price){
			curr->right=new TreeNode(JourneyCode,price,NULL,NULL,curr);
			return true;
		}
		curr->left=new TreeNode(JourneyCode,price,NULL,NULL,curr);
		return true;
	}
	// arrives here if tree is empty.
	root=new TreeNode(JourneyCode,price,NULL,NULL,NULL);
	return true;
}

TreeNode* BST::search_node(int price){ // Search for the first node with price as value
	TreeNode* curr=root;
	while(curr){
		if(curr->price==price){
			return curr;
		}
		if(price<curr->price){
			curr=curr->left;
			continue;
		}
		if(price>curr->price){
			curr=curr->right;
			continue;
		}
	}
	return curr;
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
	TreeNode* curr=search_node(price);
	while(curr){
		if(curr->JourneyCode==JourneyCode && curr->price==price)	return true;
		if(curr->price<price){
			curr=curr->right;
			continue;
		}
		curr=curr->left;
	}
	return false;
}
	
void BST::removeNode(TreeNode* node){ // removes the node
	TreeNode* par=node->parent;
	if(!node->left){
		if(!node->right){
			if(par->right == node){
				par->right=NULL;
				delete node;
				return;
			}
			par->left=NULL;
			delete node;
			return;
		}
		if(!node->parent){
			root=node->right;
			delete node;
			return;
		}
		if(node->parent->right==node){
			par->right=node->right;
			node->right->parent=par;
			delete node;
			return;
		}
		par->left=node->right;
		node->right->parent=par;
		delete node;
		return;
	}
	if(!node->left->right){ // if left of node is it's predecessor
		TreeNode* to_remove=node->left;
		node->JourneyCode=to_remove->JourneyCode;
		node->price=to_remove->price;
		node->left=to_remove->left;
		if(node->left)	node->left->parent=node;
		delete to_remove;
		return;
	}
	// If predecessor is right of it's parent
	TreeNode* replacement=getMaximum(node->left);
	replacement->parent->right=replacement->left;
	node->JourneyCode=replacement->JourneyCode;
	node->price=replacement->price;
	if(replacement->left)	replacement->left->parent=replacement->parent;
	delete replacement;
	return;
}

// Returns node with max price in tree after node
TreeNode* BST::getMaximum(TreeNode* node){
	if(node==NULL)	return NULL;
	if(node->right==NULL)	return node;
	return getMaximum(node->right);
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { //Incomplete
	if(root==NULL)	return false;
	if(root->JourneyCode==JourneyCode && root->price==price){
		if(root->left==NULL){
			root=root->right;
			if(root)	root->parent=NULL;
			return true;
		}
	}
	TreeNode* curr=search_node(price);
	while(curr){
		if(curr->JourneyCode==JourneyCode && price==curr->price){
			removeNode(curr);
			return true;
		}
		if(curr->price<price){
			curr=curr->right;
			continue;
		}
		curr=curr->left;
	}
	return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(root==NULL)	return;
	TreeNode* curr=root;
	if(typeOfTraversal==PRE_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr->left;
	traverse(typeOfTraversal);
	if(typeOfTraversal==IN_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr->right;
	traverse(typeOfTraversal);
	if(typeOfTraversal==POST_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr;
	return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	return getMinimum(root)->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){ // Does a traversal and counts the required number of nodes
	if(root==NULL){
		return 0;
	}
	int count=0;
	if(root->price<=upperPriceBound && root->price >= lowerPriceBound)	count+=1;
	TreeNode* preserved=root;
	root=preserved->left;
	count+=countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
	root=preserved->right;
	count+=countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
	root=preserved;
	return count;
}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
	ofstream fout;
	fout.open(filename,ios_base::app);
	TreeNode* preserved=root;
	fout<<root->JourneyCode<<" "<<root->price<<endl;
	if(preserved->left){
		root=preserved->left;
		customStore(filename);
	}
	if(preserved->right){
		root=preserved->right;
		customStore(filename);
	}
	fout<<-1<<endl; //put a -1 when a corresponding sub-tree is printed.
	fout.close();
	root=preserved;
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
 
void BST::customLoad (int flag, string filename){
	root=NULL;
	ifstream fin;
	fin.open(filename);
	root=new TreeNode();
	root->parent=NULL;
	fin>>root->JourneyCode>>root->price;
	int tree_progress=0;
	TreeNode* curr=root;
	int next;
	fin>>next;
	while(!fin.eof()){
		if(curr==root){
			if(tree_progress==0)	tree_progress=1;
			else if(tree_progress==1){
				if(flag==LOAD_LEFT_SUBTREE){
					root=root->left;
					break;
				}
				tree_progress=2;
			}
			else if(tree_progress==2){
				break;
			}
		}
		if(next==-1){ // When -1 is there in the file, the sub-tree is completed, now go to it's parent to complete
			curr=curr->parent;
			fin>>next;
			continue;
		}
		int JourneyCode=next;
		int price;
		fin>>price;
		if(curr->price>=price){
			curr->left=new TreeNode(JourneyCode,price,NULL,NULL,curr);
			curr=curr->left;
		}
		else{
			curr->right=new TreeNode(JourneyCode,price,NULL,NULL,curr);
			curr=curr->right;
		}
		fin>>next;
	}
	fin.close();
	return;


}


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
