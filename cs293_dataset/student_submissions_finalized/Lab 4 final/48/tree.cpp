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

bool BST::insert(unsigned  int JourneyCode, unsigned int price) { 
    if(find(JourneyCode,price)) return false;
        if(root==nullptr){
            TreeNode* d=new TreeNode(JourneyCode,price);
            d->parent=nullptr;
            root=d;
            return true;
        }
        if(price<root->price){
            if((root->left)==nullptr) {
                TreeNode* t=new TreeNode(JourneyCode,price);
                t->parent=root;
                root->left=t;
                return true;
            }
            else{
                BST d(root->left);
                d.insert(JourneyCode,price);
            }
        }
        if(price>root->price){
            if((root->right)==nullptr) {
                TreeNode* t=new TreeNode(JourneyCode,price);
                t->parent=root;
                root->right=t;
                return true;
            }
            else{
                BST d(root->right);
                d.insert(JourneyCode,price);
            }
        }
        modify();
    }


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(unsigned int JourneyCode,unsigned int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
      if(root==nullptr) return false;
    if(root->price==price) return true;
    if(root->price<price){
        if(root->right!=nullptr){
            BST d(root->right);
            return d.find(JourneyCode,price);
        }
        else{
            return false;
        }
    }
    if(root->price>price){
        if(root->left!=nullptr){
            BST d(root->left);
            return d.find(JourneyCode,price);
        }
        else{
            return false;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(unsigned int JourneyCode,unsigned int price)
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
    
    if(!find(JourneyCode,price)){return false;}
    TreeNode* x=root;
    while(x!=NULL and x->price!=price){
        if(x->price > price){
            x=x->left;
        }
        if(x->price < price){
            x=x->right;
        }
    }
    if(x->left==NULL && x->right==NULL){
        if(x->parent==NULL){
            x=NULL;
            root=x;
        }
        else if(x->parent!=NULL){
            if(x->parent->price > x->price){
                x->parent->left=NULL;
            }
            else if(x->parent->price < x->price){
                x->parent->right=NULL;
            }
        }
    }
    else if(x->left==NULL && x->right!=NULL){
        if(x->parent==NULL){
            x=x->right;
            x->parent=NULL;
            root=x;
        }
        else if(x->parent!=NULL){
            if(x->parent->price > x->price){
                TreeNode* y=x->parent;
                x=x->right;
                x->parent=y;
                y->left=x;
            }
            else if(x->parent->price < x->price){
                TreeNode* y=x->parent;
                x=x->right;
                x->parent=y;
                y->right=x;
            }
        }
    }
    else if(x->left!=NULL && x->right==NULL){
        if(x->parent==NULL){
            x=x->left;x->parent=NULL;root=x;
        }
        else if(x->parent!=NULL){
            if(x->parent->price > x->price){
                TreeNode* y=x->parent;
                x=x->left;
                x->parent=y;
                y->left=x;
            }
            else if(x->parent->price < x->price){
                TreeNode* y=x->parent;
                x=x->left;
                x->parent=y;
                y->right=x;
            }
        }
    }
    else if(x->left!=NULL && x->right!=NULL){
        TreeNode* y=x->right; 
        while(y->left!=NULL){
            y=y->left;
        }
        int pri=y->price;
        int Jcode=y->JourneyCode;
        remove(y->JourneyCode,y->price);
        x->price=pri;
        x->JourneyCode=Jcode;
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
