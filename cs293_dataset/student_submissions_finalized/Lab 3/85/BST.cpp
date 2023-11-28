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

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){
    this->root=root; }
TreeNode* node(int price){
    TreeNode *NEW = new TreeNode;
    NEW->price=price;
    NEW->left=NULL;
    NEW->right=NULL;
    return NEW;
}
TreeNode* BST::Search(TreeNode *IT,int price){
    TreeNode *s=new TreeNode;
    s=root;
    while(s!=NULL){
        if(s->price=price){return s;}
        else if(s->price>price){s=s->left;}
        else{s=s->right;}
    }
    return NULL;
}
void BST::order(TreeNode* TN,int t){
    if(TN==NULL){
        return;
    }
    if(t==0){
        cout<<TN->price<<" ";
        order(TN->left,0);
        order(TN->right,0);
    }
    if(t==1){
        order(TN->left,1);
        order(TN->right,1);
        cout<<TN->JourneyCode<<" ";
    }
    if(t==2){
        order(TN->left,2);
        cout<<TN->JourneyCode<<" ";
        order(TN->right,2);
    }
}
TreeNode* BST::del(TreeNode *node,int price){
    if(node==NULL){
        return node;
    }
    if(price< node->price){node->left=del(node->left,price)}
    else if(price>node->price){node->right=del(node->right,price)}
    
}
    

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode , int price) { 
    if(find(JourneyCode,price)){return false;}
    else{
   TreeNode* T=new TreeNode;
    T->price=price;
    T->left=NULL;
    T->right=NULL;
    TreeNode* t=new TreeNode;
    t=root;
    if(root==NULL){root=T;}
    else{{while(t!=NULL){
        if(t->price<price){
            if(t->right==NULL){
                t->right=T;
                break;
            }
            t=t->right;}
            else if(t->price>price){
                if(t->left==NULL){
                    t->left=T;
                    break;
                }
                t=t->left;
            }
    }}

   }
   return true;}}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    
   TreeNode* T=new TreeNode;
   T->price=price;
   if(Search(T,price)!=NULL){return true;}
   else{return false;} }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (!find(JourneyCode,price)){return false;}
    if()
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
  
    if(typeOfTraversal==0){
        order(root,0);
    }
     if(typeOfTraversal==1){
        order(root,1);
    }
      if(typeOfTraversal==2){
        order(root,2);
    }

 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* min=root;
    while(min->left!=NULL){
        min=min->left;}
        return min->price;}

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


