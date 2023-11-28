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
    root = NULL;
}

BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    //std::cout<< "inserting"<<endl;
    if (root == NULL){
        root = new TreeNode;
        root->JourneyCode = JourneyCode;
        root->price = price;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        return true;
        //std::cout<<"hmm"<<endl;
    }

    //std::cout<<"searching"<<endl;
    if( search_journey(JourneyCode) ){
        return false;
    }
    //std::cout<< "continuing"<<endl;
    if (root->price > price){

        if(root->left == NULL){
            
            root->left = new TreeNode;
            root->left->JourneyCode = JourneyCode;
            root->left->price = price;
            root->left->left = NULL;
            root->left->right = NULL;
            root->left->parent = root;
            return true;
        }

        else {
            BST left_child(root->left);
            return left_child.insert(JourneyCode, price);
        }


    }

    else if (root->price <= price){

        if(root->right == NULL){
            root->right = new TreeNode;
            root->right->JourneyCode = JourneyCode;
            root->right->price = price;
            root->right->left = NULL;
            root->right->right = NULL;
            root->right->parent = root;
            return true;
        }

        else {
            BST right(root->right);
            return right.insert(JourneyCode, price);            
        }
    }

    return false;
    
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if (root == NULL){
        return false;
    }    

    if(root->price == price){
        if(root->JourneyCode == JourneyCode){
            return true;
        }

        else {
            BST right(root->right);
            return right.find(JourneyCode, price);
        }
    }

    else if (root->price < price){
        BST right(root->right);
        return right.find(JourneyCode, price);
    }

    else{
        BST left(root->left);
        return left.find(JourneyCode, price);
    }
    

    return false;

}
	
//traverse entire tree to find journeycode
bool BST::search_journey(int JourneyCode){
    //std::cout<<"bruh"<<endl;
    if(root == NULL){
        return false;
    }

    else if (root->JourneyCode == JourneyCode)
    {
        return true;
    }
    
    //std::cout << "hi left"<<endl;
    BST left_child(root->left);
    if(left_child.search_journey(JourneyCode)){
        return true;
    }

    //std::cout<<"hi right"<<endl;
    BST right(root->right);

    if(right.search_journey(JourneyCode)){
        return true;
    }

    return false;    
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if( root == NULL ){
        return false;
    }

    if(root->price == price){
        if(root->JourneyCode == JourneyCode){
            //find predecessor and replace
            BST left(root->left);
            TreeNode* predecessor = left.getMaximum();
            predecessor->parent->right = predecessor->left;
            predecessor->parent = root->parent;
            predecessor->left = root->left;
            predecessor->right = root->right;
            
            if(root->parent->right ==  root){
                root->parent->right = predecessor;
            }
            else if(root->parent->left == root){
                root->parent->left = predecessor;
            }
            return true;
        }

        else {
            BST right(root->right);
            return right.remove(JourneyCode, price);
        }
    }

    else if (root->price < price){
        BST right(root->right);
        return right.remove(JourneyCode, price);
    }

    else{
        BST left(root->left);
        return left.remove(JourneyCode, price);
    }

    return false;

}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal = 2) {
    if( root == NULL){return;}

    if(typeOfTraversal == 0){
        std::cout << root->JourneyCode <<"\n";
        BST left(root->left);
        left.traverse(0);

        BST right(root->right);
        right.traverse(0);
    }

    else if (typeOfTraversal == 1){
        BST left(root->left);
        left.traverse(1);

        BST right(root->right);
        right.traverse(1);

        std::cout << root->JourneyCode << "\n";
    }

    else{
        BST left(root->left);
        left.traverse(2);

        std::cout << root->JourneyCode << "\n";

        BST right(root->right);
        right.traverse(2);     

    }

    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    BST left_child(root->left);

    while ((left_child.root)->left != NULL){
        left_child = BST((left_child.root)->left);
    }

    return (left_child.root)->price;
}

TreeNode* BST::getMaximum(){
    BST right_child(root->right);

    while((right_child.root)->right != NULL){
        right_child = BST((right_child.root)->right);
    }

    return right_child.root;
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
