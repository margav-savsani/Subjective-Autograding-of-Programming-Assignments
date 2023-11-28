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

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  if(root->JourneyCode==JourneyCode ) return true;
    
    if(price<=root->price && root->left==nullptr){
        return false;
    }

    if(price>root->price && root->right==nullptr){
        return false;
    }

    if(price<=root->price){
        BST l(root->left);
        return l.find(JourneyCode,price);
    }

    if(price>root->price){
        BST r(root->right);
        return r.find(JourneyCode,price);
    }
}
	

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
    if(find(JourneyCode,price)) return false;

    if(root->JourneyCode==0 && root->price==0){
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }

    if(price<=root->price && root->left==nullptr){
        TreeNode *l=new TreeNode(JourneyCode,price);
        l->parent=root;
        root->left=l;
        return true;
    }
    
    if(price<=root->price){
        BST l(root->left);
        
        return l.insert(JourneyCode,price);
    }

    if(price>root->price && root->right==nullptr){
        TreeNode *r=new TreeNode(JourneyCode,price);
        r->parent=root;
        root->right=r;
        return true;
    }

    if(price>root->price){
        BST r(root->right);

        return r.insert(JourneyCode,price);
    }

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    
}

TreeNode *BST::getadress(int JourneyCode,int price){
    if(root->price ==price && root->JourneyCode==JourneyCode) return root;
    
    if(price<=root->price){
        BST l(root->left);
        return l.getadress(JourneyCode,price);
    }

    if(price>root->price){
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

    if(tn->right==NULL && tn->left==NULL){ if(tn->parent->left==NULL) {tn->parent->right=NULL;return true;}
                                            else if(tn->parent->right==NULL) {tn->parent->left=NULL;return true;}
                                            else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=NULL;return true;}
                                                    else {tn->parent->right=NULL;return true;}}
                                         }
    else if(tn->right==NULL && tn->left!=NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->left;
                                    tn->left->parent=tn->parent;
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->left;
                                          tn->left->parent=tn->parent;
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->left;
                                                                tn->left->parent=tn->parent;
                                                                return true;}
                else {tn->parent->right=tn->left;
                        tn->left->parent=tn->parent;
                        return true;}
            }
    }


    else if(tn->right!=NULL && tn->left==NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->right;
                                    tn->right->parent=tn->parent;
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->right;
                                          tn->right->parent=tn->parent;
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->right;
                                                                tn->right->parent=tn->parent;
                                                                return true;}
                else {tn->parent->right=tn->right;
                        tn->right->parent=tn->parent;
                        return true;}
            }
    }

    else {

        TreeNode *predecessor=getpredecessor(tn);
        bool god=remove(predecessor->JourneyCode,predecessor->price);

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

