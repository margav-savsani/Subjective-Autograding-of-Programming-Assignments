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
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}



bool BST::searchForJourney(int JourneyCode) {
    TreeNode *curr = root;

    if (root == nullptr){
        return false;
    }
    else{
        if (curr->JourneyCode == JourneyCode){
            return true;
        }

        root = curr->left;

        if(searchForJourney(JourneyCode)){
            return true;
        }

        root = curr->right;

        if(searchForJourney(JourneyCode)){
            return true;
        }
        root = curr;
        return false;
    }
} 


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


bool BST::insert(int JourneyCode, int price) { 
    if (searchForJourney(JourneyCode)){
        return false;
    }


    TreeNode *parent_node = nullptr;
    TreeNode *child_node = root;
    TreeNode *node_to_insert = new TreeNode(JourneyCode, price);

    while(child_node != nullptr){
        parent_node = child_node;
        if (price >= child_node->price){
            child_node = child_node->right;
        }
        else{
            child_node = child_node->left;
        }
    }
    
    node_to_insert->parent = parent_node;
    if (parent_node == nullptr){
        root = node_to_insert;
    }
    else if(price>=parent_node->price){
        parent_node->right = node_to_insert;
    }
    else{
        parent_node->left = node_to_insert;
    }
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {

    TreeNode *curr = root;
    while (curr != nullptr && curr->JourneyCode!=JourneyCode){
        if (price >= curr->price){
            curr = curr->right;
        }
        else{
            curr = curr->left;
        }
    }
    if (curr == nullptr){
        return false;
    }
    else if (curr->price != price){
        return false;
    }
    return true;

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

// Assumed with TA confirmation that delete only when whole entry found. Otherwise return false



bool BST::remove(int JourneyCode, int price) {
    TreeNode *parent_node = nullptr;
    TreeNode *child_node = root;

    while(child_node != nullptr && child_node->JourneyCode!=JourneyCode){
        parent_node = child_node;
        if (price >= child_node->price){
            child_node = child_node->right;
        }
        else{
            child_node = child_node->left;
        }
    }

    if(child_node == nullptr){
        return false;
    }


    if (child_node->right == nullptr && child_node->left ==nullptr){//0 child case
        if(parent_node != nullptr){
            if (parent_node->right == child_node){
                parent_node->right = nullptr;
            }
            else{
                parent_node->left = nullptr;
            }
        }
        else{
            root = nullptr;
        }
    }
    else if (child_node->right == nullptr){ // 1 child case
        if(parent_node != nullptr){
            if (parent_node->right == child_node){
                parent_node->right = child_node->left;
            }
            else{
                parent_node->left = child_node->left;
            }
        }
        else{
            root = child_node->left;
        }
        child_node->left->parent = parent_node;

        
    }
    else if (child_node->left == nullptr){
        if(parent_node != nullptr){
            if (parent_node->right == child_node){
                parent_node->right = child_node->right;
            }
            else{
                parent_node->left = child_node->right;
            }
        }
        else{
            root = child_node->right;
        }
        child_node->right->parent = parent_node;
        
    }

    else{ //2 child case

        TreeNode *curr = child_node->right;
        TreeNode *curr_parent = child_node;

        while (curr->left != nullptr){
            curr_parent = curr;
            curr = curr->left;
        }

        if (curr->right != nullptr){
            curr->right->parent = curr_parent;
        }
        if (curr_parent!=child_node){
            curr_parent->left = curr->right;
        }

        curr->parent = parent_node;

        if (parent_node != nullptr){
            if(parent_node->right == child_node){
                parent_node->right = curr;
            }
            else{
                parent_node->left = curr;
            }
        }
        else{
            root = curr;
        }

        if (child_node->right!= curr){
            curr->right = child_node->right;

            child_node->right->parent = curr;
        }

        curr->left = child_node->left;

        child_node->left->parent = curr;

     
    

    }
    delete child_node;



    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal==0){ //preorder
        TreeNode *curr = root;

        if (root == nullptr){
            return;
        }
        else{
            curr->visit();
            root = curr->left;
            traverse(0);
            root = curr->right;
            traverse(0);
            root = curr;
        }
    }
    else if (typeOfTraversal==1){ //postorder
        TreeNode *curr = root;

        if (root == nullptr){
            return;
        }
        else{
            root = curr->left;
            traverse(1);
            root = curr->right;
            traverse(1);
            root = curr;
            curr->visit();
        }
    }
    else if (typeOfTraversal==2){ //inorder
        TreeNode *curr = root;

        if (root == nullptr){
            return;
        }
        else{
            root = curr->left;
            traverse(2);
            curr->visit();
            root = curr->right;
            traverse(2);
            root = curr;

        }
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *curr = root;
    while (curr->left != nullptr){
        curr = curr->left;
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
