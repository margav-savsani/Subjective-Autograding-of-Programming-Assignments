#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <cmath>


template<typename T>
void Heap<T>::uplast()//this function is used to update last node when last node is removed from heap
{
  while(last->parent->left==last)
  {  
    last=last->parent;
    if(last->parent==nullptr)// checking whether last becomes root or not
    {
      while(last->right!=nullptr)
      {
        last=last->right;
      }
      last=last->parent;//going up the tree in the Heap
      return;
    }
  }
  last=last->parent->left;
  while (last->right!=nullptr)
  {
    last=last->right;//going down the tree in the Heap
  }
  last=last->parent;
}

template <typename T>
void Heap<T>::updatelast()//this  function  is used to update last node when a new node is inserted
{
if(last->right==nullptr)
  {
    return;
  }
  if(last->parent==nullptr)
  {
    last=last->left;
    return;
  }
  while(last->parent->left!=last)//going up in the tree
  {
    last=last->parent;
    if (last->parent==nullptr)
    {
      while (last->left!=nullptr)
      {
        last=last->left;
      }
      return;
    }
  }
  last=last->parent->right;
  while (last->left!=nullptr)
  {
    last=last->left;//going down the tree in the Heap
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (root==nullptr)//inserting a root when the root is initially nullptr
  {
    root= new TreeNode<T>(obj);
    last=root;
    return;
  }
  updatelast();
  TreeNode<T> *r=last;//stores the last element in a new tree node
  if(r->left==nullptr)
  {
    TreeNode<T> *c=new TreeNode<T>(obj);
    r->left=c;
    c->parent=r;
    r=r->left;
  }
  else
    {
      TreeNode<T> * c=new TreeNode<T>(obj);
      r->right=c;
      c->parent=r;
      r=r->right;
    }
  while (r->parent->object<r->object)
  {
      swap(r->parent->object,r->object);//swaps two elements if parent is less than child
      r=r->parent;
      if(r->parent==nullptr){return;}
  }
// printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {//deleltion of maximum element in heap

  // insert your code here
  if (root==nullptr)
  {
    return;
  }
  if(last==nullptr){root=nullptr;return;}
  if(last->right==nullptr)
  {
    if(last==root){
      swap(root->object,root->left->object);
      root->left==nullptr;
      return;
    }
    swap(last->left->object,root->object);
    last->left=nullptr;
    uplast();
  }
  else
  {
    swap(last->right->object,root->object);
    last->right=nullptr;
  }
  TreeNode<T>*t=root;
  while (true)
  {
  if(t->left==nullptr)
  {
    break;
  }
  if(t->right==nullptr)
  {
    swap(t->left->object,t->object);//swaps the element with the min of the two children
    break;
  }
  if(t->right->object < t->left->object)
  {
      swap(t->left->object,t->object);
      t=t->left;
      continue;
  }
  else
  {
    swap(t->right->object,t->object);
    t=t->right;
    continue;
  }

}
// printHeap(root);
return ;
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
      static string prefix="";
        static bool isLeft=0;
  if(node==root) {
    prefix = "";
    isLeft = 0;
  }
  // insert your code here
  if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );
        // print the value of the node
        cout << node->object << endl;
        bool s=isLeft;
        string str=prefix;
       prefix= str + (s ? "│   " : "    ");
       isLeft=1;
        TreeNode<T>*n=node;
        node=node->left;
        // enter the next tree level - left and right branch
        printHeap( node);// reccursive call for the left branch
        n=n->right;
        isLeft=0;
       prefix= str + (s ? "│   " : "    ");
        printHeap(n);// reccursive call for the right branch
    }

  return;
}

  
