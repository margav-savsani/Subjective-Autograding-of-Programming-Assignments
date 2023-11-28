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
    root = new TreeNode();
     }
BST::BST(TreeNode *root){; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool insertpls(int JourneyCode,int price,TreeNode *s){
    if((s->JourneyCode==0)&&(s->price == 0)){
        s->JourneyCode = JourneyCode;
        s->price = price;
        return true;
    }
    else if((s->price == price)&&(s->JourneyCode == JourneyCode))
        return false;
    else if( s->price >= price){
        TreeNode *r;
        if(s->right==nullptr){
            r = new TreeNode(JourneyCode,price);
            r->parent = s;
            s->right = r;
            return true;
        }
        else{
            insertpls(JourneyCode,price,r);
        }
    }
    else if(s->price < price){
        TreeNode *r;
        if(s->left == nullptr){
            r = new TreeNode(JourneyCode,price);
            r->parent = s;
            s->left = r;
            return true;
        }
        else{
            insertpls(JourneyCode,price,r);
        }
    }
}

bool BST::insert(int JourneyCode, int price) {
   return insertpls(JourneyCode,price,root);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(root->JourneyCode == JourneyCode && root->price == price ){
        return true;
    }
    else if(root->price > price){
        TreeNode *r;
        r = root->left;
        if(r==nullptr){
            return false;
        }
        else{
            m = BST(r);
            m.find(JourneyCode,price);
        }
    }
    else if(root->price <=price){
        TreeNode *r;
        r = root->right;
        if(r==nullptr){
            return false;
        }
        else{
            m = BST(r);
            m.find(JourneyCode,price);
        }
     }
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
         if(root->JourneyCode == JourneyCode && root->price == price ){
            if(root->right==nullptr&&root->left == nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = nullptr;
                }
                else if(t->left == root){
                    t->left = nullptr;
                }
            else if(root->right == nullptr && root->left != nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = root->left;
                    (root->left)->parent = t;
                } 
                else if(t->left == root){
                    t->left = root->left;
                    (root->left)->parent = t;
                } 
            }
            else if(root->left == nullptr && root->right != nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = root->right;
                    (root->right)->parent = t;
                }
                else if(t->left == root){
                    t->left = root->right;
                    (root->right)->parent = t;
                }
            }
         }
            return true;
    }
    else if(root->price > price){
        TreeNode *r;
        r = root->left;
        if(r==nullptr){
            return false;
        }
        else{
            m = BST(r);
            m.find(JourneyCode,price);
        }
    }
    else if(root->price <=price){
        TreeNode *r;
        r = root->right;
        if(r==nullptr){
            return false;
        }
        else{
            m = BST(r);
            m.find(JourneyCode,price);
        }
     }
    }
    
    
    
    
    
    return false; }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {return 0; }

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

