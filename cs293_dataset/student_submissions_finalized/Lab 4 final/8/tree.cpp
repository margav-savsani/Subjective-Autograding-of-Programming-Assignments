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
bool isLeft(TreeNode* parent, TreeNode* child);
int noOfChildren(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) return 0;
    else if (node->left != nullptr && node->right == nullptr) return 1;
    else if (node->left == nullptr && node->right != nullptr) return 1;
    else if (node->left != nullptr && node->right != nullptr) return 2;
    return -1;
}
bool isLeft(TreeNode* parent, TreeNode* child) { 
    if(parent -> left == nullptr) return false;

    else if(parent -> right == nullptr) return true;

    else if (parent -> left == child)
    {
        return true;
    }

    else if (parent -> right == child)
    {
        return false;
    }
    return false; 
}

TreeNode *treeMin(TreeNode* rootNode) {
    TreeNode * ptr = rootNode;
    while (ptr -> left != nullptr)
    {
        ptr = ptr -> left;
    }
    
    return ptr;
}

TreeNode* successor(TreeNode* node) {
    TreeNode* ptr1 = node;
    TreeNode* ptr2 = ptr1 -> parent;
    if (node -> right != nullptr)
    {
        return treeMin(node -> right);   
    }

    else {
        while (!(ptr2 -> left == ptr1))
        {
            if(ptr2 == nullptr) break;
            ptr1 = ptr2;
            ptr2 = ptr2 -> parent;
        }
        
        if (ptr2 != nullptr)
        {
            return ptr2;
        }

        return nullptr;
        
    }
    
}

void joinNodes(TreeNode* parent, TreeNode* child, bool left = true){
    if(left == true){
        parent -> left = child;
        child -> parent = parent;
    }    

    else {
        parent -> right = child;
        child -> parent = parent;
    }
}

void joinNodes2(TreeNode* node, TreeNode* Succ) {
    // making ptr form parent of the successor to the successor null
    if(isLeft(Succ->parent,Succ)) Succ->parent->left = nullptr;
    else Succ->parent->right = nullptr;

    if(Succ -> right != nullptr) joinNodes(Succ->right,Succ->parent,true);
    joinNodes(node->parent,Succ,isLeft(node->parent,node));
    Succ -> left = node -> left;
    Succ -> right = node -> right;
    Succ -> parent = node -> parent;

}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price) {
    TreeNode *ptr = root;
    TreeNode *ptr2 = nullptr;
    
    //cout << "inserting" << endl;
    while (ptr != nullptr)
    {
        //cout << "stuck" << endl;
       if (ptr -> price > price)
       {
            ptr2 = ptr;
            ptr  = ptr -> left;
       }

       else if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return false;
       }
       

       else
       {
            ptr2 = ptr;
            ptr = ptr -> right;
       }
    }

    TreeNode *node = new TreeNode(JourneyCode,price);
    //if tree do not ahs a node
    if (ptr2 == nullptr)
    {
        root = node;
    }
    
    // if node was there before
    else if(ptr2 -> price > price) {
        ptr2 -> left = node;
        node -> parent = ptr2;
    }

    else
    {
        ptr2 -> right = node;
        node -> parent = ptr2;
    }
    updateTreeData(node);
    return true;
}

  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  


// Return True, if the ticket with given attributes is found, false otherwise

bool BST::find(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return true;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    
        
    }
    
    return false;
}
TreeNode* BST::findNode(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
      //  cout << "i stuck in findNode loop" << endl;
       // cout << JourneyCode << " " << price << endl;
       // cout << endl;
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return ptr;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    }

    return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* node = findNode(JourneyCode,price);

    if (!find(JourneyCode,price))
    {
        return false;   
    }
    
    else if (node == root)
    {
       if (noOfChildren(node) == 0)
       {
        root == nullptr;
       }
       
       else if (node -> right == nullptr)
       {
        root = node -> left;
        root -> parent = nullptr;
       }

       else if (node -> left == nullptr)
       {
        root = node -> right;
        root -> parent = nullptr;
       }
       
       else {
        root = successor(root);
        root -> left = node -> left;
       }

        return true;
        
    }


    else if (noOfChildren(node) == 0)
    {
        TreeNode* parent = node->parent;
        node -> parent = nullptr;
        if (parent -> left == node)
        {
            parent -> left = nullptr;
        }
        
        else {
            parent -> right = nullptr;
        }
        return true;
    }

    else if (noOfChildren(node) == 1)
    {
        TreeNode* child = node->left == nullptr ? node->right : node->left; 
        joinNodes(node->parent,child, isLeft(node->parent,node));
        return true;
        
    }
    
    else if (noOfChildren(node) == 2) {
        //cout << successor(node) -> price << "this is the price of successor" << endl;
        joinNodes2(node, successor(node));
        return true;
    }
    
    return false; 
}

void BST::updateTreeData(TreeNode* node){
    if(node == root) return;

    if(node -> parent -> longestPathLength < node -> longestPathLength + 1) {
        node -> parent -> longestPathLength = node -> longestPathLength +1;
    }

    if (noOfChildren(node->parent) == 2)
    {
        node -> parent -> shortestPathLength = min(node -> parent -> right -> shortestPathLength +1, node -> parent -> left -> shortestPathLength +1);
    }

    else if (noOfChildren(node -> parent) == 1) {
            node -> parent -> shortestPathLength = node -> shortestPathLength +1;
    }
    
    //if (node -> parent -> shortestPathLength > node -> shortestPathLength +1)
    //{
        //node -> parent -> shortestPathLength = node -> shortestPathLength +1;
        //updateTreeData(node -> parent);
    //}

    //if (node -> parent -> longestPathLength < node -> longestPathLength + 1 ||
        //node -> parent -> shortestPathLength > node -> shortestPathLength +1)
    //{
        //updateTreeData(node -> parent);
    //}
    updateTreeData(node->parent); 
    
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
/*
int main() {
    BST Tree ;
    Tree.insert(5,5);
    Tree.insert(4,4);
    Tree.insert(8,8);
    Tree.printBST(" ");
}

*/