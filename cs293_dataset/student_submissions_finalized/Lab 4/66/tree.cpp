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

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

TreeNode* BST::findleave(TreeNode* x){
    
    if(x->left==nullptr) {return x;}
    else { return findleave(x->left);}
}

TreeNode* BST::findelement(TreeNode* x,int j,int p){
   
   if( x->price==p&&x->JourneyCode==j){   return x; 
                }
   else if(  x->price==p&&x->JourneyCode!=j){return nullptr;}           
                
                   
   else if(x->price < p){
                if(x->right==nullptr) {return nullptr;}
               else {return findelement(x->right,j,p);}
     }
     
   else {      if(x->left==nullptr) {return nullptr;}
               
               else {return findelement(x->left,j,p);}
   }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if(root==nullptr) { return false;}
     else {  
          if(findelement(root,JourneyCode,price)==nullptr) { return false;}
          else { return true; }
     } 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
   if(findelement(root,JourneyCode,price)==NULL) {return false;}
   else { 
         TreeNode* x = findelement(root,JourneyCode,price);
         
         if(x->left==nullptr && x->right == nullptr) { 
          
                                                       if((x->parent)->left==x)     {(x->parent)->left=nullptr;}
                                                       else {  (x->parent)->right=nullptr;}}
         else if(x->left==nullptr || x->right == nullptr) { 
                  if(x->left==nullptr) { if((x->parent)->left==x) {(x->parent)->left==x->right;(x->right)->parent=x->parent;}
                                         else { (x->parent)->right==x->right;(x->right)->parent=x->parent; }
                                       }
                  if(x->right==nullptr) { if((x->parent)->left==x) {(x->parent)->left==x->left;(x->left)->parent=x->parent;}
                                         else { (x->parent)->right==x->left; (x->left)->parent=x->parent;}
                                       }
          }
        else{
             
              TreeNode *y=findleave(x->right);
              (y->parent)->left=nullptr;
              if(x->parent!=nullptr){y->parent=x->parent;}
              else {y->parent=nullptr;}
              y->left=x->left; y->right=x->right;
              (x->left)->parent=y;(x->right)->parent=y;
              
        }
      return true; }
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

