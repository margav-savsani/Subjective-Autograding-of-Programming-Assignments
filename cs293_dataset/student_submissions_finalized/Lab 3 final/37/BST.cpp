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

BST::BST(){ root = nullptr; }
BST::BST(TreeNode *root_){this->root=root_; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* x=root;
    TreeNode* y=x;
    if(x==nullptr){
  
        root=new TreeNode(JourneyCode,price);
        return true;
    }
    while(x != nullptr){
        y=x;    
        if(x->price > price){
            x= x->left;
        }
        else if(x->price == price) return false;
        else x=x->right;

    }
    TreeNode* z=new TreeNode(JourneyCode,price);
    z-> parent=y;
    if(y==nullptr)root=z;
    else if(y->price > price)
        y->left=z;
    else   
        y->right=z;
    return true; 
    
}

TreeNode* successor(TreeNode* x){
    
    if(x->right !=nullptr){
        TreeNode* y=x->right;
        while(y->left != nullptr){
        y=y->left;
        }
        return y;
    }
    
    TreeNode* y=x->parent;
    while (y !=nullptr && x==y->right)
    {
        x=y;
        y=y->parent;
    }
    if(y!=nullptr)
        return y;
    else return x;
    
        
    
        
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* x=root;
    if(x==nullptr)
        return false; 
    while (x!=nullptr && x->price!= price )
    {
        if(x->price> price)
            x=x->left;
        else x=x->right;
    }
    if(x==nullptr) return false;
    if(x->price== price && x->JourneyCode==JourneyCode )
        return true;
    return false; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    
    if(!find(JourneyCode,price)) return false;
    
    TreeNode* z=root;
    TreeNode* y;
    TreeNode* x;
    if(z == nullptr)return false;
    
    while(z != nullptr && z->price!=price ){
       
        if(z->price > price){
            z= z->left;
        }
        else z=z->right;

    }
    
    if(z == nullptr)return false;
    TreeNode* zp=z->parent;
    if(z->left==nullptr && z->right == nullptr){ //case:1
        if(zp != nullptr)
            {
            if(zp->price > z->price)
                zp->left=nullptr;
            else zp-> right=nullptr;
            
            return true;
            }
        else{
            root=nullptr;
            
            return true;
        }
        
    }
    
    if((z->left!=nullptr && z->right == nullptr)){ //case-2
        if(zp != nullptr){
            (z->left)->parent=zp;
            if(price < zp->price)
                zp->left=z->left;
            else zp->right=(z->left);
           
            return true;
        }
        else{
            (z->left)->parent=nullptr;
            root=(z->left);
            
            return true;
        }
        
        
    }
   
    if((z->left==nullptr && z->right!= nullptr)){ //case-2
        if(zp != nullptr){
            (z->right)->parent=z->parent;
            if((z->right)<z->parent)
                zp->left=(z->right);
            else zp->right=(z->right);
            
            return true;
        }
        else{
            (z->right)->parent=nullptr;
            root=(z->right);
            
            return true;
        }
        
    }   
    
    if(price != successor(z)->price){ //cas-3;
        y=successor(z);
        remove(y->JourneyCode,y->price);
        z->JourneyCode=y->JourneyCode;
        z->price=y->price;
        return true;
        
    }
    return true;
}
void BST::pre(TreeNode* root){
        if(root=nullptr) return;
        cout << root->JourneyCode <<endl;
        pre(root->left);
        pre(root->right);
}
void BST::post(TreeNode* root){
        if(root=nullptr) return;
        
        post(root->left);
        post(root->right);
        cout << root->JourneyCode <<endl;
}
void BST::in(TreeNode* root){
        if(root=nullptr) return;
       
        in(root->left);
         cout << root->JourneyCode <<endl;
        in(root->right);
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){  //PREORDER
       pre(root);


    }

    else if(typeOfTraversal==1){ //POSTORDER
        post(root);
    }

    else if(typeOfTraversal==2){ //INORDER
        in(root);
    }

    
    
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* x=root;
   
    while(x->left != nullptr){
        
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


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
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
