#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//
//

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    
      
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if (grandParentNode != root)
  {
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode)
    {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode)
    {
      isGPLeftChild = false;
    }
    else
    {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

        
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }

  else root = parentNode;
      updateAVLParentChild(currNode, parentNode, true);
      TreeNode *T3 = parentNode->right;
      updateAVLParentChild(grandParentNode, parentNode, false);
      updateAVLParentChild(T3, grandParentNode, true);

      // currNode -> height = max(currNode -> height - 1, 0);
      grandParentNode -> height = grandParentNode -> height -2;

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    
      
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
      if (root != grandParentNode)
  {
    /* code */
  
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

      //
        
      updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }

  else root = currNode;
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    

    currNode -> height = currNode -> height + 1;
    parentNode -> height = parentNode -> height - 1;
    grandParentNode -> height = grandParentNode -> height - 2;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (grandParentNode != root)
  {
  
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);
  }

  else root = currNode;
  updateAVLParentChild(currNode->left,grandParentNode,false);
  updateAVLParentChild(currNode->right,parentNode,true);
  updateAVLParentChild(parentNode,currNode,false);
  updateAVLParentChild(grandParentNode,currNode,true);

    currNode -> height = currNode -> height + 1;
    parentNode -> height = parentNode -> height - 1;
    grandParentNode -> height = grandParentNode -> height - 2;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  if(root != grandParentNode){
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    
    updateAVLParentChild(parent,greatGrandParentNode,isGPLeftChild);
  }

  else root = parent; 
  updateAVLParentChild(parent->left,grandParentNode,false);
  updateAVLParentChild(grandParentNode,parent,true);
  updateAVLParentChild(currNode,parent,false);
  
      // currNode -> height = max(currNode -> height - 1, 0);
  grandParentNode -> height = grandParentNode -> height -2;
  return true;
}


int maxHeight(TreeNode* node1, TreeNode* node2){
  if (node1 == nullptr && node2 != nullptr)
  {
    return node2 -> height +1 ;
  }
  else if (node1 != nullptr && node2 == nullptr)
  {
    return node1 -> height +1;
  }
  else if(node1 == nullptr && node2 == nullptr)
  {
    cout << "comaparing two null pointers";
    return -1;
  }
  else{
    return max(node1->height +1,node2->height+1);
  }
  
  
}

void AVLTree::updateHeights(TreeNode* node){
  while (node != root)
  {
    if (node -> parent -> height == maxHeight(node -> parent -> left, node -> parent -> right)) break;

    else
    {
      node -> parent -> height = maxHeight(node -> parent -> left, node -> parent -> right);
      node = node -> parent;
    }
  }
}

bool isParentHeightChanged(TreeNode* node){
  if (node ->parent-> height == max(node -> height +1, node -> parent -> height)) return false;
  return true;  
}

bool checkParentImbalance(TreeNode* node){
  if (node -> parent -> left != nullptr && node -> parent -> right != nullptr)
  {
    if(abs((node -> parent -> left -> height) - (node -> parent -> right -> height)) > 1) return true;
    return false;
  }

  if (node -> height >= 1)
  {
    return true;
  }

  return false;
  
  
  
}

void AVLTree::rotate(TreeNode* parent, TreeNode* node, TreeNode* prevNode){

  if (parent->left == node && node->left == prevNode)
  {
    rotateLeftLeft(prevNode, node, parent);
  }
  else if (parent->right == node && node->right == prevNode)
  {
    rotateRightRight(prevNode, node, parent);
  }
  else if (parent->left == node && node->right == prevNode)
  {
    rotateLeftRight(prevNode, node, parent);
  }
  else if (parent->right == node && node->left == prevNode)
  {
    rotateRightLeft(prevNode, node, parent);
  }
}

bool AVLTree::correctImbalance(TreeNode* node){
  TreeNode* prevNode = nullptr;
  while (node != root)
  {
    if(!isParentHeightChanged(node)) break;
    else if (checkParentImbalance(node)) 
    {
      node -> parent -> height = node -> height + 1;
      rotate(node->parent,node,prevNode);
    }
    else {
      node -> parent -> height = node -> height + 1;
      prevNode = node;
      node = node -> parent;
    }
    
  }
  return true; 
}

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *ptr = root;
  cout << ptr << endl; //debugging
  TreeNode *ptr2 = nullptr;
  TreeNode *node = new TreeNode(jrnyCode,price);
    
    while (ptr != nullptr)
  {
      if (AVLLessThan(node, ptr))
      {
          ptr2 = ptr;
          ptr  = ptr -> left;
      }

      else if (ptr -> getJourneyCode() == node -> getJourneyCode())
      {
      return false;
      }
       

      else
      {
          ptr2 = ptr;
          ptr = ptr -> right;
      }
  }

  if (ptr2 == nullptr)
  {
      root = node;
  }
    
  else if(AVLLessThan(node, ptr2)) {
    updateAVLParentChild(node, ptr2, true);
  }

  else
  {
    updateAVLParentChild(node, ptr2, false);
  }

  //print(); //debugging
  // updateHeights(node);
  //print(); //debugging
  // cout << "calling imbalance for - " << node ->getJourneyCode() << endl; //debugging
  correctImbalance(node);

  return true;
}


int AVLTree::find(int jrnyCode)
{
      
          
    TreeNode *find_node = new TreeNode(jrnyCode,0);
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
       if (ptr -> getJourneyCode() == find_node -> getJourneyCode())        {
        return true;
       }

       else if (AVLLessThan(find_node, ptr))
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    
        
    }
    return false;
}


//

bool AVLTree::remove(int jrnyCode)
{
    return true;
}


