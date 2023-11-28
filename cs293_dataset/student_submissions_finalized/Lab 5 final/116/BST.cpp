#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.


bool BST::insert(int jrnyCode, int price)
{ TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode* node;
  node=new TreeNode(jrnyCode,price);

  if(root==nullptr){
    root=new TreeNode(jrnyCode,price);
    return true;
  }

  
  while (currNode != nullptr) 
  {
    if (BSTLessThan(currNode,node)) 
    {
     currNode->height=currNode->height+1;
      
      parentOfCurrNode = currNode;
      currNode = currNode->right;
      
      
    }
    else if (BSTLessThan(node,currNode)) 
    {
     currNode->height=currNode->height+1;
      
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      
      
    }
    else // currNode->JourneyCode == JourneyCode
    return false;
    
  }
  if(currNode== nullptr)
  {
   currNode=new TreeNode(jrnyCode,price);
    
    if (BSTLessThan(currNode,parentOfCurrNode)){
     parentOfCurrNode->left=currNode;
    }
    else
   {
     parentOfCurrNode->right=currNode;
     return true;
   }
     
  }  
  return true;  
}      
 
 

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  
  


 

int BST::find(int jrnyCode)
{ int Price;
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode* node;
  node=new TreeNode(jrnyCode,0); 
  if(currNode==nullptr)
  return -1;
  while (currNode != nullptr) 
  {
    if (BSTLessThan(currNode,node)) 
    {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
      
      
    }
    else if (BSTLessThan(node,currNode)) 
    {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      currNode->height=currNode->height+1;
      
    }
    
    else  
    {// currNode->JourneyCode == JourneyCode
       Price= currNode->getPrice();
      
    }


  }
 return Price;
}


// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.
TreeNode* BST::findSuccessor(TreeNode* node)
{
  TreeNode* current = node;
  
   
  while (current && current->left != NULL)
  {
   current = current->left;
  }
  return current;
}

bool BST::remove(int jrnyCode)
{       
  /*TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode* node;
  node=new TreeNode(jrnyCode,0); 
  if(currNode==NULL)return false;
      
  while (currNode != nullptr) 
  {
    if (BSTLessThan(currNode,node))
    {
     
     parentOfCurrNode = currNode;
     currNode = currNode->right;
          
      
    }
    else if (BSTLessThan(node,currNode))
    {
     currNode->height=currNode->height-1;
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      
    }
    else 
    { // currNode->JourneyCode == JourneyCode
      
   // node has no child
        
   if (currNode->left==NULL && currNode->right==NULL)
   free(root);
        
   // node with only one child or no child
   else if (currNode->left == NULL) {
   TreeNode* temp1 = currNode->right;
   temp1->parent=parentOfCurrNode;
            
   &temp1==&currNode;
             
                 
   free(currNode);
           
            
   }
   else if (currNode->right == NULL) 
   {
    TreeNode* temp2 = currNode->left;
   temp2->parent=parentOfCurrNode;
   &temp2==&currNode;
             
   free(currNode);
            
    }
    else 
    {
          
    TreeNode* temp1 = findSuccessor(currNode->right);
    if (temp1->left!=NULL){
    TreeNode* temp2=temp1->left;
    &temp2==&temp1;
   temp2->parent=temp1->parent;
                      
  
   }   
        
   currNode=new TreeNode(
        
   currNode->price = temp1->price;
          
    currNode->JourneyCode=temp1->JourneyCode;
            
          
   free(temp1);
      
      
  }*/
       
    
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  

  return true;
}


