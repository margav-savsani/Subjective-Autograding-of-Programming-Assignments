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
  
    TreeNode* varParent = NULL;
    TreeNode* varCurrent = root;
    while(varCurrent != NULL){
        int x = varCurrent->JourneyCode;
        if(x < JourneyCode){
            varParent = varCurrent;
            varCurrent = varCurrent->right;
        }
        else if(x > JourneyCode){
                varParent = varCurrent;
                varCurrent = varCurrent->left;
        }
        else{
            return false;
        }
    }

    if(varParent == NULL){
        root = new TreeNode(JourneyCode, price, NULL, NULL, NULL);
        root->longestPathLength = 0;
        root->shortestPathLength = 0;
        return true;
    }

    if(varParent->JourneyCode < JourneyCode){
        varParent->right = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        varCurrent = varParent->right;
        varParent->right->longestPathLength = 0;
        varParent->right->shortestPathLength = 0;
    }
    else{
        varParent->left = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        varCurrent = varParent->left;
        varParent->left->longestPathLength = 0;
        varParent->left->shortestPathLength = 0;
    }

    while(varParent!=NULL){
        if(varParent->right == NULL || varParent->left == NULL){
            varParent->longestPathLength ++;
            varParent->shortestPathLength ++;
        }
        else{
            if(varParent->right == varCurrent){
                if(varParent->left->longestPathLength <= varCurrent->longestPathLength-1)
                    varParent->longestPathLength++;
                if(varParent->left->shortestPathLength > varCurrent->shortestPathLength-1)
                    varParent->shortestPathLength++;
            }
            else{
                if(varParent->right->longestPathLength <= varCurrent->longestPathLength-1)
                    varParent->longestPathLength++;
                if(varParent->right->shortestPathLength > varCurrent->shortestPathLength-1)
                    varParent->shortestPathLength++;
            }
        }
        varCurrent = varCurrent->parent;
        varParent = varParent->parent;
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
    TreeNode *var = root;
    while(var != NULL){
        if(var->JourneyCode == JourneyCode)
            return true;
        else if(var->JourneyCode < JourneyCode)
            var = var->right;
        else
            var = var->left;
    }
  return false;
}

TreeNode* BST::find(TreeNode *var, int JourneyCode){
    while(var != NULL){
        if(var->JourneyCode == JourneyCode)
            return var;
        else if(var->JourneyCode < JourneyCode)
            return find(var->right, JourneyCode);
        else
            return find(var->left, JourneyCode);
    }
    return NULL;
}

TreeNode* BST::TreeMinimum(TreeNode* var){
    TreeNode *varParent = var->parent;
    while(var != NULL){
        varParent = var;
        var = var->left;
    }
    return varParent;
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
    TreeNode* varCurrent = NULL;
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
        else if(tobeDelPar->JourneyCode < JourneyCode){
            tobeDelPar->right = NULL;
        }
        else{
            tobeDelPar->left = NULL;
        }
        //delete(tobeDel);
        varCurrent = tobeDelPar;
        tobeDelPar->shortestPathLength = 0;
        if(tobeDel->left == NULL && tobeDelPar->right == NULL)
            tobeDelPar->longestPathLength = 0; 
    }
    else if(tobeDel->left == NULL){
        if(tobeDelPar == NULL){
            tobeDel->right->parent = tobeDelPar;
        }
        else if(tobeDelPar->JourneyCode < JourneyCode){
            tobeDelPar->right = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        varCurrent = tobeDelPar;
        if(tobeDelPar->right == tobeDel){
            if(tobeDelPar->left->longestPathLength <= tobeDel->longestPathLength-1)
                tobeDelPar->longestPathLength--;
            if(tobeDelPar->left->shortestPathLength >= tobeDel->shortestPathLength)
                tobeDelPar->shortestPathLength--;
        }
        if(tobeDelPar->left == tobeDel){
            if(tobeDelPar->right->longestPathLength <= tobeDel->longestPathLength-1)
                tobeDelPar->longestPathLength--;
            if(tobeDelPar->right->shortestPathLength >= tobeDel->shortestPathLength)
                tobeDelPar->shortestPathLength--;
        }
        delete(tobeDel);
    }
    else if(tobeDel->right == NULL){
        if(tobeDelPar == NULL){
            tobeDel->left->parent = tobeDelPar;
        }
        else if(tobeDelPar->JourneyCode < JourneyCode){
            tobeDelPar->right = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }

        varCurrent = tobeDelPar;
        if(tobeDelPar->right == tobeDel){
            if(tobeDelPar->left->longestPathLength <= tobeDel->longestPathLength-1)
                tobeDelPar->longestPathLength--;
            if(tobeDelPar->left->shortestPathLength >= tobeDel->shortestPathLength)
                tobeDelPar->shortestPathLength--;
        }
        if(tobeDelPar->left == tobeDel){
            if(tobeDelPar->right->longestPathLength <= tobeDel->longestPathLength-1)
                tobeDelPar->longestPathLength--;
            if(tobeDelPar->right->shortestPathLength >= tobeDel->shortestPathLength)
                tobeDelPar->shortestPathLength--;
        }
        delete(tobeDel);
    }
    else{
        TreeNode *successor = TreeSuccessor(tobeDel);
        if(successor->right == NULL){
            if(successor->parent->JourneyCode < successor->JourneyCode){
                successor->parent->right = NULL;
            }    
            else{
                successor->parent->left = NULL;
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
        }
        else{
            if(successor->parent->JourneyCode < successor->JourneyCode){
                successor->parent->right = successor->right;
                successor->right->parent = successor->parent;
            }
            else{
                successor->parent->left = successor->right;
                successor->right->parent = successor->parent;
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
        }
    
        varCurrent = successor->parent;

        if(successor->parent->right == successor){
            if(varCurrent->left->longestPathLength <= successor->longestPathLength-1)
                varCurrent->longestPathLength--;
            if(varCurrent->left->shortestPathLength >= successor->shortestPathLength)
                varCurrent->shortestPathLength--;
        }
        if(varCurrent->left == successor){
            if(varCurrent->right->longestPathLength <= successor->longestPathLength-1)
                varCurrent->longestPathLength--;
            if(varCurrent->right->shortestPathLength >= successor->shortestPathLength)
                varCurrent->shortestPathLength--;
        }  
    }

    TreeNode *varParent = varCurrent->parent;

    while(varParent != NULL){
        if(varParent->right == varCurrent){
            if(varParent->left->longestPathLength <= varCurrent->longestPathLength-1)
                varParent->longestPathLength--;
            if(varParent->left->shortestPathLength >= varCurrent->shortestPathLength)
                varParent->shortestPathLength--;
        }
        if(varParent->left == varCurrent){
            if(varParent->right->longestPathLength <= varCurrent->longestPathLength-1)
                varParent->longestPathLength--;
            if(varParent->right->shortestPathLength >= varCurrent->shortestPathLength)
                varParent->shortestPathLength--;
        }
    }
  return true;;
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

