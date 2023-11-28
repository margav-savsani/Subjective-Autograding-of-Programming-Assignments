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

BST::BST(){ ; }
BST::BST(TreeNode *root){ this->root=root; }
TreeNode *a;

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *z;
    z = new TreeNode(JourneyCode,price);
    if(find(JourneyCode,price))
      return false;
    else{
      TreeNode *y = NULL;
      TreeNode *x = root;
      while(x!=NULL){
        y=x;
        if(price<x->price)
          x = x->left;
        else
          x  = x->right;
      }
      z->parent = y;
      if(y==NULL)
        root = z;
      else {
        if(price<y->price)
          y->left = z;
        else 
          y->right = z;
      }
    }
    return true;  
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
  TreeNode *x = root;
  while(x!=NULL){
    if(price==x->price){
      if(JourneyCode==x->JourneyCode){
        a = x;
        return true;
      }
      else{
        x = x->right;
        continue;
      }
    }
    if(price<x->price)
      x = x->left;
    else
      x = x->right;
  }
    return false; 
}

TreeNode* Minimum(TreeNode* x){
  while(x->left!=NULL){
    x=x->left;
  }
  return x;
}

TreeNode* TreeSuccessor(TreeNode* x){
  TreeNode *y = NULL;
  if(x->right!=NULL)
    return Minimum(x->right);
  y=x->parent;
  while(y!=NULL && x==y->right){
    x=y;
    y=y->parent;
  }
  return y;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    
    if(!find(JourneyCode,price))
      return false;
    else {
      TreeNode *y;
      TreeNode *x = root;
      if(a->left==NULL || a->right==NULL)
        y=a;
      else
        y=TreeSuccessor(a);
      if(y->left!=NULL)
        x=y->left;
      else
        x=y->right;
      if(x!=NULL)
        x->parent=y->parent;
      if(y->parent==NULL)
        root = x;
      else if(y==y->parent->left)
        y->parent->left=x;
      else
        y->parent->right=x;
      if(y!=a){
        a->price=y->price;
        a->JourneyCode=y->JourneyCode;
      }
  
    }
    return true; 
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST :: preorder(TreeNode *root){
    if(root==NULL)
      return;
    else{
      cout << root->JourneyCode << endl;
      preorder(root->left);
      preorder(root->right);
    }

}
void BST :: postorder(TreeNode *root){
    if(root==NULL)
      return;
    else{
      postorder(root->left);
      postorder(root->right);
      cout << root->JourneyCode << endl;
    }
}
void BST :: inorder(TreeNode *root){
    if(root==NULL)
      return;
    else{
      inorder(root->left);
      cout << root->JourneyCode << endl;
      inorder(root->right);
    }

}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0)
       preorder(root); 
    else if(typeOfTraversal==1)
      postorder(root);
    else if(typeOfTraversal==2)
      inorder(root);
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
  TreeNode *x = root;
  while( x->left!=NULL){
    x = x->left;
  }
  return x->price;
}
  

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int count(TreeNode *x,int l,int u){
  if(x==NULL)
    return 0;
  if(x->price==u && x->price==l)
    return 1;
  if(x->price<=u && x->price>=l)
    return 1+count(x->left,l,u)+count(x->right,l,u);
  else if(x->price<l)
    return count(x->right,l,u);
  else
    return count(x->left,l,u);
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
  return count(root,lowerPriceBound,upperPriceBound);
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
        result.push_back(to_string(root->JourneyCode) + "\n");
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

