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


// calculate shortest path to leaf from the node specified
int TreeNode::shortest(TreeNode *rt)
{
    if(rt->left==nullptr && rt->right==nullptr){
        return 1;
    }
    else if(rt->left==nullptr){
        return 1+shortest(rt->right);
    }
    else if(rt->right==nullptr){
        return 1+shortest(rt->left);
    }
    else{
        return 1+min(shortest(rt->left), shortest(rt->right));
    }
}

// calculate longest path to leaf from the node specified
int TreeNode::longest(TreeNode *rt){
  if(rt == nullptr){
    return 0;
  }
  else{
    return 1+max(longest(rt->left), longest(rt->right));
  }
}

int BST::getImbalance()
{
  return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  if(root == nullptr){
        root = new TreeNode(JourneyCode, price);
        return true;
    }

    TreeNode *ptr = root;

    // search for required node
    while(true){

        // return false if already present
        if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            return false;
        }

        // go left if required key is less than or equal
        if(ptr->JourneyCode >= JourneyCode && ptr->left != nullptr){
            ptr = ptr->left;
        }
        // go right if required key is strictly more
        else if(ptr->JourneyCode < JourneyCode && ptr->right != nullptr){
            ptr = ptr->right;
        }
        // insert to left 
        else if(ptr->JourneyCode >= JourneyCode && ptr->left == nullptr){
            ptr->left = new TreeNode(JourneyCode, price);
            ptr->left->parent = ptr;
            return true;
        }
        // insert to right
        else if(ptr->JourneyCode < JourneyCode && ptr->right == nullptr){
            ptr->right = new TreeNode(JourneyCode, price);
            ptr->right->parent = ptr;
            return true;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *ptr = root;

    // same code as in insert
    while(true){
        if(ptr == nullptr){
            return false;
        }
        else if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            return true;
        }
        else if(ptr->JourneyCode >= JourneyCode){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  TreeNode *ptr = root;

    // get the pointer to node that we have to delete
    while(true){
        if(ptr == nullptr){
            return false;
        }
        else if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            break;
        }
        else if(ptr->JourneyCode >= JourneyCode){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }

    // if the node we want to delete is root node
    if(ptr == root){

        // if root node is a leaf
        if(ptr->left == nullptr && ptr->right == nullptr){
            delete root;
            root = nullptr;
            return true;
        }

        // if left child of root node is empty
        else if(ptr->left == nullptr && ptr->right != nullptr){
            TreeNode *p = ptr->right;
            delete root;
            root = p;
            root->parent = nullptr;
            return true;
        }

        // if right child of root node is empty
        else if(ptr->left != nullptr && ptr->right == nullptr){
            TreeNode *p = ptr->left;
            delete root;
            root = p;
            root->parent == nullptr;
            return true;
        }

        // if root node has both children
        else{
            TreeNode *xd = ptr->left;

            while(true){
                if(xd->right == nullptr){
                    break;
                }
                else{
                    xd = xd->right;
                }
            }

            int reqJourneyCode = xd->JourneyCode;
            int reqPrice = xd->price;

            remove(reqJourneyCode, reqPrice);

            ptr->JourneyCode = reqJourneyCode;
            ptr->price = reqPrice;

            return true;
        }
    }


    // for nodes which are not root nodes

    TreeNode *prnt = ptr->parent;
    TreeNode **prntToChild;


    if(prnt->left != nullptr){
        if(prnt->left->JourneyCode == ptr->JourneyCode && prnt->left->price == ptr->price){
            prntToChild = &(prnt->left);
        }
    }

    if(prnt->right != nullptr){
        if(prnt->right->JourneyCode == ptr->JourneyCode && prnt->right->price == ptr->price){
            prntToChild = &(prnt->right);
        }
    }

    // if node is a leaf
    if(ptr->left== nullptr && ptr->right == nullptr){
        delete *prntToChild;
        *prntToChild = nullptr;
        return true;
    }

    // only left child empty
    else if(ptr->left == nullptr){
        TreeNode *temp = ptr->right;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        return true;
    }

    // only right child empty
    else if(ptr->right == nullptr){
        TreeNode *temp = ptr->left;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        return true;
    }

    // node has both children
    else{
        TreeNode *xd = ptr->left;

        while(true){
            if(xd->right == nullptr){
                break;
            }
            else{
                xd = xd->right;
            }
        }

        int reqJourneyCode = xd->JourneyCode;
        int reqPrice = xd->price;

        remove(reqJourneyCode, reqPrice);

        ptr->JourneyCode = reqJourneyCode;
        ptr->price = reqPrice;

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

