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
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
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
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}
	
  TreeNode* BST::find(TreeNode *var, int price){
    while(var != NULL){
        if(var->price == price)
            return var;
        else if(var->price < price)
            return find(var->right, price);
        else
            return find(var->left, price);
    }
    return NULL;
}


TreeNode* BST::TreeSuccessor(TreeNode *var){
    if(var->right != NULL){
        return TreeMinimum(var->right);
    }
    TreeNode *varParent = var->parent;
    while(varParent != NULL && var == varParent->right){
        var = varParent;
        varParent = varParent->parent;
    }
    return varParent;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
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
    TreeNode* tobeDel = find(root, price);
    TreeNode* tobeDelPar = new TreeNode;
    if(tobeDel == NULL)
        tobeDelPar = NULL;
    else
        tobeDelPar = tobeDel->parent;
    
    if(tobeDel == NULL)
        return false;
    else if(tobeDel->left == NULL && tobeDel->right == NULL){
        if(tobeDelPar == NULL){
            root = NULL;
            return true;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = NULL;
            tobeDelPar->identity = 0;
            if(tobeDelPar->left != NULL)
                tobeDelPar->identity = -1;
        }
        else{
            tobeDelPar->left = NULL;
            tobeDelPar->identity = 0;
            if(tobeDelPar->right != NULL)
                tobeDelPar->identity = 1;
        }
        //delete(tobeDel);
        return true;
    }
    else if(tobeDel->left == NULL){
        if(tobeDelPar == NULL){
            tobeDel->right->parent = tobeDelPar;
            return true;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        delete(tobeDel);
        return true;
    }
    else if(tobeDel->right == NULL){
        if(tobeDelPar == NULL){
            tobeDel->left->parent = tobeDelPar;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }
        delete(tobeDel);
        return true;
    }
    else{
        TreeNode *successor = TreeSuccessor(tobeDel);
        if(successor->right == NULL){
            if(successor->parent->price < successor->price){
                successor->parent->right = NULL;
                if(successor->parent->left != NULL)
                    successor->parent->identity = -1;
                else
                    successor->parent->identity = 0;
            }    
            else{
                successor->parent->left = NULL;
                if(successor->parent->right != NULL)
                    successor->parent->identity = 1;
                else
                    successor->parent->identity = 0;            
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
            delete(successor);
            return true;
        }
        else{
            if(successor->parent->price < successor->price){
                if(successor->parent->right == NULL)
                    successor->parent->identity = 2;
                successor->parent->right = successor->right;
                successor->right->parent = successor->parent;
            }
            else{
                if(successor->parent->left == NULL)
                    successor->parent->identity = 2;
                successor->parent->left = successor->right;
                successor->right->parent = successor->parent;
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
            delete(successor);
            return true;
        }
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

