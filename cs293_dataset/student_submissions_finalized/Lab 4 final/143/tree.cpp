// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"





int BST::getImbalance() //returns the imbalance of the tree
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{
  TreeNode *x;
  x = this->root;
  if(x==nullptr){ //inserting the first element
        x = new TreeNode(JourneyCode,price);
        root=x;
  }
  else{
    while(true){ //inserting the elements with respect to JourneyCodes
      if(x->JourneyCode>JourneyCode){
        if(x->left==nullptr){
            x->left = new TreeNode(JourneyCode,price,nullptr,nullptr,x);
            x = x->left;
            break;
        }
        else{
            x = x->left;
        }
      }   
      if(x->JourneyCode<JourneyCode){
        if(x->right==nullptr){
            x->right= new TreeNode(JourneyCode,price,nullptr,nullptr,x);
            x = x->right;
            break;
        }
        else{
            x = x->right;
        }
      }   
      else{ //if the element is repeated it will not be inserted and return false;
        return false;
      }
    }
    }
    int check = 0;
    TreeNode *y;
    y =x;
      while(y->parent!=nullptr){ //checks if the tree is linear 
         y = y->parent;
        if(y->left==nullptr || y->right==nullptr){
          continue;
        }
        else{
          check = 1;//if check=1 tree is not linear else it is linear
          break;
        }
      }
    int length = 1;
    if(check==1){//tree is not linear
      while(x->parent!=nullptr){
        x = x->parent;
        if(length>x->longestPathLength) { //updates the longest path after inserting
          x->longestPathLength = length;
        }
        if(length<=x->shortestPathLength){ //updates the shortest path and also the second shortest path so as to keep track of adding values
          x->shortestpathlength2=x->shortestPathLength;
          x->shortestPathLength = length;  
        }
        if(length==(x->shortestPathLength)+1){
          if(x->shortestpathlength2==x->shortestPathLength){
            x->shortestPathLength = x->shortestpathlength2;
          }
          if(x->shortestpathlength2!=x->shortestPathLength){
            x->shortestPathLength = x->shortestPathLength+1;
          }
        }
        length++;
      }
    }
    else{
      while(x->parent!=nullptr){ //if tree is linear both shorter and longer lengths get updated
         x = x->parent;
        (x->shortestPathLength)++;
        (x->longestPathLength)++;
        (x->shortestpathlength2)++;
      }
    }
  return true;
}


bool BST::find(int JourneyCode, int price) //used to find if the element is present in the tree
{
  TreeNode *x;
  x = this->root;
    while(true){
        if(x==nullptr){
            break;
        }
        if(x->JourneyCode==JourneyCode && x->price == price){
            return true;
        }
        else if(x->JourneyCode>=JourneyCode){
            x = x->left;
        }
        else if(x->JourneyCode<JourneyCode){
            x= x->right;
        }
    }
return false;
}
TreeNode* BST::successor(TreeNode *ele){ //finds the successor of the element in the tree
  if(ele->right!=nullptr){
        ele = ele->right;
        while(true){
            if(ele->left==nullptr){
                return ele;
            }  
            else{
                ele = ele->left;
            }
        }
    }
    TreeNode *y;
    y = ele->parent;
    while(y!=nullptr && y->right==ele){
        ele = y;
        if(y!=root){
        y = y->parent;
        }
        else{
            y=nullptr;
        }
    }
    return y;
}
bool BST::remove(int JourneyCode, int price) //used to delete an element from the tree
{
  TreeNode *x;
    x = root;
    while(true){
        if(x==nullptr){
            return false;
        }
        if(x->JourneyCode==JourneyCode && x->price == price){
            break;
        }
        else if(x->JourneyCode>=JourneyCode){
            x = x->left;
        }
        else if(x->JourneyCode<JourneyCode){
            x = x->right;
        }
    }
    
    if(x==root && x->left==nullptr && x->right==nullptr){
        root=new TreeNode();
    }
    else{
        TreeNode *y;
        if(x==root){
            if(x->left==nullptr){
                root=x->right;
            }
            else if(x->right==nullptr){
                root=x->left;
            }
            else{
                x->left->parent=x->right;
                root=x->right;
                root->left=x->left;
            }

        }
        if(x->left==nullptr || x->right==nullptr){
            y = x;
        }
        else{
            y = successor(x);
        }
        if(y->left!=nullptr){
            x = y->left;
        }
        else{
            x = y->right;
        }
        if(x!=nullptr){
            x->parent=y->parent;
        }
        if(y->parent == nullptr){
            root = x;
        }
        else if(y==y->parent->left){
            y->parent->left = x;
        }
        else if(y==y->parent->right){
            y->parent->right=x;
        }
        if(y!=x){
            x=y;
        }
    }    
    return true;
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

