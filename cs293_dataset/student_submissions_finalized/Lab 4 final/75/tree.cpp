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

  // To check whether the current pivot is already present in the BST
  if (find(JourneyCode, price)){
    return false;
  }
  //cout<<"Inserting Journey: "<<JourneyCode<<" "<<price<<endl;
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  // initializes a node with the given parameters
    TreeNode *toInsert = new TreeNode;
    if (toInsert != NULL)
    {
        toInsert->JourneyCode = JourneyCode;
        toInsert->price = price;
    }
    if (root == NULL)
    {
        // cout<<"root is null"<<endl;
        root = toInsert;
        
        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          curr->shortestPathLength = curr->getShortestPath();
          curr->longestPathLength = curr->getLongestPath();

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }

    // cout<<"Price of node to be inserted"<<toInsert->price<<endl;
    // cout<<"JourneyCode of node to be inserted"<<toInsert->JourneyCode<<endl;

    TreeNode *y = new TreeNode;
    TreeNode *x = root;

    while (x != NULL)
    {
        y = x;
        if (price < (x->price))
        {
            x = (x->left);
        }
        else
        {
            x = (x->right);
        }
    }
    toInsert->parent = y;
    if (y == NULL)
    {
        root = toInsert;
        
        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          curr->shortestPathLength = curr->getShortestPath();
          curr->longestPathLength = curr->getLongestPath();

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }
    else if (toInsert->price < y->price)
    {
        y->left = toInsert;
        

        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          curr->shortestPathLength = curr->getShortestPath();
          curr->longestPathLength = curr->getLongestPath();

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }
    else
    {
        y->right = toInsert;

        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          curr->shortestPathLength = curr->getShortestPath();
          curr->longestPathLength = curr->getLongestPath();

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }

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
    TreeNode *x = root;
    while (x != NULL && (price != (x->price) || JourneyCode != (x->JourneyCode)))
    {

        if (price < (x->price))
        {
            x = (x->left);
        }
        else
        {
            x = (x->right);
        }
    }
    if (x == NULL)
    {
        return false;
    }
    if ((price == (x->price) && JourneyCode == (x->JourneyCode)))
    {
        return true; // both the prices and journey code matches
    }
    else
    {
        return false; // node not found
    }
  // You can look at the implementation of insert to code this part up.
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
  if (root == NULL)
    {
        return false;
    }
    bool isPresent = find(JourneyCode, price);
    if (!isPresent)
    {
        return false;
    }
    // Journey is present
    TreeNode *curr = root;

    while (curr != NULL && curr->JourneyCode != JourneyCode)
    {
        if (curr->left != NULL && price < curr->price)
        {
            curr = curr->left;
        }
        else if (curr->right != NULL && price > curr->price)
        {
            curr = curr->right;
        }
    }
    if (curr == NULL)
    {
        return false;
    }
    else
    {
        // The current node is leaf
        if (curr->left == NULL && curr->right == NULL)
        {
            if (curr->parent != NULL)
            {
                if ((curr->parent)->left == curr)
                { // curr is left child
                    curr->parent->left = NULL;
                    curr->parent = NULL;
                    return true;
                }
                else if ((curr->parent)->right == curr)
                { // curr is right child
                    curr->parent->right = NULL;
                    curr->parent = NULL;
                    return true;
                }
            }
            else
            { // if parent = null, then curr is root
                root = NULL;
                return true;
            }
        }

        // The current node has one child - left child
        if (curr->left != NULL && curr->right == NULL)
        {
            // curr does not have a parent - it is root
            if (curr == root)
            {
                root = curr->left;
                curr->left->parent = NULL;
                curr->left = NULL;
                return true;
            }
            // curr has a parent
            else if ((curr->parent)->left == curr)
            { // parent-curr-child form a straight line
                // creating new pointers
                (curr->parent)->left = curr->left;
                (curr->left)->parent = curr->parent;

                // deleting extra nodes
                curr->left = NULL;
                curr->parent = NULL;

                return true;
            }
            else
            { // parent-curr-child do not form a straight line (form an angle)
                // creating new pointers
                (curr->parent)->right = curr->left;
                (curr->left)->parent = curr->parent;

                // deleting extra nodes
                curr->left = NULL;
                curr->parent = NULL;

                return true;
            }
        }
        else if (curr->right != NULL && curr->left == NULL)
        { // It has only right child
            // curr does not have a parent - it is root
            if (curr == root)
            {
                root = curr->right;
                curr->right->parent = NULL;
                curr->right = NULL;
                return true;
            }
            // curr has a parent
            else if ((curr->parent)->right == curr)
            { // parent-curr-child form a straight line
                // creating new pointers
                (curr->parent)->right = curr->right;
                (curr->right)->parent = curr->parent;

                // deleting extra nodes
                curr->right = NULL;
                curr->parent = NULL;

                return true;
            }
            else
            { // parent-curr-child do not form a straight line (form an angle)
                // creating new pointers
                (curr->parent)->left = curr->right;
                (curr->right)->parent = curr->parent;

                // deleting extra nodes
                curr->right = NULL;
                curr->parent = NULL;

                return true;
            }
        }
        else
        { // node has both chidren
            // There will be a right tree

            TreeNode *succ = curr->right; // stores the pointer to successor of the current node
            while (succ->left != NULL)
            {
                succ = succ->left;
            }
            // cout<<"succ of 10 is "<<succ->price;
            TreeNode *temp = new TreeNode; // to store the values of temp
            temp->JourneyCode = succ->JourneyCode;
            temp->price = succ->price;

            // Remove the successor
            // The current node is leaf
            if (succ->right == NULL)
            {
                if ((succ->parent)->left == succ)
                { // succ is left child
                    succ->parent->left = NULL;
                    succ->parent = NULL;
                }
                else if ((succ->parent)->right == succ)
                { // succ is right child
                    succ->parent->right = NULL;
                    succ->parent = NULL;
                }
            }

            // It has only right child

            else if (succ->right != NULL && succ->left == NULL)
            { // It has only right child
                // succ does not have a parent - it is root
                if (succ == root)
                {
                    root = succ->right;
                    succ->right->parent = NULL;
                    succ->right = NULL;
                }
                // succ has a parent
                else if ((succ->parent)->right == succ)
                { // parent-succ-child form a straight line
                    // creating new pointers
                    (succ->parent)->right = succ->right;
                    (succ->right)->parent = succ->parent;

                    // deleting extra nodes
                    succ->right = NULL;
                    succ->parent = NULL;
                }
                else
                { // parent-succ-child do not form a straight line (form an angle)
                    // creating new pointers
                    (succ->parent)->left = succ->right;
                    (succ->right)->parent = succ->parent;

                    // deleting extra nodes
                    succ->right = NULL;
                    succ->parent = NULL;
                }
            }

            // copying the values of the successor into the current node
            curr->JourneyCode = temp->JourneyCode;
            curr->price = temp->price;
            delete temp;

            return true;
        }
    }
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
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
        root = curr->left;
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

