// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include "updated_tree.h"

using namespace std;


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


int BST::max(int a,int b){
  if(a>b)return a ;
  else return b ;
}

int BST::min(int a,int b){
  if(a>b)return b ;
  else return a ;
}


bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  //struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  /*while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else {      // currNode->JourneyCode == JourneyCode
      return false;
    }
  }*/
   
    TreeNode* new_node;
    new_node = new TreeNode(JourneyCode,price);

    TreeNode* node1;
    TreeNode* node2;
    node1 = root;
    node2 = nullptr;
    while(node1 != nullptr){
        node2 = node1 ;
        if(price == node1->price){ return false;}
        if(price < node1->price) { node1 = node1->left; }
        else node1 = node1->right;
    }

    new_node->parent = node2 ;
    if(node2 == nullptr){
      root=new_node; 
    }
    else if(price < node2->price) {
      node2->left = new_node;
    }
    else {
      node2->right = new_node;
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
    
  return false;
}

int BST::shortestLength(TreeNode *s){
    if(s == nullptr){return 0 ;}
    else if((s->left == nullptr)||(s->right == nullptr)){
      return 1 ;
    }
    else{
      return (1 + min(shortestLength(s->left),shortestLength(s->right)));
    }
}

int BST::longestLength(TreeNode *j){
    if(j == nullptr){return 0 ;}
    else if((j->left == nullptr)&&(j->right == nullptr)){
      return 1 ;
    }
    else{
      return (1 + max(longestLength(j->left),longestLength(j->right)));
    }
}

int BST::getImbalance(){
  return longestLength(root) - shortestLength(root) ;
}



// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft=false)
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

void BST::getBST(const string &prefix,  bool isLeft=false)
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


