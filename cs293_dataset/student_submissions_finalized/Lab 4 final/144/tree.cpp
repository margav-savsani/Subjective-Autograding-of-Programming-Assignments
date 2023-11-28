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
  TreeNode *temp = new TreeNode(JourneyCode, price);

    if (root == nullptr)
    {
        root = temp;
        root->parent = nullptr;
        return true;
    }


    TreeNode *next_ptr;
    TreeNode *parent_to_add = root;

    if (JourneyCode <= root->JourneyCode)
    {
        next_ptr = root->left;
    }

    else
        next_ptr = root->right;

    while (next_ptr != nullptr)
    {
        parent_to_add = next_ptr;

        if (JourneyCode <= parent_to_add->JourneyCode)
        {
            next_ptr = parent_to_add->left;
        }

        else
            next_ptr = parent_to_add->right;
    }

    if (JourneyCode <= parent_to_add->JourneyCode)
    {
        parent_to_add->left = temp;
        temp->parent = parent_to_add;
    }

    else
    {
        parent_to_add->right = temp;
        temp->parent = parent_to_add;
    }

    TreeNode* parent_node = temp->parent;
    //Updating lengths for ancestors of inserted element
    while(parent_node != nullptr){
        parent_node->updateLengths();
        parent_node = parent_node->parent;
    }
    return true;
}

  


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  return find(JourneyCode, price, root);
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  TreeNode *ptr = root;
    while (true)
    {
        if (ptr == NULL)
        {
            return false;
        }
        if (ptr->JourneyCode == JourneyCode && ptr->price == price)
            break;

        if (JourneyCode <= ptr->JourneyCode)
        {
            ptr = ptr->left;
        }

        else
        {
            ptr = ptr->right;
        }
    }

    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (ptr == root)
        {
            delete root;
            root = nullptr;
        }

        else
        {
            TreeNode *parent = ptr->parent;

            if (parent->left == ptr)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete ptr;
        }

        return true;
    }

    if (ptr->left == NULL || ptr->right == NULL)
    {

        if (ptr == root)
        {
            TreeNode *next_ptr;
            if (ptr->left == NULL)
            {
                root = ptr->right;
                root->parent = nullptr;
            }

            else
            {
                ptr->left = root;
                root->parent = nullptr;
            }

            delete ptr;
        }

        else
        {
            TreeNode *parent = ptr->parent;

            if (ptr->left == NULL)
            {
                if (parent->left == ptr)
                {
                    parent->left = ptr->right;
                    ptr->right->parent = parent;
                }

                else
                {
                    parent->right = ptr->right;
                    ptr->right->parent = parent;
                }
            }

            else
            {
                if (parent->left == ptr)
                {
                    parent->left = ptr->left;
                    ptr->left->parent = parent;
                }

                else
                {
                    parent->right = ptr->left;
                    ptr->left->parent = parent;
                }
            }

            delete ptr;
        }
        return true;
    }

    else
    {

        TreeNode *next_ptr = ptr->left;

        while (next_ptr->right != NULL)
        {
            next_ptr = next_ptr->right;
        }

        int temp_price = next_ptr->price;
        int temp_journey = next_ptr->JourneyCode;

        remove(next_ptr->JourneyCode, next_ptr->price);

        ptr->price = temp_price;
        ptr->JourneyCode = temp_journey;

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

bool BST::find(int JourneyCode, int price, TreeNode *node_ptr)
{
    if (node_ptr == nullptr)
        return false;

    if (node_ptr->JourneyCode == JourneyCode && node_ptr->price == price)
    {
        return true;
    }

    return (find(JourneyCode, price, node_ptr->left) || find(JourneyCode, price, node_ptr->right));
};

void BST::deleteNode(TreeNode* node_ptr){
	if(node_ptr == nullptr) return;

	deleteNode(node_ptr->left);
	deleteNode(node_ptr->right);
	delete node_ptr;
}

