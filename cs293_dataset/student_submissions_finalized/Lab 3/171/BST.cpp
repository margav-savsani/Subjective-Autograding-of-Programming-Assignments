#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

BST::BST(){; }
BST::BST(TreeNode *root){; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price))
      return false;
    else
      TreeNode(JrnyCode,price);
      return true;
      
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { return false; }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode,price))
      return false;
    else
      
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST :: preorder(TreeNode *root){
    if(root->JourneyCode==0)
      return;
    else{
      cout << root->JourneyCode;
      preorder(root->left);
      preorder(root->right);
    }

}
void postorder(TreeNode *root){
    if(root->JourneyCode==0)
      return;
    else{
      postorder(root->left);
      postorder(root->right);
      cout << root->JourneyCode;
    }
}
void inorder(TreeNode *root){
    if(root->JourneyCode==0)
      return;
    else{
      inorder(root->left);
      cout << root->JourneyCode;
      inorder(root->right);
    }

}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0)
       preorder(*root); 
    else if(typeOfTraversal==1)
      postorder(*root);
    else if(typeOfTraversal==2)
      inorder(*root);
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {return 0; }

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
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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

