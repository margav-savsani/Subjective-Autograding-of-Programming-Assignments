// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include<cmath>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
int TreeNode::Calculate_short() { // calculating the shortest and longest path 
  
if(right == nullptr && left == nullptr){
      shortestPathLength = 0;
    }
    else {
      if(right == nullptr){
        shortestPathLength = 1+left->Calculate_short();
      }
      else if(left == nullptr ){
        shortestPathLength = 1+right->Calculate_short();
      }
      else{
        shortestPathLength = 1 + min(left->Calculate_short(),right->Calculate_short());
      }
    }
    return  shortestPathLength;
}
int TreeNode::Calculate_long() {
  
if(right == nullptr && left == nullptr){
      longestPathLength = 0;
    }
    else {
      if(right == nullptr){
        longestPathLength = 1+left->Calculate_long();
      }
      else if(left == nullptr ){
        longestPathLength = 1+right->Calculate_long();
      }
      else{
        longestPathLength = 1 + max(left->Calculate_long(),right->Calculate_long());
      }
    }
    return longestPathLength;
}


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
    else { currNode->JourneyCode == JourneyCode;
      return false;
    }
  }
  // // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
   // TreeNode *y = new TreeNode;
    // y->left=nullptr
    TreeNode *res = new TreeNode();
    TreeNode *y = nullptr;

    if (root == nullptr) // inserting at root
    {
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);

        return true;
    }

    else
    {

        TreeNode *x = root;
        /*if (check(JourneyCode, price, x)) // if a journey code is present , insertion failed
        {
            return false;
        }*/
        while (x != nullptr) // if prices are same insert at right
        {

            if (JourneyCode >= x->JourneyCode)
            {
                y = x;
                x = x->right;
            }
            else if (JourneyCode< x->JourneyCode)
            {
                y = x;
                x = x->left;
            }
        }
        if (JourneyCode < y->JourneyCode)
        {
            res->parent = y;
            y->left = res;
            res->JourneyCode = JourneyCode;
            res->price = price;
            
            
        }
        else
        {
            res->parent = y;
            y->right = res;
            res->JourneyCode = JourneyCode;
            res->price = price;
        }
        
    }
           while(y->parent != nullptr){
            y->Calculate_long();
            y->Calculate_short();
            y=y->parent;
           }
    //return true;
  
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
  TreeNode *x = root;

    while (x != nullptr)
    {

        if (x->price == price && x->JourneyCode == JourneyCode)
        {
            return true;
        }
        if (x->JourneyCode > JourneyCode)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    //return false;
  
  return false;
}
TreeNode *BST::predecessor(TreeNode *z) // finding the largest number less than the given node
{

    if (z->left != nullptr)
    {
        TreeNode *t1 = z->left;
        while (t1->right != nullptr)
        {
            t1 = t1->right;
        }

        return t1;
    }
    if (z->parent == nullptr)
    {
        return nullptr;
    }
    TreeNode *t1 = z->parent;
    TreeNode *t2 = z;
    while (t1 != nullptr)
    {
        if (t1->right == t2)
        {
            return t1;
        }
        t2 = t1;
        t1 = t1->parent;
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
  if (find(JourneyCode, price))
    {
        TreeNode *x = root;
        while (x != nullptr)
        {

            if (x->price == price && x->JourneyCode == JourneyCode)
            {
                if (x->left == nullptr && x->right == nullptr)
                {
                    TreeNode *Y = x->parent;
                    if (x == Y->left)
                    {
                        Y->left = nullptr;
                    }
                    else if (x == Y->right)
                    {
                        Y->right = nullptr;
                    }
                    while(Y!=nullptr){
                      Y->Calculate_long();
                      Y->Calculate_short();
                      Y=Y->parent;
                    }
                }
                else if (x->right == nullptr)
                {
                    TreeNode *t = x->left;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                        while(t2!=nullptr){
                                t2->Calculate_long();
                                t2->Calculate_short();
                                t2=t2->parent;
                    }

                    }

                    else
                    {

                        root = t;
                    }

                }
                else if (x->left == nullptr)
                {
                    TreeNode *t = x->right;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                        while(t2!=nullptr){
                                t2->Calculate_long();
                                t2->Calculate_short();
                                t2=t2->parent;
                    }

                    }
                    else
                    {

                        root = t;
                    }
                }
                else
                {

                    TreeNode *p = predecessor(x);
                    x->JourneyCode = p->JourneyCode;
                    x->price = p->price;
                    if (p->left == nullptr && p->right == nullptr)
                    {
                        TreeNode *Y = p->parent;
                        if (p == Y->left)
                        {
                            Y->left = nullptr;
                        }
                        else if (p == Y->right)
                        {
                            Y->right = nullptr;
                        }
                        while(Y!=nullptr){
                                  Y->Calculate_long();
                                  Y->Calculate_short();
                                  Y=Y->parent;

                        }
                    }
                    else
                    {
                        TreeNode *z = p->parent;
                        TreeNode *y = p->left;
                        if (z->right == p)
                        {
                            y->parent = z;
                            z->right = y;
                        }
                        else
                        {
                            y->parent = z;
                            z->left = y;
                        }
                        while(z!=nullptr){
                                  z->Calculate_long();
                                  z->Calculate_short();
                                  z=z->parent;

                        }

                    }
                }
                // Calculate_long(root);
                // Calculate_short(root);
                return true;
            }

            if (x->JourneyCode > JourneyCode)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
    }

    return false;

    
  //return false;
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

