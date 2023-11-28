#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <bits/stdc++.h>

template<typename T>
void swap( TreeNode<T> *node1,TreeNode<T> *node2)
{
  T sample=node1->object;
  node1->object=node2->object;
  node2->object=sample;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *node=new TreeNode<T>(obj);
  if (root == nullptr)
  {
    num++;
    root=node;
    return;
  }
  int h=log2(num);
  int way=num-pow(2,h+1)+1;
  if (way ==0)
  {
    h=h+1;
  }
  way=num-pow(2,h)+1;
  bool *path=new bool[h+1];
  //finding the way by bits convertion
  for (int i=0;i<h+1;i++)
  {
    path[i]=way%2;
    way=way/2;
  }
  TreeNode<T> *sample=root;
  for (int i=h-1;i>0;i--)
  {
    if (path[i])
      sample=sample->right;
    else
      sample=sample->left;
    //cout<<sample->object<<endl;
  }
  if (path[0])
    sample->right=node;
  else
    sample->left=node;
  node->parent=sample;
  //incr num
  num++;
  while (node->parent != nullptr) 
  {
    if (node->parent->object < node->object)
      swap<T>(node,node->parent);
    node=node->parent;
  }
  return;
}
template<typename T>
void Heap<T>::delMax() {
  T *a;
  if (root== nullptr)
    return;
  if (num==1)
  {
    num--;
    root=nullptr;
    return;
  }
  num--;
  int h=log2(num);
  int way=num-pow(2,h+1)+1;
  if (way ==0)
  {
    h=h+1;
  }
  way=num-pow(2,h)+1;
  bool *path=new bool[h+1];
  for (int i=0;i<h+1;i++)
  {
    path[i]=way%2;
    way=way/2;
  }
  TreeNode<T> *sample=root;
  for (int i=h-1;i>=0;i--)
  {
    if (path[i])
      sample=sample->right;
    else
      sample=sample->left;
    //cout<<sample->object<<endl;
  }
  swap<T>(root,sample);
  if (sample->parent->left == sample)
    sample->parent->left=nullptr;
  else
    sample->parent->right=nullptr;
  TreeNode<T> *node=root;
  //heapifying
  while(node->left != nullptr && node->right !=nullptr)
  {
    if (node->right != nullptr)
    {
      if (node->left->object < node->right->object)
      {
        if (!(node->right->object < node->object ))
        {
          swap(node,node->right);
          node=node->right;
        }
        else
          break;
      }
      else
      {
        if (!(node->left->object < node->object ))
        {
          swap(node,node->left);
          node=node->left;
        }
        else
          break;
      }
    }
    else
    {
      if (!(node->left->object < node->object))
      {
        swap(node,node->left);
        node=node->left;
      }
      else
        break;
    }
  }
  return;
}
template<typename T>
bool Heap<T>::checkheap(TreeNode<T> *node)
{
  if (node == nullptr)
    return false;
  if (node->left != nullptr && node->right != nullptr)
    if (node->left->object < node->object && node->right->object < node->object)
      return true;
  else if (node->left !=nullptr)
    if (node->left->object < node->object)
      return true;
  else
    return true;
  return false;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  if (node==nullptr)
    return;
  if(node->left ==nullptr && node->right == nullptr)
    return;
  if(node->right == nullptr)
  {
    if (node->object < node->left->object)
    {
      swap<T>(node,node->left);
      Heapify(node->left);
    }
    else
      return;
  }
  else
  {
    if (node->left->object < node->right->object )
    {
      if (node->object < node->right->object)
      {
        swap<T>(node,node->right);
        Heapify(node->right);
      }
      else
        return;
    }
    else
    {
      if (node->object < node->left->object)
      {
        swap<T>(node,node->left);
        Heapify(node->left);
      }
      else
        return; 
    }
  }
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if (node==nullptr)
    return;
  printH("  ");
}
template<typename T>
void Heap<T>::printH(const string& prefix, bool isLeft)
{
    if (root == nullptr)
      return;
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printH( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printH( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
//by saran 210050036