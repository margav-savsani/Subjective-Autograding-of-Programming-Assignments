// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// Constructors of BST
BST::BST(){
    root = nullptr; 
}

BST::BST(TreeNode *root){
    this->root = root; 
}

// get Imbalance of tree
int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

// returns the Root Node
struct TreeNode *BST::getRoot(){
	return root;
}

// Insert the pivot into the BST
// along with updating shortest and longest path of all
// the ancestors of the new Node inserted
bool BST::insert(unsigned int JourneyCode,unsigned int price) {
  TreeNode *newNode = new TreeNode(JourneyCode,price);      // new node to be inserted
  TreeNode *y = nullptr;
  TreeNode *x = root;                   // Using two pointers to keep track of parent and current node
  while (x != nullptr) {
    y = x;
    if(newNode->JourneyCode < x->JourneyCode) x = x->left;
    else x = x->right;
  }
  newNode->parent = y;
  if(y == nullptr) root = newNode;
  else if(newNode->JourneyCode < y->JourneyCode){
      y->left = newNode;
  }
  else {
    y->right = newNode;
  }
  updatePathLength(newNode->parent);      // Update all the shortest and longest path lengths
  return true;
}

// Update the shortest and longest path lengths while inserting  
void BST::updatePathLength(TreeNode *father){
	if(father == nullptr) return;

	if(father->left == nullptr){        // Longest Path Length
		father->longestPathLength = 1 + father->right->longestPathLength;
	}
	else if(father->right == nullptr){
		father->longestPathLength = 1 + father->left->longestPathLength;
	}
	else{
		father->longestPathLength = 1 + max(father->left->longestPathLength,father->right->longestPathLength);
	}

	if(father->left == nullptr){        // Shortest path length
		father->shortestPathLength = 0;
	}
	else if(father->right == nullptr){
		father->shortestPathLength = 0;
	}
	else{
		father->shortestPathLength = 1 + min(father->left->shortestPathLength,father->right->shortestPathLength);
	}
	updatePathLength(father->parent);     // Using Recursion
 }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(unsigned int JourneyCode, unsigned int price)
{
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){       
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return true; 
    else return false;
  
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(unsigned int JourneyCode, unsigned int price)
{
    if(!find(JourneyCode,price)) return false;
    TreeNode *y = new TreeNode;
    TreeNode *x = new TreeNode;
    TreeNode *deleteNode = searchNode(JourneyCode,price);
    if(deleteNode->left == nullptr || deleteNode->right == nullptr){
        y = deleteNode;
    }
    else y = successor(deleteNode);
    if(y->left != nullptr) x = y->left;
    else x = y->right;
    if(x != nullptr) x->parent = y->parent;
    if(y->parent == nullptr) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    if(y != deleteNode){
        deleteNode->JourneyCode = y->JourneyCode;
        deleteNode->price = y->price;
    }
    return true;
}

// To search for a node and return that Node
// Quite similar to find() function, just it returns that complete node
// instead of price of it
struct TreeNode *BST::searchNode(unsigned int JourneyCode, unsigned int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){      
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return x; 
    else return nullptr; 
}

// Returns the successor of the given Node
struct TreeNode *BST::successor(TreeNode *v){
    if(v->right != nullptr){
        return minNode(v->right);
    }
    TreeNode *y = v->parent;
    while(y != nullptr && v == y->right){
        v = y;
        y = y->parent;
    }
    return y;
}

// Returns the node with minimum price
struct TreeNode *BST::minNode(TreeNode *v){
    while (v->left != nullptr){
        v = v->left;
    }
    return v; 
}

// Returns the minimum price
unsigned int BST::getMinimum() {
    TreeNode *x = root;
    while (x->left != nullptr){
        x = x->left;
    }
    return x->price; 
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

