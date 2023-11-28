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
int BST:: shortestLength(TreeNode*t){
  
  if(t==NULL)  return 0;
  
  if((t->right==NULL)&&(t->left!=NULL))  return (shortestLength(t->left)+1);
  
  if((t->left==NULL)&&(t->right!=NULL)) return (shortestLength(t->right)+1);
  
  if((t->left==NULL)&&(t->right==NULL)) return 1;
  return (min(shortestLength(t->right),shortestLength(t->left))+1);

}

int BST:: longestLength(TreeNode*t){

  if(t==NULL) return 0;
  if((t->left==NULL)&&(t->left!=NULL)) return (longestLength(t->right)+1);
  if((t->right==NULL)&&(t->right!=NULL))  return (longestLength(t->left)+1);
  if((t->left==NULL)&&(t->right!=NULL)) return 1;
  return (max(longestLength(t->left),longestLength(t->right)) +1);

}

void BST:: update(TreeNode*t){
  TreeNode*x;
  TreeNode*y;
 t->longestPathLength = longestLength(t);
 t->shortestPathLength = shortestLength(t);
  x=t->left;
  y=t->right;
  while(x!=NULL)
  {update(x);}
  while(y!=NULL){
  update(y);}

}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  if(find(JourneyCode,price)){return false;}
     TreeNode *z = new TreeNode;
    if (root==NULL){
        root=z;
        z->price=price;
        z->JourneyCode=JourneyCode;
        z->left=NULL;
        z->right=NULL;
        update(root);
        return true;
    }
    TreeNode *y=NULL;
    TreeNode *t =root;

    while(t!=NULL){
    if(t->JourneyCode==JourneyCode){return false;}
    else if(t->price>=price){
        y=t;
        t=t->left;}
    else if(t->price<price){
        y=t ;
        t=t->right;}  
    }
    if(y->price>price) y->left = new TreeNode(JourneyCode,price,NULL,NULL,y);
    else y->right =  new TreeNode(JourneyCode,price,NULL,NULL,y);
    update(root);
    return true;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
}
 

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    
// Return True, if the ticket with given attributes is found, false otherwise
TreeNode* BST::find2(TreeNode*root,int JourneyCode, int price){
    if(root==NULL){return NULL;}
    TreeNode*t=root;
    if(t->price>price)return find2(t->left,JourneyCode,price);
    if(t->price<price)return find2(t->right,JourneyCode,price);
    if(t->price==price) return t;
       return t; }
bool BST::find(int JourneyCode, int price)
{ 
  TreeNode*k= find2(root, JourneyCode,  price );
  if(k==NULL)return false;
  return true;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* BST::Minimum(TreeNode*x){
    
     while(x->left!=NULL){
       x=x->left;
    }     
    return x;
}

struct TreeNode* BST:: deleteNode(struct TreeNode* root, int price)
{
    // base case
    if (root == NULL)
        return root;
  
    // If the key to be deleted is 
    // smaller than the root's
    // key, then it lies in left subtree
    if (price < root->price)
        root->left = deleteNode(root->left, price);
  
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (price > root->price)
        root->right = deleteNode(root->right, price);
  
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
        
        // node with only one child or no child
        else if (root->left == NULL) {
            root=root->right;
            return root;
        }
        else if (root->right == NULL) {
           root=root->left;
            return root;
        }
  
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        struct TreeNode* temp =  Minimum(root->right);
                 
        // Copy the inorder successor's content to this node
        root->price = temp->price;
  
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->price);
    }
    return root;}
bool BST::remove(int JourneyCode, int price)
{
   
   if(!find(JourneyCode,price)) return false;
   else {
     root = deleteNode(root,price);
     update(root);
     return true;}
     
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

