// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

void BST::print_root(){
  std::cout<<root->JourneyCode<<endl;
}


int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else{
    int longestpathlength = this->findlongestlength(root);
    int shortestpathlength = this->findshortestlength(root);
    return longestpathlength-shortestpathlength;
  }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

  if(find(JourneyCode, price)==true){
    return false;
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
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  TreeNode* new_node = new TreeNode(JourneyCode, price, NULL, NULL, parentOfCurrNode);
  if(parentOfCurrNode==NULL){
    root=new_node;
    return true;
  }else if(JourneyCode < parentOfCurrNode->JourneyCode){
    parentOfCurrNode->left=new_node;
    return true;
  }else if(JourneyCode > parentOfCurrNode->JourneyCode){
    parentOfCurrNode->right=new_node;
    return true;
  }else{
    return false;
  }
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
    TreeNode *x = root;
    while(x!=nullptr && x->JourneyCode!=JourneyCode){
        if(JourneyCode < x->JourneyCode){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    else if(x->JourneyCode==JourneyCode){
        return true;
    }else{
        return false;
    }
}

TreeNode* BST::find_node(int JourneyCode, int price){
  TreeNode* x =root;
  while(x!=nullptr && x->JourneyCode!=JourneyCode){
    if(JourneyCode<x->JourneyCode){
      x=x->left;
    }else{
      x=x->right;
    }
  }

  if(x==nullptr){
    return NULL;
  }else if(x->JourneyCode==JourneyCode){
    return x;
  }else{
    return NULL;
  }

}

TreeNode* BST::min(TreeNode* x){
  if(x==NULL){
    return NULL;
  }
  while(x->left!=NULL){
    x=x->left;
  }
  return x;
}

TreeNode* BST::succ(TreeNode* x){
  if(x==NULL){
    return NULL;
  }
  if(x->right!=NULL){
    return min(x->right);
  }
}

int BST::findshortestlength(TreeNode* x){
  if(x==NULL){
    return 0;
  }else{
    return std::min(findshortestlength(x->left), findshortestlength(x->right)) + 1;
  }
}

int BST::findlongestlength(TreeNode* x){
  if(x==NULL){
    return 0;
  }else{
    return std::max(findlongestlength(x->left), findlongestlength(x->right)) + 1;
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

  TreeNode* x = find_node(JourneyCode, price);
  if(x==NULL){
    return false;
  }
  if(x->left==NULL && x->right==NULL){
    if(x->parent==NULL){
      x=NULL;
      root=NULL;
      return true;
    }else{
      if(x->parent->left==x){
        x->parent->left=NULL;
        x->parent=NULL;
        x=NULL;
        return true;
      }
      if(x->parent->right==x){
        x->parent->right=NULL;
        x->parent=NULL;
        x=NULL;
        return true;
      }
    }
  }
  if(x->left==NULL && x->right!=NULL){
    if(x->parent== NULL){
      x->right->parent=NULL;
      root=x->right;
      x->right=NULL;
      x=NULL;
      return true;
    }
    if(x->parent->left==x){
      x->parent->left=x->right;
      x->right->parent=x->parent;
      x->right=NULL;
      x->parent=NULL;
      x=NULL;
      return true;
    }
    if(x->parent->right==x){
      x->parent->right=x->right;
      x->right->parent=x->parent;
      x->parent=NULL;
      x->right=NULL;
      x=NULL;
      return true;
    }
  }
  if(x->left!=NULL && x->right==NULL){
    if(x->parent==NULL){
      x->left->parent=NULL;
      root=x->left;
      x->left==NULL;
      x=NULL;
      return true;
    }
    if(x->parent->left==x){
      x->parent->left=x->left;
      x->left->parent=x->parent;
      x->left=NULL;
      x->parent=NULL;
      x=NULL;
      return true;
    }
    if(x->parent->right==x){
      x->parent->right=x->left;
      x->left->parent=x->parent;
      x->parent=NULL;
      x->left=NULL;
      x=NULL;
      return true;
    }
  }
  if(x->left!=NULL && x->right!=NULL){
    TreeNode* z= succ(x);
    x->JourneyCode=z->JourneyCode;
    x->price=z->price;
    remove(z->JourneyCode, z->price);
    return true;
  }
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


