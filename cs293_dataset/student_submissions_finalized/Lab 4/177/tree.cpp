#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JC_to_find, int price_to_find) {
    // ToDo: Implement code to update shortestPathLength and longestPathLength 
    if (root -> JourneyCode == 0) {root -> JourneyCode = JC_to_find; root -> price = price_to_find; return true;}

    TreeNode* newnode = new TreeNode(JC_to_find,price_to_find);
    TreeNode* nodeptr = root;

    while (nodeptr -> JourneyCode != JC_to_find){
        if (nodeptr -> JourneyCode > JC_to_find){
            if (nodeptr -> left == nullptr) {
                newnode -> parent = nodeptr;
                nodeptr -> left = newnode;
                return true;
            }
            else nodeptr = nodeptr -> left;
        }
        if (nodeptr -> JourneyCode < JourneyCode){
            if (nodeptr -> right == nullptr){
                newnode -> parent = nodeptr;
                nodeptr -> right = newnode;
                return true;
            }
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}

bool BST::find(int JC_to_find, int price_to_find) { 
    TreeNode* nodeptr = root;

    while (nodeptr != nullptr){
        if (nodeptr -> JourneyCode == JC_to_find){
            if (nodeptr -> price == price_to_find) return true;
            else nodeptr = nodeptr -> right;
        }
        else {
            if (nodeptr -> JourneyCode > JC_to_find) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}

bool BST::remove(int JC_to_find, int price_to_find) {
  // ToDo: Implement code to update shortest and longest path length
    TreeNode* nodeptr = root;

    while (nodeptr != nullptr){
        if (nodeptr -> price == price_to_find){
            if (nodeptr -> JourneyCode == JC_to_find) break;
            else nodeptr = nodeptr -> right;
        }
        else {
            if (nodeptr -> price > price_to_find) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }

    if (nodeptr == nullptr) return false;
    else{
        TreeNode* parentptr = nodeptr -> parent;
        TreeNode* node_to_delete = nodeptr;

        if ((node_to_delete -> left == nullptr) && (node_to_delete -> right == nullptr)){
            if (parentptr -> left == node_to_delete) parentptr -> left = nullptr;
            else parentptr -> right = nullptr;
            return true;
        }
        else {
            if ((node_to_delete -> left == nullptr) || (node_to_delete -> right == nullptr)){
                if (node_to_delete -> left == nullptr){
                    if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                    else {parentptr -> right = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                    return true;
                }
                if (node_to_delete -> right == nullptr){
                    if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                    else {parentptr -> right = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                    return true;
                }
            }
            else{
                TreeNode* probe = node_to_delete -> right;
                while (probe -> left != nullptr) probe = probe -> left;
                node_to_delete -> price = probe -> price; node_to_delete -> JourneyCode = probe -> JourneyCode;
                TreeNode* probe_parent_ptr = probe -> parent;
                if (probe_parent_ptr -> left == probe) probe_parent_ptr -> left = nullptr;
                else probe_parent_ptr -> right = nullptr;
                return true;
            }
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
        result.push_back(root->JourneyCode + "\n");
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

