#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

//****************************************************************************************
//-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//****************************************************************************************

//Function to insert elements into the heap
template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *node=new TreeNode<T>(obj); //Node to store the object
  //To check whether the heap is empty or not
  if(root==nullptr){
    root=node;
    root->parent=root;
  }

//****************************************************************************************

  //To find the location where the node is to be inserted
  else{
    TreeNode<T> *temp=root->parent; //Temporary node to find where the new node is to be added
    //while loop to find the root of the subtree whose rightmost node is the last occupied node
    while(temp!=root){
      if(temp->parent->left==temp)
        break;
      temp=temp->parent;
    }
    //To check if the node found above is the root or not
    if(temp==root){
      while(temp->left!=nullptr)
        temp=temp->left;
      temp->left=node;
      node->parent=temp;
      root->parent=node;
    }
    else if(temp->parent->right==nullptr){
      temp=temp->parent;
      temp->right=node;
      node->parent=temp;
      root->parent=node;
    }
    else{
      temp=temp->parent->right;
      while(temp->left!=nullptr)
        temp=temp->left;
      temp->left=node;
      node->parent=temp;
      root->parent=node;
    }

//****************************************************************************************

    //while loop to rectify the heap property which was possibly violated after inserting the new node
    while((node->parent->object)<(node->object)){
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

//****************************************************************************************
//-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//****************************************************************************************

template<typename T>
void Heap<T>::delMax() {
  //To check whether the heap is empty or not
  if(root==nullptr){
    cout<<"Heap is Empty"<<endl;
    return;
  }

//****************************************************************************************

  TreeNode<T> *temp=root->parent;
  //To check whether the root is the only element in the heap
  if(temp==root){
    delete root;
    root=nullptr;
  }
  else{
    //while loop to find the would-be last element in the heap
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
      temp=temp->parent->left;
      while(temp->right!=nullptr)
        temp=temp->right;
    }

//****************************************************************************************

    //To move the last elemet to the root
    root->object=root->parent->object;
    if(root->parent->parent->right==root->parent)
      root->parent->parent->right=nullptr;
    else
      root->parent->parent->left=nullptr;
    delete root->parent;
    root->parent=temp;

//****************************************************************************************

    //To rectify the heap property which may have been violated due to deleting the root and putting some other element in its place
    temp=root;
    while(true){
      if(temp->left!=nullptr && (temp->object)<(temp->left->object)){
        if(temp->right!=nullptr && (temp->left->object)<(temp->right->object)){
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
      else if(temp->right!=nullptr && (temp->object)<(temp->right->object)){
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

//****************************************************************************************
//-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//****************************************************************************************

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  //To check whether the heap is empty or not
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
  if(node->left!=nullptr){
    spacer=spacer+"    ";
    printHeap(node->left);
    spacer=spacer.substr(0,spacer.length()-4);
  }

  return;
}

  
