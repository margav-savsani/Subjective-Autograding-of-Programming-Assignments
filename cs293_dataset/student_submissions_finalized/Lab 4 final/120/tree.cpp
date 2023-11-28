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

bool BST::insert(int JourneyCode,int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    TreeNode* x=new TreeNode(JourneyCode,price);
    //cout<<root->price<<endl;
    if(root==nullptr){
        root=x;
        return true;
    }
    else if(find(JourneyCode,price)==true){
        return false;
    }
    else{
        TreeNode* currNode=root;
        while(currNode->left!=nullptr || currNode->right!=nullptr){
            if(currNode->price>price){
                if(currNode->left==nullptr){
                    currNode->left=x;
                    x->parent=currNode;
                    return true;
                }
                currNode=currNode->left;
            }
            else{
                if(currNode->right==nullptr){
                    currNode->right=x;
                    x->parent=currNode;
                    return true;
                }
                currNode=currNode->right;
            }
        }
        if(currNode->price>price){
            currNode->left=x;
            x->parent=currNode;
            return true;
        }
        else{
            currNode->right=x;
            x->parent=currNode;
            return true;
        }
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
  if(root==nullptr){
        return false;
    }
    else{
        TreeNode *currNode=root;
        while(currNode!=nullptr){
            if(currNode->price==price && currNode->JourneyCode==JourneyCode){
                return true;
            }
            else if(currNode->price>price){
                currNode=currNode->left;
            }
            else{
                currNode=currNode->right;
            }
        }
        return false;
    }
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
    
  if(find(JourneyCode,price)==false){
        return false;
    }
    TreeNode *currNode=root;
    TreeNode *p;
        while(currNode!=nullptr){
            if(currNode->price==price && currNode->JourneyCode==JourneyCode){
                break;
            }
            else if(currNode->price>price){
                currNode=currNode->left;
            }
            else{
                currNode=currNode->right;
            }
        }
    if(currNode->left==nullptr && currNode->right==nullptr){
        if(currNode==root){
            root=nullptr;
            return true;
        }
        if(currNode->parent->left==currNode){
            currNode->parent->left=nullptr;
            currNode=nullptr;
            return true;
        }
        else{
            currNode->parent->right=nullptr;
            currNode=nullptr;
            return true;
        }
    }
    else if(currNode->left==nullptr || currNode->right==nullptr){
        if(currNode->left==nullptr){
            if(currNode==root){
                root->right->parent=nullptr;
                root=root->right;
                return true;
            }
            else{
                currNode->right->parent=currNode->parent;
                if(currNode->parent->right==currNode){
                    currNode->parent->right=currNode->right;
                }
                else{
                    currNode->parent->left=currNode->right;
                }
                return true;
            }
        }
        else{
            if(currNode==root){
                root->left->parent=nullptr;
                root=root->left;
                return true;
            }
            else{
                currNode->left->parent=currNode->parent;
                if(currNode->parent->left==currNode){
                currNode->parent->left=currNode->left;}
                else{
                    currNode->parent->right=currNode->left;
                }
                return true;
            }
        }
    }
    else {
        if(currNode==root){
            if(currNode->left->right==nullptr){
                p=currNode->left;
                if(p->left==nullptr){
                    p->right=root->right;
                    root->right->parent=p;
                    root=p;
                    return true;
                }
                else{
                    p->right=root->right;
                    root->right->parent=p;
                    root=p;
                    p->left->parent=p->parent;
                    return true;
                }
            }
            else{
            p=currNode->left;
            while(p->right!=nullptr){
                p=p->right;
            }
            root->price=p->price;
            root->JourneyCode=p->JourneyCode;
            p->parent->right=p->left;
            if(p->left==nullptr){
                return true;
            }
            else{
                p->left->parent=p->parent;
                return true;
            }
        }
        }
        else{
            p=currNode->left;
            if(p->right==nullptr){
                currNode->price=p->price;
                currNode->JourneyCode=p->JourneyCode;
                p->parent->left=p->left;
                if(p->left==nullptr){
                    return true;
                }
                else{
                    p->left->parent=p->parent;
                    return true;
                }
            }
            else{
                while(p->right!=nullptr){
                 p=p->right;
                }
                currNode->price=p->price;
                currNode->JourneyCode=p->JourneyCode;
                p->parent->right=p->left;
                if(p->left==nullptr){
                    return true;
                }
                else{
                    p->left->parent=p->parent;
                    return true;
                }
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
