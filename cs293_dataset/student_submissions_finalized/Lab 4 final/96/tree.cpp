#include <set>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

//returns shortest path length from given node to a leaf

int getshortestPathLength(TreeNode* node){
  if(node->left==nullptr && node->right==nullptr) return 0;
  else if(node->left==nullptr) return getshortestPathLength(node->right)+1;
  else if(node->right==nullptr) return getshortestPathLength(node->left)+1;
  else return min(getshortestPathLength(node->left),getshortestPathLength(node->right))+1;
}

//returns longest path length from given node to a leaf

int getlongestPathLength(TreeNode* node){
  if(node->left==nullptr && node->right==nullptr) return 0;
  else if(node->left==nullptr) return getlongestPathLength(node->right)+1;
  else if(node->right==nullptr) return getlongestPathLength(node->left)+1;
  else return max(getlongestPathLength(node->left),getlongestPathLength(node->right))+1;
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  root->shortestPathLength=getshortestPathLength(root);
  root->longestPathLength=getlongestPathLength(root);
  return root->getImbalance();
}
TreeNode* insert(TreeNode* node, int jc,int p)
{
    if (node == nullptr) return new TreeNode(jc,p);

    if (jc < node->JourneyCode) node->left = insert(node->left, jc, p);

    else node->right = insert(node->right, jc,p);
 
    return node;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price)
{
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  
  root=::insert(root,JourneyCode,price);
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      if(currNode->price == price) return true;
    }
  }
  return false;
}

TreeNode* minNode(TreeNode* node){
    while(true){
        if(node->left==nullptr) return node;
        node=node->left;
    }
}

TreeNode* del(TreeNode* node,int jc,int p){
    if(node->price==p){
        if (node->left==nullptr and node->right==nullptr) return nullptr;
            
        else if (node->left == nullptr) {
            node = node->right;
            
        }
        else if (node->right == nullptr) {
            node = node->left;
            
        }
        else{
            TreeNode* temp=minNode(node->right);
            node->JourneyCode=temp->JourneyCode;
            node->price=temp->price;
            node->right=del(node->right,temp->JourneyCode,temp->price);
            
        }
    }
    else if(node->price <p) node->right = del(node->right,jc,p);
    else node->left = del(node->left,jc,p);
    return node;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(find(JourneyCode,price)){
    root=del(root,JourneyCode,price);
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

