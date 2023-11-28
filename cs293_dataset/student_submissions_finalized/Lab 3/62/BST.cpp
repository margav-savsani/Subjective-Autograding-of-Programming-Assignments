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

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool TreeNode::copies(int jrnyCode){
    if (JourneyCode==jrnyCode) return true;
    if (left==NULL&&right==NULL) return false;
    if (left==NULL) return right->copies(jrnyCode);
    if (right==NULL) return left->copies(jrnyCode);
    return (right->copies(jrnyCode)|| left->copies(jrnyCode));
}

bool BST::insert(int JourneyCode, int price) {    
    if (root==NULL){
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    if (root->copies(JourneyCode)) return false;
    TreeNode* current=root;
    while(current!=NULL){
        if (price<current->price){
            if (current->left==NULL){
                current->left=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
                //TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent)
            }
            current=current->left;
        }
        else { // >=
            if (current->right==NULL){
                current->right=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
            }
            current=current->right;
        }
    }  

    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){        
        if (price<current->price){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }    
    if (current==NULL) return false;
    if (current->JourneyCode==JourneyCode) return true;
    else return false;
    //else return (BST(current->left).find(JourneyCode,price)||BST(current->right).find(JourneyCode,price));
    
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (root->JourneyCode==JourneyCode&&root->price==price){
        if (root->left==NULL&root->right==NULL){
            root=NULL;
            return true;
        } 
        else if (root->left==NULL) {
            root->right->parent=NULL;
            root=root->right;
            return true;
        }
        else if(root->right==NULL){
            root->left->parent=NULL;
            root=root->left;
            return true;
        }
    }
    TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){
        if (price<current->price){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }    
    if (current==NULL) return false;    
    if (current->JourneyCode!=JourneyCode) return false;
    
    current->rem();
    return true; 
    
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (root==NULL) return;
    switch (typeOfTraversal){
        case PRE_ORDER:{
            cout<<root->JourneyCode;
            {BST(root->left).traverse(typeOfTraversal);}
            {BST(root->right).traverse(typeOfTraversal);}
            break;
        }
        case POST_ORDER:{            
            {BST(root->left).traverse(typeOfTraversal);}
            {BST(root->right).traverse(typeOfTraversal);}
            cout<<root->JourneyCode;
            break;
        }
        case IN_ORDER:{
            {BST(root->left).traverse(typeOfTraversal);}
            cout<<root->JourneyCode;
            {BST(root->right).traverse(typeOfTraversal); }           
            break;
        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* current=root;
    for(;current->left!=NULL;current=current->left){}
    return current->price; // when null?
    //return 0; 
}

void TreeNode::rem(){
    if (parent!=NULL){
        if (left==NULL&&right==NULL){
            if(parent->left==this) parent->left=NULL;
            else parent->right=NULL;
        }
        else if (left==NULL){
            if(parent->left==this) parent->left=this->right;
            else parent->right=this->right;
            right->parent=this->parent;
            return;
        }
        else if(right==NULL){
            if(parent->left==this) parent->left=this->left;
            else parent->right=this->left;
            left->parent=this->parent;
            return;
        }
    }
    
    
    TreeNode* successor = succ_below();
    if (successor!=NULL){
        this->JourneyCode=successor->JourneyCode;
        this->price=successor->price;

        successor->rem();
    }
    return;
    
}

TreeNode* TreeNode::succ_below(){
    if (right==NULL) return NULL;

    TreeNode* get_least=right;
    for(;get_least->left!=NULL;get_least=get_least->left){}
    return get_least;
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
// takes one of two prices LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
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