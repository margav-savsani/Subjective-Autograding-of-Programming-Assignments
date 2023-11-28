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

int shortest(TreeNode* node){
  if((node->left==nullptr)&&(node->right==nullptr)) return 0;
  else if((node->left==nullptr)&&(node->right!=nullptr)){
    return 1+shortest(node->right);
  }
  else if((node->left!=nullptr)&&(node->right==nullptr)){
    return 1+shortest(node->left);
  }
  else{
    return 1+min(shortest(node->left),shortest(node->right));
  }
}

int longest(TreeNode* node){
  if((node->left==nullptr)&&(node->right==nullptr)) return 0;
  else if((node->left==nullptr)&&(node->right!=nullptr)){
    return 1+longest(node->right);
  }
  else if((node->left!=nullptr)&&(node->right==nullptr)){
    return 1+longest(node->left);
  }
  else{
    return 1+max(longest(node->left),longest(node->right));
  }
}

int BST::getImbalance()
{
  if (root == nullptr) return -1;
  else {
    root->longestPathLength=longest(root);
    root->shortestPathLength=shortest(root);
    return root->getImbalance();
  }
}
bool added(TreeNode* current, int jc, int pr){
    if((current->price==pr)&&(current->JourneyCode==jc)){
        return false;
    }
    else{
        if((current->price==0)&&(current->JourneyCode==0)){
            current->price=pr;
            current->JourneyCode=jc;
            return true;
        }
        if(current->JourneyCode <= jc){
            if(current->right==nullptr){
                TreeNode *ri= new TreeNode(jc,pr,nullptr,nullptr,current);
                current->right=ri;
                return true;
            }
            else return added(current->right,jc,pr);
        }
        if(current->JourneyCode > jc){
            if(current->left==nullptr){
                TreeNode *le= new TreeNode(jc,pr,nullptr,nullptr,current);
                current->left=le;
                return true;
            }
            else return added(current->left,jc,pr);
        }
    }
}
bool BST::insert(int JourneyCode, int price)
{
  return added(root,JourneyCode,price);
}
TreeNode* found(TreeNode* cur,int jc, int pr){
    if((cur->JourneyCode==jc)&&(cur->price==pr)) return cur;
    else{
        if(cur->price > pr){
            if(cur->left==nullptr) return NULL;
            else{
                return found(cur->left,jc,pr);
            }
        }
        if(cur->price <= pr){
            if(cur->right==nullptr) return NULL;
            else{
                return found(cur->right,jc,pr);
            }
        }
    }
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if(found(root,JourneyCode,price)!=NULL) return true;
    else return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(!find(JourneyCode,price)) return false;
    else{
        TreeNode *t_r=found(root,JourneyCode,price);
        if((t_r->left==nullptr)&&(t_r->right==nullptr)){
            TreeNode *temp=t_r->parent;
            if(temp==nullptr) this->root=nullptr;
            else{
                if(temp->left==t_r) temp->left=nullptr;
                else temp->right=nullptr;
            }
        }
        else if((t_r->left!=nullptr)&&(t_r->right==nullptr)){
            TreeNode *temp=t_r->parent;
            t_r->left->parent=temp;
            if(temp==nullptr) this->root=t_r->left;
            else{
                if(temp->left==t_r) temp->left=t_r->left;
                else temp->right=t_r->left;
            }
        }
        else if((t_r->left==nullptr)&&(t_r->right!=nullptr)){
            TreeNode *temp=t_r->parent;
            t_r->right->parent=temp;
            if(temp==nullptr) this->root=t_r->right;
            else{
                if(temp->left==t_r) temp->left=t_r->right;
                else temp->right=t_r->right;
            }
        }
        else{
            TreeNode *cur=t_r->left;
            while(cur->right!=nullptr){
                cur=cur->right;
            }
            TreeNode *temp=cur;
            remove(cur->JourneyCode,cur->price);
            TreeNode *temp_parent=t_r->parent;
            temp->right=t_r->right;
            if(t_r->right!=nullptr) t_r->right->parent=temp;
            temp->left=t_r->left;
            if(t_r->left!=nullptr) t_r->left->parent=temp;
            temp->parent=temp_parent;
            if(temp_parent==nullptr) this->root=temp;
            else{
                if(temp_parent->left==t_r) temp_parent->left=temp;
                else temp_parent->right=temp;
            }
        }
        return true;
    }
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

