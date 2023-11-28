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
int BST::shortpath(TreeNode* p){
    if(p == NULL) return 0;
    else if(p->right == NULL || p->left == NULL) return 0;
    else{
        int x = shortpath(p->right);
        int y = shortpath(p->left);
        if(x<y) return 1+x;
        else return 1+y;
    }
}

int BST::longpath(TreeNode* p){
    if(p == NULL) return 0;
    else if(p->right == NULL && p->left == NULL) return 0;
    else{
        int x = longpath(p->right);
        int y = longpath(p->left);
        if(x<y) return 1+y;
        else return 1+x;
    }
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return (longpath(root)-shortpath(root));
}

TreeNode* insertelement(TreeNode* node,int key,int JourneyCode){     // defining new function for using recursion
    if(node == NULL){
        TreeNode* n = new TreeNode(JourneyCode,key);
        node = n;
        return node;
    }
    else if(node->JourneyCode<JourneyCode){
        node->right = insertelement(node->right,key,JourneyCode);
        node->right->parent= node;
    }
    else{
        node->left = insertelement(node->left,key,JourneyCode);
        node->left->parent = node;
    }
     return node;
}

bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
        return false;
    }

    root  = insertelement(root,price,JourneyCode);   
    return true;
}

TreeNode* Search(TreeNode* node,int JourneyCode,int price){
    if(node==NULL) return NULL;
    else if(node->JourneyCode == JourneyCode){
        return node;
    }
    else if(node->JourneyCode < JourneyCode){
        return Search(node->right,JourneyCode,price);
    }
    else { 
      return Search(node->left,JourneyCode,price);
    }
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode* t =  new TreeNode(JourneyCode,price);
    t = Search(root,JourneyCode,price);

    if(t==NULL) return false;
    return true;
  return false;
}

TreeNode* minim(TreeNode* node){
    if(node->left == NULL) return node;
    else return minim(node->left); 
}

TreeNode* Sucessor(TreeNode* node){
    if(node->right != NULL) return minim(node->right);
    else if(node->parent !=NULL  && node->parent->left == node) return node->parent;
    else return NULL;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* r = new TreeNode(JourneyCode,price);
    r = Search(root,JourneyCode,price);
    if(r==NULL) return false;
    if(r->left == NULL && r->right == NULL){ 
        if (r != root){
            if (r->parent->left == r){
                r->parent->left = NULL;
            } else {
                r->parent->right = NULL;
            }
            delete r;
        } else {
            root = NULL;   
        }
    }else if(r->left == NULL ){
        TreeNode* x = new TreeNode();
        x = r->right;
        TreeNode* y = new TreeNode();
        
        y = r->parent;
        if(r != root){
            if(y->right == r){
                y->right = x;
                x->parent = y;
            }
            else if(y->left == r){
                y->left = x;
                x->parent = y;
            }
            delete r;
        }
        else {
            root->right->parent = NULL;   
            root = root->right;
        }
    }
    else if(r->right == NULL ){
        TreeNode* x = new TreeNode();
        x = r->left;
        TreeNode* y = new TreeNode();
        y = r->parent;
        if(r != root){
            if(y->right == r){
                y->right = x;
                x->parent = y;
            }
            else if(y->left == r){
                y->left = x;
                x->parent = y;
            }
        }
        else{ 
            root->left->parent = NULL;
            root = root->left;
        }
    }
    else{
       TreeNode* x = new TreeNode();
        x = Sucessor(r);
        r->price = x->price;
        r->JourneyCode = x->JourneyCode;
        if (x->right == NULL && x->left == NULL){
            if (x->parent == r){
                r->right = NULL;
            } else {
                x->parent->left = NULL;
            }
            
        }
        else if (x->right != NULL) {
            if (x->parent != r){
                x->parent->left = x->right;
                x->right->parent = x->parent;
            } else {
                x->parent->right = x->right;
                x->right->parent = x->parent;
            }
        }

        delete x;

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

