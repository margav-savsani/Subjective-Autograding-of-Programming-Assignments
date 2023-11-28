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

bool BST::insert(int JourneyCode, int price)// checks for a null position according to the way of BST insert by comparing JourneyCodes
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
    TreeNode *x = root;    
    TreeNode *y = x;
    if(root->JourneyCode==0){
        root->price = price;
        root->JourneyCode = JourneyCode;
        return true;        
    }
    int code=root->JourneyCode;
    while(x!=nullptr){ 
        if(x->JourneyCode==JourneyCode)return false;
        if(code<JourneyCode){
            y=x;
            if(y->right==nullptr){
                x = new TreeNode(JourneyCode,price);
                y->right = x;
                break;
            }           
            x=y->right;
            code=x->JourneyCode;             
        }
        else{
            y=x;
            if(y->left==nullptr){
                x = new TreeNode(JourneyCode,price);
                y->left = x;
                break;
            } 
            x=y->left;
            code=x->JourneyCode;
        }
    }  
    return true;
  }
 
bool BST::find(int JourneyCode, int price)// finds using BST and JourneyCode
{
    TreeNode *x = root;
    int code=root->JourneyCode;
    TreeNode *y = x;
    while((x->JourneyCode!=JourneyCode)&&(x!=NULL)){
        if(code<JourneyCode){
            y=x;
            if(y->right==NULL)break;
            x=y->right;
            code=x->JourneyCode;
        }
        else{
            y=x;
            if(y->left==NULL)break;
            x=y->left;
            code=x->JourneyCode;
        }
    }
    if(x->JourneyCode==JourneyCode)return true;
    return false;
}
	
TreeNode* BST :: successor(TreeNode x){ // to find successor which is required while deleting an element
    if(x.right!=NULL){
        TreeNode *z = x.right;
        TreeNode *k = z;
        while(true){
            k=z;
            if(k->left == nullptr) break;
            z=k->left;
        }
        return k; 
    }
    TreeNode *y = x.parent;
    while((y!=NULL)&&(x.JourneyCode==(y->right)->JourneyCode)){
        x=*y;
        y=y->parent;
    }   
    return y;
}

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
  if(!find(JourneyCode,price))return false; 
    TreeNode *x = root;
    TreeNode *y = x;
    int code=root->JourneyCode;
    while((x->JourneyCode!=JourneyCode)&&(x!=NULL)){// goes to position of deleting node
        if(code<JourneyCode){
            y=x;
            x=y->right;
            code=x->JourneyCode;
        }
        else{
            y=x;
            x=x->left;
            code=x->JourneyCode;
        }
    }
    if((x->left==NULL)&&(x->right==NULL)){// case of having no children
        if(y->right==x)y->right=NULL;
        else y->left=NULL;
        return true;
       
    }
    if((x->left==NULL)&&(x->right!=NULL)){// case of having one child
        if(y->right==x)y->right=x->right;
        else if(y->left==x)y->left=x->right;
        else root=x->right; 
        return true; 
    }
    if((x->left!=NULL)&&(x->right==NULL)){// case of having one child
        if(y->right==x)y->right=x->left;
        else if(y->left==x) y->left=x->left;
        else root=x->left;
        return true;      
    }
    if((x->left!=NULL)&&(x->right!=NULL)){// case of having two children
        TreeNode *z = successor(*x);
        remove(z->JourneyCode,z->price);
        if(y->right==x)y->right=z;
        else if(y->left==x) y->left=z;
        else root=z;
        z->parent = x->parent;
        z->left = x->left;
        z->right = x->right;
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

