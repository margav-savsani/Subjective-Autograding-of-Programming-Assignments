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
  else return (maxDepth() - minDepth());
}

bool BST::insert(int JourneyCode, int price){
  if(root == nullptr){
    root = new TreeNode(JourneyCode, price);
  }
  if (find(JourneyCode, price)){
        return false;
  }
  TreeNode *temp ;temp = new TreeNode();
  TreeNode *current = root;
   
  TreeNode *add;add = new TreeNode(JourneyCode,price);
  if(root->price == 0){
    root = add;
    return true;
  }
  while(current != nullptr){
      temp = current;
      if (JourneyCode < current->JourneyCode){
         current = current->left;
       }
      else {current = current->right;}
      }
   add->parent = temp;

    if (add->JourneyCode < temp->JourneyCode){
        temp->left = add;
    }
    else {
        temp->right = add;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
  TreeNode *x;
    x = root;
    while (x != NULL && price != x->price && JourneyCode != x->JourneyCode){
        if (JourneyCode < x->JourneyCode){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    if(x == NULL){
        return false;
    }
    else if(x->price == price){
        return true;
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    TreeNode *x;
    if(find(JourneyCode, price) == false){
        return false;
    }
    x = deleteNode(root, JourneyCode, price);
    if(x != NULL)
        return true;
    else 
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

