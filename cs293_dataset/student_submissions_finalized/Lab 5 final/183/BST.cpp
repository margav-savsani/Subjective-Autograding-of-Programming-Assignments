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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  int i=1;
  if(root==NULL){root=new TreeNode(jrnyCode,price);
                 return true;} //if root is null then just insert at root
  TreeNode *z=new TreeNode(jrnyCode,price);
  while (currNode != nullptr) {
  if (BSTLessThan(currNode,z)) {
      i=i+1;
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
   else if (BSTLessThan(z,currNode)) {
      i=i+1;
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { 
      return false;
    }
  }
  currNode=new TreeNode(jrnyCode,price);
  currNode->parent=parentOfCurrNode;
  if (parentOfCurrNode==NULL){root=currNode;}                    
       else if(BSTLessThan(currNode,parentOfCurrNode)){parentOfCurrNode->left=currNode;}   //updating child of parent to inserting node
            else{parentOfCurrNode->right=currNode;}
  //updating heights of necessary nodes
  while(parentOfCurrNode!=NULL){
  if(parentOfCurrNode->left==currNode){if ((parentOfCurrNode->right!=NULL)&&(parentOfCurrNode->height>currNode->height)){break;} //check if height of parent should be changed 
                                       else parentOfCurrNode->height++;                 //if yes change its height then go to its respective parent
                                            parentOfCurrNode=parentOfCurrNode->parent;
                                            currNode=currNode->parent;}
  else if(parentOfCurrNode->right==currNode){
                                     if ((parentOfCurrNode->left!=NULL)&&(parentOfCurrNode->height>currNode->height)){break;}  //check if height of parent should be changed
                                       else parentOfCurrNode->height++;                     //if yes change its height then go to its respective parent
                                            parentOfCurrNode=parentOfCurrNode->parent;
                                            currNode=currNode->parent;}
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
   struct TreeNode *x=root;
   TreeNode *z=new TreeNode(jrnyCode,0);
      while(x!=NULL){
             if (BSTLessThan(z,x)){x=x->left;}       //if JourneyCode is less then search in left subtree
             else if(BSTLessThan(x,z)){x=x->right;} //if JourneyCode is more/equal then search in right subtree
             else{return x->getprice();}                     //if found 
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

  if(find(jrnyCode)==-1){return false;}
    else{TreeNode *x=root;
         TreeNode *z=new TreeNode(jrnyCode,0);
         while(x!=NULL){
             if (BSTLessThan(z,x)){x=x->left;}       //if JourneyCode is less then search in left subtree
             else if(BSTLessThan(x,z)){x=x->right;} //if JourneyCode is more/equal then search in right subtree
             else {break;}}
    TreeNode* prev = x->parent;
    if (x->left == NULL && x->right == NULL){
       if(prev==NULL){root=NULL;return true;}
       if(x==prev->left){prev->left=NULL;}
       else{prev->right=NULL;}
       free(z);
    }
    else if (x->left == NULL || x->right == NULL) {
        TreeNode* newx;
        if (x->left == NULL){newx = x->right;}
        else {newx = x->left;}
        if (prev == NULL){root=newx;root->parent=NULL;return true;}
        if (x == prev->left){prev->left = newx;newx->parent=prev;}
        else {prev->right = newx;newx->parent=prev;}
        free(x);
    }
    else {
        TreeNode* p = NULL;
        TreeNode* temp=NULL;
        // Compute the inorder successor
        temp = x->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
        if (p != NULL){p->left = temp->right;}
        else {x->right = temp->right;}
        //x->getprice() = temp->getprice();
        //x->getcode() = temp->getcode();
        free(temp);
    }
    return true;}
}
void BST::preorder(TreeNode *y){
        if(y==NULL) {return;}
        else {cout<<y->getcode()<<" "<<y->height<<endl;
              preorder(y->left);
              preorder(y->right);
              }
        return;      }
void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==1){
           TreeNode *x=root;
           preorder(x);  
           cout<<endl;         
    }
    return; }

