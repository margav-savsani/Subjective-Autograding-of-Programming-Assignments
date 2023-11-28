#include<set>
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

BST::BST(){; }
BST::BST(TreeNode *root){
    this->root=root;
}

TreeNode* BST::search(TreeNode* node,int JourneyCode,int price){
    if(node==nullptr) return nullptr;
    if(node->JourneyCode == JourneyCode) return node;
    if(node->price > price) return search(node->left,JourneyCode,price);
    return search(node->right,JourneyCode,price);
}
TreeNode* BST::insert(TreeNode* node, int jc,int p)
{
    if (node == nullptr) return new TreeNode(jc,p);

    if (p < node->price) node->left = insert(node->left, jc, p);

    else node->right = insert(node->right, jc,p);
 
    return node;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(BST::search(root,JourneyCode,price)!=nullptr) return false;
    else{
        root=insert(root,JourneyCode,price);
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(BST::search(root,JourneyCode,price)!=nullptr && BST::search(root,JourneyCode,price)->price==price) return true;
    
    return false;
}
	
TreeNode* BST::del(TreeNode* node,int jc,int p){
    if(node->price==p){
        if (node->left==nullptr and node->right==nullptr) return nullptr;
            
        else if (node->left == nullptr) {
            TreeNode* temp = node->right;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            return temp;
        }
    }
    else if(node->price <p) node->right = del(node->right,jc,p);
    else node->left = del(node->left,jc,p);
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(BST::search(root,JourneyCode,price)==nullptr) return false;
    else{
        root=BST::del(BST::search(root,JourneyCode,price),JourneyCode,price);
        return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preOrder(TreeNode* node){
    if(node==nullptr) return;
    cout<<node->JourneyCode<<endl;
    preOrder(node->left);
    preOrder(node->right);
}
void BST::postOrder(TreeNode* node){
    if(node==nullptr) return;
    postOrder(node->left);
    postOrder(node->right);
    cout<<node->JourneyCode<<endl;
}
void BST::inOrder(TreeNode* node){
    if(node==nullptr) return;
    inOrder(node->left);
    cout<<node->JourneyCode<<endl;
    inOrder(node->right);
}


void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) BST::preOrder(root);
    else if(typeOfTraversal==1) BST::postOrder(root);
    else BST::inOrder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==nullptr) return 0;
    TreeNode* temp=root;
    while(true){
        if(temp->left==nullptr) return temp->price;
        temp=temp->left;
    }
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
