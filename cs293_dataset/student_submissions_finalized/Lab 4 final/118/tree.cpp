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

//To check whether any of the entries have this journey code by checking each element recursively
bool BST::find_JC(int *JourneyCode, TreeNode *node){
  if(node==nullptr)
    return false;
  else if(node->JourneyCode==*JourneyCode)
    return true;
  else
    return(find_JC(JourneyCode, node->left)||find_JC(JourneyCode, node->right));
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
TreeNode* BST::insert(int JourneyCode, int price) {
  //Checks whether there is tree or not
  //If not, creates the entry at the root
  
  if(root==nullptr){
    root=new TreeNode(JourneyCode, price);
    root->parent=nullptr;
    return root;
  } 
  TreeNode *curr=root;
  //To check whether an entry with the same journey code exists
  if(find_JC(&JourneyCode, root))
    return nullptr;
  //while loop to find the location of insertion
  while(true){
    if(JourneyCode<=curr->JourneyCode){
      if(curr->left==nullptr){
        curr->left=new TreeNode(JourneyCode, price);
        curr->left->parent=curr;
        return curr->left;
      }
      curr=curr->left;
    }
    else{
      if(curr->right==nullptr){
        curr->right=new TreeNode(JourneyCode, price);
        curr->right->parent=curr;
        return curr->right;
      }
      curr=curr->right;
    }
  }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
  TreeNode *curr=root;
  //whike loop to find the entry with the given price
  //If such a entry is found, the journey codes are compared
  while(curr!=nullptr){
    if(price==curr->price){
      if(curr->JourneyCode==JourneyCode)
        return true;
      else
        curr=curr->left;
    }
    else if(price<curr->price)
      curr=curr->left;
    else
      curr=curr->right;
  }
  return false; 
}

void BST::delete_node(TreeNode *node){
  TreeNode **parent_ptr; //To store the pointer to the varaible which stores the address of the node we want to delete
  //Checks whether the node to be deleted is the root
  //If true, creates a temporary parent to the root and calls the function again
  if(node->parent==nullptr){
    TreeNode *root_parent;
    root_parent=new TreeNode(0,root->price-1,nullptr,root,nullptr);
    root->parent=root_parent;
    delete_node(root);
    root=root_parent->right;
    if(root!=nullptr)
      root->parent=nullptr;
    delete root_parent;
    return;
  }
  //To find the pointer to the variable which stores the address of the node we weant to delete
  if(node->price>node->parent->price) 
    parent_ptr=&(node->parent->right);
  else
    parent_ptr=&(node->parent->left);
  //Deletes teh node directly as it has no children
  if(node->left==nullptr && node->right==nullptr){
    *parent_ptr=nullptr;
    delete node;
  }
  //Deletes the node and puts its left child in its position
  else if(node->right==nullptr){
    *parent_ptr=node->left;
    node->left->parent=node->parent;
    delete node;
  }
  //Deletes the node and puts its right child in its position
  else if(node->left==nullptr){
    *parent_ptr=node->right;
    node->right->parent=node->parent;
    delete node;
  }
  //Deletes the node, find the node in its left subtree with the maximum price and then putis it in its position
  else{
    TreeNode *curr=node->left;
    //Checks whether the root of the left subtree is the node with the maximum price
    if(curr->right==nullptr){
      curr->right=node->right;
      if(node->right!=nullptr)
        node->right->parent=curr;
      curr->parent=node->parent;
      *parent_ptr=curr;
      delete node;
    }
    else{
      curr=curr->right;
      while(curr->right!=nullptr)
        curr=curr->right;
      *parent_ptr=curr;
      curr->parent->right=curr->left;
      if(curr->left!=nullptr)
        curr->left->parent=curr->parent;
      curr->parent=node->parent;
      curr->right=node->right;
      node->right->parent=curr;
      curr->left=node->left;
      node->left->parent=curr;
      delete node;
    }
  }
}
  
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
  TreeNode *curr=root;
  //while loop to find the node to be deleted
  //After finding the node, it calls delete_node() to delete it
  while(curr!=nullptr){
    if(price==curr->price){
      if(curr->JourneyCode==JourneyCode){
        delete_node(curr);
        return true;
      }
      else
        curr=curr->left;
    }
    else if(price<curr->price)
      curr=curr->left;
    else
      curr=curr->right;
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

