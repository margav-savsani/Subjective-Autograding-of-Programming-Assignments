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

bool recursive_insert(int JourneyCode, int price, TreeNode* root, int& shortestPathLength, int& longestPathLength){

    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    bool left = false;
    bool right = false;

    while (currNode != nullptr) {


        if (currNode->JourneyCode < JourneyCode) {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
            right = true;
            left = false;
        }
        else if (currNode->JourneyCode > JourneyCode) {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
            left = true;
            right = false;
        }
        else { 
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
        
        currNode = new TreeNode(JourneyCode, price, parentOfCurrNode);

        currNode->shortestPathLength = 1;
        currNode->longestPathLength = 1;

    if (left){

        parentOfCurrNode->left = currNode;

    } else if (right){

        parentOfCurrNode->right = currNode;

    }

    while (parentOfCurrNode != nullptr){

        if (parentOfCurrNode->left == nullptr){
            parentOfCurrNode->shortestPathLength = 1;
            parentOfCurrNode->longestPathLength = 1 + parentOfCurrNode->right->longestPathLength;
        } else if (parentOfCurrNode->right == nullptr){
            parentOfCurrNode->shortestPathLength = 1;
            parentOfCurrNode->longestPathLength = 1 + parentOfCurrNode->left->longestPathLength;
        } else {
            parentOfCurrNode->longestPathLength = max(parentOfCurrNode->left->longestPathLength, parentOfCurrNode->right->longestPathLength) + 1;
            parentOfCurrNode->shortestPathLength = min(parentOfCurrNode->left->shortestPathLength, parentOfCurrNode->right->shortestPathLength) + 1;
        }

        parentOfCurrNode = parentOfCurrNode->parent;
    }

        return true; 
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  

  if (root == nullptr){
  
    root = new TreeNode(JourneyCode, price);
    root->shortestPathLength =  1 ; 
    root->longestPathLength = 1 ; 
  
  } else {
        // JourneyCode is not present in the BST.  We must now
        // insert an appropriate child of parentOfCurrNode.
        // Please implement this part yourself.
        //
        // Do not forget to update shortestPathLength and
        // longestPathLength of (possibly all) BST nodes in the
        // path from the root to the new node you are inserting
    

    recursive_insert(JourneyCode, price, root, shortestPathLength, longestPathLength);

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
  
  TreeNode *temp = root;

  while(temp != NULL){
    if(temp->JourneyCode == JourneyCode){
      return true;
    }
    else if(temp->JourneyCode > JourneyCode){
      temp = temp->left;
    }
    else{
      temp = temp->right;
    }
  } 

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

  TreeNode *temp = root;
    while(temp != NULL){

        if(temp->JourneyCode == JourneyCode){

            if (temp == root){
                if (temp->left == NULL && temp->right == NULL){
                    delete temp;
                    root = NULL;
                    return true;

                } else {

                    if (temp->left == NULL){
                        root = temp->right;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else if (temp->right == NULL){
                        root = temp->left;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else {
                        if (temp->right->left != NULL){

                            TreeNode *temp2 = temp->right->left;

                            while(temp2->left != NULL){
                                temp2 = temp2->left;
                            }

                            // temp2->right = root->right;
                            // temp2->left = root->left;

                            root->JourneyCode = temp2->JourneyCode;
                            root->price = temp2->price;

                            if(temp2->right != NULL){
                                temp2->parent->left = temp2->right;
                                temp2->right->parent = temp2->parent;
                            } else {
                                temp2->parent->left = NULL;
                            }

                            // temp2->parent->left = NULL;
                            // root = temp2;
                            // root->parent = NULL;

                            // temp2->right->parent = temp2;
                            // temp2->left->parent = temp2;

                            // delete temp;
                            delete temp2;
                            return true;

                        } else {

                            temp->right->left = root->left;
                            temp->right->left->parent = temp->right;
                            root = temp->right;
                            root->parent = NULL;

                            delete temp;
                            return true;
                        }
                    }

                }

            } else if(temp->left == NULL && temp->right == NULL){

                // cout << "!" << endl;

                if(temp->parent->left == temp){
                    temp->parent->left = NULL;
                }
                else{
                    temp->parent->right = NULL;
                }

                delete temp;
                return true;
            } else if(temp->left == NULL){
                // cout << "!!" << endl;

                // cout << temp->parent->JourneyCode << endl;
                // cout << temp->JourneyCode << endl;
                // cout << temp->parent->left->JourneyCode << endl;

                if(temp->parent->left == temp){

                    // cout << "ohmg" << endl;
                    temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;
                }
                else{


                    temp->parent->right = temp->right;

                    temp->right->parent = temp->parent;




                }
                    delete temp;
                    return true;


            } else if(temp->right == NULL){
                // cout << "!!!" << endl;

                if(temp->parent->left == temp){
                    temp->parent->left = temp->left;
                    // temp->left->parent = temp->parent;
                }
                else{
                    temp->parent->right = temp->left;
                    // temp->left->parent = temp->parent;
                }

                temp->left->parent = temp->parent;
                
                delete temp;
                return true;
            } else {

                // cout << "ohh" << endl;

                TreeNode *temp2 = temp->right;

                while(temp2->left != NULL){
                    temp2 = temp2->left;
                }

                temp->JourneyCode = temp2->JourneyCode;
                temp->price = temp2->price;

                if (temp2->parent == temp){
                    if (temp2->right != NULL){
                        temp2->parent->right = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->right = NULL;
                    }

                } else {

                    if (temp2->right != NULL){
                        // cout << "hm" << endl;
                        temp2->parent->left = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->left = NULL;
                    }

                }


                delete temp2;
                return true;
            }

        } else if(temp->price > price){
            // cout << price << " " << temp->JourneyCode << " " << temp->price << endl;
            temp = temp->left;
        } else {
            // cout << price << " " << temp->JourneyCode << " " << temp->price << endl;
            temp = temp->right;

        }

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
        // cout << root->JourneyCode << " " << root->shortestPathLength << " " << root->longestPathLength << " " << root->getImbalance() << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr;
        root = root->right;
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
        root = curr;
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

