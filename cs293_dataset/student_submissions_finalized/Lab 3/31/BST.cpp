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


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root=NULL;
}


BST::BST(TreeNode *root){
    this->root = root;   
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* node = new TreeNode(JourneyCode,price);
    TreeNode *y, *x;
    y=NULL;
    x=root;
    bool k=false;
    while(x!=NULL){
        y=x;
        if(JourneyCode == (x->JourneyCode)){
            return false;
        }
        if(price< x->price){
            x=x->left;
        }
        else x=x->right;
    }

    node->parent=y;
    if(y==NULL){
        root=node;
    }
    else if(node->price<y->price){
        y->left=node;
    }
    else y->right=node;
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x=root;
    while(x!=NULL && !(price==x->price && JourneyCode==x->JourneyCode)){
        if(price<x->price){
            x=x->left;
        }
        else x=x->right;
    } 

    if(x==NULL)
        return false;
    else return true;
}

TreeNode* BST::successor(TreeNode* node){
    TreeNode* min=node->right;
    while(min->left != NULL){
        min=min->left;
    }

    TreeNode* y=node->parent;
    if(node->right==NULL)
        return min;
    y = node->parent;
    while(y!=NULL && node==y->right){
        node=y;
        y=y->parent;
    }
    return y;

}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    /*FIND*/
    TreeNode *found=root;
    while(found!=NULL && (price!=found->price && JourneyCode!=found->JourneyCode)){
        if(price<found->price){
            found=found->left;
        }
        else found=found->right;
    } 

    TreeNode *y,*x=NULL;
    y=NULL;
    /*REMOVING*/
    if(found==NULL){
        return false;
    }


    else{
        if(found->left==NULL || found->right==NULL)
            y=found;
        else y=successor(found);
        if(y->left != NULL)
            x=y->left;
        else x=y->right;
        if(x!=NULL)
            x->parent=y->parent;
        if(y->parent==NULL)
            root=x;
        else if(y==(y->parent)->left)
            (y->parent)->left=x;
        else  (y->parent)->right=x;
        if(y!=found){
            y->JourneyCode=x->JourneyCode;
            y->price=x->price;
        }
    }
    return true;

}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::preorder(TreeNode* node){
    if(node==NULL)
        return;
    else {  
        cout << node->JourneyCode << endl;
        preorder(node->left);
        preorder(node->right);
    }
}

void BST::postorder(TreeNode* node){
    if(node==NULL)
        return;
    else{ 
        postorder(node->left);
        postorder(node->right);
        cout << node->JourneyCode << endl;
    }
}

void BST::inorder(TreeNode* node){
    if(node==NULL)
        return;
    else{ 
        inorder(node->left);
        cout << node->JourneyCode << endl;
        inorder(node->right);
    }
}


void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorder(root);
    }
    else if(typeOfTraversal==1){
        postorder(root);
    }
    else if(typeOfTraversal==2){
        inorder(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* x=root;
    while(x->left != NULL){
        x=x->left;
    }

    if(x!=NULL)
        return x->price;
    else return -1;
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

