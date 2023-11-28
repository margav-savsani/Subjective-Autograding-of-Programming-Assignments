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
    TreeNode *y;
    y=new TreeNode;
    root=y; }
BST::BST(TreeNode *root1){
    root=root1;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)==1){return false;}
    else{
        TreeNode z;z.JourneyCode=JourneyCode;z.price=price;
        TreeNode *x,*y;x=root;y=NULL;
        while(x!=NULL){
            y=x;
            if(price<x->price){x=x->left;}
            else{x=x->right;}
        }
        z.parent=y;
        if(y==NULL){root=&z;return 1;}
        else{
            if(price<y->price){y->left=&z;}
            else{y->right=&z;}
            return 1;
        }

    }}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x;x=root;
    while(x!=NULL && price!=x->price){
        if(price<x->price){x=x->left;}
        else{x=x->right;}
    }
    if(x==NULL){return 0;}
    else{return 1;}
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode,price)==0){return false;}
    else{
        TreeNode *x;x=root;
    while(x!=NULL && price!=x->price){
        if(price<x->price){x=x->left;}
        else{x=x->right;}
    }
    TreeNode *y;y=x->parent;
    if(x->left==NULL && x->right==NULL){
        if(x->price<y->price){y->left=NULL;}
        else{y->right=NULL;}
        return 1;}
    if(x->left==NULL){TreeNode *z;z=x->right;
            if(x->price<y->price){y->left=z;z->parent=y;return 1;}
            else {y->right=z;z->parent=y;return 1;}
        }
    if(x->right==NULL){TreeNode *z;z=x->left;
            if(x->price<y->price){y->left=z;z->parent=y;return 1;}
            else{y->right=y;z->parent;return 1;}}
    TreeNode *su;
    if(x->right!=NULL){TreeNode *mi;mi=x->right;
    while(mi->left!=NULL){mi=mi->left;}
    su=mi;
    }
    else{TreeNode *mi;
    mi=x->parent;
    while(mi!=NULL && x==mi->right){
        x=mi;mi=mi->parent;
    }
    su=mi;
    }
    x->JourneyCode=su->JourneyCode;x->price=su->price;su=NULL;
    return 1;}
    
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
        BST le(root->left);BST ri(root->right);
        if(typeOfTraversal==2){
        if(le.root!=NULL && ri.root!=NULL){le.traverse(2);cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}
        else if(le.root==NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}
        else if(le.root!=NULL && ri.root==NULL){le.traverse(2);cout<<" "<<root->JourneyCode<<" ";}
        else{cout<<" "<<root->JourneyCode<<" ";}}

        else if(typeOfTraversal==1){
        if(le.root!=NULL && ri.root!=NULL){le.traverse(1);ri.traverse(1);cout<<" "<<root->JourneyCode<<" ";}
        else if(le.root==NULL && ri.root!=NULL){ri.traverse(1);cout<<" "<<root->JourneyCode<<" ";}
        else if(le.root!=NULL && ri.root==NULL){le.traverse(1);cout<<" "<<root->JourneyCode<<" ";}
        else{cout<<" "<<root->JourneyCode<<" ";}}
        
        else if(typeOfTraversal==0){
        if(le.root!=NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";le.traverse(2);ri.traverse(2);}
        else if(le.root==NULL && ri.root!=NULL){cout<<" "<<root->JourneyCode<<" ";ri.traverse(2);}
        else if(le.root!=NULL && ri.root==NULL){cout<<" "<<root->JourneyCode<<" ";le.traverse(2);}
        else{cout<<" "<<root->JourneyCode<<" ";}}
}
// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x;x=root;
    while(x->left!=NULL){x=x->left;}
    return x->price;}

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
