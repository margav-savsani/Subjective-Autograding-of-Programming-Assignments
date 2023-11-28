// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

BST:: BST() {root = nullptr; }
 BST:: BST(TreeNode *curr_root) {root = curr_root;}
TreeNode *a;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == NULL) return 0;
  else return root->getImbalance();
}

int shortestpath(TreeNode* a){
  if(a==NULL) return 0;
  else if(a->left==NULL &&a->right==NULL) return 1;
  if(a->left ==NULL) return 1+shortestpath(a->right);
  else if(a->right==NULL) return 1+shortestpath(a->left);
  return 1+min(shortestpath(a->right),shortestpath(a->left));
}

int longestpath(TreeNode* a){
  if(a==NULL) return 0;
  else if(a->left==NULL &&a->right==NULL) return 1;
  if(a->left ==NULL) return 1+longestpath(a->right);
  else if(a->right==NULL) return 1+longestpath(a->left);
  return 1+max(longestpath(a->right),longestpath(a->left));
}

void update(TreeNode* root){
    if(root!=NULL){
      root->shortestPathLength=shortestpath(root);
      root->longestPathLength=longestpath(root);
    }
    if(root->right!=NULL)
      update(root->right);
    if(root->left!=NULL)
      update(root->left);

}

bool BST::insert(int JourneyCode, int price)
{ 
  TreeNode *z;
    z = new TreeNode(JourneyCode,price);
    if(find(JourneyCode,price))
      return false;
    else{
      TreeNode *y = NULL;
      TreeNode *x = root;
      while(x!=NULL){
        y=x;
        if(JourneyCode<x->JourneyCode)
          x = x->left;
        else
          x  = x->right;
      }
      z->parent = y;
      if(y==NULL)
        root = z;
      else {
        if(JourneyCode<y->JourneyCode)
          y->left = z;
        else 
          y->right = z;
      }
      update(root);
      return true; 
    }
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    
}

bool BST::find(int JourneyCode, int price)
{
  TreeNode *x = root;
  while(x!=NULL){
    if(JourneyCode==x->JourneyCode){
      if(price==x->price){
        a = x;
        return true;
      }
      else{
        return false;
      }
    }
    if(JourneyCode<x->JourneyCode)
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
bool BST::remove(int JourneyCode, int price)
{
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
        a->JourneyCode=y->JourneyCode;
        a->price=y->price;
        
      }
  
    }
    update(root);
    return true; 
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

