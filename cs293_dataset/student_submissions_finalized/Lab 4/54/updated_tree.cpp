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
   if (root==NULL) return false;
TreeNode *x=new TreeNode;
x=root;
while (x!=NULL){
if ((x->JourneyCode==JourneyCode)&&(x->price==price)){return true;} 
if (x->price>price){x=x->left;}
else if (x->price<price) {x=x->right;}
}
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}

TreeNode* BST::search(TreeNode *T,int price,int JourneyCode){
while (T!=NULL)
{
  if ((T->JourneyCode==JourneyCode)&&(T->price==price)){return T;} 
  if (T->price>price){ return search(T->left,price,JourneyCode);}
  if (T->price<price){return search (T->right,price,JourneyCode);}
} 
return NULL;
}

TreeNode* BST::predecessor(TreeNode *T,int price){
TreeNode* x=T;
while(x->right!=NULL)
{
  x=x->right;
}
return x;
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{ 
  TreeNode* x =search(root,price,JourneyCode);
if (x==NULL) {return false;}
if((root->JourneyCode==JourneyCode)&&(root->price==price)){
if((root->left==NULL)&&(root->right==NULL)){root=NULL;return true;}

if ((root->left==NULL)&&(root->right!=NULL))
{  
   root=root->right;
   root->parent=NULL;
   return true;
}
if ((root->left!=NULL)&&(root->right==NULL))
{
   root=root->left;
   root->parent=NULL;
  return true;
}
if ((root->left!=NULL)&&(root->right!=NULL))
{
 TreeNode *pre =predecessor(root->left,root->price);
 int a=0;
 int b=0;
 a=pre->price;
 b=pre->JourneyCode;
 remove(b,a);
 root->price=a;
 root->JourneyCode=b;
return true;}
}
if (x!=root){
TreeNode* p=x->parent;
if ((x->left==NULL)&&(x->right==NULL)){
  if (p->price<price){p->right=NULL;}
  else p->left=NULL;
  x=NULL;
return true;
}
if ((x->left==NULL)&&(x->right!=NULL))
{
   if (p->price<price) p->right=x->right;
   else p->left=x->right;  
   x->right->parent=p;
   return true;
}
if ((x->left!=NULL)&&(x->right==NULL))
{
   if (p->price<x->price) p->right=x->left;
   else p->left=x->left;  
   x->left->parent=p;
return true;
}
if ((x->left!=NULL)&&(x->right!=NULL))
{
 TreeNode *pre =predecessor(x->left,x->price);
 int a=0;
 int b=0;
 a=pre->price;
 b=pre->JourneyCode;
 remove(b,a);
 x->price=a;
 x->JourneyCode=b;
return true;
}
}
return true;  
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

