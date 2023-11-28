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
    if(find(JourneyCode, price)){
        return false;
    }
    TreeNode* tra;
    TreeNode* par;
    TreeNode* nw;
    nw=new TreeNode(JourneyCode, price);
    tra=root;
    par=NULL;
    while (tra != NULL){
        par=tra;
        if(tra->JourneyCode > JourneyCode){
            tra = tra->left;
        }
        else{
            tra = tra->right;
        }
    }
    tra=nw;
    tra->parent=par;
    if(par==NULL){
        root=tra;
        return true;
    }
    if(par->JourneyCode > tra->JourneyCode){
        par->left=tra;
    }
    else{
        par->right=tra;
    }
    while(tra!=root){
    
      if((par->left==NULL || par->right==NULL)){
        par->shortestPathLength=1+tra->shortestPathLength;
        par->longestPathLength=1+tra->longestPathLength;
      }
      else{
        int a1=tra->longestPathLength;
        int a2=tra->shortestPathLength;
        int b1, b2;
        if(par->left==tra){
            b1=par->right->longestPathLength;
            b2=par->right->shortestPathLength;
        }
        else{
            b1=par->left->longestPathLength;
            b2=par->left->shortestPathLength;
        }
        
        if(a1<b1) par->longestPathLength=b1+1;
        else par->longestPathLength=a1+1;

        if(a2<b2) par->shortestPathLength=a2+1;
        else par->shortestPathLength=b2+1;
      } 
      tra=par;
      par=par->parent;
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
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up. 
    TreeNode* tra;
    tra=root;
    while (tra != NULL){
        if(tra->price == price && tra->JourneyCode==JourneyCode){
            return true;
        }
        else if(tra->JourneyCode > JourneyCode){
            tra = tra->left;
        }
        else{
            tra = tra->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
// bool BST::remove(int JourneyCode, int price)
// {
//   // The following filler code snippet is only given to facilitate
//   // compilation.  You should replace it with appropriate code, very
//   // similar to what you had done in lab assignment 3.
//   //
//   // Recall from CS 213 lectures about the various ways in which the
//   // BST can be restructured when a node is deleted. You can implement
//   // any of these alternatives.
//   //
//   // Do not forget to update shortestPathLength and
//   // longestPathLength of (possibly all) BST nodes in the
//   // path from the root to nodes whose position in the BST is affected
//   // by the remove.
    
//   return false;
// }

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

        // print the value of     // if(a->insert(1,1)) cout<<"5"<<endl;the node
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

