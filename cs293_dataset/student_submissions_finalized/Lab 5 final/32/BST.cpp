 #ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
bool BST::insert(int jrnyCode, int price)
{
  TreeNode *node = new TreeNode(jrnyCode, price);
  // Adding the first node
  if(root == nullptr)
  {
    root = node;
    return true;
  }
  
  TreeNode *current = root;
  
  while(true)
  {
    // If node is less than current node
    if(BSTLessThan(node, current))
    {
      if(current->left != nullptr)      
        current = current->left;
            
      else
      {
        updateBSTParentChild(node, current, true);
        break;
      }
    }
    
    // If node is greater than current node
    else
    {
      if(current->right != nullptr)     
        current = current->right;
            
      else
      {
        updateBSTParentChild(node, current, false);
        break;
      }
    } 
  }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
int BST::find(int jrnyCode)
{
  if(root == nullptr)
  return false;
  
  TreeNode* current = root;
  TreeNode *node = new TreeNode(jrnyCode,-1);
  
  while(true)
  {
    //If node is less than current node
    if(BSTLessThan(node, current))
    {
      if(current->left == nullptr)      
        return -1;
            
      else     
        current = current->left;
      
    }
    
    // If current node is less than node
    else if(BSTLessThan(current, node))
    {
      if(current->right == nullptr)     
        return -1;
      
      
      else      
        current = current->right;      
    }
    
    else   
      return current->getprice();    
  }
}


bool BST::remove(int jrnyCode)
{
  return true;
}


