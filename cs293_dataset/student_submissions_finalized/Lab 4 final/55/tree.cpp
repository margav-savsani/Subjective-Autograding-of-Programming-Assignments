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
  // cout<<"Insert Begin"<<endl;
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *newnode;
  newnode=new TreeNode;
  newnode->JourneyCode=JourneyCode;
  newnode->price=price;
  // newnode->longestPathLength=0;
  // newnode->shortestPathLength=0;

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
  newnode->parent=parentOfCurrNode;
  if(parentOfCurrNode==NULL){
    root=newnode;
  }
  else if (price<=parentOfCurrNode->price){
    parentOfCurrNode->left=newnode;
  }
  else{
    parentOfCurrNode->right=newnode;
  }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  TreeNode *node=newnode;
  while(node!=nullptr){
    if(node->left==nullptr && node->right==nullptr){
      node->shortestPathLength=0;
      node->longestPathLength=0;
    }
    else if(node->right==nullptr){
      node->shortestPathLength=0;
      node->longestPathLength=node->left->longestPathLength+1;
    }
    else if(node->left==nullptr){
      node->shortestPathLength=0;
      node->longestPathLength=node->right->longestPathLength+1;
    }
    else{
      node->shortestPathLength=1+min(node->left->shortestPathLength,node->right->shortestPathLength);
      node->longestPathLength=1+max(node->left->longestPathLength,node->right->longestPathLength);
    }
    // cout<<"shortest: "<<node->shortestPathLength<<" longest: "<<node->longestPathLength<<endl;
    node=node->parent;
  }
  // cout<<"shortest: "<<root->shortestPathLength<<" longest: "<<root->longestPathLength<<endl;

  // cout<<"Insert End"<<endl;
  // printBST("",false);
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
  TreeNode *node=root;
  while(node!=NULL){
    if(price==node->price && JourneyCode==node->JourneyCode){
      return true;
    }
    if(price>node->price){
      node=node->right;
    }
    else{
      node=node->left;
    }
  }
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
  bool found=false;
    TreeNode *node=root;
    // TreeNode *temproot=root;
    while(node!=NULL){
        if(node->price==price && node->JourneyCode==JourneyCode){
            found=true;
            // std::vector<int>::iterator position = std::find(jCodes.begin(), jCodes.end(), node->JourneyCode);
            // if (position != jCodes.end()) // == myVector.end() means the element was not found
            // jCodes.erase(position);
            break;
        }
        if(price>node->price){
                node=node->right;
            }
            else{
                node=node->left;
            }
    }
    if(!found){return false;}
    TreeNode *y,*x;
    TreeNode *temp;
    // TreeNode *pred=node->left;
    // while(pred->right!=NULL){
    //     pred=pred->right;
    // }
    // node->price=pred->price;
    // node->JourneyCode=pred->JourneyCode;
    // TreeNode *pnode=pred->parent;
    // if(pnode->left==node) {pnode->left=pred->left;}
    // else {pnode->right=pred->left;}
    if(node->left==NULL || node->right==NULL){
        y=node;
        temp=y->parent;
    }
    else{
        y=treePred(node);
        temp=y->parent;
    }
    if(y->left!=NULL){
        x=y->left;
    }
    else{
        x=y->right;
    }
    if(x!=NULL){
        x->parent=y->parent;
    }
    if(y->parent==NULL){
        root=x;
    }
    else if(y==y->parent->left){
        y->parent->left=x;
    }
    else{
        y->parent->right=x;
    }
    if (y!=node){
        node->JourneyCode=y->JourneyCode;
        node->price=y->price;
    }
    // if(node->left==NULL and node->right==NULL){
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=NULL;}
    //     else {pnode->right=NULL;}
    // }
    // else if(node->left==NULL){
    //     TreeNode *child=node->right;
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=child;}
    //     else {pnode->right=child;}
    // }
    // else if(node->right==NULL){
    //     TreeNode *child=node->left;
    //     TreeNode *pnode=node->parent;
    //     if(pnode->left==node) {pnode->left=child;}
    //     else {pnode->right=child;}
    // }
    // else{
    //     TreeNode *pred=node->left;
    //     while(pred->right!=NULL){
    //         pred=pred->right;
    //     }
    //     node->price=pred->price;
    //     node->JourneyCode=pred->JourneyCode;
    //     TreeNode *pnode=pred->parent;
    //     if(pnode->left==node) {pnode->left=pred->left;}
    //     else {pnode->right=pred->left;}
    // }
    while(temp!=nullptr){
    if(temp->left==nullptr && temp->right==nullptr){
      temp->shortestPathLength=0;
      temp->longestPathLength=0;
    }
    else if(node->right==nullptr){
      temp->shortestPathLength=0;
      temp->longestPathLength=temp->left->longestPathLength+1;
    }
    else if(node->left==nullptr){
      temp->shortestPathLength=0;
      temp->longestPathLength=temp->right->longestPathLength+1;
    }
    else{
      temp->shortestPathLength=1+min(temp->left->shortestPathLength,temp->right->shortestPathLength);
      temp->longestPathLength=1+max(temp->left->longestPathLength,temp->right->longestPathLength);
    }
    // cout<<"shortest: "<<node->shortestPathLength<<" longest: "<<node->longestPathLength<<endl;
    temp=temp->parent;
  }
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

TreeNode* BST::treePred(TreeNode *node){
    TreeNode *pred=node->left;
    while(pred->right!=NULL){
        pred=pred->right;
    }
    return pred;
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

