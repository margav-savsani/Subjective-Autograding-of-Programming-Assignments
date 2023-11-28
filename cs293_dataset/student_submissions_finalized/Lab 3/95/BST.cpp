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

BST::BST(){root=NULL; }
BST::BST(TreeNode *root){this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
  TreeNode*a=root;
  TreeNode*parent;
  TreeNode*q=new TreeNode(JourneyCode,price);
  while(a!=NULL){
    if((a->price)<price){
        parent=a;
        a=(a->left);
    }
    else if((a->price)>price) {
        parent=a;
        a=(a->right);
    }
    else if((a->price)==price&&(a->JourneyCode)!=JourneyCode){
        q->parent=parent;
        parent->right=q;
        a->parent=q;
        q->right=a;
        
       return true;
    }
    else return false;
  }
  
  q->parent=parent;
  if(parent==NULL){
   root =q;
  }
  else if((q->price)>price){
    parent->right=q;
  }
  else parent->left=q;
  return true;

     }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *find_node=root;
    while(find_node!=NULL){
        if((find_node->price)<price){
            find_node=find_node->left;
        }
         else if((find_node->price)==price&&(find_node->JourneyCode)==JourneyCode){
            return true;
        }
         else if((find_node->price)>=price&&(find_node->JourneyCode!=JourneyCode)){
            find_node=find_node->right;
        }
       
    }
   return false;
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
     TreeNode *find_node=root;
     TreeNode*find_succesor=root;
    while(find_node!=NULL){
        if((find_node->price)<price&&(find_node->JourneyCode!=JourneyCode)){
            find_node=find_node->left;
            find_succesor=find_succesor->left;
        }
        else if((find_node->price)>=price&&(find_node->JourneyCode!=JourneyCode)){
            find_node=find_node->right;
            find_succesor=find_succesor->right;
        }
        else if((find_node->price)==price&&(find_node->JourneyCode)==JourneyCode){
            if(find_node->left==NULL&&find_node->right==NULL){
                find_node=find_node->parent;
                if(find_node->left->JourneyCode==JourneyCode){find_node->left=NULL;}
                else find_node->right=NULL;
            }
            else if(find_node->left==NULL){
                find_node->right->parent=find_node->parent;
                find_node->parent->right=find_node->right;
            }
             else if(find_node->right==NULL){
                find_node->left->parent=find_node->parent;
                find_node->parent->left=find_node->left;
            }
            else{
                find_succesor=find_succesor->right;
                while((find_succesor->left)!=NULL){
                    find_succesor=find_succesor->left;
                }
                
                find_succesor->right->parent=find_succesor->parent;
                find_succesor->parent->left=find_succesor->right;
              find_node->price=find_succesor->price;
              find_node->JourneyCode=find_succesor->JourneyCode;

            }
        }
    }

     return false; }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode*a=root;
    if(typeOfTraversal==0){
        if(a=NULL){return;}
         cout<<a->JourneyCode<<endl;
         TreeNode *b=root->left;
         BST r(b);
         r.traverse(typeOfTraversal);
         TreeNode *c=root->right;
         BST l(c);
         l.traverse(typeOfTraversal);
    }
    else if(typeOfTraversal==1){
    if(a=NULL){return;}
         
         TreeNode *b=root->left;
         BST r(b);
         r.traverse(typeOfTraversal);
         TreeNode *c=root->right;
         BST l(c);
         l.traverse(typeOfTraversal);
         cout<<a->JourneyCode<<endl;
    }
    else if(typeOfTraversal==2){
         if(a=NULL){return;}
         
         TreeNode *b=root->left;
         BST r(b);
         r.traverse(typeOfTraversal);
          cout<<a->JourneyCode<<endl;
         TreeNode *c=root->right;
         BST l(c);
         l.traverse(typeOfTraversal);
        
    }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *a=root;
    while(a->left!=NULL){
        a=a->left;
    }
    return a->price;
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
