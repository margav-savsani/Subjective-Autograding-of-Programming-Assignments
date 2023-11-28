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
template <typename T>
class StackNode{
//element of my_stack
public:
    T val;
    StackNode<T>* next;
    StackNode(T t, StackNode<T>* ptr):val{t},next{ptr}{}
};
template <typename T>
class my_stack{
//stack implemented as a linked list
    StackNode<T>* head = NULL;
public:
    bool empty(){ //returns if the stack is empty
        return (head!=NULL);
    }
    void push(T ptr){//adds an element to the top of the stack
        StackNode<T> *temp = head;
        head = new StackNode<T>{ptr, temp};
    }
    void pop(){ //removes the last added element from the stack
        StackNode<T>* temp = head;
        if(head==NULL) throw "Pop called on empty stack";
        head = head->next;
        delete temp;
    }
    T top(){//returns the value of the most recently added element of the stack
        if(head==NULL) throw "Pop called on empty stack";
        return head->val;
    }
};
BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root = root; }
bool BST::insert(int jrnyCode, int price)
{
   if(root == NULL){
        root = new TreeNode(jrnyCode,price,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    if(!find(jrnyCode))return false;
    TreeNode *curr = root;
    TreeNode *temp = new TreeNode(jrnyCode,price,NULL,NULL,NULL);
    while(true){
        curr->height++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if  is greater
        if(BSTLessThan(curr,temp)){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = temp;
                break;
                
            }
            }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = temp;
                break;
            }
            }
    }
  //  this->printBST("",false);
    return true;
 

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    TreeNode * temp = new TreeNode(jrnyCode,0);
  // Implement find in BST
    if(root==NULL)return -1;
    TreeNode* curr = root;
    while(true){
        if(curr==NULL){break;}
        else if(curr->getcode()==jrnyCode){
            return curr->getprice();
        }
        else if(BSTLessThan(temp,curr)){
            curr = curr->left;
        }
        else{
                curr = curr->right;
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
    if(!find(jrnyCode))return false;
    
    TreeNode* curr = root;
    bool last = false;
    TreeNode *temp = new  TreeNode(jrnyCode,0);
    // finding the  node to be deleted
    while(true){
        curr->height--; // Decrement size of subtree for each parent node!
        if(curr->getcode()==jrnyCode){
            break;
        }else if(BSTLessThan(temp,curr)){
            curr = curr->left;
            last = true;
        }else{
            curr = curr->right;
            last = false;
        }
    }
    // If it has no left child, just replace the node with its right child!
    if(curr->left==NULL){
    
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->right;
            }
            else{
                curr->parent->right = curr->right;
            }
            if(curr->right!=NULL){
              curr->right->parent = curr->parent;
            }
            delete curr;
        }else{
            root = curr->right;
            delete curr;  
        }
    }else if(curr->right==NULL){
        //   If it has no right child, just replace it with left child
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->left;
            }
            else{
                curr->parent->right = curr->left;
            }
            curr->left->parent = curr->parent;
            delete curr;
        }else{
            root = curr->left;
            delete curr;     
        }
    }else{
        // If its has both left and right children

        TreeNode *todel = curr; // Marking the node which is to be deleted
        
        // Find its predecessor
        curr = curr->left;
        last = false;
        
        
        while(curr->right!=NULL){
            
            curr->height--;
            curr = curr->right;
            last = true;
        }

        // Swap the node with its predecessor
        todel= curr;
        if(!last){
            curr->parent->left = curr->left;
        }else{
            curr->parent->right = curr->left;
        }
        curr->left->parent = curr->parent;
        
        // Delete the node which previously represented the predecessor
        delete curr;
        
    }
  
    return true; 
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  
}


