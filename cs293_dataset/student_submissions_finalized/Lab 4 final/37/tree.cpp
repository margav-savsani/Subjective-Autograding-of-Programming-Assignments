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
void length_reset_ins(TreeNode* &To_be_ins ){
    while(To_be_ins!=nullptr){
      if(To_be_ins->right!=nullptr && To_be_ins->left!=nullptr){
        if((To_be_ins->right)->shortestPathLength < (To_be_ins->left)->shortestPathLength )
          To_be_ins->shortestPathLength = (To_be_ins->right)->shortestPathLength +1;
        else 
          To_be_ins->shortestPathLength = (To_be_ins->left)->shortestPathLength +1;

        if((To_be_ins->right)->longestPathLength < (To_be_ins->left)->longestPathLength )
          To_be_ins->longestPathLength = (To_be_ins->left)->longestPathLength +1;
        else  
          To_be_ins->longestPathLength = (To_be_ins->right)->longestPathLength +1;
      }

      else if(To_be_ins->right!=nullptr || To_be_ins->left!=nullptr){
        if(To_be_ins->right!=nullptr){
          To_be_ins->longestPathLength = (To_be_ins->right)->longestPathLength +1;
          To_be_ins->shortestPathLength = 1;
        }
       else{
          To_be_ins->longestPathLength = (To_be_ins->left)->longestPathLength +1;
          To_be_ins->shortestPathLength = 1;
        }
      }
      else{
        To_be_ins->shortestPathLength = 1;
        To_be_ins->longestPathLength = 1;
      }
      To_be_ins=To_be_ins->parent;
     
    }
    return;
}

void length_reset_del(TreeNode* &To_be_ins ){

    while(To_be_ins!=nullptr){
      if(To_be_ins->right!=nullptr && To_be_ins->left!=nullptr){
        if((To_be_ins->right)->shortestPathLength < (To_be_ins->left)->shortestPathLength )
          To_be_ins->shortestPathLength = (To_be_ins->right)->shortestPathLength -1;
        else 
          To_be_ins->shortestPathLength = (To_be_ins->left)->shortestPathLength -1;

        if((To_be_ins->right)->longestPathLength < (To_be_ins->left)->longestPathLength )
          To_be_ins->longestPathLength = (To_be_ins->left)->longestPathLength -1;
        else  
          To_be_ins->longestPathLength = (To_be_ins->right)->longestPathLength -1;
      }

      else if(To_be_ins->right!=nullptr || To_be_ins->left!=nullptr){
        if(To_be_ins->right!=nullptr){
          To_be_ins->longestPathLength = (To_be_ins->right)->longestPathLength -1;
          To_be_ins->shortestPathLength = 1;
        }
       else{
          To_be_ins->longestPathLength = (To_be_ins->left)->longestPathLength -1;
          To_be_ins->shortestPathLength = 1;
        }
      }
      else{
        To_be_ins->shortestPathLength = 1;
        To_be_ins->longestPathLength = 1;
      }

      To_be_ins=To_be_ins->parent;
    }
    return;

}
int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  

  if(root==nullptr){
    root=new TreeNode(JourneyCode,price);
    root->longestPathLength=1;
    root->shortestPathLength=1;
    return true;
  }
  
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
  TreeNode* To_be_ins=new TreeNode(JourneyCode,price);
  To_be_ins->longestPathLength=1;
  To_be_ins->shortestPathLength=1;
  To_be_ins->parent=parentOfCurrNode;
  if(parentOfCurrNode->JourneyCode < JourneyCode)
    parentOfCurrNode->right=To_be_ins;
  else  
    parentOfCurrNode->left=To_be_ins;
  parentOfCurrNode->longestPathLength=(parentOfCurrNode->longestPathLength==1)? 2:parentOfCurrNode->longestPathLength;
  parentOfCurrNode->shortestPathLength=2;
  To_be_ins=parentOfCurrNode;
  
  length_reset_ins(To_be_ins);
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    return true;

}

TreeNode* successor(TreeNode* x){
    
    if(x->right !=nullptr){
        TreeNode* y=x->right;
        while(y->left != nullptr){
        y=y->left;
        }
        return y;
    }
    
    TreeNode* y=x->parent;
    while (y !=nullptr && x==y->right)
    {
        x=y;
        y=y->parent;
    }
    if(y!=nullptr)
        return y;
    else return x;
    
        
    
        
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  struct TreeNode *currNode = root;
  if(root=nullptr){
    
    return false;
  }
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
    
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return true;
    }
  }
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if(!find(JourneyCode,price)) return false;
    
    TreeNode* z=root;
    TreeNode* y;
    TreeNode* x;
    if(z == nullptr)return false;
    
    while(z != nullptr && z->JourneyCode!=JourneyCode ){
       
        if(z->JourneyCode > JourneyCode){
            z= z->left;
        }
        else z=z->right;

    }
    
    if(z == nullptr)return false;
    TreeNode* zp=z->parent;
    if(z->left==nullptr && z->right == nullptr){ //case:1
        if(zp != nullptr)
            {
            if(zp->JourneyCode > z->JourneyCode)
                zp->left=nullptr;
            else zp-> right=nullptr;
            length_reset_del(zp);
            return true;
            }
        else{
            root=nullptr;
            
            return true;
        }
        
    }
    
    if((z->left!=nullptr && z->right == nullptr)){ //case-2
        if(zp != nullptr){
            (z->left)->parent=zp;
            if(JourneyCode < zp->JourneyCode)
                zp->left=z->left;
            else zp->right=(z->left);
            length_reset_del(zp);
            return true;
        }
        else{
            (z->left)->parent=nullptr;
            root=(z->left);
            
            return true;
        }
        
        
    }
   
    if((z->left==nullptr && z->right!= nullptr)){ //case-2
        if(zp != nullptr){
            (z->right)->parent=z->parent;
            if((z->right)<z->parent)
                zp->left=(z->right);
            else zp->right=(z->right);
            length_reset_del(zp);
            return true;
        }
        else{
            (z->right)->parent=nullptr;
            root=(z->right);
            
            return true;
        }
        
    }   
    
    if(JourneyCode != successor(z)->JourneyCode){ //cas-3;
        y=successor(z);
        remove(y->JourneyCode,y->price);
        z->JourneyCode=y->JourneyCode;
        z->price=y->price;
        return true;
        
    }
    return true;

  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
    return false;
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

