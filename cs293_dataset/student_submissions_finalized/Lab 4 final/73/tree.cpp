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

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) 
  {
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
  currNode=new TreeNode(JourneyCode,price); //making node
  currNode->parent=parentOfCurrNode;    //giving the parent to it
  if (parentOfCurrNode==nullptr)
  {
    root=currNode;  //if parent is nullptr then it is root
    return true;
  }
  else if (currNode->JourneyCode<=parentOfCurrNode->JourneyCode)
  {
    parentOfCurrNode->left=currNode;//left child
    return true;
  }
  else
  {
    parentOfCurrNode->right=currNode;   //rigth child
    return true;
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
  TreeNode *sample=this->root;        //checking from root
  if (sample==nullptr)        //nothing is added
      return false;
  while(sample!=nullptr && JourneyCode!=sample->JourneyCode)  //checking for equal price or it will go to nullptr
  {
      if (price > sample->price)
          sample=sample->right;
      else
          sample=sample->left;
  }
  if (sample==nullptr)        //if nullptr return false
      return false;
  if (sample->price==price)   //if same price then check Journy Code
      return true;
  return false;
}
TreeNode *BST::getnode(int JourneyCode,int price)   //this will return node with same Journy Code and price
{
    if (!find(JourneyCode,price))   //if not present then return nullptr
    {
        return nullptr;
    }
    else
    {       //if present checkmin similar manner as in above function 
        TreeNode *sample=this->root;
        if (sample==nullptr)
            return nullptr;
        while(sample!=nullptr && price!=sample->price)
        {
            if (price > sample->price)
                sample=sample->right;
            else
                sample=sample->left;
        }
        if (sample==nullptr)
            return nullptr;
        if (sample->JourneyCode==JourneyCode)
            return sample;
        return nullptr;
    }
};
TreeNode *BST::getSuccessor(int JourneyCode,int price)
{   //checking for successor that is rigth subtress's min value
    if (!find(JourneyCode,price))
        return nullptr;
    TreeNode *node=this->getnode(JourneyCode,price);
    if (node->right!=nullptr)
    {
        node=node->right;
        while(node->left!=nullptr)
            node=node->left;
        return node;
    }
    TreeNode *sample=node->parent;
    while( sample!=nullptr && node==sample->right )
    {
        node=sample;
        sample=sample->parent;
    }
    return sample;
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
  if (!find(JourneyCode,price)) 
    return false;
  TreeNode *node=this->getnode(JourneyCode,price);
    TreeNode *sample1,*sample2;
    if (node->right==nullptr || node->left==nullptr)    //if it is leaf or having one child
        sample1=node;
    else
        sample1=getSuccessor(JourneyCode,price);        //if it has 2 childs
    if (sample1->left==nullptr)         //0 or 1 child
        sample2=sample1->left;
    else
        sample2=sample1->right;
    if (sample2!=nullptr)       
        sample2->parent=sample1->parent;
    if (sample1->parent==nullptr)
        this->root=sample2;
    else if ( sample1=sample1->parent->left)
        sample1->parent->left=sample2;
    else
        sample1->parent->right=sample2;
    if (sample1!=node)
    {
        node->JourneyCode=sample1->JourneyCode;
        node->price=sample1->price;
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
        cout << root->JourneyCode<<" Imbalance "<<root->getImbalance() << endl; // getting imbalance
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

