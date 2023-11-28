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

//<----------Valid: Assumption I----------->//
//Everything is under the very good assumption that Journey Codes
//for two different journeys cannot be the same.

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  
  else{
    //cout << root->shortestPathLength << " " << root->longestPathLength << endl;
    return root->getImbalance();
  } 
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  //If root is null, then it is an empty tree, simply return false.
  if(root==NULL) return false;

  //If the root's journey code is the same as the reqd journey code, 
  //then compare the prices, if they are same, then return true.
  //else return false, in accordance to Assumption I.
  if(root->JourneyCode==JourneyCode){
    if(root->price==price) return true;
    else return false;
  }

  //If the root's journey code is less than the reqd journey code, then 
  // search only in the right subtree.
  if(root->JourneyCode<JourneyCode){
    BST T2(root->right);
    return T2.find(JourneyCode, price);
  }

  // If the root's journey code is greater than the reqd journey code, then 
  // search only in the left subtree.
  BST T1(root->left);
  return T1.find(JourneyCode, price);
}


//This function update shortestPathLength and LongestPathLength
//by iterating from given TreeNode all the way to the root
//by updating all the nodes along the way.
//We use the recursive definition but iterative implementation
void BST::updateLengths(TreeNode* parentOfCurrNode){
  while(parentOfCurrNode!=nullptr){
      int rightS, leftS, rightL, leftL;
      if(parentOfCurrNode->right == nullptr){
        rightS = 1;
        rightL = 1;
      } 
      else{
        rightS = 1 + parentOfCurrNode->right->shortestPathLength;
        rightL = 1 + parentOfCurrNode->right->longestPathLength;
      } 
      if(parentOfCurrNode->left == nullptr){
        leftS = 1;
        leftL = 1;
      } 
      else{
        leftS = 1 + parentOfCurrNode->left->shortestPathLength;
        leftL = 1 + parentOfCurrNode->left->longestPathLength;
      } 

      parentOfCurrNode->shortestPathLength = min(rightS,leftS);
      parentOfCurrNode->longestPathLength = max(rightL, leftL);
      parentOfCurrNode = parentOfCurrNode->parent;
  }
}

bool BST::insert(int JourneyCode, int price){
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
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //<-----------_Important Part Below_---------------->
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  if(parentOfCurrNode == nullptr){
    root = new TreeNode(JourneyCode,price);
  }
  else{
    if(parentOfCurrNode->JourneyCode < JourneyCode){
      parentOfCurrNode->right = new TreeNode(JourneyCode, price);
      parentOfCurrNode->right->parent = parentOfCurrNode;
    }
    else{
      parentOfCurrNode->left = new TreeNode(JourneyCode, price);
      parentOfCurrNode->left->parent = parentOfCurrNode;
    }

    //update the entire path upto root
    updateLengths(parentOfCurrNode);    
  }
  return true;
}


	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
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
    
  if(!find(JourneyCode, price)) return false;
  
  //When the root itself is the required node
  if(root->JourneyCode==JourneyCode){
    root = NULL;
    return true;  
  }
  else{
    //Iteratively finding the required node and its parent.
    TreeNode* curr = root;
    TreeNode* curr_parent = NULL;
    while(!(curr->JourneyCode==JourneyCode)){
      if(curr->JourneyCode<JourneyCode){
        curr_parent = curr;
        curr = curr->right;
      }
      else{
        curr_parent = curr;
        curr = curr->left;
      }
    }
    
    //If the current node is a leaf, that is it has no children
    //Then simply delete the element
    if(curr->right == NULL && curr->left == NULL){
      if(curr_parent->JourneyCode<JourneyCode) curr_parent->right = NULL;
      else curr_parent->left = NULL;
      //update the entire path upto root
      updateLengths(curr_parent);
    }
    
    //If the current node has only one child
    //That is one of the sides(right or left) is a NULL
    //Then link the node's parent and child, thereby removing the node
    else if(curr->right == NULL || curr->left == NULL){
      if(curr->left!=NULL){
        if(curr_parent->JourneyCode<JourneyCode) curr_parent->right = curr->left;
        else curr_parent->left=curr->left;
      }
      else{
        if(curr_parent->JourneyCode<JourneyCode) curr_parent->right = curr->right;
        else curr_parent->left=curr->right;
      }
      //update the entire path upto root
      updateLengths(curr_parent);
    }
    
    //If the current Node has two children.
    //That means both the sides, right and left are not empty.
    //Firstly, delete the successor node of the current node using
    //either one of the previous two cases, depending on the case.
    //Then replace the current node with journey code and price values
    //as that of the succesor.
    else{
      TreeNode* succ = curr->right;
      TreeNode* succ_parent = curr;
      while(succ->left!=NULL){
        succ_parent = succ;
        succ = succ->left;
      }
      if(succ->right!=NULL){
        succ->right->parent = succ->parent;
        if(succ_parent==curr) succ_parent->right = succ->right;
        else succ_parent->left = succ->right;
      } 
      remove(succ->JourneyCode, succ->price);
      curr->JourneyCode = succ->JourneyCode;
      curr->price = succ->price;
      //update the entire path upto root
      updateLengths(succ_parent);
    }
  }
  return true;  
}

//Recursively destroying nodes
void BST::DestroyRecursive(TreeNode* node){
    if (node)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

BST::~BST()
{
    DestroyRecursive(root);
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode //<< " S-" << root->shortestPathLength << " L-" << root->longestPathLength
            << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false){
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

