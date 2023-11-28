#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "tree.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
void TreeNode::update(){
    if(!((left) || (right))){
        longestPathLength++;
        shortestPathLength++;
    }
    else if(!left){
        longestPathLength=right->longestPathLength+1;
        shortestPathLength=right->shortestPathLength+1;
    }
    else if(!right){
        longestPathLength=left->longestPathLength+1;
        shortestPathLength=left->shortestPathLength+1;
    }
    else{
        if(left->longestPathLength>right->longestPathLength){
            longestPathLength=left->longestPathLength+1;
        }
        else{
            longestPathLength=right->longestPathLength+1;
        }
        if(left->shortestPathLength<right->shortestPathLength){
            shortestPathLength=left->shortestPathLength+1;
        }
        else{
            shortestPathLength=right->shortestPathLength+1;
        }
    }
    if(parent){
        parent->update();
    }
}

BST::BST(){
    root=nullptr;
}

BST::BST(TreeNode *r){
    root=r;
    //root->shortestPathLength=1;
    //root->longestPathLength=1;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    TreeNode nodeInsert(JourneyCode,price);

    if(!root){
        root=new TreeNode(nodeInsert);
        root->parent=nullptr;
        root->update();
        return true;
    }

    TreeNode* parentIns=nullptr;
    TreeNode* temp=root;

    while(temp){
        parentIns=temp;
        if(nodeInsert.JourneyCode>temp->JourneyCode){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }

    if (parentIns->JourneyCode>nodeInsert.JourneyCode){
        nodeInsert.parent=parentIns;
        parentIns->left=new TreeNode(nodeInsert);
    }
    else{
        nodeInsert.parent=parentIns;
        parentIns->right=new TreeNode(nodeInsert);
    }
    nodeInsert.update();
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    if(!root){
        return false;
    }
    //cout<<"1a"<<endl;
    if(price==root->price && JourneyCode==root->JourneyCode){
        //cout<<"2"<<endl;
        return true;
    }
    TreeNode* temp=root;
    bool found=false;
    if(JourneyCode>root->JourneyCode){
        //cout<<"3a"<<endl;
        root=root->right;
        found=find(JourneyCode,price);
    }
    else{
        //cout<<"4"<<endl;
        root=root->left;
        found=find(JourneyCode,price);
    }
    root=temp;
    return found;
    //return find2(JourneyCode,price,root);
}


void BST::prestore(){
    if(!root){
        return;
    }
    cout<<root->shortestPathLength<<" "<<root->longestPathLength<<endl;
    TreeNode* temp=root;
    root=root->left;
    prestore();
    root=temp->right;
    prestore();
    root=temp;
}

void BST::getImbalance(){
    cout<<root->getImbalance();
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
        //root=root->right;
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

        result.push_back(isLeft ? "├──" : "└──" );

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

