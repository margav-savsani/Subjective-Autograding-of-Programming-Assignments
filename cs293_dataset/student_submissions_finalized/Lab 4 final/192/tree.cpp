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

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  TreeNode *node = new TreeNode(JourneyCode, price);
  node->shortestPathLength = 0;
  node->longestPathLength = 0;
  TreeNode *currNode = this->root;
  if(root == nullptr){
    
    this->root = node;
    return true;
  } else {
    
    
    while (currNode != nullptr){
      //if node to be inserted is less than the current node
      if (currNode->JourneyCode > node->JourneyCode){
        //if left node empty then insert
        if(currNode->left != nullptr){
         currNode = currNode->left;
         
        } else {
          currNode->left = node;
          node->parent = currNode;
          currNode->shortestPathLength = 1;
          break;
          
        }
      }

      else if (currNode->JourneyCode < node->JourneyCode){
        //if element to be inserted is greater than the current node.
        if(currNode->right != nullptr){
        //if right node empty then insert
         currNode = currNode->right;
          
        } else {
          node->parent = currNode;
          currNode->right = node;
          currNode->shortestPathLength = 1;
          break;
        }
      } else {
        return false;
      }
    }
  }

  //On the unique path from leaf to the root, update the values of longest Path length and shortest path length

  /* EXPLANATION : For those elements that do not lie on the path from root to the leaf, their subtrees
    remain the same. Therefore, their values of the shortestPathLength and LongestPathLength would not change.
    We only look at nodes from the leaf to the node, in that order, and for each node compare the values of the shortest 
    path and the longest path of its children, to determine the height of the current node.
  */
  while(currNode != nullptr){
    if (currNode -> left == nullptr){
      currNode->longestPathLength = currNode->right->longestPathLength+1;
      currNode->shortestPathLength = currNode->right->shortestPathLength+1;

    } else if (currNode -> right == nullptr){
      currNode->longestPathLength = currNode->left->longestPathLength+1;
      currNode->shortestPathLength = currNode->left->shortestPathLength+1;

    } else {
      if (currNode->right->shortestPathLength < currNode->left->shortestPathLength) 
         currNode->shortestPathLength = currNode->right->shortestPathLength+1;
      else
        currNode->shortestPathLength = currNode->left->shortestPathLength+1;


      if (currNode->left->longestPathLength < currNode->right->longestPathLength)
        currNode->longestPathLength = currNode->right->longestPathLength+1;
      else 
        currNode->longestPathLength = currNode->left->longestPathLength+1;
    }

    //if (currNode->parent == nullptr)
    //cout << currNode->shortestPathLength << " " << currNode->longestPathLength << endl; 

    currNode = currNode->parent;
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
  
  
  

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode * currNode = root;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
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
        //cout << "whats wrong?";
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

