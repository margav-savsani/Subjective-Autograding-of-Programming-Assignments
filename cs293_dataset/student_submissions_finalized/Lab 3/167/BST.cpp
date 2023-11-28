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
  TreeNode *t;
  t=new TreeNode [100];
  } 
  
BST::BST(TreeNode *root){
 root=new TreeNode [100]; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
 if(find(JourneyCode,price) return false;
 else  TreeNode t; 
    t.JourneyCode=JourneyCode;
    t.price=price;
    return true;

}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
 if(strcmp( typeOfTraversal,PRE_ORDER)==0){
  int i=0;
     while(1){
       if(root[i].parent==NULL) return;
       else 
         cout<<&(root[i].parent);
         root[i].parent=root[i].leftchild(); 
         continue;
         root[i].parent=root[i].rightchild();
         continue;
         i++;
           }}
 if(strcmp( typeOfTraversal,POST_ORDER)==0){
    int i=0;
     while(1){
       if(root[i].parent==NULL) return;
       else 
         root[i].parent=root[i].leftchild(); 
         continue;
         root[i].parent=root[i].rightchild();
         continue;
         cout<<&(root[i].parent);
         i++;
           }}
 if(strcmp( typeOfTraversal,IN_ORDER)==0){
   int i=0;
     while(1){
       if(root[i].parent==NULL) return;
       else 
         root[i].parent=root[i].leftchild(); 
         continue;
         cout<<&(root[i].parent);
         root[i].parent=root[i].rightchild();
         continue;         
         i++;
           }
      }
}



// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
  
  for(int i=1;i<100;i++){  
     if(root[i].JourneyCode==JourneyCode && root[i].price==price)
       return true;
     }    
  return false; }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
 if(!find(JourneyCode, price) return false;
 else 
  for(int i=0;i<100;i++){
   if(root[i].JourneyCode==JourneyCode && root[i].price==price){
     root[i]==NULL;
     return true;  
  }
 }
}	


// Returns the price of the cheapest journey
int BST::getMinimum() {
  int s=root[0].price;
    for(int i=1;i<100;i++){
      s=min(s,root[i].price);
  }
 return s;  
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


