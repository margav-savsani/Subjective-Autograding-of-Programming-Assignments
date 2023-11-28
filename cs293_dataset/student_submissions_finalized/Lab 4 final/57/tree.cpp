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
  longestPathLength = maxhig(root);
  shortestPathLength = minhig(root);
  return (longestPathLength - shortestPathLength);
  
}


bool BST::insert(int jc ,int pc)
{if(root==nullptr){root=new TreeNode(jc,pc);return true;}
 if(find(jc,pc))return false;
    

   TreeNode *tempNode ;tempNode= new TreeNode();
   TreeNode *current=root;
   
   TreeNode *add;add=new TreeNode(jc,pc);
   if(root->price==0){root=add;return true;}
   
   while(current !=nullptr){
      tempNode= current;
      if (jc <current->JourneyCode){
         current=current->left;
       }
      else {current=current->right;}
      }
   add->parent=tempNode;

  if (add->JourneyCode <= tempNode->JourneyCode){tempNode->left=add;}
    else {tempNode->right=add;}
    
   return true;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int jc, int pc)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  struct TreeNode *current =root;
   if(root->price==0){return false;}
   while(current!=nullptr){
    if((current->JourneyCode==jc)&&(current->price=pc)){return true;}

    if( current->JourneyCode > jc){
        current=current->left;}
     else{current=current->right;}
    }
   return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{TreeNode *x = this->root; // STARTING FROM ROOT NODE
    while (x != NULL && ((x->price != price) || (x->JourneyCode != JourneyCode)))
    {
        // SEARCH TILL THE EXACT STATION IS FOUND
        // OR WE REACH A NULL.
        if (price < (x->price))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    } // Finally x would be the element returned from our search
    if (x == NULL)
    { // IF NO SUCH NODE
        return false;
    }
    else
    { // TRUE IF NODE IS FOUND.
        TreeNode *y = new TreeNode;
        TreeNode *z = new TreeNode;
        if (x->left == NULL || x->right == NULL)
        {
            // If there is no left or right child of x
            // That means atmost one child for x.
            y = x; // y is the node to be deleted.
        }
        else
        {
            y = successor(x); // IF not then x has two child and we assign y as the successor of x.
        }
        if (y->left != NULL)
        { // If no left child of y then assign z as the left child of y.
            z = y->left;
        }
        else
        {
            z = y->right; // otherwise z is the right child
        }
        if (z != NULL)
        {
            z->parent = y->parent;
        }
        if (y->parent == NULL)
        {
            this->root = z; // if y is the root
        }
        else if (y == y->parent->left)
        {
            y->parent->left = z;
        }
        else
        {
            y->parent->right = z;
        }
        if (y != x)
        {
            x->JourneyCode = y->JourneyCode;
            x->price = y->price; // Copying all the content
        }
        return true;
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

