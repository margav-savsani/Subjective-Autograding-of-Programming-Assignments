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


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root=nullptr; 
}
BST::BST(TreeNode *root){
    this->root=root;
}
//returns predecesssor
TreeNode getpredecessor(TreeNode *root){
    TreeNode *subtree = root->left;
    TreeNode maxpricenode;

    int maxprice;
    while((*subtree).price > maxprice){
        maxpricenode = *subtree;
    }
    return maxpricenode;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode,price))return false;
    TreeNode *root;
    while(root!=nullptr){
        if(root->JourneyCode == JourneyCode) return false;
        if(root->price < price)return insert(root->left->JourneyCode, root->left->price);
        else return insert(root->right->JourneyCode, root->right->price);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {  
    TreeNode *root;
    /*root->JourneyCode = JourneyCode;
    root->price = price;*/
    if (root == nullptr) return false;
    if(root->JourneyCode == JourneyCode) return true;
    if(root->price < price)return find(root->left->JourneyCode, root->left->price);
    else return find(root->right->JourneyCode, root->right->price);
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode, price))return false;
    TreeNode *root;
    TreeNode *x = root;
//    TreeNode *y = root->left; // y is pointer to leftChild
    TreeNode *z = root->right; // z is pointer to rightChild
    //TreeNode *x = &root;
    if(!find(JourneyCode,price))return false;
    //CASE1: root has no child
    if(root->left == nullptr && root->right == nullptr){
        if(root->parent->left == root)root->parent->left = nullptr;
        else root->parent->right = nullptr;
    }

    if(root != nullptr)return false;

    //CASE2: root has one child
    else if(root->left == nullptr || root->right == nullptr){
        root->parent = root;
        root->parent->left = nullptr;
        root->parent->right = nullptr;
    }

    //CASE3: root has two children
    else{
       // x = root->left;
      //  root->left = nullptr;
        TreeNode y;
        y = getpredecessor(root);
        if(y.left!=nullptr){
            y = *(y.left);
        }
        *root = y;
       // y = &successor(root);
    }
    return true;
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode *root;
    if(typeOfTraversal == PRE_ORDER){
        if(root==nullptr)return;
       // if(*(root->right) == nullptr && *(root->left) == nullptr){
            
       //     return;
       // }
        cout << root->JourneyCode << endl;

        // if(*(root->left) != nullptr){
            // cout << root->left->JourneyCode;
        //   root = (root->right);
        BST(root->left).traverse(0);
        // }
        // if(*(root->right) != nullptr){
            // cout << (root->right)->JourneyCode;
        BST(root->right).traverse(0);
    }
    else if(typeOfTraversal == POST_ORDER){
        BST(root->left).traverse(typeOfTraversal);
        BST(root->right).traverse(typeOfTraversal);
        cout << root->JourneyCode << endl;

    }
    else if(typeOfTraversal == IN_ORDER){
        BST(root->left).traverse(typeOfTraversal);
        cout << root->JourneyCode << endl;
        BST(root->right).traverse(typeOfTraversal);

    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *root;
    TreeNode *x;
    while(root->left!=nullptr){
        x = root->left;
    }
    return x->price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
        TreeNode *root;
        if(root->price < lowerPriceBound){
            root = root->right;
        }
        else if(root->price > upperPriceBound){
            root = root->left;
        }
        else
        {
            int count = 0;
            while(root->right != nullptr && root->price <= upperPriceBound ){
            count++;
            }
        }
    return 0; 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void store(TreeNode *root, string filename){
    ofstream outfile;
    outfile.open(filename);
    if(root!=nullptr){
        if(root->left!=nullptr)store(root->left, filename);
        outfile<<root->JourneyCode<<endl<<root->price<<endl;
        //using recursion to store subtrees till you reach nullptr
        if(root->right!=nullptr)store(root->right, filename);        
    }
    else return;
}
void BST::customStore(string filename) { 
    store(root, filename);
    //storing bst in inorder traversal
    return; 
}
  
   /* TreeNode *root;
    ofstream outfile;
    outfile.open(filename);
    while(root!=nullptr){
        outfile << "\n   |---" << store(root->left) <<endl;
        outfile << root << endl;
        outfile << "\n   |___" << store(root->right)<<endl;        
        outfile.close();
    }*/

	
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
void print(TreeNode *root, string filename){
    ifstream infile;
    infile.open(filename);
    if(root!=nullptr){
        if(root->left!=nullptr)print(root->left,filename);
        infile>>root->JourneyCode>>root->price;
        if(root->right!=nullptr)print(root->right,filename);
    }
}

void BST::customLoad (int flag, string filename) { 
        if(flag==LOAD_FULL_BST){
        cout << print(root, filename);
    }
    else if(flag==LOAD_LEFT_SUBTREE){
        cout << print(root->left, filename);  
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