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
  if (root == NULL) return 0;
  else return root->getImbalance();
}
void BST::path(int JourneyCode,int price){

}
int BST::shortpath(int JourneyCode,int price){
  TreeNode* node=new TreeNode;
    node->JourneyCode=JourneyCode;
    node->price=price;
    if(node==NULL){
      return 0;
    }
    int a=shortpath(node->left->JourneyCode,node->left->price);
    int b=shortpath(node->right->JourneyCode,node->right->price);
     if(node->right==NULL){
      return 1+a;
     }
     if(node->left==NULL){
      return 1+b;
     }
     if(a<b){
      return a+1;
     }
     else {return b+1;}
}
int BST::longpath(int JourneyCode,int price){
  TreeNode* node=new TreeNode;
    node->JourneyCode=JourneyCode;
    node->price=price;
    if(node==NULL){
      return 0;
    }
    int a=shortpath(node->left->JourneyCode,node->left->price);
    int b=shortpath(node->right->JourneyCode,node->right->price);
     if(node->right==NULL){
      return 1+a;
     }
     if(node->left==NULL){
      return 1+b;
     }
     if(a<b){
      return b+1;
     }
     else {return a+1;}
}

  TreeNode* BST::Search(TreeNode *s, int price,int JourneyCode)
{
    while (s != NULL)
    {
        if (s->JourneyCode == JourneyCode)
        {
            
            
            return s;
        }
        else if (s-> JourneyCode> JourneyCode)
        {
            s = s->left;
        }
        else
        {
            s = s->right;
        }
    }
    return NULL;
}

bool BST::insert(int JourneyCode, int price)
{ 
  
    if (find(JourneyCode, price))
    {
        return false;
    }
    else
    {
        TreeNode *T = new TreeNode;
        T->price = price;
        T->left = NULL;
        T->right = NULL;
        T->JourneyCode = JourneyCode;
        T->longestPathLength=longpath(JourneyCode, price);
        T->shortestPathLength=shortpath(JourneyCode,price);
        TreeNode *t = new TreeNode;
        t = root;
        if (root == NULL)
        {
            root = T;
            root->left = NULL;
            root->right = NULL;
        }
        else
        {

            while (t != NULL)
            {
                if (t->JourneyCode < JourneyCode)
                {
                    if (t->right == NULL)
                    {
                        t->right = T;
                        T->parent = t;
                        T->JourneyCode=JourneyCode;
                        T->price=price;
                        T->longestPathLength=longpath(JourneyCode, price);
        T->shortestPathLength=shortpath(JourneyCode,price);
                        return true;
                    }
                    else
                    {
                        t = t->right;
                    }
                }
                else if (t->JourneyCode > JourneyCode)
                {
                    if (t->left == NULL)
                    {
                        t->left = T;
                        T->parent = t;
                        T->JourneyCode=JourneyCode;
                        T->price=price;
                        T->longestPathLength=longpath(JourneyCode, price);
        T->shortestPathLength=shortpath(JourneyCode,price);
                        return true;
                    }
                    t = t->left;
                }
            }
        }
        return true;
    }
}
  

  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
   if (Search(root,price,JourneyCode) == NULL)
    {
        return false;
    }
    else
    {
        if(Search(root,price,JourneyCode)->JourneyCode == JourneyCode || (Search(root,price,JourneyCode))->price==price) return true;
        else {return false;}
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

