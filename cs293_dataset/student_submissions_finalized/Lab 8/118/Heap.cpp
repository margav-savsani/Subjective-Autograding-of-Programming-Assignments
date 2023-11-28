#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root->object=obj;
    root->parent=root;
  }
  else{
    TreeNode<T> *node=new TreeNode<T>(obj);
    TreeNode<T> *temp=root->parent;
    while(temp!=root){
      if(temp->parent->left==temp)
        break;
      temp=temp->parent;
    }
    if(temp==root){
      while(temp->left!=nullptr)
        temp=temp->left;
      temp->left=node;
      node->parent=temp;
      root->parent=node;
    }
    else if(temp->right=nullptr){
      temp->right=node;
      node->parent=temp;
      root->parent=node;
    }
    else{
      temp=temp->right;
      while(temp->left!=nullptr)
        temp=temp->left;
      temp->left=node;
      node->parent=temp;
      root->parent=node;
    }
    while(node->object>node->parent->object){
      T tempobj=node->object;
      node->object=node->parent->object;
      node=node->parent;
      node->object=tempobj;
      if(node==root)
        break;
    }
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

//****************************************************************************************

  TreeNode<T> *temp=root->parent;
  if(temp==root){
    delete root;
    root=nullptr;
  }
  else{
    while(temp!=root){
      if(temp==temp->parent->right)
        break;
      temp=temp->parent;
    }
    if(temp==root){
      while(temp->right!=nullptr)
        temp=temp->right;
    }
    else{
      temp=temp->left;
      while(temp->right!=nullptr)
        temp=temp->right;
    }

//****************************************************************************************

    root->object=root->parent->object;
    if(root->parent->parent->right==root->parent)
      root->parent->parent->right=nullptr;
    else
      root->parent->parent->left=nullptr;
    delete root->parent;
    root->parent=temp;

//****************************************************************************************

    temp=root;
    while(true){
      if(temp->left!=nullptr && temp->left->object>temp->object){
        if(temp->right!=nullptr && temp->right->object>temp->left->object){
          T tempobj=temp->object;
          temp->object=temp->right->object;
          temp=temp->right;
          temp->object=tempobj;
        }
        else{
          T tempobj=temp->object;
          temp->object=temp->left->object;
          temp=temp->left;
          temp->object=tempobj;
        }
      }
      else if(temp->right!=nullptr && temp->right->object>temp->object){
        T tempobj=temp->object;
        temp->object=temp->right->object;
        temp=temp->right;
        temp->object=tempobj;
      }
      else
        break;
    }

//****************************************************************************************

  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  if(root==nullptr){
    cout<<"Empty HEAP"<<endl;
    return;
  }

  static string spacer="";

  if (spacer=="")
    cout<<node->object<<endl;
  else
    cout<<spacer.substr(0,spacer.length()-4)<<"|---"<<node->object<<endl;
  if(node->right!=nullptr){
    spacer=spacer+"|   ";
    printHeap(node->right);
    spacer=spacer.substr(0,spacer.length()-4);
  }
  else if(node->left!=nullptr){
    spacer=spacer+"|   ";
    printHeap(node->left);
    spacer=spacer.substr(0,spacer.length()-4);
  }

  return;
}

  
