#ifndef BST_H
#include "BST.h"
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//=================================================


void heightUpdater(TreeNode *(*currentNode)){
  TreeNode*temp;
  temp=*currentNode;
  if(temp->parent==nullptr){
    if(temp->left==nullptr && temp->right!=nullptr){
      temp->height=temp->right->height+1;
    }
    else if(temp->left!=nullptr && temp->right==nullptr){
      temp->height=temp->left->height+1;
    }  
    else{
      temp->height=max(temp->left->height,temp->right->height)+1;
    }  
    return;
  }
  else{
    if(temp->left==nullptr && temp->right!=nullptr){
      temp->height=temp->right->height+1;
    }
    else if(temp->left!=nullptr && temp->right==nullptr){
      temp->height=temp->left->height+1;
    }  
    else{
      temp->height=max(temp->left->height,temp->right->height)+1;
    }  
    temp=(*currentNode)->parent;
    return heightUpdater(&temp);
  }
}



bool actualInsert(int JourneyCode, int price, TreeNode *(*currentNode), TreeNode *(*currentParent))
{ 
  //Has to create a recursion to check and update height,,,

  BST a(1,1);
  TreeNode*temp=new TreeNode(JourneyCode, price);
  // cout<<"Reached checkpoint 2 \n";
  if (*currentNode == nullptr)
  {
    // cout<<"Address:"<<&*currentNode<<endl;
    *currentNode = new TreeNode(JourneyCode, price);
    //, nullptr, nullptr, (*currentParent));
    (*currentNode)->parent = *currentParent;
    heightUpdater(&((*currentNode)->parent));
    return true;
  }
  //(*currentNode)->price > price && (*currentNode)->price != 0
  else if (a.BSTLessThan(temp,(*currentNode)))
  {
    // cout<<"Going left in insert \n";
    return actualInsert(JourneyCode, price, &((*currentNode)->left), &(*currentNode));
  } //
  else if (a.BSTLessThan((*currentNode),temp))
  {
    // cout<<"Going right in insert \n";
    return actualInsert(JourneyCode, price, &((*currentNode)->right), &(*currentNode));
  }
  else
  {
    return false;
  }
};

bool actualFind(int JourneyCode, TreeNode *currentNode, TreeNode *currentParent)
{ BST a(1,1);
  // cout<<"Reached checkpoint 4 \n";
  TreeNode*temp=new TreeNode(JourneyCode, 0);
  if (currentNode == nullptr)
  {
    return false;
  }
  else if (currentNode->JourneyCode == JourneyCode)
  {
    return true;
    // actualInsert(JourneyCode,price,currentNode->left,currentNode);
  }
  else if (a.BSTLessThan((currentNode),temp))
  {
    // cout<<"Going right in find \n";
    return actualFind(JourneyCode, currentNode->right, currentNode);
  }
  else if (a.BSTLessThan(temp,(currentNode)))
  {
    // cout<<"Going left in find \n";
    return actualFind(JourneyCode, currentNode->left, currentNode);
  }
}

bool actualRemove(int JourneyCode, TreeNode *(*currentNode), TreeNode *(*currentParent))
{ BST a(1,1);
  TreeNode*temp2=new TreeNode(JourneyCode, 0);
  if ( (*currentNode)->JourneyCode == JourneyCode)
  {
    if ((*currentNode)->right == nullptr && (*currentNode)->left == nullptr)
    {
      (*currentNode) = nullptr;
      return true;
    }
    // if has one child only either right or left
    else if ((*currentNode)->left == nullptr && (*currentNode)->right != nullptr)
    {
      (*currentNode) = (*currentNode)->right;
    }
    else if ((*currentNode)->left != nullptr && (*currentNode)->right == nullptr)
    {
      (*currentNode) = (*currentNode)->left;
      return true;
    }
    // if has two childs;
    else if ((*currentNode)->left != nullptr && (*currentNode)->right != nullptr)
    {
      TreeNode *temp;
      temp = (*currentNode)->left;
      if (temp->right == nullptr)
      {
        return false;
      }
      // temp=(*currentNode)->left->right;
      while (true)
      {
        if (temp != nullptr && temp->right == nullptr)
        {
          // temp->parent->right=nullptr;
          temp->parent->left = nullptr;
          temp->parent = nullptr;
          temp->parent = (*currentNode)->parent;
          temp->right = (*currentNode)->right;
          temp->left = (*currentNode)->left;
          *currentNode = temp;
          return true;
        }
        else
        {
          temp = temp->right;
        }
      }
    }
  }
  else if (a.BSTLessThan(temp2,(*currentNode)))
  {
    return actualRemove(JourneyCode, &((*currentNode)->left), &(*currentNode));
  }
  else if (a.BSTLessThan((*currentNode),temp2))
  {
    return actualRemove(JourneyCode, &((*currentNode)->right), &(*currentNode));
  }
}

//=============================================

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
  if (find(jrnyCode))
  {
    return false;
  }
  // cout<<"Reached checkpoint 1 \n";
  // if (root->JourneyCode == 0)
  // {
  //   root->JourneyCode = jrnyCode;
  //   root->price = price;
  //   return true;
  // }
  return actualInsert(jrnyCode, price, &root, nullptr);
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
  if(actualFind(jrnyCode, root, nullptr)){
    return 1;
  }
  else return -1;
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

  if (!find(jrnyCode))
  {
    return false;
  }
  else
  {
    return actualRemove(jrnyCode, &root, nullptr);
  }
}
