#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root=nullptr; }
BST::BST(TreeNode *root){ this->root=root; }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(root==nullptr) return false;
    TreeNode *x=root;
    while(x->price!=0){
        if(x->price==price) return true;
        else if ((x->price)<price) x=x->left;
        else x=x->right;
    }
    return false; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode,price)) return false;
    else {
        TreeNode *y=nullptr;
        TreeNode *x=root;
        while(x->price!=0){
            y=x;
            if(price<(x->price)) x=x->left;
            else x=x->right;
        }
        if(root==nullptr) root= new TreeNode(JourneyCode,price);
        else if(price< y->price) {
            y->left=new TreeNode(JourneyCode,price,nullptr,nullptr,y);
        }
        else {
            y->right= new TreeNode(JourneyCode,price,nullptr,nullptr,y);
        }
    return true;}
    }

TreeNode* BST::nodemin(TreeNode *node1){
    TreeNode *x=node1;
    while(x->left!=nullptr){
        x=x->left;
    }
    return x;
}

TreeNode* BST::sucscr(TreeNode *node1){
    TreeNode *x=node1;
    TreeNode *y;
    if(x->right!=nullptr) return nodemin(x->right);
    else return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if (!find(JourneyCode,price)) return false;
    else {
        TreeNode *x=root;
        TreeNode *res;
        while(true){
            if(x->price==price) {res=x; break;}
            else if (x->price <price) x=x->left;
            else x=x->right;
    }
        if(res->left==nullptr && res->right==nullptr){
            res->JourneyCode=0;
            res->price=0;
        }
        else if(res->left==nullptr && res->right!=nullptr){
            TreeNode *respar=res->parent;
            if(respar->left->price==price){
                respar->left=res->right;
                res->right->parent=respar;
            }
            else {
                respar->right=res->right;
                res->right->parent=respar;
            }
        }
        else if(res->left!=nullptr && res->right==nullptr){
           TreeNode *respar=res->parent;
            if(respar->left->price==price){
                respar->left=res->left;
                res->left->parent=respar;
            }
            else {
                respar->right=res->left;
                res->left->parent=respar;
            }
        }
        else{
            TreeNode *rep=nodemin(res);
            int newjc=rep->JourneyCode;
            int newpc=rep->price;
            remove(rep->JourneyCode,rep->price);
            res->JourneyCode=newjc;
            res->price=newpc;
        }
    return true;
    }
    }

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode *node1){
    if(node1->price==0) return;
    else {
        cout<<node1->JourneyCode<<endl;
        preorder(node1->left);
        preorder(node1->right);
    }
    return;
}

void BST::postorder(TreeNode *node1){
    if(node1->price==0) return;
    else {
        postorder(node1->left);
        postorder(node1->right);
        cout<<node1->JourneyCode<<endl;
    }
    return;
}

void BST::inorder(TreeNode *node1){
    if(node1->price==0) return;
    else {
        inorder(node1->left);
        cout<<node1->JourneyCode<<endl;
        inorder(node1->right);
    }
    return;
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) preorder(root);
    else if(typeOfTraversal==1) postorder(root);
    else if(typeOfTraversal==2) inorder(root);
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    while(x->left!=nullptr){
        x=x->left;
    }
    return x->price;}

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
