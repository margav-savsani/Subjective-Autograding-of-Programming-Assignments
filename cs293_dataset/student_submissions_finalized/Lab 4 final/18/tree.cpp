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

struct TreeNode* BST::search(int JourneyCode, int price){
    TreeNode *y = root;
    while(y!=nullptr){
        if(price==y->JourneyCode) break;
        if(price<y->JourneyCode) {
            y=y->left;
        }
        else y=y->right;
    }
    return y;
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  if(currNode==nullptr){
      TreeNode *x = new TreeNode(JourneyCode,price);
      root=x;
      root->shortestPathLength=root->longestPathLength=1;
      return true;
  }
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

    TreeNode *insertion = new TreeNode(JourneyCode,price);
    insertion->parent=parentOfCurrNode;
    if(parentOfCurrNode==nullptr) root=insertion;
    else if(insertion->JourneyCode<parentOfCurrNode->JourneyCode) parentOfCurrNode->left = insertion;
    else parentOfCurrNode->right = insertion;
    TreeNode *parent = insertion->parent;
    insertion->shortestPathLength=insertion->longestPathLength=1; //because in the updated_tree.h file, the constructor says that the shortest path length and the lognest path length for the root is 1, when only the root is present
    parent->shortestPathLength=parent->longestPathLength=2;
    parent=parent->parent;
    while(parent!=nullptr){
      if(parent->left==nullptr){
        parent->shortestPathLength=parent->right->shortestPathLength+1;
        parent->longestPathLength=parent->right->longestPathLength+1;
      }
      else if(parent->right==nullptr){
        parent->shortestPathLength=parent->left->shortestPathLength+1;
        parent->longestPathLength=parent->left->longestPathLength+1;
      }
      else{
        int shorter=min(parent->left->shortestPathLength,parent->right->longestPathLength);
        int longer=max(parent->left->longestPathLength,parent->right->longestPathLength);
        parent->shortestPathLength=shorter+1;
        parent->longestPathLength=longer+1;
      }
      parent=parent->parent;
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
bool BST::find(int JourneyCode, int price){

  if(search(JourneyCode,price)!=nullptr) return true;
    return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  }
	
struct TreeNode* BST::successor(int JourneyCode, int price){
    TreeNode *x =new TreeNode;
    x=search(JourneyCode, price);
    if(x==nullptr) return x;
    if(x->right!=nullptr){
        TreeNode *y=root->right;
        while(y->left != nullptr){
            y = y->left;
        }
        return y;
    }
    TreeNode *parent=x->parent;
    while((parent!=nullptr)&&(x==parent->right)){
        x=parent;
        parent=parent->parent;
    }
    return parent;
    
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

  if(!find(JourneyCode, price)) return false;
    TreeNode *x=search(JourneyCode,price);
    if((x->left==nullptr)&&(x->right==nullptr)){
        x->parent->left=nullptr;
        x->parent->right=nullptr;
    }
    else if((x->left==nullptr)&&(x->right!=nullptr)){
        x->right->parent = x->parent;
        x->parent->right=x->right;
        x->parent->left=nullptr;

    }
    else if((x->left!=nullptr)&&(x->right==nullptr)){
        x->left->parent = x->parent;
        x->parent->left=x->left;
        x->parent->right=nullptr;
    }
    else if((x->left!=nullptr)&&(x->right!=nullptr)){
        TreeNode *succ=successor(JourneyCode, price);
        remove(succ->JourneyCode,succ->price);
        x=succ;
    }

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

