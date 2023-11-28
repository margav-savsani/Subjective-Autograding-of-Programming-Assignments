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
        }
        else if(A->JourneyCode < y->JourneyCode){
            y->left=A;       
         }
        
        else{
         y->right=A;
        }
    shortl(root);
    longl(root);
    return true;
}
int BST::shortl(TreeNode *node){
    if(node==NULL){
        return 0;
    }
    else if(node->left==NULL || node->right==NULL){
        node->shortestPathLength=1;
        return 1;
    }
    else{
        int path1=shortl(node->left)+1;
        int path2=shortl(node->right)+1;
        if(path1>path2){
            node->shortestPathLength=path2;
            return path2;
        }
        else {
            node->shortestPathLength=path1;
            return path1;
        }
    }
}
int BST::longl(TreeNode *node){
    if(node==NULL){
        return 0;
    }
    
        int path1=longl(node->left)+1;
        int path2=longl(node->right)+1;
         if(path1>path2){
            node->longestPathLength=path1;
            return path1;
        }
        else {
            node->longestPathLength=path2;
            return path2;
        }
    }
    


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *A=new TreeNode;
     A->JourneyCode=JourneyCode;
     A->price=price;
     TreeNode *x;
     x=root;
     while(x!=NULL && A->JourneyCode!=x->JourneyCode){
        if(A->JourneyCode<x->JourneyCode){
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
struct TreeNode* BST::succ(TreeNode *element){
 TreeNode *A=root;
 if(element->right!=NULL){
    A=element->right;
    return treemin(A);
 }
 else{
 TreeNode *y=element->parent;
 while(y!=NULL && element==y->right){
    element=y;
    y=y->parent;
 }
 return y;
 }
}
struct TreeNode* BST::treemin(TreeNode *Root){
    while(Root->left!=NULL){
        Root=Root->left;
    }
    return Root;
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

