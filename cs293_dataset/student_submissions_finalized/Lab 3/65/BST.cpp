#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    
    root=nullptr;
    
 }
BST::BST(TreeNode root){
     this->root=&root;
     }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
            return false;
    }
         TreeNode *A=new TreeNode;
         A->JourneyCode=JourneyCode;
         A->price=price;
         TreeNode *y=NULL;
         TreeNode *x=root;

         while(x!=NULL){
            y=x;
            if(price<x->price){
                x=x->left;
            }
            else x=x->right;
         }
        A->parent=y;
        if(y==NULL){
            root=A;
            return true;
        }
        else if(A->price < y->price){
            y->left=A;
            return true;       
         }
        
        else{
         y->right=A;
         return true;
        }
    
    return false;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
     TreeNode *A=new TreeNode;
     A->JourneyCode=JourneyCode;
     A->price=price;
     TreeNode *x;
     x=root;
     while(x!=NULL && A->price!=x->price){
        if(A->price<x->price){
            x=x->left;
        }
        else {x=x->right;}
     }
     if(x==NULL){
        return false;
     }
     else {return true;}
      }
struct TreeNode* BST::treemin(TreeNode *Root){
    while(Root->left!=NULL){
        Root=Root->left;
    }
    return Root;
}
struct TreeNode* BST::succ(TreeNode *element){
 TreeNode *A=root;
 if(element->right!=NULL){
    A=element->right;
    return treemin(A);
 }
 else{
 TreeNode *y=element->parent;
 while(y!=NULL && element==y->right){
    element=y;
    y=y->parent;
 }
 return y;
 }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

    if(!find(JourneyCode,price)){
            return false;
    }
    else{
    TreeNode *y;
    TreeNode *x;
   TreeNode *A= new TreeNode;
   A->JourneyCode=JourneyCode;
   A->price=price;
   if(A->left==NULL || A->right==NULL){
    y=A;
   }
   else {y=succ(A);}
   if(y->left!=NULL){
    x=y->left;
   }
   else {x=y->right;}
   if(x!=NULL){
    x->parent=y->parent;
   }
   if(y->parent==NULL){
    root=x;
   }
   else if(y==y->parent->left){
    y->parent->left=x;
   }
   else {y->parent->right=x;}
   if(y!=A){
    A->JourneyCode=JourneyCode;
    A->price;
   }
   return true;
 }
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	TreeNode *A=root;
    if(typeOfTraversal==0){
        if(A==NULL){
            return;
        }
        else{
            cout<<A->JourneyCode<<endl;
            {
                A=A->left;
                traverse(0);
            }
            {
                A=A->right;
                traverse(0);
            }
        }
    }
    else if(typeOfTraversal==1){
    
        if(A==NULL){
            return;
        }
            {
                A=A->left;
                traverse(1);
            }
            {
                A=A->right;
                traverse(1);
            }
            cout<<A->JourneyCode<<endl; 
        }
        
    else if(typeOfTraversal==2){
        if(A==NULL){
            return;
        }
            {
                A=A->left;
                traverse(2);
            }
            cout<<A->JourneyCode<<endl;
            {
                A=A->right;
                traverse(2);
            }
             
        }
    
    return;
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *A=root;
    while(A->left!=NULL){
        A=A->left;
    }
    return A->price; 
     }

// // Part II

// // Returns the count of journeys that are at least as expensive
// // as lowerPriceBound and at most as expensive as upperPriceBound,
// // both bounds included.
// int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

// // Store the current tree in a file called filename.  You should
// // store using a scheme that uses no more disk space than that
// // required to store all elements in the BST, plus perhaps a small
// // constant times the number of elements.  You should also store
// // in a manner such that your implementation of customLoad is as
// // memory and time efficient as possible.
// void BST::customStore(string filename) { return; }
	
// // While loading a tree from a file written by customStore, we
// // can have one of two modes of loading.  We could either ask
// // for the entire tree to be loaded or only the left subtree of
// // the root (if it exists) to be loaded.  The loadMode flag
// // takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// // that are #defined in BST.cpp.
// // If loadMode is LOAD_FULL_BST, customLoad should load the
// // entire BST that was stored in filename using customStore.
// // If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// // only the left subtree of the root of the BST that was
// // stored in filename using customStore.
// // Your implementation of customLoad should be efficient --
// // its time and space complexity should be linear in the size
// // of the tree that is being loaded.  So, for example, if the
// // left sub-tree of the root is small compared to the right
// // sub-tree, customLoad's time and space complexity should
// // be small even though the entire BST may be very large.
 
//void BST::customLoad (int flag, string filename) { return; }


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){return 0;}
void BST::customStore(string filename){};
void BST::customLoad (int flag, string filename){};
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
