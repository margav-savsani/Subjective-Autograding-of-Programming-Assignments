// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <iostream>
#include <vector>
#include <string>

using namespace std;
#include "journey.h"
#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  // cout << "Hello" << endl; 
        
        TreeNode *present = root;
        

        TreeNode *newNode = new TreeNode(JourneyCode, price);
        if(present == nullptr){
            // Tree was empty earlier, just insert it at root
            root = newNode;
            newNode = root;
            root->longestPathLength = root->shortestPathLength = 0;
            return true;
        }
        while(true){
            /* cout << "Inserting"  << endl; */
            if(present->JourneyCode == JourneyCode){
                return false;
            }
            if (Journey(newNode->JourneyCode, newNode->price) < Journey(present->JourneyCode, present->price)){
                if (present->left == nullptr){
                    // Found a place to insert, present->left
                    present->left = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->left;
                    newNode->parent = present;
                    break;
                    // return true;
                }
                else{
                    // Keep traversing
                    present = present->left;
                    
                }
            }
            else{
                if (present->right == nullptr){
                    // Insert at present->right 
                    /* cout << "Inserting to the right"  << endl; */
                    present->right = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->right;
                    newNode->parent = present;

                    break;
                    // return true;
                }
                else{
                    present = present->right ;
                    
                }
            }
        }
    
    int height = -1;
    while(present != nullptr){
      height += 1;
      if(present->left == nullptr && present->right == nullptr){
        present->longestPathLength = 0;
        present->shortestPathLength = 0;
      }
      else if(present->left == nullptr){
        present->longestPathLength = present->right->longestPathLength + 1;
        // present->shortestPathLength = present->right->shortestPathLength + 1;
        present->shortestPathLength = 0;
      }
      else if(present->right == nullptr){
        present->longestPathLength = present->left->longestPathLength + 1;
        present->shortestPathLength = 0;
      }
      else{
       present->longestPathLength = std::max(present->left->longestPathLength + 1,present->right->longestPathLength + 1) ;
        present->shortestPathLength = std::min(present->left->shortestPathLength + 1, present->right->shortestPathLength + 1); 
      }
      // cout << "Longest path of present " << present->longestPathLength << endl;
      present = present->parent;

      // cout << present << endl;
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
          TreeNode *present = root;
        // From the root, keep iterating according to the binary tree specification: if the price is <= price of present go in the left subtree else right
        // Equal value prices are sent in the left subtree
        while(present != nullptr){
            if(present->JourneyCode == JourneyCode && present->price == price){
                    return true;
                    // Entry found
            }
            if(price <= present->price){
                present = present->left;
            }
            else {
                present = present->right;
            }
        }
        return false; 

  return false;
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
    
            TreeNode *present = root;
        while(present != nullptr){
            if(present->JourneyCode == JourneyCode && present->price == price){
                break;
            }
            if(price <= present->price){
                present = present->left;
            }
            else {
                present = present->right;
            }
        }
        if(present == nullptr) return false;
        if(present->parent == nullptr){
            // We are deleting the root node
            TreeNode *temp = root;
            if(root == nullptr){
                // Should never happen
                return false;
            }
            if(root->right == nullptr && root->left == nullptr){
                root = nullptr;
            }
            else if (root->right == nullptr){
                root = root->left;
                root->parent = nullptr;
            }
            else if (root->left== nullptr){
                root = root->right;
                root->parent = nullptr;
            }
            else{
                
                    TreeNode *succ = root->right;
                    while(succ->left != nullptr){
                        succ = succ->left;
                    }
                    // Remove succ from its present position, it can have no children, or atmost a right subtree
                    int newprice = succ->price;
                    int newJC = succ->JourneyCode;
                    remove(newJC, newprice);
                    root->JourneyCode = newJC;
                    root->price = newprice;
                    return true;
            }
            delete temp;
            return true;
        }

        //Handle the general case when node is not the root node
        if (present->right == nullptr && present->left == nullptr){
            // Leaf node
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = nullptr;
            }
            else{
                present->parent->left = nullptr;
            }
            delete present;
            return true;
        }
        else if(present->right == nullptr){
            //Only the left child is present
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = present->left;
            }
            else{
                present->parent->left = present->left;
            }
            present->left->parent = present->parent;
            /* // delete present; */
            return true;
        }
        else if(present->left== nullptr){
            //Only the right child is present
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = present->right;
            }
            else{
                present->parent->left = present->right;
            }
            present->right->parent = present->parent;
            delete present;
            return true;
        }
        else{
            // Both children are present
            // Find the successor
            TreeNode *succ = present->right;
            while(succ->left != nullptr){
                succ = succ->left;
            }
            /* cout << succ->JourneyCode  << endl; */
            // Remove succ from its present position, it can have no children, or atmost a right subtree
            int jcode = succ->JourneyCode;
            int newprice = succ->price;
            remove(jcode, newprice);
            present->JourneyCode = jcode;
            present->price = newprice;
            return true;


        }


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

