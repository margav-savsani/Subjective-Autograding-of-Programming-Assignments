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

TreeNode* BST::search(TreeNode *T,int price){
if (T==NULL) return NULL;
if (T->price==price) return T;
if (T->price<price) return search (T->right,price);
else return search (T->left,price);}

TreeNode* BST::predecessor(TreeNode *T,int price){


}


bool BST::insert(int JourneyCode, int price) {
 bool x=find(JourneyCode,price);
if (x) return false;
TreeNode *y;
TreeNode *z=root;
while(z!=NULL){
 y=z;
 if (price<z->price){
   z=z->left;}
 else z=z->right;
}
if (y==NULL) 
{root->JourneyCode=JourneyCode;
 root->price=price;
}
else{
z->JourneyCode=JourneyCode;
z->price=price;
z->parent=y;
}
if(price<y->price){
 y->left=z }
else y->right=z;
return true;}


bool BST::find(int JourneyCode, int price) { 
TreeNode *x=root;
if (x==NULL) return NULL;
while ((x!=NULL){
if ((x->JourneyCode==JourneyCode)&&(x->price==price)){return true;} 
if (x->price<price){ x=x->left;}
else x=x->right;
}
return false;
}
	

bool BST::remove(int JourneyCode, int price) { 
if (!find(JourneyCode,price)) return false;
TreeNode *f=search(root,price);
if ((f->right==NULL)&&(f->left==NULL)){
   TreeNode *parent=f->parent;
   if(parent->right == f) {parent->right = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
   else {parent->left = NULL;f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
}
else if((found->right == NULL)||(found->left ==NULL)){
   if(found->right == NULL){
      TreeNode *p = f->parent;
      if(p->left == f) {p->left = f->left; f->left->parent =p; f->left = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
      else {p->right = f->left; f->left->parent = p;f->left = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
   }
   else{      
      TreeNode *p = f->parent;
      if(p->left == f) {p->left = f->right; f->right->parent = p; f->right = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
      else {p->right =f->right; f->right->parent =p;f->right = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true;}
   }
}
else{
    TreeNode *p = predecessor(root,f->price);
    p->parent->right =p->left;
    p->left->parent = p->parent;
    p->left = f->left;
    p->right = f->right;
    f>left->parent = p;
    f->right->parent = p;
    f->parent = p->parent;
    f->left = NULL; f->right = NULL; f->parent = NULL; f->JourneyCode = 0;f->price = 0; return true; 
}
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
void PRE_ORDER(TreeNode *X){
if (X==NULL) return;
else{
 cout<<X-JourneyCode<<" ";
 PRE_ORDER (X->left);
 PRE_ORDER(X->right);
}
}
void POST_ORDER(TreeNode *X){
if (X==NULL) return;
else{
 POST_ORDER(X-left);
 POST_ORDER(X-right);
 cout<<X->JourneyCode<<" ";
}   
}
void IN_ORDER(TreeNode *X){
if (X==NULL) return ;
else{
  IN_ORDER(X->left);
  cout<<JourneyCode<<" ";
  IN_ORDER(X->right);
}
}
}

int BST::getMinimum() {
TreeNode *x=root;
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

