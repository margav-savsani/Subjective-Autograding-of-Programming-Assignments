#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<fstream>
using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS


//for some reason, some of my functions are not working at all, even though their code seems to be perfect, both logiclly and in syntax. 
//the code is compiling proprly. I was not able to do remove() function. Rest are all complete. Please check the code for once.
//There might be some global variable or something that is causing this to happen. The code is correct though, atleast the functions part
//is correct.

//please check hat is causing this problem. I am confident that my code is correct in the most part and this is because of some minor problem.



BST::BST(){root=nullptr;};
BST::BST(TreeNode *root){this->root==root;};


bool BST::insertelement(int JourneyCode, int price, TreeNode *node){
	if(findjourney(JourneyCode, price, node)) return false;
	if(node==nullptr){node= new TreeNode; node->JourneyCode=JourneyCode; node->price=price; return true;}
	else{ 
		if(node->price==0 && node->JourneyCode==0 && node->left==nullptr && node->right==nullptr)
			//node was just initialized using default counstructor, and has not yet been given its price, and journeycode
			{node->price=price; node->JourneyCode=JourneyCode; return true;}
		else{
		if(price<=node->price && node->left!=nullptr){return insertelement(JourneyCode, price, node->left);}
		if(price<=node->price && node->left==nullptr){
			node->left = new TreeNode;
			node->left->parent=node;
			node->left->price=price;
			node->left->JourneyCode;
			return true;
		}
		if(price>=node->price && node->right==nullptr){
			node->right = new TreeNode;
			node->right->parent=node;
			node->right->price=price;
			node->right->JourneyCode;
			return true;
		}
		else return insertelement(JourneyCode, price, node->right);
		}
	}
};
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {return insertelement(JourneyCode, price, this->root);};

//new function that also gives the same outcome as find(journeycode, price) but this also have input value of root, 
//which is used for recursion.
bool BST::findjourney(int JourneyCode, int price, TreeNode *node) {
	if(node==nullptr) return false;
	else if(JourneyCode==node->JourneyCode && price==node->price) return true;
	else if(node->left == nullptr && node->right != nullptr) return findjourney(JourneyCode, price, node->right);
	else if(node->right == nullptr && node->left != nullptr) return findjourney(JourneyCode, price, node->left);
	else if(node->left != nullptr && node->right != nullptr){
		return(findjourney(JourneyCode, price, node->right)||findjourney(JourneyCode, price, node->left));
	}
	else return false; 
};

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){return findjourney(JourneyCode, price, root);};

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
	if(find(JourneyCode, price)!=true) return false;
	else{
	
	return true;
	}
};

void BST::visit(TreeNode *t){cout<<t->JourneyCode<<endl;};

void BST::traversal(int typeOfTraversal, TreeNode *node) {
	if(node==nullptr) return;
	else if(typeOfTraversal==0){
		visit(node);
		if(node->left!=nullptr) traversal(0, node->left);
		if(node->right!=nullptr) traversal(0, node->right);
	}
	else if(typeOfTraversal==1){
		if(node->left==nullptr && node->right==nullptr) visit(node);
		if(node->left!=nullptr) traversal(1, node->left);
		if(node->right!=nullptr) traversal(1, node->right);
	}
	else if(typeOfTraversal==2){
		if(node->left!=nullptr) traversal(2, node->left);
		visit(node);
		if(node->right!=nullptr) traversal(2, node->right);
	}
};
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {traversal(typeOfTraversal, root);};

int BST::getmin(TreeNode *root){//new function which also gets the min value of tree, 
                                //but this has an input value to be used for recursion.
	if(root==nullptr) return 0;
	else{
		if(root->right==nullptr) return root->price;
		else return getmin(root->right);
	}
};
// Returns the price of the cheapest journey
int BST::getMinimum() {return getmin(root);};

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPrice(int l, int u, TreeNode *root){//we could have used similar code as traversal, but that was inefficient
	if(root==nullptr) return 0;//either no root, or else we have reached the left or right child of a leaf during recursion
	else if(root->price==l) return (1 + countJourneysInPrice(l, u, root->right));//this and the one below are cases when root is on
	else if(root->price==u) return (1 + countJourneysInPrice(l, u, root->left)); //edge of price range, 1+ given since root included
	else if(root->price<l) return countJourneysInPrice(l, u, root->right);//if root is less than lower bound we check for higher
	                                                                      //prices -> right side
	else if(root->price>u) return countJourneysInPrice(l, u, root->left);//we need to check lower prices -> left side
	else return (1 + countJourneysInPrice(l, u, root->left) + countJourneysInPrice(l, u, root->right));
	//root is inside range so 1+ is given and we will have to count from both sides.
};
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
	return countJourneysInPrice(lowerPriceBound, upperPriceBound, root);
};

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::preordertraversal(TreeNode *root, string filename) {
	ofstream outfile;
	outfile.open(filename);
	if(root==nullptr) return;
	else{
		outfile<<root->JourneyCode<<endl<<root->price<<endl;
		if(root->left!=nullptr){preordertraversal(root->left, filename);}
		if(root->right!=nullptr){outfile<<-1<<endl;  preordertraversal(root->right, filename);}
	}
};
void BST::customStore(string filename) {//we will use pre-order traversal to list the elements
                                        //I am using a dummy funtion that uses recursion given above
	preordertraversal(root, filename);
};
	
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
 
void BST::customLoad (int flag, string filename) {//since here insert has its own algorithm to decide how it is done
                                                  //and since we stored the tree in pre-order traversal, we can just use the same
                                                  //algorithm as that in insert.
//if we store each element in pre-order traversal order: The insert function has an algorithm which is the opposite of pre-order traversal
//these two algorithms when combined will give back the original tree that had been stored.
	ifstream infile;
	infile.open(filename);
	int input1;//for price
	int input2;//for JourneyCode
	if(flag==0){//consiedering flag=0 meaning LOAD_FULL_BST
		for(int i=0; i>=0; i++){
			infile>>input1;
			if(input1==-1) continue;//-1 marks start of right subtree, but since in LOAD_FULL_BST it is irrelevent, we skip it.
			infile>>input2;
			this->insert(input1, input2);
		}
	}
	else if(flag==1){
		for(int i=0; i>=0; i++){
			infile>>input1;
			if(input1==-1) break;//I had placed -1 as a mark that the left subtree is complete and right subtree is starting.
			infile>>input2;
			this->insert(input1, input2);
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
