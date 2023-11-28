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
int height(struct TreeNode* x){
    if (x==NULL){
        return 0;
    }
    else{
        return x->height;
    }
}
int max(int a , int b){
    if(a>b){
        return a;
    }
    return b;
}
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  if(currNode==nullptr){
    currNode->JourneyCode=JourneyCode;
    currNode->price=price;
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
    else { 
       currNode->JourneyCode == JourneyCode;
       currNode->price == price;
      return false;
    }
    return true;

  }
  while(currNode!=nullptr){
        currNode->height=1+std::max(height(currNode->right),height(currNode->left));
        currNode=currNode->parent;
    }
  while(currNode!=nullptr){
  if(height(currNode->right)>=height(currNode->left)){
    shortestPathLength = height(currNode->left);
    longestPathLength = height(currNode->right);
  }
  else{
    shortestPathLength = height(currNode->right);
    longestPathLength = height(currNode->left);
  }
  }
  
 
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if(root == NULL || price == root->price)
       {return true;}
  else if(price < root->price){
        root = root->left;
        return find(JourneyCode, price);
    }   
  else{
        root = root->right;
        return find(JourneyCode , price);
      }
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
struct TreeNode* BST::search(int price){
    struct TreeNode* temp = root;

    if (root == nullptr){
        return NULL;
    }

    while(temp!=NULL){
        if (price==temp->price)
        {
            return temp;
        }
        else if (price>=temp->price)
        {
            temp=temp->right;
        }
        else {
            temp=temp->left;
        }
    }
    return NULL;
}
bool BST::remove(int JourneyCode, int price)
{
  bool t;
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    if(root == NULL){
     struct TreeNode* r = search(price);
    bool t;

    if (r==NULL){
        t=false;
    }
    else{
        struct TreeNode *y = new TreeNode();
        struct TreeNode *x = new TreeNode();
        if (r->left == NULL || r->right == NULL)
        {
            y=r;
        }
        else
        {
            y=successor(r);
        }

        if (y->left != NULL)
        {
            x=y->left;
        }
        else
        {
            x=y->right;
        }

        if (x != NULL)
        {
            x->parent = y->parent;
        }

        if (y->parent == NULL)
        {
            this->root=x;
        }
        else {
            if (y==y->parent->left){
                y->parent->left=x;
            }
            else{
                y->parent->right=x;
            }
        }
        delete r;
        t=true;
    }
   return t;
}   
  while(currNode!=nullptr){
   if(height(currNode->right)>=height(currNode->left)){
    shortestPathLength = height(currNode->left);
    longestPathLength = height(currNode->right);
  }
   else{
    shortestPathLength = height(currNode->right);
    longestPathLength = height(currNode->left);
  }
  }
}
struct TreeNode* BST::successor(struct TreeNode* n){
    if (n->right!=nullptr){
        struct TreeNode* temp=n->right;
        while(temp->left!=nullptr){
            temp=temp->left;
        }
        return temp;
    }

    struct TreeNode* p=n->parent;
    while(p!=nullptr&&n==p->right){
        n=p;
        p=p->parent;
    }
    return p;
}
struct TreeNode* BST::predecessor(struct TreeNode* n){
    if (n->left!=nullptr){
        struct TreeNode* temp=n->left;
        while(temp->right!=nullptr){
            temp=temp->right;
        }
        return temp;
    }
    
    struct TreeNode* p=n->parent;
    while(p!=nullptr&&n==p->right){
        n=p;
        p=p->parent;
    }
    return p;
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
        result.push_back(root->JourneyCode + "\n");
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

