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
BST::BST() {root =new TreeNode(0,0,nullptr,nullptr,nullptr); shortestPathLength = longestPathLength = 0;}
BST::BST(TreeNode *curr_root) {root = curr_root; shortestPathLength = longestPathLength = 1;}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price){
  TreeNode *wu=root;
  TreeNode *wi=nullptr; int b=0;
  if(find(JourneyCode,price)) return false; 
  else {
    if(wu->price==0){
    TreeNode *tem;
    tem = new TreeNode(JourneyCode,price,nullptr,nullptr,nullptr);
    wu=tem;
    return true;
    }
    while(wu!=nullptr){
      if(wu->price>price){
        wi=wu;
        b=1;
        wu=wu->left;
      }
      else if(wu->price<price){
        wi=wu;
        b=2;
        wu=wu->right;
      }
    }
    wu=new TreeNode(JourneyCode,price,nullptr,nullptr,wi);
    if(b==1) wi->left=wu;
    else if(b==2) wi->right=wu;
    return true;
    }
    
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
  TreeNode *we;
    we=root;
    bool b1=false;
    bool b2=true;
    while(b1 ==false && we != nullptr && b2==true){
      if(we->price ==price){
        b1=true;
        break;
      }
      else if(we->price > price && we->left != nullptr){
        we=we->left;
      }
      else if(we->price > price && we->left == nullptr){
        b2=false;
        break;
      }
      else if(we->price < price && we->right != nullptr){
        we=we->right;
      }
      else if(we->price < price && we->left == nullptr){
        b2=false;
        break;
      }
    }
    if(b1==true)return true;
    
    else return false;
    
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

