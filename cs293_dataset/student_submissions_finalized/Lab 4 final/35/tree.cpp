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
int BST::min_height(TreeNode*T){
  int h = 0;
   if (T != nullptr) {
      int l_height = min_height(T->left);
      int r_height = min_height(T->right);
      int minheight = min(l_height, r_height);
      h = minheight + 1;
   }
   return h;
}
int BST::max_height(TreeNode* T){
  int h = 0;
   if (T != nullptr) {
      int l_height = max_height(T->left);
      int r_height = max_height(T->right);
      int maxheight = max(l_height, r_height);
      h = maxheight + 1;
   }
   return h;
}
int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else { return max_height(root)-min_height(root);}
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  /* struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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
  } */
  if(this->find(JourneyCode,price)){return false;}  
    TreeNode * New = new TreeNode();
    New->JourneyCode = JourneyCode;
    New->price = price;
    New->parent = nullptr;
    TreeNode * y = nullptr;
    TreeNode * x = this->root;
    while(x != nullptr){
        y = x;
        if(JourneyCode < x->JourneyCode ){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    New->parent = y;
    if( y == nullptr){
        this->root = New;
    }
    else if(JourneyCode  < y->JourneyCode ){
        y->left = New;
    }
    else if(JourneyCode  > y->JourneyCode ){
        y->right = New;
    }
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
  if(this->root == nullptr){  
        return false;
    }
    TreeNode* x = this->root;
    while((x!= nullptr)&&(x->JourneyCode != JourneyCode)){
        if(x->JourneyCode > JourneyCode){x = x->left;}
        else{x = x->right;}
    }
    if(x == nullptr){
        return false;
    }
    else if((x->JourneyCode == JourneyCode)&&(x->price == price)){
        
        return true;
    }
    else {return false;};
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* BST :: superfind(int JourneyCode, int price){
    if(this->root == nullptr){
        return nullptr;
    }
    TreeNode* x = this->root;
    while((x!= nullptr)&&(x->JourneyCode  != JourneyCode )){
        if(x->JourneyCode  > JourneyCode ){x = x->left;}
        else{x = x->right;}
    }
    if(x == nullptr){
        return nullptr;
    }
    else if((x->price == price)&&(x->JourneyCode == JourneyCode)){
        return x;
    }
    else return nullptr;
}
TreeNode * BST :: predecessor(TreeNode * T){
    if(T->left == nullptr){
        return nullptr;
    }
    TreeNode * x = T->left;
    while(x->right != nullptr){
        x = x->right;
    }
    return x;
}
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
  TreeNode * x = this->superfind(JourneyCode,price);
    if(x == nullptr) return false; 
    if((x->left == nullptr)&&(x->right == nullptr)){
        if(x->parent == nullptr){this->root = nullptr;}
        else if(x->parent->JourneyCode  > x->JourneyCode){
            x->parent->left = nullptr;
        }
        else{x->parent->right = nullptr;}
        return true;
    }
    if((x->left == nullptr)&&(x->right != nullptr)){
        if(x->parent == nullptr){
            this->root = x->right;
            x->right->parent = nullptr;
        }
        else if(x->parent->JourneyCode  > x->JourneyCode ){
            x->parent->left = x->right;
            x->right->parent = x->parent;
        }
        else if(x->parent->JourneyCode < x->JourneyCode){
            x->parent->right = x->right;
            x->right->parent = x->parent;
        }
        return true;
    }
    if((x->left != nullptr)&&(x->right == nullptr)){
        if(x->parent==nullptr){
            this->root = x->left;
            x->left->parent = nullptr;
        }
        else if(x->parent->JourneyCode > x->JourneyCode){
            x->parent->left = x->left;
            x->left->parent = x->parent;
        }
        else if(x->parent->JourneyCode < x->JourneyCode){
            x->parent->right = x->left;
            x->left->parent = x->parent;
        }
        return true;
    }
    if((x->left != nullptr)&&(x->right != nullptr)){
        TreeNode * z = predecessor(x);
        if(z->left != nullptr){
            z->left->parent = z->parent;
            z->parent->right = z->left;
            if(x->parent->left = x){
                x->parent->left = z;
            }
            else if(x->parent->right = x){
                x->parent->right = z;
            }
            x->left->parent = z;
            x->right->parent = z;
        }
        else{
            if(x->left != z){
                z->parent->right = nullptr;
                x->left->parent = z;
                x->right->parent = z;
                if(x->parent->left = x){
                    x->parent->left = z;
                }
                else if(x->parent->right = x){
                    x->parent->right = z;
                }
            }
            else{
            x->right->parent = z;
            if(x->parent->left = x){
                x->parent->left = z;
            }
            else if(x->parent->right = x){
                x->parent->right = z;
            }
            }
        }
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

