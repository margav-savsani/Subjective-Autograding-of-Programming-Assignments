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

bool BST::insert(int JourneyCode, int price, int& comp)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
 
    TreeNode* x = root;
    TreeNode* y = nullptr;

    // when tree is empty, new element added is the root itself
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
        return true;
    }


    // in any other case
    while(true){
        if(x == nullptr){
            x = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
            if(y->JourneyCode < x->JourneyCode) y->right = x;
            else y->left = x;
            comp++;

            TreeNode* p = x;
            while(y != nullptr){
              if(y->left == nullptr || y->right == nullptr){
                y->shortestPathLength = p->shortestPathLength + 1;
                y->longestPathLength = p->longestPathLength + 1;
              }
              else{
                y->shortestPathLength = min(p->shortestPathLength + 1, y->shortestPathLength);
                y->longestPathLength = max(p->longestPathLength + 1, y->longestPathLength);
              }

              p = y;
              y = p->parent;



            }
            return true;
        
        } else if(x->JourneyCode == JourneyCode) {
            return false;   // returns false when same journey code
            comp++;
        } else {
            if(JourneyCode > x->JourneyCode){
                y = x;
                x = x->right;   // moves right, if element has greater price than current node
            } else {
                y = x;
                x = x->left;    // moves left, if element has smaller price than current node
            }
            comp++;
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
TreeNode *x = root;

    while(true){
        if(x == nullptr){
            return false;   // returns false if no element is found
        } else if(x->JourneyCode == JourneyCode){
            return true;    
        } else {
            if(JourneyCode > x->JourneyCode){
                x = x->right;
            } else {
                x = x->left;
            }
        }
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *x = root;
    TreeNode *y;

    // uses the code for 'find' to search element before removing

    while(true){
        if(x == nullptr){  
            return false;   
        } else if(x->JourneyCode == JourneyCode){
            y = x->parent;

            // case when the node has no children

            if(x->right == nullptr && x->left == nullptr){
        
                if(y->right == x){
                    y->right = nullptr;
                    return true;
                } else {
                    y->left = nullptr;
                    return true;
                }
            } 

            // case when the node has only a left child

            else if(x->right == nullptr && x->left != nullptr){
                
                if(y->right == x){
                    y->right = x->left;
                    return true;
                } else {
                    y->left = x->left;
                    return true;
                }

            }

            // case when the node has only a right child

            else if(x->right != nullptr && x->left == nullptr){

                if(y->right == x){
                    y->right = x->right;
                    return true;
                } else {
                    y->left = x->right;
                    return true;
                }

            }

            // case when the node has both left and right children

            else {

                TreeNode* curr = x->left;

                while(curr->right != nullptr)
                    curr = curr->right;

                BST::remove(curr->JourneyCode, curr->price);

                x->JourneyCode = curr->JourneyCode;
                x->price = curr->price;

            }


        } else {
            if(JourneyCode > x->JourneyCode){
                x = x->right;
            } else {
                x = x->left;
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

