// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

BST::BST(){root=NULL;}     //constructor  
BST::BST(TreeNode *curr_root){root=curr_root;}    //constructor

TreeNode* BST :: Minimum(TreeNode* X){
     while(X->left != NULL)             // returns the node that has Journey code minimum 
          X=X->left;
      return X;  
}

TreeNode* BST :: successor(TreeNode* X){
   if(X->right != NULL)
     return Minimum(X->right);           // returns the node which is the successor of the node X
   TreeNode* Y = X->parent;             
  while( (Y!=NULL) && (X=Y->right) )   
    {
      X=Y;
      Y=Y->parent;
     }
   return Y;
}   
 
int BST :: shortpath(TreeNode* Y){
                                      
    if(Y==NULL) return 0;
    else if( (Y->left==NULL) && (Y->right==NULL) ) return 1;  
    if(Y->left==NULL) return 1+shortpath(Y->right);
    else if(Y->right==NULL) return 1+shortpath(Y->left); 
    return 1+min(shortpath(Y->left),shortpath(Y->right));

}

int BST :: longpath(TreeNode* Y){
                                         // function that returns the length of the longtest path from node Y to leaf
    if(Y==NULL) return 0;
    else if( (Y->left==NULL) && (Y->right==NULL) ) return 1;
    if(Y->left==NULL) return 1+longpath(Y->right);
    else if(Y->right==NULL) return 1+longpath(Y->left);     
    return 1+max(longpath(Y->left),longpath(Y->right));

}

void BST :: updatepathlength(TreeNode* Y){
   if(Y==NULL) return;
   else                                 // function that updates the shortestPathLength, longestPathLength of all nodes of a tree 
    {
      	Y->shortestPathLength=shortpath(Y);
          Y->longestPathLength=longpath(Y); 
          updatepathlength(Y->left);
          updatepathlength(Y->right);
     }
  } 

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

int BST::getImbalance(){
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price){

  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *Node=new TreeNode(JourneyCode,price);
  
  while (currNode != nullptr) {
  
       if (currNode->JourneyCode < JourneyCode) {
          parentOfCurrNode = currNode;
          currNode = currNode->right;
         }
    
       else if (currNode->JourneyCode > JourneyCode) {
           parentOfCurrNode = currNode;
           currNode = currNode->left;
         }
    
       else {     // currNode->JourneyCode == JourneyCode
          return false;
         }  
    }
  
     Node->parent=parentOfCurrNode;
     if(parentOfCurrNode==NULL)
           root=Node;
     else if (JourneyCode < parentOfCurrNode->JourneyCode)
           parentOfCurrNode->left=Node;
     else parentOfCurrNode->right=Node;
   
     TreeNode* Z=root;      
     updatepathlength(Z);           // updating shortestPathLength, longestPathLength of all nodes of a tree after deleting a node 
   
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

bool BST::find(int JourneyCode, int price){

        TreeNode* X=root; 
        while(true){
        if(X==NULL) return false;
        else if((X->JourneyCode==JourneyCode)&&(X->price==price)) return true;
        else
           { 
              if( X->JourneyCode > JourneyCode) X=X->left; 
              else X=X->right;
           }
       }        
       
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  // You can look at the implementation of insert to code this part up.

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price){
 
        TreeNode* Z;
        TreeNode* Y;
        TreeNode* X=root; 
        while(true){
        if(X==NULL) return false;
        else if((X->JourneyCode==JourneyCode)&&(X->price==price))
         {           
               if( X->left == NULL || X->right == NULL )
                    Y=X;
               else Y=successor(X);
               
               
               if(Y->left != NULL) Z=Y->left;
               else Z=Y->right;
               
               if(Z != NULL) Z->parent=Y->parent;		     
               if(Y->parent == NULL) root=Z;
               else if (Y == (Y->parent)->left)  (Y->parent)->left=Z;
               else (Y->parent)->right=Z;
               if(Y != X)
                 {
                   X->JourneyCode=Y->JourneyCode;
                   X->price=Y->price;
                   }
                   
                  TreeNode* Z=root;
                  updatepathlength(Z);  // updating shortestPathLength, longestPathLength of all nodes of a tree after deleting a node 
                return true;   
           }
            
        else
           {
              if( X->JourneyCode > JourneyCode) X=X->left; 
              else X=X->right;
           }
       }       
 
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

