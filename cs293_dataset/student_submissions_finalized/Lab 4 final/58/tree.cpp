// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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


void BST::update(int JourneyCode, int price){

    if(root->JourneyCode==JourneyCode){
        
        int m=leastlength(),n=highestlength();
        if(m+1> root->shortestPathLength) root->shortestPathLength=m+1;
        if(n+1> root->longestPathLength)  root->longestPathLength=n+1;

        return;
    }

    if(JourneyCode<=root->JourneyCode){

        int m=leastlength(),n=highestlength();
        if(m+1> root->shortestPathLength) root->shortestPathLength=m+1;
        if(n+1> root->longestPathLength)  root->longestPathLength=n+1;

        BST l(root->left);
        return l.update(JourneyCode,price);
    }

    if(JourneyCode>root->JourneyCode){

        int m=leastlength(),n=highestlength();
        if(m+1> root->shortestPathLength) root->shortestPathLength=m+1;
        if(n+1> root->longestPathLength)  root->longestPathLength=n+1;

        BST r(root->right);
        return r.update(JourneyCode,price);
    }
}

int BST::leastlength(){
    if(root->left==nullptr && root->right==nullptr) return 0;

    else if(root->left==nullptr && root->right!=nullptr) return 0;

    else if(root->left!=nullptr && root->right==nullptr) return 0;

    else{
        BST l(root->left),r(root->right);
        return 1+min(l.leastlength(),r.leastlength());
    }
}

int BST::highestlength(){
    if(root->left==nullptr && root->right==nullptr) return 0;

    else if(root->left==nullptr){
        BST r(root->right);
        return 1+r.highestlength();
    }

    else if(root->right==nullptr){
        BST l(root->left);
        return 1+l.highestlength();
    }

    else {
        BST l(root->left),r(root->right);
        return 1+max(l.highestlength(),r.highestlength());
    }
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

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
  } 

    if(parentOfCurrNode!=nullptr){
      if(JourneyCode<parentOfCurrNode->JourneyCode){
        currNode=new TreeNode(JourneyCode,price);
        currNode->parent=parentOfCurrNode;
        parentOfCurrNode->left=currNode;
        currNode->shortestPathLength=currNode->longestPathLength=1;

        update(JourneyCode,price);
      } 
      else if(JourneyCode>parentOfCurrNode->JourneyCode){
        currNode=new TreeNode(JourneyCode,price);
        currNode->parent=parentOfCurrNode;
        parentOfCurrNode->right=currNode;
        currNode->shortestPathLength=currNode->longestPathLength=1;

        update(JourneyCode,price);
      }
    }

    else{
      currNode=new TreeNode(JourneyCode,price);
      currNode->shortestPathLength=currNode->longestPathLength=1;
      root=currNode;
    }
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
  
  if(root==nullptr) return false;

    if(root->JourneyCode==JourneyCode ) return true;
    
    if(JourneyCode<=root->JourneyCode && root->left==nullptr){
        return false;
    }

    if(JourneyCode>root->JourneyCode && root->right==nullptr){
        return false;
    }

    if(JourneyCode<=root->JourneyCode){
        BST l(root->left);
        return l.find(JourneyCode,price);
    }

    if(JourneyCode>root->JourneyCode){
        BST r(root->right);
        return r.find(JourneyCode,price);
    }
}

TreeNode *BST::getadress(int JourneyCode,int price){
    if(root->price ==price && root->JourneyCode==JourneyCode) return root;
    
    if(JourneyCode<=root->JourneyCode){
        BST l(root->left);
        return l.getadress(JourneyCode,price);
    }

    if(JourneyCode>root->JourneyCode){
        BST r(root->right);
        return r.getadress(JourneyCode,price);
    }
}

TreeNode *BST::getmax(TreeNode *kingleft){
    if(kingleft->right==NULL) {return kingleft;}

    else {return getmax(kingleft->right);}
}

TreeNode *BST::getpredecessor(TreeNode *king){
    return getmax(king->left);
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
    
  if(!find(JourneyCode,price)) return false;

    TreeNode *tn=getadress(JourneyCode,price);

    if(tn->right==NULL && tn->left==NULL){ if(tn->parent->left==NULL) {tn->parent->right=NULL;update(tn->parent->JourneyCode,tn->parent->price);return true;}
                                            else if(tn->parent->right==NULL) {tn->parent->left=NULL;update(tn->parent->JourneyCode,tn->parent->price);return true;}
                                            else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=NULL;update(tn->parent->JourneyCode,tn->parent->price);return true;}
                                                    else {tn->parent->right=NULL;update(tn->parent->JourneyCode,tn->parent->price);return true;}}
                                         }
    else if(tn->right==NULL && tn->left!=NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->left;
                                    tn->left->parent=tn->parent;
                                    update(tn->parent->JourneyCode,tn->parent->price);
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->left;
                                          tn->left->parent=tn->parent;
                                          update(tn->parent->JourneyCode,tn->parent->price);
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->left;
                                                                tn->left->parent=tn->parent;
                                                                update(tn->parent->JourneyCode,tn->parent->price);
                                                                return true;}
                else {tn->parent->right=tn->left;
                        tn->left->parent=tn->parent;
                        update(tn->parent->JourneyCode,tn->parent->price);
                        return true;}
            }
    }


    else if(tn->right!=NULL && tn->left==NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->right;
                                    tn->right->parent=tn->parent;
                                    update(tn->parent->JourneyCode,tn->parent->price);
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->right;
                                          tn->right->parent=tn->parent;
                                          update(tn->parent->JourneyCode,tn->parent->price);
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->right;
                                                                tn->right->parent=tn->parent;
                                                                update(tn->parent->JourneyCode,tn->parent->price);
                                                                return true;}
                else {tn->parent->right=tn->right;
                        tn->right->parent=tn->parent;
                        update(tn->parent->JourneyCode,tn->parent->price);
                        return true;}
            }
    }

    else {

        TreeNode *predecessor=getpredecessor(tn);
        bool god=remove(predecessor->JourneyCode,predecessor->price);
        update(predecessor->JourneyCode,predecessor->price);

        tn->JourneyCode=predecessor->JourneyCode;
        tn->price=predecessor->price;

        return true;
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

