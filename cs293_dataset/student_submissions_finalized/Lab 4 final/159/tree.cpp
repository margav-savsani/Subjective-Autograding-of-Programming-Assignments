// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
void BST:: reset(TreeNode* p){
   if(p==nullptr){return;}
   else{
    p->shortestPathLength=minheight(p);
    p->longestPathLength=maxheight(p);
    reset(p->left);
    reset(p->right);
    return;
   }
}
int BST::getImbalance()
{ if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  if(find(JourneyCode,price)){return false;}
    else{
         root = insertion(root,JourneyCode,price);
         reset(root);
         return true;
    }
}
TreeNode* BST::insertion(TreeNode* x,int JourneyCode,int price){
     if (x == NULL) {
        TreeNode* z = new TreeNode(JourneyCode,price);
        return z;
    }
    if (x -> price > price) {
        x -> left = insertion(x -> left, JourneyCode,price);
    }
    else {
        x -> right = insertion(x -> right , JourneyCode,price);
    }
    return x;
}
int BST::maxheight(TreeNode* r){
      int h=0;
       if(r==nullptr){
        return h;
       }
       else{
        h=1+max(maxheight(r->left),maxheight(r->right));
        return h;
       }
}
int BST::minheight(TreeNode* r){
      int h=0;
       if(r==nullptr){
        return h;
       }
       else{
        h=1+min(minheight(r->left),minheight(r->right));
        return h;
       }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode* P;
    if(root==nullptr){return false;}
    else if(price<root->price){
         P=root->left;
         BST Q(P);
         return Q.find(JourneyCode,price);
      }
    else if(price>root->price){
         P=root->right;
         BST Q(P);
         return Q.find(JourneyCode,price);
      }
    else {return true;}
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

