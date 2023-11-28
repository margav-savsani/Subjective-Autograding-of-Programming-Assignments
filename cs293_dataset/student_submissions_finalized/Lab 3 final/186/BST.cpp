#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// Name        : Atishay Jain
// Roll Number : 210050026
// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = nullptr; 
}
BST::BST(TreeNode *root){
    this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)) return false;
    TreeNode *newNode = new TreeNode(JourneyCode,price);
    TreeNode *y = nullptr;      // Using 2 pointers x and y to keep track
    TreeNode *x = root;         // of current Node and its parent
    while(x != nullptr){
        y = x;
        if(newNode->price < x->price) x = x->left;
        else x = x->right;
    }
    newNode->parent = y;
    if(y == nullptr) root = newNode;
    else if(newNode->price < y->price) y->left = newNode;
    else y->right = newNode;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){       
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return true; 
    else return false;
}

// To search for a node and return that Node
// Quite similar to find() function, just it returns that complete node
// instead of price of it
struct TreeNode *BST::searchNode(int JourneyCode, int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){      
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return x; 
    else return nullptr; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode,price)) return false;
    TreeNode *y = new TreeNode;
    TreeNode *x = new TreeNode;
    TreeNode *deleteNode = searchNode(JourneyCode,price);
    if(deleteNode->left == nullptr || deleteNode->right == nullptr){
        y = deleteNode;
    }
    else y = successor(deleteNode);
    if(y->left != nullptr) x = y->left;
    else x = y->right;
    if(x != nullptr) x->parent = y->parent;
    if(y->parent == nullptr) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    if(y != deleteNode){
        deleteNode->JourneyCode = y->JourneyCode;
        deleteNode->price = y->price;
    }
    return true;
}

// Returns the successor of the given Node
struct TreeNode *BST::successor(TreeNode *v){
    if(v->right != nullptr){
        return minNode(v->right);
    }
    TreeNode *y = v->parent;
    while(y != nullptr && v == y->right){
        v = y;
        y = y->parent;
    }
    return y;
}

// Returns the Node with minimum price
struct TreeNode *BST::minNode(TreeNode *v){
    while (v->left != nullptr){
        v = v->left;
    }
    return v; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        preOrder(root);
    }
    else if(typeOfTraversal == 1){
        postOrder(root);
    }
    else if(typeOfTraversal == 2){
        inOrder(root);
    }
    return; 
}

// PreOrder Traversel
void BST::preOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        cout << v->JourneyCode << endl;
        preOrder(v->left);
        preOrder(v->right);
        return;
    }
}

// PostOrder Traversel
void BST::postOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        postOrder(v->left);
        postOrder(v->right);
        cout << v->JourneyCode << endl;
        return;
    }
}

// InOrder Traversel
void BST::inOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        inOrder(v->left);
        cout << v->JourneyCode << endl;
        inOrder(v->right);
        return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = root;
    while (x->left != nullptr){
        x = x->left;
    }
    return x->price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    if(root == nullptr) return count;
    else{
        return countinRange(lowerPriceBound,upperPriceBound,root);
    }
}

// Helper function for countJourneysInPriceBound to use Recursion
int BST::countinRange(int lowerprice, int upperprice, TreeNode *v){
    if(v == nullptr) return 0;
    if(v->price < lowerprice){
        return countinRange(lowerprice,upperprice,v->right);
    }
    else if(v->price > upperprice){
        return countinRange(lowerprice,upperprice,v->left);
    }
    else{
        return  1 + countinRange(lowerprice,upperprice,v->right) + countinRange(lowerprice,upperprice,v->left);
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    storePreOrder(root, filename);
    return; 
}

// Helper function for customStore to use Recursion
// This function stores the current tree in its pre-order traversel into the file
// Also, whenever it encounters a left child = NULL, it prints '-10' as sentinel value
// for indicating left child as NULL and similarly '-20' for right child = NULL
void BST::storePreOrder(TreeNode *v, string filename){
    int sentinel_left = -10, sentinel_right = -20;  // Using -10 like a sentinel value for left null node 
    ofstream outfile;                               // and -20 for right null node
    outfile.open(filename,std::ios_base::app);
    if(v == nullptr){
        return;
    }                            // Storing the tree in Pre-Order Traversel into the file 'filename'
    else {
        outfile << v->JourneyCode << " " << v->price << endl;
        if(v->left == nullptr) {
            outfile << sentinel_left << " " << sentinel_left << endl;
        }
        storePreOrder(v->left, filename);
        if(v->right == nullptr){
            outfile << sentinel_right << " " << sentinel_right << endl;
        }
        storePreOrder(v->right, filename);
        outfile.close();
        return;
    }
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
    TreeNode *v = new TreeNode();   
    TreeNode *father = nullptr;
    root = v;
    ifstream infile;
    if(flag == LOAD_FULL_BST){      // Load directly from the file if we have to Load full BST
        infile.open(filename);
        makeTree(root,father,infile,filename);
    }
    else if(flag == LOAD_LEFT_SUBTREE){     // else skip the first input and load the rest
        int val1 = 0, val2 = 0;
        infile.open(filename);
        infile >> val1 >> val2;
        infile >> val1 >> val2;             // If input at 2nd line is -10 => left node of root is NULL
        if(val1 == -10 && val2 == -10) return;  // So just return as left SubTree is NULL
        else {              // else reopen the file and start making tree from taking input from 2nd line
            infile.close();
            infile.open(filename);
            infile >> val1 >> val2;         // Skipping the first input here
            makeTree(root,father,infile,filename);
        }
    }
    infile.close();
    return; 
}

// Make load for left subtree also work!!!!!!!!!!!!!!
void BST::makeTree(TreeNode *v, TreeNode *father, ifstream &infile, string filename){
    int val1, val2;
    infile >> val1 >> val2;
    if(val1 == val2 && val1 == -10){        // Make parent's left as NULL 
        father->left = nullptr;             // and return
        return;
    }
    if(val1 == val2 && val2 == -20){        // Make parent's right as NULL
        father->right = nullptr;            // and return
        return;
    }
    v->JourneyCode = val1;                  // else make the Current Node
    v->price = val2;
    v->parent = father;
    v->left = new TreeNode();
    makeTree(v->left,v,infile,filename);    // Then make its left subtree
    v->right = new TreeNode();
    makeTree(v->right,v,infile,filename);   // Then make its right subtree
    return;
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

        result.push_back(isLeft ? "├──" : "└──" );

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

