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
void BST::updateLength(TreeNode* node){
  // this fucntion update the lengths of the shortest and longest paths of the node by 
  //using the lengths of its 2 children recursively.shortest length is taken 0 
  //if any one the children is null.
  int sl,ll,sr,lr;
  {if(node->left==NULL){
    sl=0;
    ll=0;
  }
  else{
    sl=node->left->shortestPathLength+1;
    ll=node->left->longestPathLength+1;
  }}
  {if(node->right==NULL){
    sl=0;
    ll=0;
  }
  else{
    sl=node->right->shortestPathLength+1;
    ll=node->right->longestPathLength+1;
  }}
  node->longestPathLength=max(ll,lr);
  node->shortestPathLength=min(sl,sr);
  if(node==root)return;
  updateLength(node->parent);
}
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  TreeNode* current=root;
    if(root==NULL){
        root=new TreeNode(JourneyCode,price);
        root->longestPathLength=0;
        root->shortestPathLength=0;
        return true;
    }
    
    while(true){
        if(current->JourneyCode==JourneyCode){
            if(current->price==price)return false;
            if(current->left==NULL){
                current->left=new TreeNode(JourneyCode,price,NULL,NULL,current);
                current->left->longestPathLength=0;
                current->left->shortestPathLength=0;
                updateLength(current->left);
                return true;
            }
            else{
                current=current->left;
                continue;
            }

        }
        if(current->JourneyCode>JourneyCode){
            if(current->left==NULL)break;
            current=current->left;
            continue;
        }
        if(current->JourneyCode<JourneyCode){
            if(current->right==NULL)break;
            current=current->right;
            continue;
        }

    }
    if(current->JourneyCode>JourneyCode){
        current->left= new TreeNode(JourneyCode,price,NULL,NULL,current);
        current->left->longestPathLength=0;
        current->left->shortestPathLength=0;
        updateLength(current->left);
        return true;
    }
    if(current->JourneyCode<JourneyCode){
        current->right= new TreeNode(JourneyCode,price,NULL,NULL,current);
        current->right->longestPathLength=0;
        current->right->shortestPathLength=0;
        updateLength(current->right);
        return true;
    }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode* current=root;
  while(true){
        if(current==NULL)return false;
        else if (JourneyCode==current->JourneyCode){
          if(price==current->price)return true;
          else current=current->left;
        }
        else if(JourneyCode>current->JourneyCode){
            if(current->right==NULL)return false;
            current=current->right;
        }
        else if(current->JourneyCode>JourneyCode){
            if(current->left==NULL)return false;
            current=current->left;
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
    
    TreeNode* current=root;
    TreeNode* parent=NULL;
    bool left=false;
    
    while(true){
        
        if(current==NULL)return false;   
        if(current->JourneyCode==JourneyCode){
            if(current->price==price){
                if(current==root){
                    
                    if(current->left==NULL && current->right==NULL){
                    
                    root=NULL;
                    return true;
                    }
                    
                    if(current->left==NULL){
                        root=current->right;
                        return true;
                    }
                    
                    if(current->right==NULL){
                        root=current->left;
                        return true;
                    }
                    

                }
                
                if(current->left==NULL && current->right==NULL){
                    
                    if(left)parent->left=NULL;
                    else parent->right=NULL;
                    updateLength(parent);
                    return true;
                }
                if(current->left==NULL){
                    if(left)parent->left=current->right;
                    else parent->right=current->right;
                    updateLength(parent);
                    return true;
                }
                if(current->right==NULL){ 
                    if(left)parent->left=current->left;
                    else parent->right=current->left;
                    updateLength(parent);
                    return true;
                }
                
                TreeNode* temp=current->left;
                
                if(temp->right==NULL){
                    
                    current->left=temp->left;
                    current->JourneyCode=temp->JourneyCode;
                    current->price=temp->price;
                    updateLength(current);
                    return true;
                }
                while(temp->right!=NULL)temp=temp->right;
                current->JourneyCode=temp->JourneyCode;
                current->price=temp->price;
                temp->parent->right=temp->left;
                updateLength(temp->parent);
                return true;
            

            }
            else{
                    current=current->left;
                    continue;
            }

        }
        if(current->JourneyCode>JourneyCode){
            if(current->left==NULL)return false;
            parent=current;
            current=current->left;
            left=true;
        }
        if(current->JourneyCode<JourneyCode){
            if(current->right==NULL)return false;
            parent=current;
            current=current->right;
            left=false;
        }

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

