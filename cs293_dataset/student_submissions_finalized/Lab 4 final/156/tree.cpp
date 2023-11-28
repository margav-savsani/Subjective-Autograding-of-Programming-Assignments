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

BST::BST(){
    root = nullptr;
    N=0;
}
BST::BST(TreeNode *root){
    this->root=root;
    N=1;
}

int BST::getImbalance()
{
  if (root == nullptr)
    return 0;
  else
    return root->getImbalance();
}

void TreeNode::updatepathlengths(){

    //if a node has both left and right as nullptr both shortest and longest length would be 1
    if(left==nullptr && right==nullptr){
        shortestPathLength=1;
        longestPathLength=1;
    }

    //if right is not nullptr then longest would be 1 + longest of the right child
    else if(left==nullptr){
        shortestPathLength=1;
        longestPathLength=1 + (right->longestPathLength);
    }

    //if right is not nullptr then longest would be 1 + longest of the right child
    else if(right==nullptr){
        shortestPathLength=1;
        longestPathLength=1 + (left->longestPathLength);
    }

    //if both child are not nullptr then shortest = 1+min(left->shortest,right->shortest)
    //if both child are not nullptr then longest = 1+max(left->longest,right->longest)
    else{
        shortestPathLength = 1 + min(left->shortestPathLength,right->shortestPathLength);
        longestPathLength = 1 + max(left->longestPathLength,right->longestPathLength);
    }

    if(parent!=nullptr){
        parent->updatepathlengths();
    }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

  if(N==0){
        root = new TreeNode(JourneyCode,price);
        N++;
        root->shortestPathLength=1;
        root->longestPathLength=1;
        root->parent = nullptr;
    }
    else{
        TreeNode *x;
        TreeNode *y;
        x = root;
        y = nullptr;
        while(x!=nullptr){
            y = x;
            //y is needed as when x becomes null we need to know what was the last element that would be the parent
            if(JourneyCode==y->JourneyCode){
                return false;
            }
            //could do either left or right in case of equality but I chose left
            else if(JourneyCode<(y->JourneyCode)){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        if(JourneyCode > (y->JourneyCode)){
            //need to pass y as well else how would you access parent of a child in remove function!!!
            //not setting parent here was giving segfault while running delete function 
            y->right = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
            //traverse from new leaf to the root i.e starting from newly inserted node go up (node->parent)
            //as only for the nodes that lie in path , there is a possibility of their shortest and longest path 
            //length changing
            (y->right)->updatepathlengths();
        }
        else{
            y->left = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
            (y->left)->updatepathlengths();
        }
    }
    //update path lengths by traversing the tree
    
    return true;

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

  TreeNode *x = root;

    while(x!=nullptr){
        if((x->price==price) && (x->JourneyCode==JourneyCode)){
            return true;
        }
        else if(price <= (x->price)){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    
  return false;
}

TreeNode* BST::successor(TreeNode *x){
    //made this function only for use in the remove function hence did not consider the case of
    //x->right being null as this function is being called only when node has two children
    return min(x->right);
}
	
TreeNode* BST::min(TreeNode *x){
    TreeNode *k = x;
    while(k->left!=nullptr){
        k = k->left;
    }
    return k;
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

  bool fnd = find(JourneyCode,price);
    if(fnd==false) {return false;}
    else{
        TreeNode *x = root;
        long long int n=0;
        while(x!=nullptr){
            if((x->price==price) && (x->JourneyCode==JourneyCode)){
                //when the node to be removed is a leaf
                if((x->left==nullptr) && (x->right==nullptr)){
                    if(n==0){
                        root = nullptr;
                        N=0;
                    }
                    else{
                        if((x->parent)->price >= price){
                            (x->parent)->left = nullptr;
                            x->parent = nullptr;
                        }
                        else{
                            (x->parent)->right = nullptr;
                            x->parent = nullptr;
                        }
                    }
                }

                //the node to be deleted has only one child
                else if((x->left==nullptr) || (x->right==nullptr)){
                    if(n==0){
                        if(x->left==nullptr){
                            root = (x->right);
                            (x->right)->parent = nullptr;
                            x->right = nullptr;
                        }
                        else{
                            root = x->left;
                            (x->left)->parent = nullptr;
                            x->left = nullptr;
                        }
                    }
                    else{
                        if(x->left==nullptr){
                            if((x->parent)->price >= x->price){
                                (x->parent)->left = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                (x->parent)->right = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                        else{
                            if((x->parent)->price >= x->price){
                                (x->parent)->left = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                (x->parent)->right = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                    }
                }

                //The case where the node to be deleted has two children
                else{
                        //use recursion you would not need to take care of cases as in the prev code
                        TreeNode* z=successor(x);
                        if(x->parent == nullptr){
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            root->JourneyCode = temp->JourneyCode;
                            root->price = temp->price;
                            return true;
                        }
                        else{
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            x->JourneyCode = temp->JourneyCode;
                            x->price = temp->price;
                            return true;
                        }
                }
                return true;
            }
            else if(price <= (x->price)){
                n++;
                x = x->left;
            }
            else{
                n++;
                x = x->right;
            }
        }
    }
    return false;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->JourneyCode << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    result.push_back(prefix);

    result.push_back(isLeft ? "|--" : "|__");

    // print the value of the node
    result.push_back(to_string(root->JourneyCode) + "\n");
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    getBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    getBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST::clearResult()
{
  result.clear();
}

vector<string> BST::getResult()
{
  return result;
}
