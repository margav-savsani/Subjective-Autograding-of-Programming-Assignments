// #include <bits/stdc++.h>
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

BST::BST(){root=NULL; }
BST::BST(TreeNode *root){this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    // ***** Checking Journey Code already present in the BST remaining.
    //Equal case is inserted on left
    TreeNode *newnode;
    newnode=new TreeNode;
    newnode->JourneyCode=JourneyCode;
    newnode->price=price;

    for(int i=0;i<jCodes.size();i++){
        if(jCodes[i]==JourneyCode) return false;
    }
    jCodes.push_back(JourneyCode);

    TreeNode *y=NULL;
    TreeNode *x=root;
    while(x!=NULL){
        y=x;
        if(price<=x->price){x=x->left;}
        else {x=x->right;}
    }
    newnode->parent=y;
    if(y==NULL){
        root=newnode;
        // delete newnode;
        return true;
    }
    else if (price<=y->price){
        y->left=newnode;
        // delete newnode;
        return true;
    }
    else {
        y->right=newnode;
        // delete newnode;
        return true;
    }


    // if(root==NULL){
    //     root=newnode;
    //     delete newnode;
    //     return true;
    // }
    // else{
    //     TreeNode *node=root;
    //     while(node!=NULL){
    //         if(price>node->price){
    //             node=node->right;
    //         }
    //         else{
    //             node=node->left;
    //         }
    //     }
    //     cout<<"Here1\n";
    //     node=node->parent;
    //     if(price>node->price){
    //         newnode->parent=node;
    //         node->right=newnode;
    //     }
    //     else{
    //         newnode->parent=node;
    //         node->left=newnode;   
    //     }
    //     delete newnode;
    //     return true;
    // }
    // delete newnode;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *node=root;
    while(node!=NULL){
            if(price==node->price && JourneyCode==node->JourneyCode){
                return true;
            }
            if(price>node->price){
                node=node->right;
            }
            else{
                node=node->left;
            }
    }
    return false; 
}

//Returns the Pred
TreeNode* BST::treePred(TreeNode *node){
    TreeNode *pred=node->left;
    while(pred->right!=NULL){
        pred=pred->right;
    }
    return pred;
}




// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 

    //tbd:to be deleted
    bool found=false;
    TreeNode *node=root;
    // TreeNode *temproot=root;
    while(node!=NULL){
        if(node->price==price && node->JourneyCode==JourneyCode){
            found=true;
            break;
        }
        if(price>node->price){
                node=node->right;
            }
            else{
                node=node->left;
            }
    }
    if(!found){return false;}
    TreeNode *y,*x;

    // TreeNode *pred=node->left;
    // while(pred->right!=NULL){
    //     pred=pred->right;
    // }
    // node->price=pred->price;
    // node->JourneyCode=pred->JourneyCode;
    // TreeNode *pnode=pred->parent;
    // if(pnode->left==node) {pnode->left=pred->left;}
    // else {pnode->right=pred->left;}
    if(node->left==NULL || node->right==NULL){
        y=node;
    }
    else{
        y=treePred(node);
    }
    if(y->left!=NULL){
        x=y->left;
    }
    else{
        x=y->right;
    }
    if(x!=NULL){
        x->parent=y->parent;
    }
    if(y->parent==NULL){
        root=x;
    }
    else if(y==y->parent->left){
        y->parent->left=x;
    }
    else{
        y->parent->right=x;
    }
    if (y!=node){
        node->JourneyCode=y->JourneyCode;
        node->price=y->price;
    }
    // if(node->left==NULL and node->right==NULL){
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=NULL;}
    //     else {pnode->right=NULL;}
    // }
    // else if(node->left==NULL){
    //     TreeNode *child=node->right;
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=child;}
    //     else {pnode->right=child;}
    // }
    // else if(node->right==NULL){
    //     TreeNode *child=node->left;
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=child;}
    //     else {pnode->right=child;}
    // }
    // else{
    //     TreeNode *pred=node->left;
    //     while(pred->right!=NULL){
    //         pred=pred->right;
    //     }
    //     node->price=pred->price;
    //     node->JourneyCode=pred->JourneyCode;
    //     TreeNode *pnode=pred->parent;
    //     if(pnode->left==node) {pnode->left=pred->left;}
    //     else {pnode->right=pred->left;}
    // }
    return true; }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        if(root==NULL) {return;}
        cout<<root->JourneyCode<<endl;
        BST left(root->left);
        left.traverse(typeOfTraversal);
        BST right(root->right);
        right.traverse(typeOfTraversal);
    }
    else if(typeOfTraversal==1){
        if(root==NULL) {return;}
        BST left(root->left);
        left.traverse(typeOfTraversal);
        BST right(root->right);
        right.traverse(typeOfTraversal);
        cout<<root->JourneyCode<<endl;
    }
    else if(typeOfTraversal==2){
        if(root==NULL) {return;}
        BST left(root->left);
        left.traverse(typeOfTraversal);
        cout<<root->JourneyCode<<endl;
        BST right(root->right);
        right.traverse(typeOfTraversal);
    }
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *node=root;
    while(node->left!=NULL){
        node=node->left;
    }
    return node->price;
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
        // root = root->right;
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

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        // root = root->right;
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

