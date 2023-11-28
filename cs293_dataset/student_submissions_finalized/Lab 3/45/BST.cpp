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
    
    root=NULL;
    
 }
BST::BST(TreeNode *root){
    this->root=root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode,price)){ return false;}
    else{
        if(root==NULL){
            root=new TreeNode(JourneyCode,price);  
            root->parent=NULL;         
        }
        else{

            if(price > root->price){
                TreeNode *x=root->right;
                if(x==NULL){
                    x=new TreeNode(JourneyCode,price); 
                    x->parent=root;
                    root->right=x;
                }
                else{
                    BST b(root->right);
                    b.insert(JourneyCode, price);
                }
                
            }

            else if(price < root->price){
                TreeNode *x=root->left;
                if(x==NULL){
                    x=new TreeNode(JourneyCode,price); 
                    x->parent=root;
                    root->left=x;
                }
                else{
                    BST b(root->left);
                    b.insert(JourneyCode, price);
                }
            }

        }

        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root->price==price && root->JourneyCode==JourneyCode){
        return true;
    }
    if(root==NULL){return false;}
    if(root->price > price){
        BST b(root->left);
        b.find(JourneyCode,price);
    }
    else if(root->price < price){
        BST b(root->right);
        b.find(JourneyCode,price);
    }   
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(!find(JourneyCode, price)){return false;}
    if(root->price==price && root->JourneyCode==JourneyCode){
        if(root->right==NULL){
            if(root->left==NULL){
                root=NULL;
                return true;
            }
            TreeNode *l=root->left;
            TreeNode *r=root->right;
            TreeNode *x=root->left;
            while (x!= NULL){
                x=x->right;
            }
            root=x->parent;
            root->right=r;
            root->left=l;
            root->parent=NULL;
            x->parent=NULL;
            return true;
        }

        TreeNode *l=root->left;
        TreeNode *r=root->right;
        TreeNode *x=root->right;
        while (x!= NULL){
            x=x->left;
        }
        root=x->parent;
        root->right=r;
        root->left=l;
        root->parent=NULL;
        x->parent=NULL;
        return true;

    }
    if(root->price < price){
        BST b(root->right);
        b.remove(JourneyCode,price);
    }
    else{
        BST b(root->left);
        b.remove(JourneyCode,price);
    }


}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        if(root==NULL){return;}
        else{
            cout<<root->price;
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(0);
            br.traverse(0);
        }
    }
    else if(typeOfTraversal==1){
        if(root==NULL){return;}
        else{   
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(1);
            br.traverse(1);
            cout<<root->price;
        }
    }
    else if(typeOfTraversal==2){
        if(root==NULL){return;}
        else{   
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(2);
            cout<<root->price;
            br.traverse(2);
        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==NULL){return 0;} 
    if(root->left==NULL){return root->price;}
    BST b(root->left);
    b.getMinimum();
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
    if( root != NULL )
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
    if( root != NULL )
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

