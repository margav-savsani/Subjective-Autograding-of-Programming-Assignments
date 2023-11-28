#include <algorithm>
#include <cmath>
#include <set>
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

BST::BST(){root = new TreeNode;}
BST::BST(TreeNode *root){this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{ 
    TreeNode *ins_l;
    TreeNode *ins_r = nullptr;
    ins_l = root;
    
    if(ins_l->JourneyCode == JourneyCode) return false;
    if(root->JourneyCode == 0 && root->price==0)
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
    }
    
    while(ins_l!=nullptr){
        ins_r = ins_l;
        if(price < ins_l->price){
            ins_l = ins_l->left;
        }
        else ins_l = ins_l->right;
    }
    ins_l->JourneyCode = JourneyCode;
    ins_l->price = price;
    ins_l->parent = ins_r;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{
    TreeNode *ins_l;
    TreeNode *ins_r = nullptr;
    ins_l = root;
    
    while(ins_l->JourneyCode!=JourneyCode){
        ins_r = ins_l;
        if(price < ins_l->price){
            ins_l = ins_l->left;
        }
        else ins_l = ins_l->right;
    }
    if(ins_l==nullptr) return false;
    else return true;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{ 
    return false; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preorder(TreeNode *v)
{
    if(v!=nullptr){
        cout << v->JourneyCode << " ";
        preorder(v->left);
        preorder(v->right);
    }
}
void postorder(TreeNode *v)
{
    if(v!=nullptr){
        postorder(v->left);
        postorder(v->right);
        cout << v->JourneyCode << " ";
    }
}
void inorder(TreeNode *v)
{
    if(v!=nullptr){
        inorder(v->left);
        cout << v->JourneyCode << " ";
        inorder(v->right);
    }
}

void BST::traverse(int typeOfTraversal) 
{
    if(typeOfTraversal==0){
        preorder(root);
    }
    if(typeOfTraversal==1){
        postorder(root);
    }
    if(typeOfTraversal==2){
        inorder(root);
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *ins_l;
    ins_l = root;
    while(ins_l->left!=nullptr){
        ins_l = ins_l->left;
    }
    return ins_l->price;
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

