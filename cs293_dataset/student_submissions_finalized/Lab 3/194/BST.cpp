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
    this->root=nullptr;
}

BST::BST(TreeNode *root){
    this->root= new TreeNode(root->JourneyCode,root->price,root->left=nullptr,root->right=nullptr,root->parent=nullptr);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(root==nullptr){
        root=new TreeNode(JourneyCode, price);
        root->parent=nullptr;
        return true;
    }
    if(BST::find(JourneyCode, price)==false){
        return false;
    }
    else{
        TreeNode * Root= new TreeNode(root->JourneyCode,root->price,root->left=nullptr,root->right=nullptr,root->parent=nullptr);
        while(true){
            if(Root->price < price){
                if(Root->right==NULL){
                    Root->right=new TreeNode(root->JourneyCode,root->price,nullptr,nullptr,Root);
                    break;
                }
                else{
                    Root= Root->right;
                    continue;
                }
            }
            else{
                if(Root->left==NULL){
                    Root->left=new TreeNode(root->JourneyCode,root->price,nullptr,nullptr,Root);
                    break;
                }
                else{
                    Root=Root->left;
                    continue;
                }
            }
        }
        delete[] Root;
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 

    TreeNode * Root= new TreeNode(root->JourneyCode,root->price,root->left=nullptr,root->right=nullptr,root->parent=nullptr);
    while(true){ 
        if(Root == nullptr){
            delete[] Root;
            return false;
        }
        else if(Root->price == price && Root->JourneyCode == JourneyCode){
            delete[] Root;
            return true;
        }
        else{
            if(Root->price < price){
                if(Root->right ==nullptr) {
                    delete[] Root;
                    return false;
                }
                else{
                    Root=Root->right;
                    continue;
                }
            }
            else{
                if(Root->left ==nullptr) {
                    delete[] Root;
                    return false;
                }
                else{
                    Root=Root->left;
                    continue;
                }
            }
        }
    }
}
/*
TreeDelete(T,z)
01 if left[z] NIL or right[z] = NIL
02 then y z
03 else y TreeSuccessor(z)
04 if left[y] NIL
05 then x left[y]
06 else x right[y]
07 if x NIL
08 then p[x] p[y]
09 if p[y] = NIL
10 then root[T] x
11 else if y = left[p[y]]
12 then left[p[y]] x
13 else right[p[y]] x
14 if y z
15 then key[z] key[y] //copy all fileds of y
16 return y
*/
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

    TreeNode* temp = getNode(JourneyCode, price);
    if(temp == nullptr) return false;
    if((temp->left == nullptr)&&(temp->right == nullptr)){
        temp=nullptr;
    }
    else if(temp->left==nullptr){
        temp->right->parent=temp->parent;
    }
    else if(temp->left==nullptr){
        temp->left->parent=temp->parent;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(root == nullptr) return;
    if(typeOfTraversal == 0){
        while(root->left != nullptr){

        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode * Root= new TreeNode(root->JourneyCode,root->price);
    int min = Root->price;
    while(true){
        if(Root->left==nullptr){
            break;
        }
        else{
            Root=Root->left;
            min=Root->price;
        }
    }
    delete[] Root;
    return min;
}

TreeNode * BST::getNode(int JourneyCode,int price){
    TreeNode * Root= root;
    while(true){
        if(root==nullptr){
            return nullptr;
        }
        if(Root->JourneyCode==JourneyCode){
            return Root;
        }
        if(Root->price < price){
            Root=Root->right;
        }
        else{
            Root=Root->left;
        }
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


