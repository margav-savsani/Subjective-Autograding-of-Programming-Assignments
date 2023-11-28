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
  if (root == nullptr)
    return 0;
  else
    return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

  if (find(JourneyCode, price))
  {
    return false;
  }
  else
  {
    TreeNode *y = new TreeNode();
    y = NULL;
    TreeNode *x = new TreeNode();
    x = root;

    while (x != NULL)
    {
      y = x;
      if (JourneyCode < x->JourneyCode)
      {
        x = x->left;
        if (x->shortestPathLength == (x->left->shortestPathLength + 1) && x->right->shortestPathLength != x->left->shortestPathLength)
        {
          x->shortestPathLength++;
        } 
        if (x->longestPathLength == (x->left->longestPathLength + 1) && x->right->longestPathLength != x->left->longestPathLength)
        {
          x->longestPathLength++;
        } 
      }
      else
      {
        x = x->right;
        if (x->shortestPathLength == (x->right->shortestPathLength + 1) && x->right->shortestPathLength != x->left->shortestPathLength)
        {
          x->shortestPathLength++;
        } 
        if (x->longestPathLength == (x->right->longestPathLength + 1) && x->right->longestPathLength != x->left->longestPathLength)
        {
          x->longestPathLength++;
        } 
      }
    }
    TreeNode *newnode = new TreeNode(JourneyCode, JourneyCode, NULL, NULL, y);
    newnode->shortestPathLength=1;
    newnode->longestPathLength=1;
    if (y == NULL)
    {
      
      root = newnode;
      root->shortestPathLength=1;
      root->longestPathLength=1;
    }
    else if (JourneyCode < y->JourneyCode)
    {
      y->left = newnode;
      if(y->longestPathLength == 1){
        y->longestPathLength++;
      }
      y->shortestPathLength=2;
    }
    else
    {
      y->right = newnode;
      if(y->longestPathLength == 1){
        y->longestPathLength++;
      }
      y->shortestPathLength=2;
    }
    return true;
  }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
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

    TreeNode *x = new TreeNode();
    x = root;
    if(x == NULL){
        return false;
    }
    if(price == x->price){
        cout<<x->price;
        return true;
    }
    else{
        if(price < x->price){
            x = x->left;
            BST leftTree(x);
            return leftTree.find(JourneyCode, price);
        }
        else{
            x = x->right;
            BST rightTree(x);
            return rightTree.find(JourneyCode,price);
        }
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
    TreeNode *x = new TreeNode();
    x = root;
    if(x == NULL){
        return false;
    }
    if(price == x->price){
        if((x->left == NULL) && (x->right == NULL)){
            TreeNode *par = new TreeNode(); //parent of x
            par=x->parent;
            if(par->price < x->price){
                par->right = NULL;
                x->parent = NULL;
                par->shortestPathLength = 1;
                if (par->longestPathLength == 2)
                {
                  par->longestPathLength = 1;
                }
                
                return true;
            }
            else
            {
                par->left = NULL;
                x->parent = NULL;
                par->shortestPathLength = 1;
                if (par->longestPathLength == 2)
                {
                  par->longestPathLength = 1;
                }
                return true;
            }
            
        }
        else if ((x->left == NULL) || (x->right == NULL))
        {
            TreeNode *par =  new TreeNode(); //parent of x
            par=x->parent;
            TreeNode *chi =  new TreeNode(); //single child of x
            chi = NULL;
            if (x->left == NULL) //if chi is to the right of x
            {
                chi=x->right;     //saving child  
                x->right = NULL;    //seperating from parent
            }
            else{           //if chi is to the left of x
                chi=x->left;  //saving child
                x->left = NULL;     //seperating from parent
            }
            if(par != NULL){
                if(par->left == x ){     //if x is to left of par
                if (par->shortestPathLength == (par->left->shortestPathLength + 1) && par->right->shortestPathLength != par->left->shortestPathLength)
                {
                  par->shortestPathLength--;
                }
                if (par->longestPathLength == (par->left->longestPathLength + 1) && par->right->longestPathLength != par->left->longestPathLength)
                {
                  par->longestPathLength--;
                }
                par->left=chi;     //child must be less than par, so assign par's left child's role to chi   
                chi->parent =par;  //tell child that par is his parent
                x->parent = NULL; //seperate x from his parents too
                }
                else if(par->right == x){       //if x is to right of par
                if (par->shortestPathLength == (par->right->shortestPathLength + 1) && par->right->shortestPathLength != par->left->shortestPathLength)
                {
                  par->shortestPathLength--;
                }
                if (par->longestPathLength == (par->right->longestPathLength + 1) && par->right->longestPathLength != par->left->longestPathLength)
                {
                  par->longestPathLength--;
                }
                par->right=chi;    //chi must be greater than p
                chi->parent=par;  //tell chi that par is his parent 
                x->parent = NULL;       //seperate x from hiss parent
                }
            }
            else{
                root = chi;
                chi->parent = NULL; 
            }
        }
        else{ //if x has 2 children
            TreeNode* suc =  new TreeNode();
            TreeNode* suc_chi =  new TreeNode();
            TreeNode* suc_par =  new TreeNode();
            suc_par=suc->parent;
            suc_chi=suc->right;
            suc=this->successor(x);
            suc_par->left = suc_chi;
            suc_chi->parent = suc_par;
            x = suc;
        }
        return true;
    }
    else{
        if(price < x->price){
            x=x->left;
            BST leftTree(x);
            return leftTree.remove(JourneyCode, price);
        }
        else{
            x=x->right;
            BST rightTree(x);
            return rightTree.remove(JourneyCode,price);
        }
    }
}

// Returns the root with price of the cheapest journey
TreeNode* BST::getMinimumRoot(){
    if(root->left == NULL){
        return root;
    }
    else{
        BST leftTree(root->left);
        return leftTree.getMinimumRoot();
    }    
}

//Returns successor of given TreeNode as argument
TreeNode* BST::successor(TreeNode* x){
    if (x->right != NULL){
        BST rightTree(x->right);
        return rightTree.getMinimumRoot();
    }
    TreeNode* suc_par =  new TreeNode();
    suc_par = x->parent;
    while ((suc_par != NULL) & (x == suc_par->right))
    {
        TreeNode* p = new TreeNode();
        p=suc_par->parent; 
        x = suc_par;
        suc_par = p;
    }
    return suc_par;
}
// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->JourneyCode << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    result.push_back(prefix);

    result.push_back(isLeft ? "|--" : "|__");

    // print the value of the node
    result.push_back(to_string(root->JourneyCode) + "\n");
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    getBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    getBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST::clearResult()
{
  result.clear();
}

vector<string> BST::getResult()
{
  return result;
}
