#ifndef TREE_CPP
#define TREE_CPP
// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"
#include "journey.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;

  else{ 

    return root->getImbalance();
  }
}

bool BST::insert(int JourneyCode, int price)
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

    if (root == NULL){
        root = new TreeNode;
        root->JourneyCode = JourneyCode;
        root->price = price;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->shortestPathLength = 1;
        root->longestPathLength = 1;
        return true;
    }

    // if(root->JourneyCode == JourneyCode){
    //     return false;
    // }
    
    if (root->JourneyCode > JourneyCode){

        if(root->left == NULL){
            root->left = new TreeNode;
            root->left->JourneyCode = JourneyCode;
            root->left->price = price;
            root->left->left = NULL;
            root->left->right = NULL;
            root->left->parent = root;
            root->left->shortestPathLength = 1;
            root->left->longestPathLength = 1;
            
            if(root->right == NULL){
                root->shortestPathLength = 1;
                root->longestPathLength = 1+root->left->longestPathLength;
            }
            else{
                root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }
            return true;
        }

        else {
            BST left_child(root->left);
            bool inserted = left_child.insert(JourneyCode, price);
            if(inserted){
                if(root->right == NULL){
                    root->shortestPathLength = 1;
                    root->longestPathLength = 1+root->left->longestPathLength;
                }
                else{
                    root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                    root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
                }
            }
            return inserted;
        }


    }

    else if (root->JourneyCode <= JourneyCode){

        if(root->right == NULL){
            root->right = new TreeNode;
            root->right->JourneyCode = JourneyCode;
            root->right->price = price;
            root->right->left = NULL;
            root->right->right = NULL;
            root->right->parent = root;
            root->right->shortestPathLength = 1;
            root->right->longestPathLength = 1;
            
            if(root->left == NULL){
                root->shortestPathLength = 1;
                root->longestPathLength = 1+root->right->longestPathLength;
            }
            else{
                root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }

            return true;
        }

        else {
            BST right(root->right);
            bool inserted = right.insert(JourneyCode, price);         
            if(inserted){
                if(root->left == NULL){
                    root->shortestPathLength = 1;
                    root->longestPathLength = 1+root->right->longestPathLength;

                }

                else{
                    root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                    root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
                }
            }
            return inserted;
        }
    }
    return false;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
    if (root == NULL){
        return false;
    }    

    if(root->JourneyCode == JourneyCode){
        if(root->price == price){
            return true;
        }

        else {
            BST right(root->right);
            return right.find(JourneyCode, price);
        }
    }

    else if (root->JourneyCode < JourneyCode){
        BST right(root->right);
        return right.find(JourneyCode, price);
    }

    else{
        BST left(root->left);
        return left.find(JourneyCode, price);
    }
    

    return false;


}


void BST::assign_path_lengths(){
    if(root == NULL){
        return;
    }

    else if(root->right == NULL){
        if(root->left == NULL){
            root->shortestPathLength = 1;
            root->longestPathLength = 1;
        }
        else{
            BST left_child(root->left);
            left_child.assign_path_lengths();
            root->shortestPathLength = 1;
            root->longestPathLength = 1+root->left->longestPathLength;
        }
    }

    else if(root->left == NULL){
        BST right_child(root->right);
        right_child.assign_path_lengths();
        root->shortestPathLength = 1;
        root->longestPathLength = 1+root->right->longestPathLength;
    }

    else{
        BST left_child(root->left);
        BST right_child(root->right);
        left_child.assign_path_lengths();
        right_child.assign_path_lengths();
        root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
        root->longestPathLength = 1+max(root->right->longestPathLength, root->left->longestPathLength);
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

    if( root == NULL ){
        return false;
    }

    if(root->JourneyCode == JourneyCode){
        if(root->price == price){
            //std::cout<<"found node"<<endl;
            if(root->left == NULL){
                if(root->parent == NULL){
                    TreeNode* newroot = root->right;
                    delete root;
                    root = newroot;
                }
                else if(root->parent->left == root){
                    root->parent->left = root->right;
                    if(root->right != NULL){
                        root->right->parent = root->parent;
                    }
                   
                }
                else if(root->parent->right == root){
                    //std::cout << "deleting"<<endl;
                    root->parent->right = root->right;

                    if(root->right != NULL){
                        root->right->parent = root->parent;
                    }
                    
                }
                delete root;
            }

            else if(root->right == NULL){
                if(root->parent == NULL){
                    TreeNode* newroot = root->left;
                    delete root;
                    root = newroot;
                }

                else if(root->parent->left == root){
                    root->parent->left = root->left;
                    if(root->left != NULL){
                        root->left->parent = root->parent;
                    }                    
                    
                }
                else if(root->parent->right == root){
                    //std::cout<<"bruh"<<endl;
                    root->parent->right = root->left;
                    if(root->left != NULL){
                        root->left->parent = root->parent;
                    }
                    
                }

                delete root;
            }

            //find predecessor and replace
            else{
                BST left(root->left);
                TreeNode* predecessor = left.getMaximum();
                int newjourneycode = predecessor->JourneyCode;
                int newprice = predecessor->price;
                remove(newjourneycode, newprice);
                root->JourneyCode = newjourneycode;
                root->price = newprice;
            }

            assign_path_lengths();
            return true;
        }
            
        

        else {
            BST right(root->right);
            bool removed = right.remove(JourneyCode, price);
            if(removed){
                if(root->left == NULL){
                    root->shortestPathLength = 0;
                    root->longestPathLength = 1+root->right->longestPathLength;
                }
                else{
                    root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                    root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
                }
            }
            return removed;
        }
    }

    else if (root->JourneyCode < JourneyCode){
        //std::cout<< "hi right"<<endl;
        BST right(root->right);
        bool removed = right.remove(JourneyCode, price);
        if(removed){
            if(root->left == NULL){
                root->shortestPathLength = 0;
                root->longestPathLength = 1+root->right->longestPathLength;
            }
            else{
                root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }
        }
        return removed;
    }

    else{
        BST left(root->left);
        bool removed = left.remove(JourneyCode, price);
        if(removed){
            if(root->right == NULL){
                root->shortestPathLength = 0;
                root->longestPathLength =  1+ root->left->longestPathLength;
            }
            else{
                root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }
        }
        return removed;
    }

    return false;
    

}

TreeNode* BST::getMaximum(){
    if(root == NULL){return NULL;}
    else if (root -> right == NULL){return root;}
    BST right_child(root->right);

    while((right_child.root)->right != NULL){
        right_child = BST((right_child.root)->right);
    }

    return right_child.root;
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

#endif