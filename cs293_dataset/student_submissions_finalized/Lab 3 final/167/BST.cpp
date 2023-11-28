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

void BST :: preorder(TreeNode *a){
 if(a==NULL) {return;}
 else {
  cout<< a->JourneyCode<<endl ;
  preorder(a->left); 
  preorder(a->right);
  }
 }; 
 
    
void BST :: postorder(TreeNode* a){
 if(a==NULL) {return;}
 else { 
  postorder(a->left); 
  postorder(a->right);
  cout<< a->JourneyCode <<endl;;
  }
 };  
 
 
void BST :: inorder(TreeNode* a){
 if(a==NULL) {return;}
 else {  
  inorder(a->left); 
  cout<< a->JourneyCode <<endl ;
  inorder(a->right);
  }
 };      

BST::BST(){

  } 
  
BST::BST(TreeNode* root){
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
   
    TreeNode *x=root;
     while(x != nullptr ){
         if (x->price >= price ) {
           if(x->JourneyCode==JourneyCode) return true;
           else x=x->left;
          }
         else {
           if(x->JourneyCode==JourneyCode) return true;
           else x=x->right;
          }
         }
  return false;}


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
 if(find(JourneyCode,price)==true){return false;} 
 else{
   TreeNode *N;
   N=new TreeNode(JourneyCode,price);
   TreeNode *x=root;
   TreeNode *T=NULL;
   while(x!=NULL){ 
     T=x;          
     if(x->price > price) x=x->left;
     else x=x->right;
     
      }
   N->parent=T;
   if(T==NULL){
           root=N;
        }
   else {
        if(price>(T->price)){
             T->right=N; }
        else{
            T->left=N;}
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

 if(typeOfTraversal == 0) 
    preorder(root);
 else if(typeOfTraversal == 1)
     postorder(root);
 else if(typeOfTraversal==2)
    inorder(root);
 return;
}
TreeNode* BST :: min(TreeNode* k){
  while(k->left !=NULL){
     k=k->left;}
  return k;
}
TreeNode* BST :: successor(TreeNode* k){
 if(k->right!=NULL)
       return min(k->right);
  TreeNode* t=k->parent;
  while((t!=NULL)&&(k=t->right)){ 
  t=t->parent;
  k=t;
  }
  return t;

}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
 TreeNode* k=NULL;
 TreeNode* x=root;
 while(1){
 if(x==NULL)return false;
 else if(x->JourneyCode == JourneyCode && x->price == price){         
	   if(x->left == nullptr && x->right == nullptr){
	     
             if(x->parent !=NULL){
	       if((x->parent)->price<x->price)
		       (x->parent)->right=NULL;    
	       else 
	       (x->parent)->left=NULL;
	     }
	     else x=NULL;
	     delete x;
      
      }
   else if(x->left != nullptr && x->right == nullptr){
             
	       if(x->parent !=NULL){
	         if((x->parent)->price<x->price)
	            (x->parent)->right=x->left;
	         else  
	            (x->parent)->right=x->right;}
	       else root=x->left;
	       delete x;
      }
   else if(x->left == nullptr && x->right != nullptr){
            
             if(x->parent !=NULL){
	       if((x->parent)->price<x->price)
		     (x->parent)->left=x->left;
	      else 
	            (x->parent)->left=x->right;
	          }
	     else root=x->right;
	     delete x;
      }
   else {
     TreeNode* T=x;
     TreeNode* P=successor(T);
     int a,b;
     a=P->JourneyCode;
     b=P->price;
     
     remove(P->JourneyCode,P->price);
     T->JourneyCode=a;
     T->price=b;
     
     }
     return true;
     }
  else {
       if (x->price > price ) {x=x->left;}
       else {x=x->right;}
      }
     
   }

}	


// Returns the price of the cheapest journey
int BST::getMinimum() {
TreeNode *x=root;
if(x==NULL) return 0;
while (x->left !=nullptr){
    x=x->left;
   }
  return x->price;}
     
  
 


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.


int BST:: count(TreeNode* t,int l,int h){
if (!root) return 0;
    if (root->price == h && root->price== l)
        return 1;
    if (root->price <= h && root->price >= l)
         return (1 + count( root->left,l,h) + count(root->right, l, h));
    else if (root->price <l)
         return count(root->right, l,h);
    else return count(root->left, l,h);

}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int x,y;
    x=lowerPriceBound;
    y=upperPriceBound;
    return count(root,x,y);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { ifstream file;
	  file.open(filename);
	  return;}
	
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




