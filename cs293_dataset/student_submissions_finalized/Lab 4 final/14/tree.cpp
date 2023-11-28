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
  
  // struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  // while (currNode != nullptr) {
  //   if (currNode->JourneyCode < JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->right;
  //   }
  //   else if (currNode->JourneyCode > JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->left;
  //   }
  //   else { // currNode->JourneyCode == JourneyCode
  //     return false;
  //   }
  // }

  //if found tHen rturns false as it can't insert
    if(find(JourneyCode, price)) return false;

    TreeNode* newnode;
    newnode = new TreeNode(JourneyCode,price);
    TreeNode* r = root;
    TreeNode* n = NULL;
    bool done=false;

    // if root is empty before the new node will tself become the root
    if(root == NULL)
    {
        //cout << "insert at root\n";
        root = newnode;
        root->parent = NULL;
        return true;
    }
    
    while(r!=NULL && !done)
    {
        n=r;
        if(price < r->price) r=r->left;
        else r=r->right;
    }

    if(price < n->price && !done)
    {
        n->left = newnode;
        newnode->parent = r;
        done=true;
    }

    else if(!done)
    {
        n->right = newnode;
        newnode->parent = n;
        done = true;
    }

    TreeNode *t = new TreeNode;
    int g = 1;
    t = newnode->parent;
    while(!(t==NULL))
    {
      if(t->shortestPathLength > g) t->shortestPathLength = g;
      else if(t -> longestPathLength < g) t->longestPathLength = g;
      g=g+1;
      t=t->parent;
    }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  return done;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  TreeNode* needed;
    TreeNode* r;
    needed = new TreeNode(JourneyCode, price);
    r = root;
    bool isthere = false;

    //if the tree is empty then returns false 
    if(root == NULL) return false;

    while(!isthere)
    {
        if(r == NULL) return false;

        if(r->sameattributes(needed)) return true;

        if( (r->price == price && r->JourneyCode != JourneyCode) || (r->price != price && r->JourneyCode == JourneyCode) )return false;
        //anyways the second case in the above doesn't occur ig but still to be defensive

        //navigate till it finds
        if(r->price < price) r=r->right;
        else if(r->price > price) r=r->left;
    }
    return isthere;
}

//utility functions for remove
TreeNode* BST::minvaluenode(TreeNode* given)
{
    if(given == NULL) return NULL;

    while(given->left != NULL) given = given->left;
    return given;
}

TreeNode* BST::successor(TreeNode* given)
{
    TreeNode* pog = given->parent; //parent of given
    //if we are given a empty value to find successor
    //to be defensive
    if(given == NULL) return NULL;

    if(given->right !=NULL) return minvaluenode(given->right);
    else
    {
        if(given == pog->left) return pog; //given is the left child
        while(pog!=NULL && given == pog->right)
        {
            given = pog;
            pog = pog->parent;
        }
        return pog;
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
    
   //If node is not there then return
    if(!find(JourneyCode, price)) return false;
    
    TreeNode* needed;
    needed = new TreeNode(JourneyCode, price);
    TreeNode *n = NULL;
    TreeNode *r = root;

    bool done=false;

    while(!done)
    {
        //after reaching the node which has to be deleted
        //three cases may take place
        if(r->sameattributes(needed))
        {
            //case 1
            //no chidren -> leaf node
            if(r->left == NULL && r->right == NULL)
            {
                if(r == root){root = NULL; return true;}
                if(r == n->left) n->left = NULL;
                else n->right = NULL;
            }
            //if 1 child
            //2 subcases
            else if(r->left == NULL && r->right!=NULL)
            {
                if(r == root) {root = r->right; return true;}
                if(r == n->left) n->left = r->right;
                else n->right = r->right;
            }
            else if(r->left != NULL && r->right==NULL)
            {
                if(r == root) {root = r->left; return true;}
                if(r == n->left) n->left = r->left;
                else n->right = r->left;
            }
            //if 2 children
            //can solve in two ways using successor way
            else
            {
                TreeNode* s = successor(r);
                remove(s->JourneyCode,s->price);
                if(r == root) 
                {
                    root = s;
                    s->left = r->left;
                    s->right = r->left;
                }
                else
                {
                    n->right = s;
                    s->left = r->left;
                    s->right = r->right;
                }
            }
            return true;
        }
        if(r->price < price)
        {
            n = r;
            r =r->right;
        }
        else if(r->price > price)
        {
            n = r;
            r = r->left;
        }
    } 
    return done;
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


