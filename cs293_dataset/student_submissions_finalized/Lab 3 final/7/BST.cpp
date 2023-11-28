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

BST::BST(){
    
    this->root = new TreeNode();
    
}
BST::BST(TreeNode *root){
    
    this->root = new TreeNode();
    this->root = root;
    
}

bool BST::recurse_insert(int JourneyCode, int price, TreeNode *node){   // extra function
    if((node != NULL)&&(node->JourneyCode == JourneyCode)){
        return false;
    }
    
    else if(node->JourneyCode == 0){   // node == NULL
        node->JourneyCode = JourneyCode;  // check here
        node->price = price;
        node->left = new TreeNode();
        node->right = new TreeNode();
        return true;
    }
    else if(price<= node->price){   // have kept equal to in left
        return recurse_insert(JourneyCode,price,node->left);
    }
    else if(price> node->price){
        return recurse_insert(JourneyCode,price,node->right);
    }
    
    return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    
    
    return this->recurse_insert(JourneyCode,price,this->root);
    
    return false;
    
}



bool BST::recurse_find(int JourneyCode, int price, TreeNode *node){
    if((node->JourneyCode != 0)&&(node->JourneyCode == JourneyCode)&&(node->price == price)){
        return true;
    }
    else if((node->JourneyCode != 0)&&(price<=node->price)){  // have kept equal to in left
        return this->recurse_find(JourneyCode,price,node->left);
    }
    else if((node->JourneyCode != 0)&&(price>node->price)){
        return this->recurse_find(JourneyCode,price,node->right);
    }
    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    
    return recurse_find(JourneyCode,price,this->root);
    
    return false;
    
}




bool BST::smallest(TreeNode *del_node, TreeNode *node){  // extra function removes the required element.
    if((node->left->JourneyCode == 0)&&(node->right->JourneyCode == 0)){
        //del_node = nullptr;
        //del_node = node;
        del_node->JourneyCode = node->JourneyCode;
        del_node->price = node->price;
        node = nullptr;
        node = new TreeNode();
        return true;
    }
    
 
    else if((node->left->JourneyCode == 0)&&(node->right->JourneyCode != 0)){
        //del_node = NULL;
        //del_node = node;
        del_node->JourneyCode = node->JourneyCode;
        del_node->price = node->price;
        node = node->right;
        //largest(node,node->right);   // check here.
        return true;
    }
    else return smallest(del_node,node->left);
    
}


bool BST::largest(TreeNode *del_node, TreeNode *node){  // extra function removes the required element.
    if((node->right->JourneyCode == 0)&&(node->left->JourneyCode == 0)){
        //del_node = nullptr;
        //del_node = node;
        del_node->JourneyCode = node->JourneyCode;
        del_node->price = node->price;
        node = nullptr;
        node = new TreeNode();
        return true;
    }
    
    else if((node->right->JourneyCode == 0)&&(node->left->JourneyCode != 0)){
        //del_node = NULL;
        //del_node = node;
        del_node->JourneyCode = node->JourneyCode;
        del_node->price = node->price;
        node = node->left;
        //smallest(node,node->left);   // check here.
        return true;
    }
    else return largest(del_node,node->right);
}


bool BST::recurse_remove(int JourneyCode, int price, TreeNode *node){
    if(node->JourneyCode == 0){
        return false;
    }
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left->JourneyCode == 0)&&(node->right->JourneyCode == 0)){   // case 1: when it doesnot have any child
        //node = nullptr;
        //node = new TreeNode();
        node->JourneyCode = 0;
        node->price = 0;
        return true;
    }

    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left->JourneyCode == 0)&&(node->right->JourneyCode != 0)&&(node->right->right->JourneyCode == 0)&& (node->right->left->JourneyCode == 0)){  // when it has exactly one child(right).
        
        //node = NULL;
        //node = node->right;
        node->JourneyCode = node->right->JourneyCode;
        node->JourneyCode = node->right->price;
        node->right = nullptr;
        node->right = new TreeNode();
        return true;
    }
    
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left->JourneyCode != 0)&&(node->right->JourneyCode == 0)&&(node->left->right->JourneyCode == 0)&& (node->left->left->JourneyCode == 0)){  // when it has exactly one child(left).
        
        //node = NULL;
        //node = node->left;
        node->JourneyCode = node->left->JourneyCode;
        node->price = node->left->price;
        node->left = nullptr;
        node->left = new TreeNode();
        return true;
    }
    
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left->JourneyCode != 0)){ //using predecessor to delete the JourneyCode by replacin it with predecessor(largest element in the left subtree)
        largest(node,node->left);
        
    }
    
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left->JourneyCode == 0)){
        //TreeNode *n;
        //n = new TreeNode();
        //n = node->right;
        //node = nullptr;
        //node = n;
        //n = nullptr;
//        node->JourneyCode = node->right->JourneyCode;
//        node->price = node->right->price;
//        node->right = node->right->right;
//        node->left = node->right->left;
        
        smallest(node, node->right);
        
        return true;
        
    }
    
    else if(price <= node->price){
        return this->recurse_remove(JourneyCode,price,node->left);
    }
    
    else if(price > node->price){
        return this->recurse_remove(JourneyCode,price,node->right);
    }
    
    return false;
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    
    return this->recurse_remove(JourneyCode,price,this->root);
    
    return false;
    
}




void BST::recurse_traverse_0(TreeNode *node){   // extra function
    if(node->JourneyCode != 0){
        cout << node->JourneyCode << endl;
        recurse_traverse_0(node->left);
        recurse_traverse_0(node->right);
    }
}

void BST::recurse_traverse_1(TreeNode *node){
    if(node->JourneyCode != 0){
        recurse_traverse_1(node->left);
        recurse_traverse_1(node->right);
        cout << node->JourneyCode << endl;
    }
}

void BST::recurse_traverse_2(TreeNode *node){
    if(node->JourneyCode != 0){
        recurse_traverse_2(node->left);
        cout << node->JourneyCode << endl;
        recurse_traverse_2(node->right);
    }
}


	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    
    if(typeOfTraversal == PRE_ORDER){
        this->recurse_traverse_0(this->root);
    }
    else if(typeOfTraversal == POST_ORDER){
        this->recurse_traverse_1(this->root);
    }
    else if(typeOfTraversal == IN_ORDER){
        this->recurse_traverse_2(this->root);
    }
    
}


int BST::recurse_getMinimum(TreeNode *node){
    if(node->left->JourneyCode == 0){
        return node->price;
    }
    else {
        return this->recurse_getMinimum(node->left);
    }
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    
    return recurse_getMinimum(this->root);
    
    return 0;
    
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.


int BST::cnt(int lower_bound, int upper_bound,TreeNode *node){
    int ct = 0;
    if((node->JourneyCode != 0)&&(node->price>=lower_bound)&&(node->price<=upper_bound))
        ct++;
    return (ct+(cnt(lower_bound,upper_bound,node->left))+cnt(lower_bound,upper_bound,node->right));
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    
    if(this->root->JourneyCode != 0)
        return cnt(lowerPriceBound,upperPriceBound,this->root);
    else
        return 0;
    
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.


void BST::store_left(ofstream &file, TreeNode *node){
    if(node->JourneyCode != 0){
        store(file,node->left);
        store(file, node->right);
        file << node->JourneyCode << " " << node->price << endl;
    }
    file << "X" << endl;   // sentenel value.
}


void BST::store(ofstream &file, TreeNode *node){  // Storing in inorder.
    if(node->JourneyCode != 0){
        store(file,node->left);
        
        store(file,node->right);
        
        file << node->JourneyCode << " " << node->price << endl;
    }
}


void BST::store_start(ofstream &file, TreeNode *node){  // Storing in inorder.
    if(node->JourneyCode != 0){
        store_left(file,node->left);
        
        store(file,node->right);
        
        file << node->JourneyCode << " " << node->price << endl;
    }
}

void BST::customStore(string filename) {
    
    ofstream file;
    file.open(filename);
    
    store_start(file,this->root);
    
    file.close();
    
    return;
    
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

void BST::load(ifstream &f, TreeNode *node){
    
}


void BST::load_left(ifstream &f, TreeNode *node){
    //f >>
}
 
void BST::customLoad (int flag, string filename){
    
    ifstream f;
    f.open(filename);
    
    BST b;
    
    if(flag == LOAD_FULL_BST){
        load_left(f, b.root);
    }
    
    else if(flag == LOAD_LEFT_SUBTREE){
        load(f, b.root);
    }
    
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
        root = root->right;
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
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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

