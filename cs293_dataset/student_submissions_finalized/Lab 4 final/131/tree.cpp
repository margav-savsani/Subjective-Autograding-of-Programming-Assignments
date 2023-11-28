// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

//#include <bits/stdc++.h>
#include <iostream>
#include<vector>
#include<cmath>
#include <string>
#include <vector>
# include <fstream>

 

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
int i=0;

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  if ( find(JourneyCode,price) ){return false;cout<<"found";}
   
   TreeNode * B[64];
   int m=0;
    TreeNode *z=&A[i];
    i++;
    z->JourneyCode=JourneyCode;
    z->price=price;
    TreeNode *y=nullptr;
    TreeNode *x=root;
    while(x!=nullptr){
        y=x; 
        m++;
         B[m]=x;   // store the pointers in an array whose values for longest path and shortest path have to be changed
        if (z->price< x->price)
           x=x->left;
        else x=x->right;
    }
    z->parent=y; 
    if (y==nullptr) 
      root=z;
    else if (z->price< y->price)
      y->left =z;
    else y->right=z;
        
    
     while(m>0){

      B[m]->longestPathLength=nodelong(B[m]);  // change values here 
      B[m]->shortestPathLength=nodeshort(B[m]);
      
      m--;} 
      return true;
}

int BST:: nodelong (TreeNode *x){   //calculate longest path
 if (x==nullptr) return 0;

 return max(nodelong(x->left),nodelong( x->right))+1;
}

int BST:: nodeshort (TreeNode *x){//calculate shortest path
 if (x==nullptr) return 0;
 return min(nodeshort(x->left),nodeshort( x->right))+1;
}


  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
 // struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  //while (currNode != nullptr) {
    //if (currNode->JourneyCode < JourneyCode) {
     // parentOfCurrNode = currNode;
      //currNode = currNode->right;
  //  }
   // else if (currNode->JourneyCode > JourneyCode) {
     // parentOfCurrNode = currNode;
    //  currNode = currNode->left;
   // }
   // else { // currNode->JourneyCode == JourneyCode
    //  return false;
  //  }
 // }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  struct TreeNode* BST:: search(int JourneyCode, int price){ // search and return the node
      TreeNode *x=root;
    while(x!=nullptr && JourneyCode!=x->JourneyCode && price!=x->price){
        if (price< x->price ) x=x->left;
        else x=x->right;
    }
    return x;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{ TreeNode *x=search(JourneyCode, price);
    if (x==nullptr) {return false;}
    else if ( JourneyCode==x->JourneyCode && price==x->price) return true;
    else return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.

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
        printBST( prefix +(isLeft ? "│   " : "    "), false);
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

