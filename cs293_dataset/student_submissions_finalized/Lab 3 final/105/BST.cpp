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

BST::BST(){root=new TreeNode;}
BST::BST(TreeNode *root){
    this->root=root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode *x=root;
    TreeNode *y=NULL; int b=0; 
    if(x->price==0){
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }    
    while(x!=NULL){
        if(x->price==price)return false;
        else if(x->price>price){   
            y=x;
            b=1;
            x=x->left;
        }
        else if(x->price<price){
            y=x;
            b=2;
            x=x->right;
        }
    } 
    x=new TreeNode(JourneyCode,price,NULL,NULL,y);
    if(b==1) y->left=x;
    else if(b==2) y->right=x;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x=root;
    if(x==NULL)return false;
    while(x!=NULL){
        if(x->price==price) return true;
        else if(x->price>price){
            x=x->left;   
        }
        else if(x->price<price){
            x=x->right;
        }
    }    
    return false; 
}

TreeNode* successor(TreeNode* x){
    x=x->right;
    while(x->left!=NULL){
        x=x->left;
    }
    return x; 
} 
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *x=root, *y=NULL; int b=0;
    if(x->price==0)return false; 
    while(x!=NULL){
        if(x->price==price)break;
        else if(x->price>price){
            b=1;
            y=x;
            x=x->left;   
        }
        else if(x->price<price){
            b=2;
            y=x;
            x=x->right;
        }
    } 

    if(x->left==NULL && x->right==NULL){
        if(b==1) y->left=NULL;
        else if(b==2) y->right=NULL;
        return true;
    }

    if(x->left==NULL && x->right!=NULL){
        if(b==1) y->left= x->right; 
        else if(b==2) y->right= x->right;
        x->right->parent=y;
        return true;
    }

    if(x->left!=NULL && x->right==NULL){
        if(b==1) y->left= x->left;
        else if(b==2) y->right= x->left;
        x->left->parent=y;
        return true;
    }

    if(x->left!=NULL && x->right!=NULL){
        TreeNode *z=successor(x);
        remove(z->JourneyCode,z->price);
        z->left=x->left;
        z->right=x->right;
        if(b==2)y->right=z;
        else if(b==1)y->left=z;
        
        z->parent=y;
        x->left->parent=z;
        x->right->parent=z;
        return true;
    }
    return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
    
void Pre_ORDER(TreeNode *y){
        TreeNode *x;
        cout<<y->price<<endl;     
        x = y->left;
        Pre_ORDER(x);
        x = y->right;
        Pre_ORDER(x);
}

void Post_ORDER(TreeNode *y){
        TreeNode *x;
        x = y->left;
        Post_ORDER(x);
        x = y->right;
        Post_ORDER(x);
        cout<<y->price<<endl;
}

void In_ORDER(TreeNode *y){
        TreeNode *x;
        x = y->left;            
        In_ORDER(x);
        cout<<y->price<<endl;
        x = y->right;
        In_ORDER(x);
}

void BST::traverse(int typeOfTraversal) {

    if(typeOfTraversal == 0)
        return Pre_ORDER(root);
    if(typeOfTraversal == 1)
        return Post_ORDER(root);
    if(typeOfTraversal == 2)
        return In_ORDER(root);

}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    if(x==NULL)return 0;
    while(x->left!=NULL){
        x=x->left;
    }
    return x->price; 
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
