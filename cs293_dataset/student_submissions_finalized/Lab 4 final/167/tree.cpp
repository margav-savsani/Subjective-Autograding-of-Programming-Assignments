// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


BST::BST() {root = nullptr;}
BST::BST(TreeNode *curr_root) {root=curr_root; }

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

int BST:: shortpath(TreeNode* a){
  if(a==NULL) return 0;
  else if(a->left==NULL &&a->right==NULL) return 1;
  if(a->left ==NULL) return 1+shortpath(a->right);
  else if(a->right==NULL) return 1+shortpath(a->left);
  return 1+min(shortpath(a->right),shortpath(a->left));
}
int BST::longpath(TreeNode* a){
  if(a==NULL) return 0;
  else if(a->left==NULL &&a->right==NULL) return 1;
  if(a->left ==NULL) return 1+longpath(a->right);
  else if(a->right==NULL) return 1+longpath(a->left);
  return 1+max(longpath(a->right),longpath(a->left));
}
void BST::update(TreeNode* k){
  if(k!=NULL){
    k->shortestPathLength=shortpath(k);
    k->longestPathLength=longpath(k);
  }
  if(k->right!=NULL)
   update(k->right);
  if(k->left!=NULL)
   update(k->left);
  
}
bool BST::insert(int JourneyCode, int price)
{ if(find(JourneyCode,price)==true){return false;} 
 else{
   TreeNode *N;
   N=new TreeNode(JourneyCode,price);
   TreeNode *x=root;
   TreeNode *T=NULL;
   while(x!=NULL){ 
     T=x;          
     if(x->JourneyCode > JourneyCode) x=x->left;
     else x=x->right;
     
      }
   N->parent=T;
   if(T==NULL){
           root=N;
        }
   else {
        if(JourneyCode>(T->JourneyCode)){
             T->right=N; }
        else{
            T->left=N;}
    }
    update(root);  
    
   return true; 
   }
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  /*struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right; 
    }
    else if (currNode->JourneyCode > JourneyCode) {
       parentOfCurrNode = currNode; 
       currNode = currNode->left;  
    } 
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }*/
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{TreeNode *x=root;

     while(x != nullptr ){
       
         if (x->JourneyCode >= JourneyCode ) {
           if(x->JourneyCode==JourneyCode) return true;
           else x=x->left;
          }
         else {
           if(x->JourneyCode==JourneyCode) return true;
           else x=x->right;
          }
         }
  return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry3 and returns True otherwise

TreeNode* BST :: minimum(TreeNode* k){
  while(k->left !=NULL){
     k=k->left;}
  return k;
}
TreeNode* BST :: successor(TreeNode* k){
 if(k->right!=NULL)
       return minimum(k->right);
  TreeNode* t=k->parent;
  while((t!=NULL)&&(k=t->right)){ 
  t=t->parent;
  k=t;
  }
  return t;

}

bool BST::remove(int JourneyCode, int price)
{ TreeNode* k=NULL;
 TreeNode* x=root;
 while(1){
 if(x==NULL)return false;
 else if(x->JourneyCode == JourneyCode && x->price == price){         
	   if(x->left == nullptr && x->right == nullptr){
	     
             if(x->parent !=NULL){
	       if((x->parent)->JourneyCode<x->JourneyCode)
		       (x->parent)->right=NULL;    
	       else 
	       (x->parent)->left=NULL;
	     }
	     else x=NULL;
	     delete x;
      
      }
   else if(x->left != nullptr && x->right == nullptr){
             
	       if(x->parent !=NULL){
	         if((x->parent)->JourneyCode<x->JourneyCode)
	            (x->parent)->right=x->left;
	         else  
	            (x->parent)->right=x->right;}
	       else root=x->left;
	       delete x;
      }
   else if(x->left == nullptr && x->right != nullptr){
            
             if(x->parent !=NULL){
	       if((x->parent)->JourneyCode<x->JourneyCode)
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
       if (x->JourneyCode > JourneyCode ) {x=x->left;}
       else {x=x->right;}
      }
     
   }
   
  
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
  
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

