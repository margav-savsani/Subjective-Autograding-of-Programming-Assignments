// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include "bits-stdc++.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "updated_tree.h"

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

  currNode = new TreeNode();
  currNode->JourneyCode=JourneyCode;
  currNode->price=price;
  currNode->parent=parentOfCurrNode;
  if(parentOfCurrNode!=NULL)
  {
    if(parentOfCurrNode->JourneyCode>JourneyCode)
    parentOfCurrNode->left=currNode;
    else
    parentOfCurrNode->right=currNode;
  }
  else{
    root=currNode;
  }
  while(currNode != NULL){
    cout<<"Here"<<endl;
    int mi = 65536,mx = 0;
    if(currNode->left != NULL){
      mi = min(mi , 1+ currNode->left->shortestPathLength);
      mx = max(mx , 1+ currNode->left->longestPathLength);
    }
    if(currNode->right != NULL){
      mi = min(mi , 1+ currNode->right->shortestPathLength);
      mx = max(mx , 1+ currNode->right->longestPathLength);
    }
    if(mi == 65536)currNode->shortestPathLength = 0;
    else currNode->shortestPathLength= mi;
    currNode->longestPathLength = mx;
    cout<<currNode->shortestPathLength<<" "<<mx<<endl;
    currNode= currNode->parent;
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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return (currNode->price==price);
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
  if(root==NULL)
  return false;
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      currNode = currNode->right;
      if (currNode->JourneyCode==JourneyCode && currNode->price==price)
      break;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      if (currNode->JourneyCode==JourneyCode && currNode->price==price)
      break;
    }
    else { // currNode->JourneyCode == JourneyCode
      if (currNode->price==price) break;
    }
  }
  if(currNode->left==NULL && currNode->right==NULL)
  {
    if (currNode== currNode->parent->left)
    parentOfCurrNode->left=NULL;
    else
    parentOfCurrNode->right=NULL;
    return true;
  }
  else  if(currNode->left == NULL)
  {
    currNode->parent->right=currNode->right;
  }
  else if(currNode->right == NULL)
  {
    currNode->parent->left=currNode->left;
  }
  else
  {
    TreeNode *temp= currNode->successor();
    currNode->price=temp->price;
    currNode->JourneyCode=temp->JourneyCode;
    remove(temp->JourneyCode, temp->price);
    
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

