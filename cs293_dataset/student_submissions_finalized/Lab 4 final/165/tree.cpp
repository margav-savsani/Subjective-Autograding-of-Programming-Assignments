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

// int minTreeDepth(TreeNode* p)
// {
//     if(p == NULL) 
//       return 0;
//     else
//       min(minTreeDepth(p->left), minTreeDepth(p->right)) + 1;
// }

// int maxTreeDepth(TreeNode* p)
// {
//     if(p == NULL) 
//       return 0;
//     else
//       max(maxTreeDepth(p->left), maxTreeDepth(p->right)) + 1;
// }

// int TreeNode::getImbalance()
// {
//   longestPathLength = maxTreeDepth(TreeNode* );
//   shortestPathLength = minTreeDepth(TreeNode* );
//   return (longestPathLength - shortestPathLength);
// }
void BST::updatePathLength(TreeNode* node){
  if(node == nullptr) return;

  TreeNode* temp = node;
  while(true){
    if(temp->parent == nullptr) return;
    temp = temp->parent;
    if(temp->left == nullptr){
      temp->longestPathLength = temp->right->longestPathLength +1;
      temp->shortestPathLength = temp->right->shortestPathLength +1;
    }
    else if(temp->right == nullptr){
      temp->longestPathLength = temp->left->longestPathLength+1;
      temp->shortestPathLength = temp->left->shortestPathLength+1;
    }
    else{

      temp->longestPathLength = 1+max(temp->right->longestPathLength,temp->left->longestPathLength);
      temp->shortestPathLength = 1+min(temp->right->shortestPathLength,temp->left->shortestPathLength);
    }

  }

}

bool BST::insert(int JourneyCode, int price)
{

   if (find(JourneyCode, price))
    {
        return false;
    }

    TreeNode *nodeToInsert = new TreeNode(JourneyCode, price);//stores the new node to be inserted

    TreeNode *temp = root;//initialize temp as root of the tree

   
    TreeNode *prev = NULL;//stores the prvious temp

    while (temp != NULL)//loop for finding location for insertion
    {
        prev = temp;
        if (JourneyCode < temp->JourneyCode)
            temp = temp->left;
        else
            temp = temp->right;
    }

    // If the root is NULL i.e the tree is empty
    // The new node is the root node
    if (prev == NULL)
    {
        root = nodeToInsert;

        return true;
    }

    // If the new key is less than the leaf node key
    // Assign the new node to be its left child
    else if (JourneyCode < prev->JourneyCode)
    {
        prev->left = nodeToInsert;
        prev->left->parent = prev;
        prev->left->longestPathLength = 1;
        prev->left->shortestPathLength = 1;
        updatePathLength(prev->left);
    }
    // else assign the new node its right child
    else
    {
        prev->right = nodeToInsert;
        prev->right->parent = prev;
        prev->right->longestPathLength = 1;
        prev->right->shortestPathLength = 1;
        updatePathLength(prev->right);

    }

    
    return true;
}

TreeNode *BST::successor(TreeNode *node)
{ // two child case, so successor always in right subtree
    TreeNode *temp = node->right;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp;

  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  
  //return true;
}

//void update(){}




// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.

   TreeNode *temp = root;

    while (temp != nullptr)
    {
        if (temp->JourneyCode == JourneyCode)//temporarily store journeycode 
            return true;

        if (JourneyCode < temp->JourneyCode)
        {
            temp = temp->left;//keep going left
        }
        else
        {
            temp = temp->right;//keep going right
        }
    }

    if (temp == nullptr)//if null
        return false;
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise


void BST::mydelete(TreeNode *node)
{

    // leaf
    if (node->left == nullptr && node->right == nullptr)//leaf
    {
        if (node == root)//separate checking for root
            delete (node);
        else
        {
            if (node == node->parent->left)
            {

                node->parent->left = nullptr;//deletion requires certain relations to be changed
                delete (node);
            }

            else
            {

                node->parent->right = nullptr;//deletion requires certain relations to be changed
                delete (node);
            }
        }
    }
    // one child
    else if (node->left == nullptr || node->right == nullptr)
    {
        if (node == root)//separate checking for root
        {
            if (node->left == nullptr)
            {
                root = root->right;//deletion requires certain relations to be changed
                root->parent = nullptr;
            }
            else
            {
                root = root->left;//deletion requires certain relations to be changed
                root->parent = nullptr;
            }
        }
        else
        {
            if (node == node->parent->left)
            {

                if (node->left == nullptr)
                {
                    node->right->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->left = node->right;//deletion requires certain relations to be changed
                }
                else
                {
                    node->left->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->left = node->left;//deletion requires certain relations to be changed
                }
            }
            else
            {

                if (node->left == nullptr)
                {
                    node->right->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->right = node->right;//deletion requires certain relations to be changed
                }
                else
                {
                    node->left->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->right = node->left;//deletion requires certain relations to be changed
                }
            }
            delete (node);
        }
    }

    else//two children
    {
        TreeNode *succ = successor(node);//min of right node
        int JourneyCode = succ->JourneyCode;
        int price = succ->price;
        mydelete(succ);
        node->JourneyCode = JourneyCode;
        node->price = price;
    }
}

bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.

    TreeNode *nodeToDelete = root;
    while (true)
    {
        if (nodeToDelete == NULL)
            return false;

        if (nodeToDelete->JourneyCode == JourneyCode)
        {
            mydelete(nodeToDelete);
            return true;
        }
        if (nodeToDelete->JourneyCode > JourneyCode)
        {
            nodeToDelete = nodeToDelete->left;
        }
        else
        {
            nodeToDelete = nodeToDelete->right;
        }
    }

    return true;
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

