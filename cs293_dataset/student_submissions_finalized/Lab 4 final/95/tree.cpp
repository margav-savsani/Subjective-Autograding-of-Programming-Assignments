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
  else{ return root->getImbalance();}
}

// insert node in bst
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  
 TreeNode *a = root;
    TreeNode *parent = NULL;
    TreeNode *q = new TreeNode(JourneyCode, price);
    while (a != NULL)
    {
        if ((a->JourneyCode) < JourneyCode)
        {
            parent = a;
            a = (a->right);
        }
        else if ((a->JourneyCode) > JourneyCode)
        {
            parent = a;
            a = (a->left);
        }
        
        else
            return false;
    }

    q->parent = parent;
    if (parent == NULL)
    {  
        this->root = q;
        q->shortestPathLength=0;
        q->longestPathLength=0;
    }
    else if ((parent->JourneyCode) < JourneyCode)
    {   
        parent->right = q;
         q->longestPathLength=0;
    q->shortestPathLength=0;
    
    while(parent!=NULL){
        if(parent->left!=NULL&&parent->right!=NULL){
      if(parent->longestPathLength==parent->left->longestPathLength+1&&parent->shortestPathLength==parent->left->shortestPathLength+1){
             break;
        }
        else {
            parent->longestPathLength=1+max(parent->right->longestPathLength,parent->left->longestPathLength);
            parent->shortestPathLength=1+min(parent->right->shortestPathLength,parent->left->shortestPathLength);
        }
        }
        else{
            if(parent->left==NULL){
            parent->longestPathLength=parent->right->longestPathLength+1;}
            else{
                parent->longestPathLength=parent->left->longestPathLength+1;
            }
            parent->shortestPathLength=0;
        }
        parent=parent->parent;
    }
    }
    else
    {parent->left = q; 
     q->longestPathLength=0;
    q->shortestPathLength=0;
    
    while(parent!=NULL){
        if(parent->right!=NULL&&parent->left!=NULL){
        
            parent->longestPathLength=1+max(parent->right->longestPathLength,parent->left->longestPathLength);
            parent->shortestPathLength=1+min(parent->right->shortestPathLength,parent->left->shortestPathLength);
             
        }
       
        else{
            if(parent->left==NULL){
            parent->longestPathLength=parent->right->longestPathLength+1;}
            else{
                parent->longestPathLength=parent->left->longestPathLength+1;
            }
            parent->shortestPathLength=0;
        }
        
    parent=parent->parent;
    }
    }
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
{TreeNode *find_node = root;
    while (find_node != NULL)
    {
        if ((find_node->JourneyCode) <= price && (find_node->JourneyCode) != JourneyCode)
        {
            find_node = find_node->right;
        }
        else if ((find_node->JourneyCode) == JourneyCode && (find_node->JourneyCode) == JourneyCode)
        {
            return true;
        }
        else if ((find_node->JourneyCode) > JourneyCode)
        {
            find_node = find_node->left;
        }
    }
    return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{TreeNode *find_node = root;
    TreeNode *find_succesor = root;
    while (find_node != NULL)
    {
        if ((find_node->price) <= price && (find_node->JourneyCode != JourneyCode))
        {
            find_node = find_node->right;
            find_succesor = find_succesor->right;
        }
        else if ((find_node->price) > price)
        {
            find_node = find_node->left;
            find_succesor = find_succesor->left;
        }
        else if ((find_node->price) == price && (find_node->JourneyCode) == JourneyCode)
        {
            if (find_node->left == NULL && find_node->right == NULL)
            {
                if (find_node->parent == NULL)
                {
                    this->root = NULL;
                    return true;
                }
                find_node = find_node->parent;
                if (find_node->left != NULL)
                {
                    if (find_node->left->JourneyCode == JourneyCode)
                    {
                        find_node->left = NULL;
                    }
                }
                else
                    find_node->right = NULL;
                return true;
            }
            else if (find_node->left == NULL)
            {
                if (find_node->parent == NULL)
                {
                    find_node->right->parent = NULL;
                    this->root = find_node->right;
                    return true;
                }
                else if (find_node->parent->left != NULL)
                {
                    if (find_node->parent->left->price == price && find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->right->parent = find_node->parent;
                        find_node->parent->left = find_node->right;
                        return true;
                    }
                }
                else
                {
                    find_node->right->parent = find_node->parent;
                    find_node->parent->right = find_node->right;
                    return true;
                }
            }
            else if (find_node->right == NULL)
            {
                if (find_node->parent == NULL)
                {
                    find_node->left->parent = NULL;
                    this->root = find_node->left;
                    return true;
                }
                else if (find_node->parent->left != NULL)
                {
                    if (find_node->parent->left->price == price && find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->left->parent = find_node->parent;
                        find_node->parent->left = find_node->left;

                        return true;
                    }
                }
                else
                {
                    find_node->left->parent = find_node->parent;
                    find_node->parent->right = find_node->left;
                    return true;
                }
            }
            else
            {
                find_succesor = find_succesor->right;
                if (find_succesor->left == NULL)
                {
                    if (find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->parent->left = find_succesor;
                        find_node->right->parent = find_node->parent;
                        find_node->left->parent = find_succesor;
                        find_succesor->left = find_node->left;
                        return true;
                    }
                }
                while ((find_succesor->left) != NULL)
                {
                    find_succesor = find_succesor->left;
                }
                if (find_succesor->right == NULL)
                {
                    find_succesor->parent->left = NULL;
                    find_node->price = find_succesor->price;
                    find_node->JourneyCode = find_succesor->JourneyCode;
                    return true;
                }
                find_succesor->right->parent = find_succesor->parent;
                find_succesor->parent->left = find_succesor->right;
                find_node->price = find_succesor->price;
                find_node->JourneyCode = find_succesor->JourneyCode;
                return true;
            }
        }
    }

    return false;
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
        cout << root->JourneyCode<<" " <<root->shortestPathLength <<"  "<<root->longestPathLength<< endl;
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

