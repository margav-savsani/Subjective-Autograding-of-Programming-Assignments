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

TreeNode* BST::search(int JourneyCode, int price){
  TreeNode* parent;
  parent=root;
  while (parent != nullptr){
    if(price ==parent->price && JourneyCode == parent->JourneyCode){
      return parent;
    }
    if (price < parent->price){
      parent = parent->left;
    }
    else{
      parent=parent->right;
    }
  }
  return parent;
}

void BST::updateimbalance(TreeNode* a){
  if((a->left==nullptr)&&(a->right==nullptr)){
    a->longestPathLength=0;
    a->shortestPathLength=0;
    return;
  }
  else{
    if(a->left==nullptr){
      a->shortestPathLength=a->right->shortestPathLength;
      a->longestPathLength=a->right->longestPathLength;
    }
    else if(a->right==nullptr){
      a->shortestPathLength=a->left->shortestPathLength+1;
      a->longestPathLength=a->left->longestPathLength+1;
    }
    else {
      a->shortestPathLength=min(a->right->shortestPathLength,a->left->shortestPathLength)+1;
      a->longestPathLength=min(a->right->longestPathLength,a->left->longestPathLength)+1;
    }
  }
}

void BST::update(TreeNode* a){
  if(a->left!=nullptr){
  cout<<"yes";
  update(a->left);
  }
  if(a->right!=nullptr){
  update(a->right);
  }
  updateimbalance(a);
}



bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  if(root==nullptr){
    TreeNode* j=new TreeNode(JourneyCode,price);
    root=j;
  }
  else if(parentOfCurrNode->JourneyCode<JourneyCode){
    TreeNode* j=new TreeNode(JourneyCode,price);
    parentOfCurrNode->right=j;
    parentOfCurrNode->right->parent=parentOfCurrNode;
  }
  else{
    TreeNode* j=new TreeNode(JourneyCode,price);
    parentOfCurrNode->left=j;
    parentOfCurrNode->left->parent=parentOfCurrNode;
  }
  updateimbalance(root);
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode* x;
  x=root;
  while (x != nullptr){
    if(price ==x->price && JourneyCode == x->JourneyCode){
        return true;
    }
    if (price < x->price){
        x = x->left;
    }
    else{
        x=x->right;
    }
  }  
  return false;
}

TreeNode* BST::TreeMinimum(TreeNode* x){
    while(x->left != nullptr){
        x =x->left;
    }
    return x;
}

TreeNode* BST::TreeSuccessor(TreeNode* x){
    if(x->right != nullptr){
        return TreeMinimum(x->right);
    }
    TreeNode* y = x->parent;
    while (y != nullptr and x == y->right){
        x = y;
        y = y->parent;
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
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
  TreeNode* z;
  z=search(JourneyCode,price);
  if(z==nullptr){
      return false;
  }
  if((z->left == nullptr)&&( z->right == nullptr)){
    if(z->parent->left==nullptr){
      z->parent->right=nullptr;
    }
    else if(z->parent->left==z){
      z->parent->left=nullptr;
    }
    else if(z->parent->left==z){
      z->parent->left=nullptr;
    }
    else{
      z->parent->right=nullptr;
    }
    updateimbalance(root);
    return true;
  }
  else if(z->left == nullptr){
    if(z->parent->left==z){
      z->parent->left=z->right;
    }
    else{
      z->parent->right=z->right;
    }
    updateimbalance(root);
    return true;
  }
  else if( z->right == nullptr){
    if(z->parent->left==z){
      z->parent->left=z->left;
    }
    else{
      z->parent->right=z->left;
    }
    updateimbalance(root);
    return true;
  }
  else{
    TreeNode* y;
    y = TreeSuccessor(z);
    z->price = y->price;
    z->JourneyCode=y->JourneyCode;
    if((y->left == nullptr)&&( y->right == nullptr)){
      if(y->parent->left==y){
        y->parent->left=nullptr;
      }
      else{
        y->parent->right=nullptr;
      }
      updateimbalance(root);
      return true;
    }
    else if(y->left == nullptr){
      if(y->parent->left==y){
        y->parent->left=y->right;
      }
      else{
        y->parent->right=y->right;
      }
      updateimbalance(root);
      return true;
    }
    else if( y->right == nullptr){
      if(y->parent->left==y){
        y->parent->left=y->left;
      }
      else{
        y->parent->right=y->left;
        }
      updateimbalance(root);
      return true;
    }
      updateimbalance(root);
    return true;
  }
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
