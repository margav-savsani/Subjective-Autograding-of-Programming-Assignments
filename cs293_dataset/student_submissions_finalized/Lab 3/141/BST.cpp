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

// if node is uninitialised, its price and Journey code are set to 0 by default constructor. 
// I will check JourneyCode == 0.

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Memory : Each node insertion has memory already present for the root and alllocates memory for its immediate chilren. 

BST::BST(){
    // everything set to default values. 

    root = new TreeNode(); 
}

// this constructor is NOT used to allot memory. Segfault : Modified to allocation as well. It is only used for subtraversals. 
// memory allocation happens only in construction of BST and insertion

BST::BST(TreeNode *root){
    // root already contains information of linking before insertion. 
    // hence, only set the root as root of BST
    this->root = new TreeNode(root->JourneyCode, root->price, root->left, root->right, root->parent);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price) { 
    // assumption : if price is equal, element is included in the right subtree.
    // if the child is NULL , established parent, inserts in the null node. returns true
    // establishment of parent is done while insertion itself. 

    // base case i.e. first node. 
    // root has space allocated already, and knows that its parent is nullptr during construction itself.
    // if segfault, try *root = TreeNode(JourneyCode, price)
    // root can be nullptr if previously deleted. 
    
    if (root == nullptr){
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    
    if (root->JourneyCode == 0) {
        root = new TreeNode(JourneyCode, price);
        return true;
    }

    if (JourneyCode == root->JourneyCode){
        return false;
    }

    

    // if root is not nullptr, it will check its children beforehand, hence, no issues of wrong insertions. 

    if (price < root->price){
        
        // if the left child is NULL, insert this as the left child, else insert recursively

        // left subtree constructor assuming that the root of left subtree has some value stored. (i.e. leftptr is not nullptr)
        // if not, the insert function should insert there itself 

        if (root->left == nullptr) {
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            return true;
        }
        else {

            // left is not null hence left child has memory allocated. 

            BST leftchild(root->left);
            return leftchild.insert(JourneyCode, price);
        }
    }

    else if (price >= root->price){

        // if the right child is NULL, insert this as the right child, else insert recursively

        if (root->right == nullptr) {
            // this node is given information about parent during insertion. 
            root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            return true;
        }
        else {
            BST rightchild(root->right);
            return rightchild.insert(JourneyCode, price);
        }
    }

}

// from this point onwards memory has been allocated, so no issue will arise regarding segfaults.


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    cout << root->parent->JourneyCode << endl;
    // base case -- checking inside the root itself
    if (root == nullptr){

        // check in predecessor -- no need (we start by calling root of the tree.)
        return false;
    }
    if (root->JourneyCode == 0){
        return false;
    }
    //cout << "Outside check" << endl;
    // this is the root of some subtree. Which has some non-trivial value.
    if ((root->JourneyCode == JourneyCode) && (root->price == price)){
        //cout << "Inside correct node" << endl;
        return true;
    }  
    // if root is the "actual" node, it being set to nullptr might cause issues. Hence using TreeNode() here. 
    // can cause excess use of memory, however inlab so will optimise later. 

    
    // checking in the corresponding children depending upon the price. 
    if (price < root->price){

        // first check for null pointer. 
        if (root->left == nullptr) {
            return false;
        }
        else {
            BST leftchild(root->left);
            return leftchild.find(JourneyCode, price);
        }
    }
    else if (price >= root->price){
        if (root->right == nullptr) {
            return false;
        }
        else {
            //cout << "Pre recursive call" << endl;
            BST leftchild(root->right);
            //cout << "First recursive call" << endl;
            bool result = leftchild.find(JourneyCode, price);
            //cout << result << endl;
            return result;
        }
    }

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

// DELETION IS NOT THAT EASY
bool BST::remove(int JourneyCode, int price) { 
    
    // base case -- checking inside the root itself
    // sets the node to NULL upon deletion and the parent is a pointer so no need to update it.

    if (root == nullptr){
        return false;
    }

    // FOUND
    if ((root->JourneyCode == JourneyCode) && (root->price == price)){
        
        // now that the node is found, let us focus upon deleting it. 

        // LEAF NODE
        if ((root->left == nullptr) && (root->right == nullptr)){
            // memory allocation to this node will again happen during insertion, so we can safely set this to nullptr
            // it has no need of remembering its parent. 
            // parent of the root points to its child's memory, changing value of child has no effect on that.  
            
            // if the parent about to become the root node, the tree needs to know that. 
            
            root = nullptr;
            return true;
        }
        
        // ONE CHILD EXISTS ONLY
        else if ((root->left == nullptr) && (root->right != nullptr)) {
            
            // now we replace root with right memory. Memory allocation has been done for the node since it ain't null. 
            (root->right)->parent = root->parent;
            root = root->right;
            return true;
        }

        else if ((root->right == nullptr) && (root->left != nullptr)) {

            // now we replace root with left memory. 
            (root->left)->parent = root->parent;
            root = root->left;
            return true;
            
        }

        // neither of the nodes is null. 

        else {
            // find the node in the tree which is the predecessor. 
            // predecessor node is then deleted as well. 

            // WILL BE UPDATED.
            return false;

        }
    }  
    
    
    // FINDING
    // checking in the corresponding children depending upon the price. 
    if (price < root->price){

        // checking if the left subtree is there. 
        if (root->left == nullptr){
            return false;
        }
        else{
            BST leftchild(root->left);
            return leftchild.remove(JourneyCode, price);
        }
    }
    else if (price >= root->price){

        // checking if the right subtree is there
        if (root->right == nullptr){
            //cout << "Here" << endl;
            return false;
        }
        else{
            BST rightchild(root->right);
            //cout << "Iterations" << endl;
            return rightchild.remove(JourneyCode, price);
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    // traverses the tree and prints the journey codes corresponding to the traversal. 
    
    BST leftchild(root->left);
    BST rightchild(root->right);
    
    // base case
    if (root == NULL){return;}

    // PRE_ORDER case
    if (typeOfTraversal == 0){
        //cout << root->JourneyCode << endl;
        leftchild.traverse(typeOfTraversal);
        rightchild.traverse(typeOfTraversal);
    }

    // IN_ORDER case
    else if (typeOfTraversal == 1) {
        leftchild.traverse(typeOfTraversal);
        //cout << root->JourneyCode << endl;
        rightchild.traverse(typeOfTraversal);
    }

    // POST_ORDER case
    else if (typeOfTraversal == 2) {
        leftchild.traverse(typeOfTraversal);
        rightchild.traverse(typeOfTraversal);
        //cout << root->JourneyCode << endl;
    }

    return;
    
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    

    // if the tree is empty 0 is returned
    // base cases : assumption -- the price is positive
    if (root == nullptr){
        return 0;
    }
    
    // if the root does not have a left child then return the node's price, else, return the price of leftchild.
    if (root->left == NULL){
        return root->price;
    }
    else {
        BST leftchild(root->left);
        return leftchild.getMinimum();
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
