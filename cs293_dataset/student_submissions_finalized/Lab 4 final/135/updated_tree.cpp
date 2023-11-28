// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "updated_tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

void BST::update(TreeNode* currNode){
  while(currNode != nullptr){
    if(currNode->left == nullptr && currNode->right == nullptr){
      currNode->shortestPathLength = 0;
      currNode->longestPathLength = 0;
    }
    else if(currNode->left != nullptr && currNode->right == nullptr){
      currNode->shortestPathLength = 0;
      currNode->longestPathLength = currNode->left->longestPathLength + 1;
    }
    else if(currNode->left == nullptr && currNode->right != nullptr){
      currNode->shortestPathLength = 0;
      currNode->longestPathLength = currNode->right->longestPathLength + 1;
    }
    else{
      currNode->shortestPathLength = min(currNode->left->shortestPathLength, currNode->right->shortestPathLength)+1;
      currNode->longestPathLength = max(currNode->left->longestPathLength, currNode->right->longestPathLength)+1;
    }
    currNode = currNode->parent;
  }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  if(find(JourneyCode, price)) return false;
    
    TreeNode* check = root, *toadd = new TreeNode(JourneyCode, price);
    if(check == nullptr){
        toadd->parent = check;
        root = toadd;
        update(toadd);
        return true;
    }
    while(true){
        if(check->price >= price){
            if(check->left != nullptr){
                check = check->left;
            }
            else{
                toadd->parent = check;
                check->left = toadd;
                update(toadd);
                return true;
            }
        }
        else{
            if(check->right != nullptr){
                check = check->right;
            }
            else{
                toadd->parent = check;
                check->right = toadd;
                update(toadd);
                return true;
            }
        }
    }

  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting

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
  TreeNode* check = root;
    if(check == nullptr) return false;
    if(check->price == price){
        // std::cout << "find " <<  check->JourneyCode << "\n";
        return (check->JourneyCode == JourneyCode) || BST(check->left).find(JourneyCode, price) || BST(check->right).find(JourneyCode, price);
    }
    if(price < check->price) return (BST(check->left).find(JourneyCode, price));
    else return (BST(check->right).find(JourneyCode, price));
}
	
// Returns false, if JourneyCode isn't present


TreeNode* BST::findnode(int JourneyCode, int price){
    struct TreeNode *currNode = root;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      break;
    }
  }

  return currNode;
}

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
  if(!find(JourneyCode, price)) return false;

    TreeNode* node = findnode(JourneyCode, price);
    
    if(node->left == nullptr && node->right == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root = root->right;
        }
        else if(a->left != nullptr && a->left->JourneyCode == JourneyCode && a->left->price == price){
            a->left = nullptr;
        }
        else{
            a->right = nullptr;
        }
        update(a);

        return true;
    }
    if(node->left == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root = root->right;
        }
        else if(a->left != nullptr && a->left->JourneyCode == JourneyCode && a->left->price == price){
            node->right->parent = a;
            a->left = node->right;
        }
        else{
            node->right->parent = a;
            a->right = node->right;
        }
        update(a);

        return true;
    }
    if(node->right == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root = root->left;
        }
        if(a->left != nullptr && a->left->JourneyCode == JourneyCode && a->left->price == price){
            node->left->parent = a;
            a->left = node->left;
        }
        else{
            node->left->parent = a;
            a->right = node->left;
        }
        update(a);

        return true;
    }

    TreeNode* pred = node->left;
    while(pred->right != nullptr){
        pred = pred->right;
    }
    TreeNode temp = *pred;
    TreeNode* currNode = pred->parent;
    remove(pred->JourneyCode, pred->price);
    node->JourneyCode = temp.JourneyCode;
    node->price = temp.price;
    update(currNode);

    return true;

    //
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

