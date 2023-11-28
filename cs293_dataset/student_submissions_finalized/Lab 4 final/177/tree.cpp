#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

int getShortestLength(TreeNode* nodeptr){
    if (nodeptr == nullptr) return 0;

    int left_length = getShortestLength(nodeptr -> left);
    int right_length = getShortestLength(nodeptr -> right);

    if (nodeptr -> right == nullptr) return left_length + 1;
    if (nodeptr -> left == nullptr) return right_length + 1;

    return min(left_length,right_length) + 1;
}

int getLongestLength(TreeNode* nodeptr){
    if (nodeptr == nullptr) return 0;

    int left_length = getLongestLength(nodeptr -> left);
    int right_length = getLongestLength(nodeptr -> right);

    if (nodeptr -> right == nullptr) return left_length + 1;
    if (nodeptr -> left == nullptr) return right_length + 1;

    return max(left_length,right_length) + 1;
}

void updatePathLengths(TreeNode* nodeptr){
    nodeptr -> shortestPathLength = getShortestLength(nodeptr);
    nodeptr -> longestPathLength = getLongestLength(nodeptr);
}

void updatePathLengths_Tree(TreeNode* root_){
    updatePathLengths(root_);
    if (root_ -> left != nullptr) updatePathLengths_Tree(root_ -> left);
    if (root_ -> right != nullptr) updatePathLengths_Tree(root_ -> right);
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root -> getImbalance();
}

bool BST::insert(int JC_to_find, int price_to_find) {
    if (root -> JourneyCode == 0) {root -> JourneyCode = JC_to_find; root -> price = price_to_find; updatePathLengths(root); return true;}

    vector<TreeNode*> path;
    path.push_back(root);

    TreeNode* newnode = new TreeNode(JC_to_find,price_to_find);
    TreeNode* nodeptr = root;
    bool found = false;

    while (nodeptr -> JourneyCode != JC_to_find){
        if (nodeptr -> JourneyCode > JC_to_find){
            if (nodeptr -> left == nullptr) {
                newnode -> parent = nodeptr;
                nodeptr -> left = newnode;
                path.push_back(newnode);
                found = true;
                break;
            }
            else nodeptr = nodeptr -> left;
        }
        if (nodeptr -> JourneyCode < JC_to_find){
            if (nodeptr -> right == nullptr){
                newnode -> parent = nodeptr;
                nodeptr -> right = newnode;
                path.push_back(newnode);
                found = true;
                break;
            }
            else nodeptr = nodeptr -> right;
        }

        path.push_back(nodeptr);
    }

    for (auto i = path.begin(); i != path.end(); i++) {updatePathLengths(*i);}
    return found;
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
        if (nodeptr != root){ // Incase the node to be deleted isn't the root
            TreeNode* parentptr = nodeptr -> parent;
            TreeNode* node_to_delete = nodeptr;

            if ((node_to_delete -> left == nullptr) && (node_to_delete -> right == nullptr)){
                if (parentptr -> left == node_to_delete) parentptr -> left = nullptr;
                else parentptr -> right = nullptr;
            }
            else {
                if ((node_to_delete -> left == nullptr) || (node_to_delete -> right == nullptr)){
                    if (node_to_delete -> left == nullptr){
                        if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                        else {parentptr -> right = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                    }
                    if (node_to_delete -> right == nullptr){
                        if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                        else {parentptr -> right = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                    }
                }
                else{
                    TreeNode* probe = node_to_delete -> right;
                    while (probe -> left != nullptr) probe = probe -> left;
                    node_to_delete -> price = probe -> price; node_to_delete -> JourneyCode = probe -> JourneyCode;
                    TreeNode* probe_parent_ptr = probe -> parent;
                    if (probe -> right == nullptr){
                        if (probe_parent_ptr -> left == probe) probe_parent_ptr -> left = nullptr;
                        else probe_parent_ptr -> right = nullptr;
                    }
                    else{
                        if (probe_parent_ptr -> left == probe) {probe_parent_ptr -> left = probe -> right; probe -> right -> parent = probe_parent_ptr;}
                        else {probe_parent_ptr -> right = probe -> right; probe -> right -> parent = probe_parent_ptr;}                   
                    }
                }
            }
        }
        else{ // Handling root deletion
            if ((root -> left == nullptr) && (root -> right == nullptr)){
                root -> price = 0; root -> JourneyCode = 0;
            }
            else {
                if ((root -> left == nullptr) || (root -> right == nullptr)){
                    if (root -> left == nullptr){ root = root -> right;}
                    if (root -> right == nullptr){ root = root -> left;}
                }
                else{
                    TreeNode* probe = root -> right;
                    while (probe -> left != nullptr) probe = probe -> left;
                    root -> price = probe -> price; root -> JourneyCode = probe -> JourneyCode;
                    TreeNode* probe_parent_ptr = probe -> parent;
                    if (probe -> right == nullptr){
                        if (probe_parent_ptr -> left == probe) probe_parent_ptr -> left = nullptr;
                        else probe_parent_ptr -> right = nullptr;
                    }
                    else{
                        if (probe_parent_ptr -> left == probe) {probe_parent_ptr -> left = probe -> right; probe -> right -> parent = probe_parent_ptr;}
                        else {probe_parent_ptr -> right = probe -> right; probe -> right -> parent = probe_parent_ptr;}                   
                    }
                }  
            }
        }
        updatePathLengths_Tree(root);
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

        
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        
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

        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;

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