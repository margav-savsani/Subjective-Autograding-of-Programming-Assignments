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
  }
  TreeNode* nnode;
  nnode=new TreeNode(JourneyCode,price);
  nnode->longestPathLength=1;
  nnode->shortestPathLength=1;
  nnode->parent=parentOfCurrNode;
  if(parentOfCurrNode==nullptr)root=nnode;
  else if(JourneyCode<parentOfCurrNode->JourneyCode)parentOfCurrNode->left=nnode;
  else parentOfCurrNode->right=nnode;
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //

  TreeNode* curr=parentOfCurrNode;

  do{
    if(curr==nullptr)break;
    if(curr->left==nullptr){
      curr->longestPathLength=1+curr->right->longestPathLength;
      curr->shortestPathLength=1;
    }
    else if(curr->right==nullptr){
      curr->longestPathLength=1+curr->left->longestPathLength;
      curr->shortestPathLength=1;
    }
    else{
      curr->shortestPathLength=1+min(curr->left->shortestPathLength,curr->right->shortestPathLength);
      curr->longestPathLength=1+max(curr->left->longestPathLength,curr->right->longestPathLength);
    }
    curr=curr->parent;
  }while(curr!=nullptr);

  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  //cout<<root->getImbalance()<<endl;
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *x;
    x=root;
    while(x!=NULL){
        if(x->JourneyCode == JourneyCode){
            if(x->price == price) return true;
            else return false;
        }
        else if(x->JourneyCode > JourneyCode) x=x->left;
        else x=x->right;
    }
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}

TreeNode* BST::getNode(int JourneyCode ,int price){
    TreeNode *x;
    x=root;
    while(x!=NULL){
        if(x->JourneyCode ==JourneyCode){
            if(x->price == price) return x;
        }
        else if(x->JourneyCode >JourneyCode) x=x->left;
        else x=x->right;
    }
    return NULL;
}
	
TreeNode* BST::succesessor(TreeNode* node){
    if(node->right!=NULL){
        TreeNode* x;
        x=node;
        if(x==NULL)return NULL;
        while(x->left!=NULL){
            x=node->left;
        }
        return x;
    }
    TreeNode* y=node->parent;
    while(y!=NULL && node==y->right){
        node=y;
        y=y->parent;
    }
    return y;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.

  bool found=find(JourneyCode ,  price);
  if(found==false)return false;
  TreeNode* z=getNode(JourneyCode,price);
  TreeNode* y,*x;
  if(z->left==NULL || z->right==NULL)y=z;
  else y=succesessor(z);
  if(y->left!=NULL)x=y->left;
  else x=y->right;
  if(x!=NULL)x->parent=y->parent;
  if(y->parent==NULL)root=x;
  else if(y==y->parent->left)y->parent->left=x;
  else y->parent->right=x;
  if(y!=z){
    z->price=y->price;
    z->JourneyCode=y->JourneyCode;
  }
  TreeNode* curr=x->parent;

  do{
    if(curr->left==nullptr){
      curr->longestPathLength=1+curr->right->longestPathLength;
      curr->shortestPathLength=1+curr->right->longestPathLength;
    }
    if(curr->right==nullptr){
      curr->longestPathLength=1+curr->left->longestPathLength;
      curr->shortestPathLength=1+curr->left->longestPathLength;
    }
    else{
      curr->shortestPathLength=1+min(curr->left->shortestPathLength,curr->right->shortestPathLength);
      curr->longestPathLength=1+max(curr->left->longestPathLength,curr->right->longestPathLength);
    }
    curr=curr->parent;
  }while(curr!=root);
  
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
  return true;
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

