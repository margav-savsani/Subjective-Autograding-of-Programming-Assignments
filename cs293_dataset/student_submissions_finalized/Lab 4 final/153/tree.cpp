// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance(){
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price){
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  if(this->findAndReturn(JourneyCode, price) != nullptr) return false;

  if(this->root == nullptr){
      this->root = makeLeaf(JourneyCode, price, nullptr);
      return true;
  }

  TreeNode* cur_node = this->root;
  TreeNode* prev_node = nullptr;
  
  while(cur_node != nullptr){
      if(cur_node->JourneyCode == JourneyCode) return false;
      if(price < cur_node->price){
          prev_node = cur_node;
          cur_node = prev_node->left;
      }else{
          prev_node = cur_node;
          cur_node = prev_node->right;
      }
  }

  if(price < prev_node->price && prev_node->left == nullptr){
      cur_node = makeLeaf(JourneyCode, price, prev_node);
      prev_node->left = cur_node;
  }else if(prev_node->right == nullptr){
      cur_node = makeLeaf(JourneyCode, price, prev_node);
      prev_node->right = cur_node;
  }

  this->updatePathLengths(cur_node);
  return true;
}

void BST::updatePathLengths(TreeNode* node){
    if(node == nullptr) return;
    
    if(node->left == nullptr && node->right == nullptr){
        node->longestPathLength = node->shortestPathLength = 1;
    }else if(node->left != nullptr && node->right == nullptr){
        node->longestPathLength = node->left->longestPathLength + 1;
        node->shortestPathLength = node->left->shortestPathLength + 1;
    }else if(node->left == nullptr && node->right != nullptr){
        node->longestPathLength = node->right->longestPathLength + 1;
        node->shortestPathLength = node->right->shortestPathLength + 1;
    }else{
        node->longestPathLength = max(node->left->longestPathLength + 1, node->right->longestPathLength + 1);
        node->shortestPathLength = min(node->left->shortestPathLength + 1, node->right->shortestPathLength + 1);
    }
    
    this->updatePathLengths(node->parent);
}

TreeNode* BST::makeLeaf(int JourneyCode, int price, TreeNode* parent){
    TreeNode* res = new TreeNode();
    res->price = price;
    res->JourneyCode = JourneyCode;
    res->parent = parent;
    res->right = nullptr;
    res->left = nullptr;

    return res;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  return (this->findAndReturn(JourneyCode,price) != nullptr);
}
TreeNode* BST::findAndReturn(int JourneyCode, int price){
    TreeNode* cur_node = this->root;

    while(cur_node != nullptr){
        if(cur_node->JourneyCode==JourneyCode && cur_node->price==price) return cur_node;

        if(price < cur_node->price) cur_node = cur_node->left;
        else cur_node = cur_node->right;
    }

    return nullptr;
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
  return this->removeNode(this->findAndReturn(JourneyCode, price));    
}
bool BST::removeNode(TreeNode* cur_node){
    if(cur_node == nullptr) return false;

    if(cur_node->right == nullptr && cur_node->left==nullptr){
        if(this->isLeftChild(cur_node)) cur_node->parent->left = nullptr;
        else cur_node->parent->right = nullptr;
        this->updatePathLengths(cur_node->parent);

        delete cur_node;
    }else if(cur_node->right == nullptr){
        cur_node->left->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->left;
        else cur_node->parent->right = cur_node->left;
        this->updatePathLengths(cur_node->parent);

        delete cur_node;
    }else if(cur_node->left == nullptr){
        cur_node->right->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->right;
        else cur_node->parent->right = cur_node->right;
        this->updatePathLengths(cur_node->parent);

        delete cur_node;
    }else{
        TreeNode* successor = this->minNode(cur_node->right);
        cur_node->price = successor->price;
        cur_node->JourneyCode = successor->JourneyCode;

        return this->removeNode(successor);
    }

    return true;
}

bool BST::isLeftChild(TreeNode* node){
    if(node->parent == nullptr) return false;
    return (node->parent->left == node);
}

TreeNode* BST::minNode(TreeNode* sub_root){
    if(sub_root == nullptr) return nullptr;

    TreeNode* res = sub_root;
    while(res->left != nullptr) res = res->left;

    return res;
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

