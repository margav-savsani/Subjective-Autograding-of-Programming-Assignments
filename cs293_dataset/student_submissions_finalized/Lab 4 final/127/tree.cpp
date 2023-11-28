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

vector<int> getlongestpath(TreeNode* search_node) {

    if(search_node==nullptr) {
        vector<int> temp_return={};
        return temp_return;
    }

    vector<int> left_path=getlongestpath(search_node->left);
    vector<int> right_path=getlongestpath(search_node->right);

    if(left_path.size()>right_path.size()) left_path.push_back(search_node->JourneyCode);
    else right_path.push_back(search_node->JourneyCode);

    if(left_path.size()>right_path.size()) return left_path;
    else return right_path;

}

vector<int> getshortestpath(TreeNode* search_node) {

    if(search_node==nullptr) {
        vector<int> temp_return={};
        return temp_return;
    }

    vector<int> left_path=getshortestpath(search_node->left);
    vector<int> right_path=getshortestpath(search_node->right);

    if(left_path.size()<right_path.size()) left_path.push_back(search_node->JourneyCode);
    else right_path.push_back(search_node->JourneyCode);

    if(left_path.size()<=right_path.size()) return left_path;
    else return right_path;

}

int TreeNode::getImbalance() {
    vector<int> longest_path=getlongestpath(this);
    vector<int> shortest_path=getshortestpath(this);

    return longest_path.size()-shortest_path.size();

}

int BST::getImbalance() {
    vector<int> longest_path=getlongestpath(root);
    vector<int> shortest_path=getshortestpath(root);

    return longest_path.size()-shortest_path.size();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.


    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    TreeNode* search_node=root;
    if(search_node==nullptr){
        root=new TreeNode(JourneyCode, price);
        return true;
    }
    while(true) {
        if(search_node->JourneyCode==JourneyCode) return false;
        if(price<=search_node->price) {
            if(search_node->left==nullptr) {
                TreeNode* new_node = new TreeNode(JourneyCode, price, nullptr, nullptr, search_node);
                search_node->left=new_node;
                new_node->left=nullptr;
                new_node->right=nullptr;
                new_node->parent=search_node;
                new_node->JourneyCode=JourneyCode;
                new_node->price=price;
                search_node->left=new_node;
                return true;
            }
            else {
                search_node=search_node->left;
            }
        }
        else {
            if(search_node->right==nullptr) {
                TreeNode* new_node = new TreeNode();
                new_node->left=nullptr;
                new_node->right=nullptr;
                new_node->parent=search_node;
                new_node->JourneyCode=JourneyCode;
                new_node->price=price;
                search_node->right=new_node;
                return true;
            }
            else {
                search_node=search_node->right;
            }
        }
        
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.


    TreeNode search_node=*root;
    while(true) {
        if(search_node.JourneyCode==JourneyCode && search_node.price==price) {
            return true;
        }
        else if(price<=search_node.price) {
            if(search_node.left==nullptr) return false;
            else search_node=*(search_node.left);
        }
        else {
            if(search_node.right==nullptr) return false;
            else search_node=*(search_node.right);
        }
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


    TreeNode* search_node=root;
    if(search_node==nullptr) return false;
    while(true) {
        if(search_node->JourneyCode==JourneyCode && search_node->price==price) {
            TreeNode* search_node_parent=search_node->parent;
            if(search_node_parent==nullptr) {
                if(search_node->left==nullptr && search_node->right==nullptr) {
                    root->left=nullptr;
                    root->right=nullptr;
                    root->parent=nullptr;
                    root->price=0;
                    root->JourneyCode=0;
                    return true;
                }
                if(search_node->left==nullptr) {
                    root=search_node->right;
                }
                else if(search_node->right==nullptr) {
                    root=search_node->left;
                }
                else {
                    TreeNode* new_node=search_node->right;
                    while(true) {
                        if(new_node->left==nullptr) break;
                        else new_node=new_node->left;
                    }
                    if(new_node->parent==search_node) {
                        new_node->left=search_node->left;
                        new_node->parent=search_node->parent;
                        root=new_node;

                        return true;
                    }
                    else {
                        (new_node->parent)->left=nullptr;
                        new_node->left=search_node->left;
                        new_node->right=search_node->right;
                        new_node->parent=search_node->parent;
                        root=new_node;

                        return true;
                    }
                }


            }
            else {
                std::string branch_of_child;
                if(search_node_parent->left==search_node) branch_of_child="left";
                else branch_of_child="right";

                if(search_node->left==nullptr && search_node->right==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=nullptr;
                    else search_node_parent->right==nullptr;
                    return true;
                }

                else if(search_node->left==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=search_node->right;
                    else search_node_parent->right=search_node->left;
                    return true;
                }

                else if(search_node->right==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=search_node->left;
                    else search_node_parent->left=search_node->left;
                    return true;
                }

                else {
                    TreeNode* new_node=search_node->right;
                    while(true) {
                        if(new_node->left==nullptr) break;
                        else new_node=new_node->left;
                    }
                    if(new_node->parent==search_node) {
                        new_node->left=search_node->left;
                        new_node->parent=search_node->parent;

                        if(branch_of_child=="left") search_node_parent->left=new_node;
                        else search_node_parent->right=new_node;

                        return true;
                    }
                    else {
                        (new_node->parent)->left=nullptr;
                        new_node->left=search_node->left;
                        new_node->right=search_node->right;
                        new_node->parent=search_node->parent;

                        if(branch_of_child=="left") search_node_parent->left=new_node;
                        else search_node_parent->right=new_node;

                        return true;
                    }
                }
            }
        }
        else if(price<=search_node->price) {
            if(search_node->left==nullptr) return false;
            else search_node=search_node->left;
        }
        else {
            if(search_node->right==nullptr) return false;
            else search_node=search_node->right;
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

