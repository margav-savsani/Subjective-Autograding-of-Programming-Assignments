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

BST::BST(){; }
BST::BST(TreeNode *root){; }


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    
    if(find(JourneyCode,price)){
        return false;
    }
    if(root==NULL)
    {
        root=new TreeNode(JourneyCode,price);
        root->parent=NULL;
      
        return true;
    }
    BST n;
    n.root=root;
    if(n.root->left ==NULL && n.root->right==NULL ){
        if(n.root->price>price){
            n.root->left=new TreeNode(JourneyCode,price);
            n.root->left->parent=n.root;
        }
        if(n.root->price<price){
            n.root->right=new TreeNode(JourneyCode,price);
            n.root->right->parent=n.root;
        }
        return true;
    }
    if(n.root->left ==NULL && n.root->right!=NULL ){
        if(n.root->price>price){
            n.root->left=new TreeNode(JourneyCode,price);
            n.root->left->parent=n.root;
            return true;}
            else {n.root=n.root->right;
                return n.insert(JourneyCode,price);}
        
        
    }
    if(n.root->left !=NULL && n.root->right==NULL ){
        if(n.root->price<price){
            n.root->right=new TreeNode(JourneyCode,price);
            n.root->right->parent=n.root;
            return true;}
            else{n.root=n.root->left;
            return n.insert(JourneyCode,price);}
    }
    
    if(n.root->price>price)
    {
        n.root=n.root->left;
        n.insert(JourneyCode,price);
    }
    if(n.root->price<price)
    {
        n.root=n.root->right;
        n.insert(JourneyCode,price);
    }
    return false; 
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    BST n;
    n.root=root;
    if(n.root==NULL){
        return false;
    }
    if(n.root->price>price)
    {
        n.root=n.root->left;
        return n.find(JourneyCode,price);
    }
    if(n.root->price<price)
    {
        n.root=n.root->right;
        return n.find(JourneyCode,price);
    }
    if(n.root->price==price)
    {
        return true;
    }
    
    return false; 
    }
TreeNode* BST::get(int JourneyCode, int price){
    
    BST n;
    n.root=root;
    if(n.root->price>price)
    {
        n.root=n.root->left;
        return n.get(JourneyCode,price);
    }
    if(n.root->price<price)
    {
        n.root=n.root->right;
        return n.get(JourneyCode,price);
    }
    if(n.root->price==price)
    {
        return n.root;
    }
    return NULL;
}    
TreeNode* BST::successor(int JourneyCode, int price){
    TreeNode* t=get(JourneyCode,price);
    t=t->right;
    while(!(t->left==NULL))
    {
        t=t->left;
    }
    return t;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    bool b=find(JourneyCode,price);
    if (!b){return false;}
    TreeNode *t=get(JourneyCode,price);
    if(t==root){

        if(t->left==NULL && t->right==NULL)
        {
            root=NULL;   
        }
         else if(t->left==NULL)
        {
            t->right->parent=NULL;
        }
         else if(t->right==NULL)
        {
            t->left->parent=NULL;
        }
        else
        {
            TreeNode* s;
            s=successor(JourneyCode,price);
            root->left->parent=s;
            root->right->parent=s;
            s->left=root->left;
            s->right=root->right;
            s->parent=NULL;
        }
    }
    else if(t->left==NULL && t->right==NULL)
    {
        if(t->parent->left==t)
        {
            t->parent->left=NULL;
        }
         if(t->parent->right==t)
        {
            t->parent->right=NULL;
        }

    }
    else if(t->left==NULL)
    {
         if(t->parent->left==t)
        {
            t->parent->left=t->right;
        }
         if(t->parent->right==t)
        {
            t->parent->right=t->right;
        }
    }
    else if(t->right==NULL)
    {
         if(t->parent->left==t)
        {
            t->parent->left=t->left;
        }
         if(t->parent->right==t)
        {
            t->parent->right=t->left;
        }
    }
    else{
        TreeNode* s;
        s=successor(JourneyCode,price);
        s->parent->left=NULL;
        s->parent=t->parent;
        s->left=t->left;
        s->right=t->right;
        t->left->parent=s;
        t->right->parent=s;
        if(t->parent->left==t)
        {
            t->parent->left=s;
        }
        if(t->parent->right==t)
        {
            t->parent->right=s;
        }
    }
    return true;
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0)
    {
        BST n;
        
        if(root==NULL){return;}
        n.root=root;
        cout<<root->JourneyCode<<endl;
        n.root=root->left;
        n.traverse(0);
        n.root=root->right;
        n.traverse(0);
    } 
    if(typeOfTraversal==1)
    {
        BST n;
        if(root==NULL){return;}
        n.root=root->left;

        n.traverse(1);
        n.root=root->right;
        n.traverse(1);
        n.root=root;
        cout<<n.root->price<<endl;
    } 
    if(typeOfTraversal==2)
    {
        BST n;
        if(root==NULL){return;}
        n.root=root->left;
        n.traverse(2);
        n.root=root;
        cout<<n.root->price<<endl;
        n.root=root->right;
        n.traverse(2);
       
    } 
    }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    BST n;
    n.root=root;
    if(n.root->left==NULL)
    {
        return n.root->price;
    }
    else{
        n.root=n.root->left;
        return n.getMinimum();

    }
 }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.i
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int a=0;
     return count(lowerPriceBound,upperPriceBound,root,a);
}
int BST::count(int lowerPriceBound, int upperPriceBound,TreeNode*r,int &a) {
    if(r==NULL){
        return a;
    }
    if(r->price==lowerPriceBound){
        a++;
        return count(lowerPriceBound,upperPriceBound,r->right,a);
    }
    else if(r->price==upperPriceBound){
        a++;
        return count(lowerPriceBound,upperPriceBound,r->left,a);
    }
    else if(r->price>upperPriceBound){
        return count(lowerPriceBound,upperPriceBound,r->left,a);
    }
    else if(r->price<lowerPriceBound){
        return count(lowerPriceBound,upperPriceBound,r->right,a);
    }
    else if(r->price>lowerPriceBound && r->price<upperPriceBound){
        return count(lowerPriceBound,r->price,r->left,a)+count(r->price,upperPriceBound,r->right,a)+1;
    }
    
}

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

