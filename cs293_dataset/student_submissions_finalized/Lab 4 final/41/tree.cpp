// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <algorithm>
#include <cmath>
#include <set>
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
  
  // struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  // while (currNode != nullptr) {
  //   if (currNode->JourneyCode < JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->right;
  //   }
  //   else if (currNode->JourneyCode > JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->left;
  //   }
  //   else { // currNode->JourneyCode == JourneyCode
  //     return false;
  //   }

  TreeNode *NEW = new TreeNode(JourneyCode,price);
  TreeNode *ins_l = root;
  TreeNode *ins_r = nullptr;
    
  while(ins_l!=nullptr){
    ins_r = ins_l;
    if(NEW->price < ins_l->price){
      ins_l = ins_l->left;
    }
    else ins_l = ins_l->right;
  }
  if(ins_r==nullptr) root = NEW;
  else if(NEW->price < ins_r->price) ins_r->left=NEW;
  else ins_r->right = NEW;
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
  
  TreeNode *ins_l = new TreeNode();
  ins_l = root;
  if(ins_l==nullptr) return false;
  if(JourneyCode > ins_l->JourneyCode) {
    BST new_tree(ins_l->right);
    return new_tree.find(JourneyCode, price);
  }
  else if(JourneyCode < ins_l->JourneyCode) {
    BST new_tree(ins_l->left);
    return new_tree.find(JourneyCode, price);
  }
  else {
    if(price==ins_l->price) return true;
    BST new_tree(ins_l->right);
    return new_tree.find(JourneyCode, price);
  }
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
  
  if(find(JourneyCode,price)==0) return false;
    else
    {
      //finding node for given journeycode and price
      TreeNode *z = root;
      while(z->price != price && z != nullptr){
          if(JourneyCode > z->JourneyCode) z=z->right;
          else if (JourneyCode < z->JourneyCode) z=z->left;
          else break;
      }
      // deletes the node
      TreeNode *new_x = new TreeNode();
      TreeNode *new_y = new TreeNode();
      if(z->right == nullptr || z->left == nullptr) new_y = z;
      else new_y = sucessor(z);
      if(new_y->left != nullptr)
      {
        new_x = new_y->left;
      }
      else new_x = new_y->right;
      if(new_x != nullptr)
      {
        new_x->parent = new_y->parent;
      }
      if(new_y->parent == nullptr)
      {
        root = new_x;
      }
      else if(new_y == new_y->parent->left)
      {
        new_y->parent->left = new_x;
      }
      else new_y->parent->right = new_x;
      if(z!=new_y)
      {
        z->JourneyCode = new_y->JourneyCode; z->price = new_y->price;
      }
      return true;
    }
}

//finding minimum node in the whole tree
struct TreeNode *BST::minimum(TreeNode *v){
    TreeNode *ins_l;
    ins_l = v;
    while(ins_l->left!=nullptr){
        ins_l = ins_l->left;
    }
    return ins_l;
}

//finding sucessor in the tree
struct TreeNode *BST::sucessor(TreeNode *v){
    TreeNode *min_2 = new TreeNode();
    if(v->right != nullptr) return minimum(v->right);
    min_2 = v->parent;
    while(min_2!=nullptr && min_2->right == v){
        v = min_2; 
        min_2 = min_2->parent; 
    }
    return min_2;
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

