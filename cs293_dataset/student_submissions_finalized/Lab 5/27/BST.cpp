#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
  return true;
}


