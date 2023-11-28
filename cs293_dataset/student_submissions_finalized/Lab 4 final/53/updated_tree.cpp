// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "updated_tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

void BST::update_longest_path_length(TreeNode* z){ // updating longest path for pointers above supplied node
    TreeNode*y = z->parent;
    while(y!=nullptr){
        int temp;
        temp = y->longestPathLength;
        if(y->left==nullptr && y->right==nullptr) y->longestPathLength=1;
        else if(y->left!=nullptr && y->right==nullptr) y->longestPathLength= y->left->longestPathLength + 1;
        else if(y->right!=nullptr && y->left==nullptr) y->longestPathLength= y->right->longestPathLength + 1;
        else y->longestPathLength = max(y->right->longestPathLength,y->left->longestPathLength)+1;
        if(temp == y->longestPathLength) return;
        y = y->parent;
    }
}
void BST::update_shortest_path_length(TreeNode* z){ // updating shortest path for pointers above supplied node
    TreeNode*y = z->parent;
    while(y!=nullptr){
        int temp;
        temp = y->shortestPathLength;
        if(y->left==nullptr && y->right==nullptr) y->shortestPathLength=1;
        else if(y->left!=nullptr && y->right==nullptr) y->shortestPathLength= y->left->shortestPathLength + 1;
        else if(y->right!=nullptr && y->left==nullptr) y->shortestPathLength= y->right->shortestPathLength + 1;
        else y->shortestPathLength = min(y->right->shortestPathLength,y->left->shortestPathLength)+1;
        if(temp == y->shortestPathLength) return;
        y = y->parent;
    }
}


bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
    TreeNode* y = nullptr;
    TreeNode* x = root;
    if(x->JourneyCode==0 && x->price==0){
        x->JourneyCode=JourneyCode;
        x->price=price;
        return true;
    }
    while (x!=nullptr){
        y = x;
        if (JourneyCode == x->JourneyCode && price == x->price) return false;
        else if(JourneyCode < x->JourneyCode) x = x->left;
        else x = x->right;
    }
    TreeNode *z = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
    z->longestPathLength = 1;
    z->shortestPathLength = 1;
    if (y == nullptr) root = z;
    else if (z->JourneyCode < y->JourneyCode) y->left = z;
    else y->right = z;
    update_longest_path_length(z);
    update_shortest_path_length(z);
    return true;

    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting - done
    
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST :: find (int JourneyCode, int price)
{ 
  TreeNode* x = root;
    while (x != nullptr && (x->price!=price || x->JourneyCode != JourneyCode)){
        if (JourneyCode < x->JourneyCode)
            x = x->left;
        else{
            x = x->right;
        }
    }
    if (x == nullptr)
        return false;
    else
        return true;
}

TreeNode* BST::treenode_min(TreeNode *x){
    while(x->left != nullptr){
        x = x->left;
    }
    return x;
}

TreeNode* BST::successor(TreeNode* x){
    if (x->right != nullptr)
        return treenode_min(x->right);
    TreeNode* y = x->parent;    
    while (y != nullptr && x==y->right){
        x = y;
        y = x->parent;
    }
    return y;
}

TreeNode* BST::search(int JourneyCode,int price){
    TreeNode* x = root;
    while (x != nullptr && (x->price!=price || x->JourneyCode != JourneyCode)){
        if (JourneyCode < x->JourneyCode)
            x = x->left;
        else{
            x = x->right;
        }
    }
    return x;
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{  //shortest and longest length have been updated

  TreeNode* z = search(JourneyCode,price);
    if(z == nullptr){
        return false;
    }
    if(z == root){
        if(z->left == nullptr && z->right == nullptr){
            root = nullptr;
            return true;
        }
        else if(z->left != nullptr && z->right == nullptr){
            root = z->left;
            return true;
        }
        else if(z->left == nullptr && z->right != nullptr){
            root = z->right;
            return true;
        }
    }
    if(z->left == nullptr && z->right == nullptr){
        TreeNode *y = z->parent;
        if(y->left == z){
            y->left = nullptr;
        }
        else y->right = nullptr;
        update_longest_path_length(z);
        update_shortest_path_length(z);
        return true;
    }
    else if(z->left == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->right;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->right;
            x->parent = y;
            y->right = x;
        }
        update_longest_path_length(z);
        update_shortest_path_length(z);
        return true;
    }
    else if(z->right == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->left;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->left;
            x->parent = y;
            y->right = x;
        }
        update_longest_path_length(z);
        update_shortest_path_length(z);
        return true;
    }
    else{
        TreeNode*y = successor(z);
        remove(y->JourneyCode,y->price);
        z->JourneyCode=y->JourneyCode;
        z->price=y->price;
        update_longest_path_length(y);
        update_shortest_path_length(z);
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

