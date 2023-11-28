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
int TreeNode::getShortestPath() {
  if(left==nullptr&& right==nullptr) {
    shortestPathLength=1;
    return shortestPathLength;
  }
  else if((left==nullptr&&right!=nullptr)||(left!=nullptr&&right==nullptr)) {
    shortestPathLength=1;
    return shortestPathLength;
  }
  else {

  shortestPathLength= min(left->getShortestPath(),right->getShortestPath())+1;
  return shortestPathLength;
}
}
int TreeNode::getLongestPath() {
  if(left==nullptr&& right==nullptr) {
    longestPathLength=1;
    return longestPathLength;
  }
  else if(left==nullptr&&right!=nullptr){
    longestPathLength=right->getLongestPath()+1;
    return longestPathLength;
  }
  else if(left!=nullptr&&right==nullptr) {
    longestPathLength=left->getLongestPath()+1;
    return longestPathLength;
  }
  else {
    longestPathLength=max(left->getLongestPath(),right->getLongestPath())+1;
    return longestPathLength;
  }
  
}
int TreeNode::getImbalance(){
    return getLongestPath()-getShortestPath();
}
int BST::getShortestPath(TreeNode *x) {
  if(x==nullptr) return 0;
  else if(x->right==nullptr&&x->left==nullptr) return 1;
  else return min(getShortestPath(x->left),getShortestPath(x->right))+1;
}
int BST::getLongestPath(TreeNode *x) {
  if(x==nullptr) return 0;
  else if(x->right==nullptr&&x->left==nullptr) return 1;
  else return max(getLongestPath(x->left),getLongestPath(x->right))+1;

}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}
bool BST::Insert(int JourneyCode,int price, TreeNode *x) {
    root=x;
    if(JourneyCode==x->JourneyCode) {
            if(x->price==price) return false;
            else {
                if(x->right==nullptr) {
                x->right->JourneyCode=JourneyCode;
                x->right->price=price;
                x->right->right=nullptr;
                x->right->left=nullptr;
                x->right->parent=x;
                x->right->shortestPathLength=1;
                x->right->longestPathLength=1;
                x->shortestPathLength=getShortestPath(x);
                x->longestPathLength=getLongestPath(x);
                
                return true;
                }
                else{
                BST rightTree;
                rightTree.root=x->right;
                return rightTree.Insert(JourneyCode,price,x->right);
            }
            }
        }
        else if(JourneyCode<x->JourneyCode) {
            if(x->left==nullptr) {
                x->left->JourneyCode=JourneyCode;
                x->left->price=price;
                x->left->left=nullptr;
                x->left->right=nullptr;
                x->parent->parent=x;
                x->left->shortestPathLength=1;
                x->left->longestPathLength=1;
                x->shortestPathLength=getShortestPath(x);
                x->longestPathLength=getLongestPath(x);
                return true;
            }
            else{

              BST leftTree;
              leftTree.root=x->left;
              return leftTree.Insert(JourneyCode,price,x->left);
            }
        }
        else  {
            if(x->right==nullptr) {
                x->right->JourneyCode=JourneyCode;
                x->right->price=price;
                x->right->right=nullptr;
                x->right->left=nullptr;
                x->right->parent=x;
                x->right->shortestPathLength=1;
                x->right->longestPathLength=1;
                x->shortestPathLength=getShortestPath(x);
                x->longestPathLength=getLongestPath(x);
                return true;
                }
                else{
                   BST rightTree;
                   rightTree.root=x->right;
                   return rightTree.Insert(JourneyCode,price,x->right);
        }
        }
}
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  /*struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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
  
  
  return true;*/
  return Insert(JourneyCode,price,root);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::Find(int JourneyCode,int price, TreeNode *x) {
     if(x==nullptr) return false;
    if(x->JourneyCode==JourneyCode) {
        if(x->price==price) return true;
        else{
            BST rightTree;
            rightTree.root=x->right;
            return rightTree.Find(JourneyCode,price,x->right);
        }
    }
    else if(x->JourneyCode>JourneyCode) {
        BST leftTree;
        leftTree.root=x->left;
        return leftTree.Find(JourneyCode,price,x->left);
    }
    else {
        BST rightTree;
        rightTree.root=x->right;
        return rightTree.Find(JourneyCode,price,x->right);
    }

}
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  return Find(JourneyCode,price,root) ;
  
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* BST::Successor(TreeNode *x) {
    if(x->right!=nullptr) {
        x=x->right;
        while(x->left!=nullptr) {
            x=x->left;

        }
        return x;
    }
    else {
      return NULL;
    }
     
}
bool BST::Remove(int JourneyCode, int price,TreeNode *x) {

    x=root ;
    if(x==nullptr) return false;
    else {
        if(x->price==price) {
            if(x->JourneyCode==JourneyCode) {
                if((x->left==nullptr)&&(x->right==nullptr)) {
                    x=nullptr;
                    return true;
                } 
                else if((x->left!=nullptr)&&(x->right==nullptr)){
                    if(x->parent->price>x->price){
                        x->parent->left=x->left;
                        x->left->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                    else{
                        x->parent->right=x->left;
                        x->left->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                }
                else if((x->left=nullptr)&&(x->right=nullptr)){
                    if(x->parent->price<=x->price) {
                        x->parent->right=x->right;
                        x->right->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                    else{
                        x->parent->left=x->right;
                        x->right->parent=x->parent;
                        x=nullptr;
                        return true;
    
                }
               }
               else{
                   int tempprice=0;
                   int tempJourneyCode=0;
                   TreeNode *tempnode;
                   tempprice=Successor(x)->price;
                   tempJourneyCode=Successor(x)->JourneyCode;
                   x->price=tempprice;
                   x->JourneyCode=tempJourneyCode;
                   if(Successor(x)->right==nullptr) {
                     tempnode=Successor(x);
                     tempnode=nullptr;
                     return true;
                     }
                   else {
                       Successor(x)->parent->left=Successor(x)->right;
                       Successor(x)->right->parent=Successor(x)->parent;
                       tempnode=Successor(x);
                       tempnode=nullptr;
                       return true;
                   }

               }
               
             
        }
        else{
            BST rightTree;
            rightTree.root=x->right;
            return rightTree.Remove(JourneyCode,price,x->right);
        }
    }
    else if(x->price>price) {
        BST leftTree;
        leftTree.root=x->left;
        return leftTree.Remove(JourneyCode,price,x->left);
    }
    else {
        BST rightTree;
        rightTree.root=x->right;
        return rightTree.Remove(JourneyCode,price,x->right);
    }
    }
}
bool BST::remove(int JourneyCode, int price)
{return Remove(JourneyCode,price,root);
}
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

