#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"

int BST::getImbalance()
{
    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        return root->getImbalance();
    }
}

bool BST::insert(int JourneyCode, int price)
{
    TreeNode *currNode = root, *parentOfCurrNode = NULL;
    while(currNode != nullptr)
    {
        if(currNode->JourneyCode < JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if(currNode->JourneyCode > JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else
        {
            return false;
        }
    }
    TreeNode* dummy=parentOfCurrNode;
    TreeNode* dummy1;
    int length=2;
    while(dummy!=NULL)
    {
        if(dummy->longestPathLength<length)
        {
            dummy->longestPathLength=length;
        }
        dummy=dummy->parent;
        length++;
    }
    TreeNode* leaf= new TreeNode;
    leaf->JourneyCode=JourneyCode;
    leaf->price=price;
    leaf->parent=parentOfCurrNode;
    leaf->left=NULL;
    leaf->right=NULL;
    leaf->shortestPathLength=1;
    leaf->longestPathLength=1;
    dummy=parentOfCurrNode;
    dummy1=leaf;
    if(parentOfCurrNode==NULL)
    {
        root=leaf;
        TotalNodes++;
        return true;
    }
    if(parentOfCurrNode->JourneyCode > JourneyCode)
    {
        if(parentOfCurrNode->left==NULL && parentOfCurrNode->right !=NULL)
        {
            parentOfCurrNode->shortestPathLength=2;
        }
        parentOfCurrNode->left=leaf;
    }
    else
    {
        if(parentOfCurrNode->right==NULL && parentOfCurrNode->left !=NULL)
        {
            parentOfCurrNode->shortestPathLength=2;
        }
        parentOfCurrNode->right=leaf;
    }
    TotalNodes++;
    while(dummy!=NULL)
    {
        if(dummy->left==dummy1 &&dummy->right!=NULL)
        {
            if(dummy->right->shortestPathLength < dummy1->shortestPathLength )
            {
                dummy->shortestPathLength=dummy1->shortestPathLength;
            }
        }
        else if(dummy->right==dummy1 &&dummy->left!=NULL)
        {
            if(dummy->left->shortestPathLength < dummy1->shortestPathLength )
            {
                dummy->shortestPathLength=dummy1->shortestPathLength;
            }
        }
        dummy1=dummy;
        dummy=dummy->parent;
    }
    return true;
}

bool BST::find(int JourneyCode, int price)
{
    TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    while(currNode != nullptr)
    {
        if(currNode->JourneyCode < JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if(currNode->JourneyCode > JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else
        {
            return true;
        }
    }
    return false;
}
	
bool BST::remove(int JourneyCode, int price)
{
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

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
    return;
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

