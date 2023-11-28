#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void Heap<T>::updateAfterDelete()
{
  if(last==root)
  {
    root=nullptr;
    last=nullptr;
    nextInsert=nullptr;
    nextleftInsert=false;
  }
  nextInsert=last->parent;
  if(last->parent->left==last)
  {
    nextleftInsert=true;
    while(last->parent!=nullptr && last->parent->left==last)
    {
      last=last->parent;
    }
    if(last->parent!=nullptr)
    {
      last=last->parent->left;
    }
    last=last->right;
    while(last->right!=nullptr)
    {
      last=last->right;
    }
  }
  else
  {
    nextleftInsert=false;
    last=last->parent->left;
  }
  return;
}


template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *newNode=new TreeNode<T>(obj);
  last=newNode;
  if(root==nullptr)
  {
    root=newNode;
    nextInsert=root;
    nextleftInsert=true;
    return;
  }
  newNode->parent=nextInsert;
  if(nextleftInsert)
  {
    nextInsert->left=newNode;
    nextleftInsert=false;
  }
  else
  {
    nextInsert->right=newNode;
    nextleftInsert=true;
    while(nextInsert->parent!=nullptr && nextInsert->parent->right==nextInsert)
    {
      nextInsert=nextInsert->parent;
    }
    if(nextInsert->parent!=nullptr)
    {
      nextInsert=nextInsert->parent->right;
    }
    while(nextInsert->left!=nullptr)
    {
      nextInsert=nextInsert->left;
    }
  }

  return;
}


template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(last==nullptr)
    return;
  swap(last->object, root->object);
  updateAfterDelete();
  TreeNode<T> *curr=root;
  while(true)
  {
    if(curr->left==nullptr)
      return;
    else if(curr->right==nullptr)
    {
      if(curr->object < curr->left->object)
        swap(curr->object, curr->left->object);
      return;
    }
    else
    {
      if(curr->left->object < curr->right->object)
      {
        if(curr->object < curr->right->object)
        {
          swap(curr->object, curr->right->object);
          curr=curr->right;
        }
        else
          return;
      }
      else
      {
        if(curr->object < curr->left->object)
        {
          swap(curr->object, curr->left->object);
          curr=curr->right;
        }
        else
          return;
      }
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
