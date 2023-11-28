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

bool BST::insert(int JourneyCode, int price){
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
    TreeNode *x=root;
    TreeNode *y=NULL; int b=0; 
    if(x->price==-1){
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }    
    while(x!=NULL){
        if(x->price==price)return false;
        else if(x->price>price){   
            y=x;
            b=1;
            x=x->left;
        }
        else if(x->price<price){
            y=x;
            b=2;
            x=x->right;
        }
    } 
    x=new TreeNode(JourneyCode,price,NULL,NULL,y);
    if(b==1) y->left=x;
    else if(b==2) y->right=x;
    return true;

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
  TreeNode *x=root;
    if(x==NULL)return false;
    while(x!=NULL){
        if(x->price==price) return true;
        else if(x->price>price){
            x=x->left;   
        }
        else if(x->price<price){
            x=x->right;
        }
    }    
    return false;
}
	
TreeNode* successor(TreeNode* x){
    x=x->right;
    while(x->left!=NULL){
        x=x->left;
    }
    return x; 
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
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
  TreeNode *x=root, *y=NULL; int b=0;
    if(x->price==-1)return false; 
    while(x!=NULL){
        if(x->price==price)break;
        else if(x->price>price){
            b=1;
            y=x;
            x=x->left;   
        }
        else if(x->price<price){
            b=2;
            y=x;
            x=x->right;
        }
    } 
    if(x==NULL)return false;

    if(x->left==NULL && x->right==NULL){
        if(b==1) y->left=NULL;
        else if(b==2) y->right=NULL;
        return true;
    }

    if(x->left==NULL && x->right!=NULL){
        if(b==1) y->left= x->right; 
        else if(b==2) y->right= x->right;
        x->right->parent=y;
        return true;
    }

    if(x->left!=NULL && x->right==NULL){
        if(b==1) y->left= x->left;
        else if(b==2) y->right= x->left;
        x->left->parent=y;
        return true;
    }

    if(x->left!=NULL && x->right!=NULL){
        TreeNode *z=successor(x);
        remove(z->JourneyCode,z->price);
        z->left=x->left;
        z->right=x->right;
        if(b==2){
            y->right=z;z->parent=y;
        }    
        else if(b==1){
            y->left=z;z->parent=y;
        }    
        x->left->parent=z;
        x->right->parent=z;
        return true;
    }
  return false;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false){
  if( root != nullptr ){
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

