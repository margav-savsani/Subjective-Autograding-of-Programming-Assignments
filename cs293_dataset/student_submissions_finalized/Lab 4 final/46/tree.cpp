// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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

void BST::modify(TreeNode* x) {
    if(x==NULL) return;
    if(x->left==NULL&&x->right==NULL) x->assign();
    if(x->left !=NULL && x->right==NULL) modify(x->left);
    else if(x->right==NULL && x->left!=NULL) modify(x->right);
    else {
        modify(x->left);
        modify(x->right);
    }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  

  TreeNode *x,*y,*z;
        x = root;
        y = NULL;
        z = new TreeNode(JourneyCode,price);
        if(find(JourneyCode,price)) return false;
        if(x==NULL) {
            root = z;
            root->parent = NULL;
            return true;
        }
        while(x != NULL) {
            y = x;
            if(z->price < x->price) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if(z->price < y->price) {
                 y->left = z;
                 return true; 
        }
        else {
                y->right = z;
                return true;
        }
        return false;
  

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of y.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
}

// Return True, if the ticket with given attributes is found, false otherwise

TreeNode* BST::find_tree(TreeNode* x,int JourneyCode) {
        if(x == NULL) {
            return NULL;
        }
        if(JourneyCode == x->JourneyCode) {
            return x;
        }
        if(JourneyCode < x->JourneyCode) {
            return find_tree(x->left,JourneyCode);
        }
        else {
            return find_tree(x->right,JourneyCode);
        }
        return NULL;
}

bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  if(find_tree(root,JourneyCode)==NULL) return false;
    return true;
  // You can look at the implementation of insert to code this part up.
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise


TreeNode* tr_suc(TreeNode* x) {
    if(x->right!=NULL) {
        TreeNode *a,*b;
        a = x->right;
        while(a->left != NULL) {
            a = a->left;
        }
        return a;
    }
    TreeNode* y=x->parent;
    while(y!=NULL && x==(y->right)) {
        x=y;
        y=y->parent;
        return y;
    }
    return NULL;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode* BST::tr_suc(TreeNode* x) {
    if(x->right!=NULL) {
        TreeNode *a,*b;
        a = x->right;
        while(a->left != NULL) {
            a = a->left;
        }
        return a;
    }
    TreeNode* y=x->parent;
    while(y!=NULL && x==(y->right)) {
        x=y;
        y=y->parent;
        return y;
    }
    return NULL;
}

bool BST::remove(int JourneyCode, int price) {
    TreeNode* x = find_tree(root,JourneyCode);
    if(x==NULL) return false;
    
    // case-1 no children to x
    TreeNode* x_p = x->parent;
    if(x->left==NULL && x->right==NULL) {
        if(x_p==NULL) {
            root = NULL;
        }
        else if(x_p->right==x) {
            x_p->right=NULL;
            x->parent=NULL;
        }
        else if(x_p->left==x) {
            x_p->left=NULL;
            x->parent=NULL;
        }
         modify(root);
        return true;
    }

    // case-2 exactly one child
    TreeNode* x_c;
    bool val=false;
    if(x->left != NULL && x->right == NULL) {
        x_c=x->left;
        val=true;
    }
    else if(x->left == NULL && x->right != NULL) {
        x_c=x->right;
        val=true;
    }
    if(val==true) {
        if(x==root) {
            root=x_c;
            x_c->parent=NULL; 
        }
        else if(x_p->left==x) {
            x_p->left=x_c;
            x_c->parent=x_p;
        }
        else if(x_p->right==x) {
            x_p->right=x_c;
            x_c->parent=x_p;
        }
         modify(root);
        return true;
    }

    // case-3 2 children
    TreeNode* suc_x = tr_suc(x);
    int pri = suc_x->price;
    int code = suc_x->JourneyCode;
    remove(suc_x->JourneyCode,suc_x->price);
    x->price = pri;
    x->JourneyCode = code; 
    modify(root);
    return true;

    // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.

  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.

  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
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

TreeNode* BST::getRoot() {
    return root;
}

vector<string> BST::getResult(){
    return result;
}


