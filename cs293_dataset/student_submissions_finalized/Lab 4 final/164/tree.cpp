// Code up the functions defined in tree.h
// Reuse the   Search Tree implemented in lab 3 as much as possible2810
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"
#include<cmath>
// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
int BST::shortestPath(TreeNode*t)
{
  if(t->left==NULL || t->right==NULL)
  {
    return 0;
  }
  else
  {
    return 1+min(shortestPath(t->right),shortestPath(t->left));
  }
}
int BST::LongestPath(TreeNode*t)
{
  if(t->left==NULL && t->right==NULL)
  {
    return 0;
  }
  else if(t->left==NULL)
  {
    return 1+LongestPath(t->right);
  }
  else if(t->right==NULL)
  {
    return 1+LongestPath(t->left);
  }
  else
  {
    return 1+max(LongestPath(t->right),LongestPath(t->left));
  }
}
int BST::getImbalance()
{
  if (root == nullptr) return 0;
  cout<<"LongestPathlength: "<<LongestPath(root)<<endl<<"ShortestPathLength: "<<shortestPath(root)<<endl<<"ImBalance: ";
   return LongestPath(root)-shortestPath(root);
}
bool BST::insert(int JourneyCode, int price) { 
    
    if(find(JourneyCode,price)){
        return false;
    }
    if(root==NULL)
    {
        root=new TreeNode(JourneyCode,price);      
        return true;
    }
    BST n;
    n.root=root;
    if(n.root->left ==NULL && n.root->right==NULL ){
        if(n.root->JourneyCode >JourneyCode){
            n.root->left=new TreeNode(JourneyCode,price);
        }
        if(n.root->JourneyCode<JourneyCode){
            n.root->right=new TreeNode(JourneyCode,price);
        }
        return true;
    }
    if(n.root->left ==NULL && n.root->right!=NULL ){
        if(n.root->JourneyCode>JourneyCode){
            n.root->left=new TreeNode(JourneyCode,price);
            return true;}
            else {n.root=n.root->right;
                return n.insert(JourneyCode,price);}
    }
    if(n.root->left !=NULL && n.root->right==NULL ){
        if(n.root->JourneyCode<JourneyCode){
            n.root->right=new TreeNode(JourneyCode,price);
            return true;}
            else{n.root=n.root->left;
            return n.insert(JourneyCode,price);}
    }
    if(n.root->JourneyCode>JourneyCode)
    {
        n.root=n.root->left;
        n.insert(JourneyCode,price);
    }
    if(n.root->JourneyCode<JourneyCode)
    {
        n.root=n.root->right;
        n.insert(JourneyCode,price);
    }
    return false; 
    }


// // Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    BST n;
    n.root=root;
    if(n.root==NULL){
        return false;
    }
    if(n.root->JourneyCode>JourneyCode)
    {
        n.root=n.root->left;
        return n.find(JourneyCode,price);
    }
    if(n.root->JourneyCode<JourneyCode)
    {
        n.root=n.root->right;
        return n.find(JourneyCode,price);
    }
    if(n.root->JourneyCode==JourneyCode)
    {
        return true;
    }
    
    return false; 
    }
//  Schneider's code on StackOverflow
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
