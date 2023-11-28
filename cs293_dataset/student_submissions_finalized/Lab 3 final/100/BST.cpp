#include <bits/stdc++.h>
#include<fstream>
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

BST::BST(){};
BST::BST(TreeNode *root){
    this->root=root; };

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::isJcode(TreeNode* node,int Jcode){
    if(node==NULL)return false;
    if(node->JourneyCode==Jcode)return true;
    if(isJcode(node->left,Jcode)||isJcode(node->right,Jcode)) return true;
    return false;
}

bool BST::insert(int JourneyCode, int price) {

    if(isJcode(root,JourneyCode))return false;

    TreeNode *x,*nnode,*y;
    y=NULL;
    x=root;
    nnode=new TreeNode(JourneyCode,price);
    while(x!=NULL){
        y=x;
        if(price < x->price)x=x->left;
        else x=x->right;
    }
    nnode->parent=y;
    if(y==NULL)
        root=nnode;
    else if(price< y->price)y->left=nnode;
    else y->right=nnode;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x;
    x=root;
    while(x!=NULL){
        if(x->price == price){
            if(x->JourneyCode == JourneyCode) return true;
            else x=x->left;
        }
        else if(x->price > price) x=x->left;
        else x=x->right;
    }
    return false; 
}

TreeNode* BST::getNode(int JourneyCode ,int price){
    TreeNode *x;
    x=root;
    while(x!=NULL){
        if(x->price == price){
            if(x->JourneyCode == JourneyCode) return x;
            else x=x->left;
        }
        else if(x->price > price) x=x->left;
        else x=x->right;
    }
    return NULL;
}

TreeNode* BST::succesessor(TreeNode* node){
    if(node->right!=NULL){
        TreeNode* x;
        x=node;
        if(x==NULL)return NULL;
        while(x->left!=NULL){
            x=node->left;
        }
        return x;
    }
    TreeNode* y=node->parent;
    while(y!=NULL && node==y->right){
        node=y;
        y=y->parent;
    }
    return y;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    bool found=find(JourneyCode ,  price);
    if(found==false)return false;
    TreeNode* z=getNode(JourneyCode,price);
    TreeNode* y,*x;
    if(z->left==NULL || z->right==NULL)y=z;
    else y=succesessor(z);
    if(y->left!=NULL)x=y->left;
    else x=y->right;
    if(x!=NULL)x->parent=y->parent;
    if(y->parent==NULL)root=x;
    else if(y==y->parent->left)y->parent->left=x;
    else y->parent->right=x;
    if(y!=z){
        z->price=y->price;
        z->JourneyCode=y->JourneyCode;
    }
    return true; 
}  
    
    
    
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode* node){
    if(node==NULL)return;
    cout<<node->JourneyCode<<endl;
    inorder(node->left);
    inorder(node->right);
}

void BST::postorder(TreeNode *node){
    if(node==NULL)return;
    postorder(node->left);
    postorder(node->right);
    cout<<node->JourneyCode<<endl;
}

void BST::inorder(TreeNode* node){
    if(node==NULL)return;
    inorder(node->left);
    cout<<node->JourneyCode<<endl;
    inorder(node->right);
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==PRE_ORDER){
        preorder(root);
    }
    else if(typeOfTraversal==POST_ORDER)postorder(root);
    else if(typeOfTraversal==IN_ORDER)inorder(root);
    else
        return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node;
    node=root;
    if(node==NULL)return -1;
    while(node->left!=NULL){
        node=node->left;
    }
    return node->price;
}

// Part II
int BST::count(TreeNode* node, int LB,int UB){
    if(node==NULL)return 0;
    int leftcount=0,rightcount=0;
    leftcount=count(node->left,LB,UB);
    rightcount =count(node->right,LB,UB);  
    if(node->price>=LB && node->price<=UB){
        return 1+leftcount+rightcount;
    }
    else return leftcount+rightcount;
}
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return count(root,lowerPriceBound,upperPriceBound); 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::store(TreeNode* node,ofstream &name){
    if(node==NULL){
        name << -1<<endl;
        return;
    }
    name << node->price <<endl;
    name<< node->JourneyCode<<endl;
    store(node->left,name);
    store(node->right,name);
}

void BST::customStore(string filename) { 
    ofstream file;
    file.open(filename);
    store(root,file);   
    file.close();
}
	
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

void BST::load(TreeNode* &node,ifstream &file){
    int x;
    if(!(file>>x) || x==-1)return;
    int y;
    file>>y;
    node=new TreeNode(y,x);
    load(node->left,file);
    load(node->right,file);
}
 
void BST::customLoad (int flag, string filename) {
    ifstream file;
    file.open(filename);
    if(flag==LOAD_FULL_BST)load(root,file);
    else if(flag==LOAD_LEFT_SUBTREE)load(root->left,file);
    file.close();
    
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
        result.push_back(to_string(root->JourneyCode) + "\n");
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
