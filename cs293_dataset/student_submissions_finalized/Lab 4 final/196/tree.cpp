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
//Updates the shortest and longestPathLength of the argument treenode
void updatelen(TreeNode *r){
    if (r->left==nullptr && r->right==nullptr){
      r->shortestPathLength=0;
      r->longestPathLength=0;
    }
    else if (r->left==nullptr){
      r->shortestPathLength=0;
      r->longestPathLength=r->right->longestPathLength+1;
    }
    else if (right==nullptr){
      r->shortestPathLength=0;
      r->longestPathLength=r->left->longestPathLength+1;
    }
    else{
      r->shortestPathLength=min(r->left->shortestPathLength+1,r->right->shortestPathLength+1);
      r->longestPathLength=max(r->left->longestPathLength+1,r->right->longestPathLength+1);
    }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  // similar to what you had done in lab assignment 3.
  
      TreeNode *y=new TreeNode();
      TreeNode *x=new TreeNode();
      y=nullptr;
      x = root;
      TreeNode *z=new TreeNode(JourneyCode,price);
      while (x!=nullptr){
        y=x;
        
        if (JourneyCode<x->JourneyCode){
         x=x->left;
        }
        else{
          x=x->right;
        }
      }
      z->parent=y;
      if (y==nullptr){
        root=z;
        z->longestPathLength=1;
        z->shortestPathLength=1;
        return true;
      }
      else if (z->JourneyCode<y->JourneyCode){
        y->left=z;
        while(y!=nullptr){
            updatelen(y);
            y=y->parent;
        } 
        return true;
      }
      else{
        y->right=z;
        while(y!=nullptr){
            updatelen(y);
            y=y->parent;
        }
        return true;
      }
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
  TreeNode *x= new TreeNode();
    x=root;
    while(x!=nullptr && x->JourneyCode!=JourneyCode){
        if (JourneyCode<x->JourneyCode){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    return true;
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
  TreeNode *x=new TreeNode();
    x=root;
    while(x!=nullptr && x->JourneyCode!=JourneyCode){
        if (JourneyCode<x->JourneyCode){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    else{
        if(x->right==nullptr && x->left==nullptr){
            if (x->parent==nullptr){
                x=nullptr;
                return true;
            }
            else if(x->JourneyCode<x->parent->JourneyCode){
                x->parent->left=nullptr;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
            else{
                x->parent->right=nullptr;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
        }
        else if(x->right==nullptr){
            if (x->parent==nullptr){
                x=x->left;
                if (x->left==nullptr && x->right==nullptr){
                    x->shortestPathLength=1;
                    x->longestPathLength=1;
                }
                else{
                    updatelen(x);
                }
                return true;
            }
            else if(x->JourneyCode<x->parent->JourneyCode){
                x->parent->left=x->left;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
            else{
                x->parent->right=x->left;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
        }
        else if(x->left==nullptr){
            if (x->parent==nullptr){
                x=x->right;
                if (x->left==nullptr && x->right==nullptr){
                    x->shortestPathLength=1;
                    x->longestPathLength=1;
                }
                else{
                    updatelen(x);
                }
                return true;
            }
            else if(x->JourneyCode<x->parent->JourneyCode){
                x->parent->left=x->right;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
            else{
                x->parent->right=x->right;
                while(x->parent!=nullptr){
                    updatelen(x->parent);
                    x=x->parent;
                }
                return true;
            }
        }
        else{
            TreeNode *y=new TreeNode();
            y=x->left;
            while (y->right!=nullptr){
                y=y->right;
            }
            if (y==x->left){
                x->left=y->left;
                x->JourneyCode=y->JourneyCode;
                x->price=y->price;
                while(x!=nullptr){
                    updatelen(x);
                    x=x->parent;
                }
                return true;
            }
            if (y->left==nullptr){
                y->parent->right=nullptr;
                x->JourneyCode=y->JourneyCode;
                x->price=y->price;
                while(y->parent!=nullptr){
                    updatelen(y->parent);
                    y=y->parent;
                }
                return true;
            }
            else{
                y->parent->right=y->left;
                x->JourneyCode=y->JourneyCode;
                x->price=y->price;
                while(y->parent!=nullptr){
                    updatelen(y->parent);
                    y=y->parent;
                }
                return true;
            }
            
        }
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

