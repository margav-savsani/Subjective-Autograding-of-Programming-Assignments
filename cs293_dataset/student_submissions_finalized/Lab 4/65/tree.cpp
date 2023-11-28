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
  if(find(JourneyCode,price)){
            return false;
    }
         TreeNode *A=new TreeNode;
         A->JourneyCode=JourneyCode;
         A->price=price;
         TreeNode *y=NULL;
         TreeNode *x=root;

         while(x!=NULL){
            y=x;
            if(JourneyCode<x->JourneyCode){
                x=x->left;
            }
            else x=x->right;
         }
        A->parent=y;
        if(y==NULL){
            root=A;
            return true;
        }
        else if(A->JourneyCode < y->JourneyCode){
            y->left=A;
            return true;       
         }
        
        else{
         y->right=A;
         return true;
        }
    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *A=new TreeNode;
     A->JourneyCode=JourneyCode;
     A->price=price;
     TreeNode *x;
     x=root;
     while(x!=NULL && A->price!=x->price){
        if(A->price<x->price){
            x=x->left;
        }
        else {x=x->right;}
     }
     if(x==NULL){
        return false;
     }
     else {return true;}
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(!find(JourneyCode,price)){
            return false;
    }
    else{
    TreeNode *y;
    TreeNode *x;
   TreeNode *A= new TreeNode;
   A->JourneyCode=JourneyCode;
   A->price=price;
   if(A->left==NULL || A->right==NULL){
    y=A;
   }
   else {y=succ(A);}
   if(y->left!=NULL){
    x=y->left;
   }
   else {x=y->right;}
   if(x!=NULL){
    x->parent=y->parent;
   }
   if(y->parent==NULL){
    root=x;
   }
   else if(y==y->parent->left){
    y->parent->left=x;
   }
   else {y->parent->right=x;}
   if(y!=A){
    A->JourneyCode=JourneyCode;
    A->price;
   }
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

