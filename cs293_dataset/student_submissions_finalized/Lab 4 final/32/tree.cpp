// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible


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
  if (root == nullptr) 
  return 0;
  
  else 
  return root->getImbalance();
}

// inserts new node and also returns the height of the newly
// inserted branch from the 
int BST::insert(int JourneyCode, int price, TreeNode* node, TreeNode* parent_node) 
{
  if (node == nullptr) 
  {   
    node = new struct TreeNode;
    node->price = price;
    node->JourneyCode = JourneyCode;
    node->parent = parent_node;
    
    if(root != nullptr)
    {
    	if((node->JourneyCode) > (parent_node->JourneyCode)) 
    	(parent_node->right) = node;
    	
    	else 
    	(parent_node->left) = node;
    }
    
    else 
    root = node;
    
    return 0;
  }
  
  else
  {
    int level = 1;
    
    if(JourneyCode > (node->JourneyCode))   
    level += insert(JourneyCode, price, node->right,node);
    
    else if (JourneyCode < (node->JourneyCode))
    level += insert(JourneyCode, price, node->left, node);
        
    if((node->shortestPathLength) > level) 
    (node->shortestPathLength) = level;
    
    else if((node->longestPathLength) < level) 
    (node->longestPathLength) = level;
        
    return level;
  } 
 return 0; 
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

