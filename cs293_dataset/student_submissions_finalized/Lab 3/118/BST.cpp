#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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

BST::BST(){
	root=nullptr; //To initialise the root prt to NULL
 }
 //To initialise the root pointer to the one passed by the user
BST::BST(TreeNode *root){
	this->root=root;
	this->root->parent=nullptr;
}

//To check whether any of the entries have this journey code by checking each element recursively
bool BST::find_JC(int *JourneyCode, TreeNode *node){
	if(node==nullptr)
		return false;
	else if(node->JourneyCode==*JourneyCode)
		return true;
	else
		return(find_JC(JourneyCode, node->left)||find_JC(JourneyCode, node->right));
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	//Checks whether there is tree or not
	//If not, creates the entry at the root
	if(root==nullptr){
		root=new TreeNode(JourneyCode, price);
		root->parent=nullptr;
		return true;
	} 
	TreeNode *curr=root;
	//To check whether an entry with the same journey code exists
	if(find_JC(&JourneyCode, root))
		return false;
	//while loop to find the location of insertion
	while(true){
		if(price<=curr->price){
			if(curr->left==nullptr){
				curr->left=new TreeNode(JourneyCode, price);
				curr->left->parent=curr;
				return true;
			}
			curr=curr->left;
		}
		else{
			if(curr->right==nullptr){
				curr->right=new TreeNode(JourneyCode, price);
				curr->right->parent=curr;
				return true;
			}
			curr=curr->right;
		}
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
	TreeNode *curr=root;
	//whike loop to find the entry with the given price
	//If such a entry is found, the journey codes are compared
	while(curr!=nullptr){
		if(price==curr->price){
			if(curr->JourneyCode==JourneyCode)
				return true;
			else
				curr=curr->left;
		}
		else if(price<curr->price)
			curr=curr->left;
		else
			curr=curr->right;
	}
	return false; 
}

void BST::delete_node(TreeNode *node){
	TreeNode **parent_ptr; //To store the pointer to the varaible which stores the address of the node we want to delete
	//Checks whether the node to be deleted is the root
	//If true, creates a temporary parent to the root and calls the function again
	if(node->parent==nullptr){
		TreeNode *root_parent;
		root_parent=new TreeNode(0,root->price-1,nullptr,root,nullptr);
		root->parent=root_parent;
		delete_node(root);
		root=root_parent->right;
		if(root!=nullptr)
			root->parent=nullptr;
		delete root_parent;
		return;
	}
	//To find the pointer to the variable which stores the address of the node we weant to delete
	if(node->price>node->parent->price) 
		parent_ptr=&(node->parent->right);
	else
		parent_ptr=&(node->parent->left);
	//Deletes teh node directly as it has no children
	if(node->left==nullptr && node->right==nullptr){
		*parent_ptr=nullptr;
		delete node;
	}
	//Deletes the node and puts its left child in its position
	else if(node->right==nullptr){
		*parent_ptr=node->left;
		node->left->parent=node->parent;
		delete node;
	}
	//Deletes the node and puts its right child in its position
	else if(node->left==nullptr){
		*parent_ptr=node->right;
		node->right->parent=node->parent;
		delete node;
	}
	//Deletes the node, find the node in its left subtree with the maximum price and then putis it in its position
	else{
		TreeNode *curr=node->left;
		//Checks whether the root of the left subtree is the node with the maximum price
		if(curr->right==nullptr){
			curr->right=node->right;
			if(node->right!=nullptr)
				node->right->parent=curr;
			curr->parent=node->parent;
			*parent_ptr=curr;
			delete node;
		}
		else{
			curr=curr->right;
			while(curr->right!=nullptr)
				curr=curr->right;
			*parent_ptr=curr;
			curr->parent->right=curr->left;
			if(curr->left!=nullptr)
				curr->left->parent=curr->parent;
			curr->parent=node->parent;
			curr->right=node->right;
			node->right->parent=curr;
			curr->left=node->left;
			node->left->parent=curr;
			delete node;
		}
	}
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	TreeNode *curr=root;
	//while loop to find the node to be deleted
	//After finding the node, it calls delete_node() to delete it
	while(curr!=nullptr){
		if(price==curr->price){
			if(curr->JourneyCode==JourneyCode){
				delete_node(curr);
				return true;
			}
			else
				curr=curr->left;
		}
		else if(price<curr->price)
			curr=curr->left;
		else
			curr=curr->right;
	}
	return false; 
}

//To print the tree in InOrder traversal format
void BST::in_Order(TreeNode *node){
	if(node!=nullptr){
		in_Order(node->left);
		cout<<node->JourneyCode<<endl;
		in_Order(node->right);
	}
}

//To print the tree in PreOrder traversal format
void BST::pre_Order(TreeNode *node){
	if(node!=nullptr){
		cout<<node->JourneyCode<<endl;
		pre_Order(node->left);
		pre_Order(node->right);
	}
}

//To print the tree in PostOrder traversal format
void BST::post_Order(TreeNode *node){
	if(node!=nullptr){
		post_Order(node->left);
		post_Order(node->right);
		cout<<node->JourneyCode<<endl;
	}
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	//if  statements to call the respective print functions
	if(typeOfTraversal==IN_ORDER){
		in_Order(root);
	}
	else if(typeOfTraversal==PRE_ORDER){
		pre_Order(root);
	}
	else if(typeOfTraversal==POST_ORDER){
		post_Order(root);
	}
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	TreeNode *curr=root;
	//while loop to find the left most element in the tree 
	while(curr->left!=nullptr)
		curr=curr->left;
	return curr->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
	int count=0;
	//Calls the countPrice function and prints the value returned
	countPrice(&lowerPriceBound,&upperPriceBound,root,&count);
	return count;
}

//To find the number of nodes whose price lieas between lb and ub
//It iterates through every node which has a reasonable chance to have a price between lb and ub
int BST::countPrice(int* lb, int* ub, TreeNode* node, int* count){
	if(node!=nullptr){
		if(*lb <= node->price <= *ub){
			*count++;
			countPrice(lb,ub,node->right,count);
			countPrice(lb,ub,node->left,count);
		}
		else if(*lb > node->price)
			countPrice(lb,ub,node->right,count);
		else
			countPrice(lb,ub,node->left,count);
	}
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
	ofstream outfile;
	outfile.open(filename);
	//To check if the tree is empty
	if(root==nullptr){
		outfile<<"n ";
	}
	else{
		outfile<<"y "<<root->JourneyCode<<" "<<root->price<<" ";
		TreeNode* curr=root;
		curr->cnt=3;
		//while loop to print the elements of the tree along with their relation to the previous entry
		while(root->cnt>1){
			if(curr->cnt==1){
				curr=curr->parent;
				outfile<<"p ";
			}
			else if(curr->cnt==2){
				curr->cnt--;
				if(curr->right!=nullptr){
					curr=curr->right;
					curr->cnt=3;
					outfile<<"r "<<curr->JourneyCode<<" "<<curr->price<<" ";
				}
			}
			else if(curr->cnt==3){
				curr->cnt--;
				if(curr->left!=nullptr){
					curr=curr->left;
					curr->cnt=3;
					outfile<<"l "<<curr->JourneyCode<<" "<<curr->price<<" ";
				}
			}
		}
		outfile<<"f";
	}
	outfile.close();
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
 
void BST::customLoad (int flag, string filename) {
	ifstream infile;
	infile.open(filename);
	unsigned short int ck=0;
	int jc,p;
	char ch;
	//To check wether the tree stored was empty or not
	infile>>ch;
	if(ch=='n')
		return;
	if(root=nullptr){
		root=new TreeNode();
		root->parent=nullptr;
	}
	infile>>jc;
	root->JourneyCode=jc;
	infile>>p;
	root->price=p;
	TreeNode* curr=root;
	//if else statements to check whether teh entire tree or the left subtree have to be loaded
	if(flag==LOAD_FULL_BST)
		ck=2;
	else if(flag==LOAD_LEFT_SUBTREE){
		ck=1;
		infile>>ch;
		if(ch=='l'){
			infile>>jc>>p;
			curr->JourneyCode=jc;
			curr->price=p;
		}
		else{
			delete root;
			return;
		}
	}	
	//while loop to create the nodes of the tree
	while(ck>0){
		infile>>ch;
		if(ch=='l'){
			infile>>jc>>p;
			curr->left=new TreeNode(jc,p);
			curr->left->parent=curr;
			curr=curr->left;
			ck++;
		}
		else if(ch=='r'){
			infile>>jc>>p;
			curr->right=new TreeNode(jc,p);
			curr->right->parent=curr;
			curr=curr->right;
			ck++;
		}
		else if(ch=='p'){
			curr=curr->parent;
			ck--;
		}
		else{
			break;
		}
	}
	infile.close();
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
        result.push_back(root->JourneyCode + "\n");
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
