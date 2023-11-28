#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath>

// function to swap the objects of the two treenodes passed as arguments
template<typename T>
void Heap<T>::swap (TreeNode<T> *node1, TreeNode<T> *node2){
  T temp = node1->object;
  node1->object = node2->object;
  node2->object = temp;
}

// heapify process at the node passed as an argument
template<typename T>
void Heap<T>::heapify (TreeNode<T> *node){
  if(node == nullptr) return;
  heapify(node->left);
  heapify(node->right);
  if(node->left == nullptr && node->right == nullptr)return;
  else if(node->right == nullptr){
    if(node->object < node->left->object){
      swap(node,node->left);
    }
  }
  else{
    if(node->left->object < node->right->object && node->object < node->right->object ){
      swap(node, node->right);
    }
    else if(node->object < node->left->object){
      swap(node, node->left);
    }
  }
  return;
}

//function to heapify the heap from the argument node upwards
template<typename T>
void Heap<T>::heapifyup (TreeNode<T> *node){
  if(node == nullptr) return;
  if(node->parent == nullptr)return;
  if(node->parent->object < node->object) {
    swap(node, node->parent);
    heapifyup(node->parent);
  }
  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  cout<<"1"<<endl;
  if(root == nullptr){
    cout << "root is null" << endl;
    root = new TreeNode<T>(obj);
    lastnode = root;
    totalnodes++;
    return;
  }
  TreeNode<T> *n1 = lastnode;
  if(lastnode == root ){
    if(lastnode->left == nullptr){
      root->left = new TreeNode<T>(obj);
      root->left->parent = root;
      if(root->object < root->left->object) swap(root, root->left);
      lastnode = root->left;
      totalnodes++;
    }
    else{
      root->right = new TreeNode<T>(obj);
      root->right->parent = root;
      if(root->object < root->right->object) swap(root, root->right);
      lastnode = root->right;
      totalnodes++;
    }
    return;
  }
  TreeNode<T> *p = lastnode->parent;
  bool isleft = (p->left == lastnode);
  if(isleft == true){
    p->right = new TreeNode<T>(obj);
    p->right->parent = p;
    lastnode = p->right;
    totalnodes++;
    heapifyup(lastnode);
    return;
  }
  if(lastnode == lastnode->parent->right){
    TreeNode<T> *p = lastnode->parent;
    while(p!=nullptr){
      if(p->left == lastnode){
        p=p->right;
        break;
      }
      p=p->parent;
      lastnode=lastnode->parent;
    }
    if(p==nullptr){
      p=root;
    }
    while(p->left !=nullptr){
      p=p->left;
    }
    p->left = new TreeNode<T>(obj);
    p->left->parent = p;
    lastnode=p->left;
  }
  else{
    lastnode->parent->right = new TreeNode<T>(obj);
    lastnode->parent->right->parent = lastnode->parent;
    lastnode=lastnode->parent->right;
    }
  totalnodes++;
  heapifyup(lastnode);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr)return;
  if(lastnode == root){
    root = nullptr;
    totalnodes--;
    lastnode = nullptr;
    return;
  }
  swap(lastnode, root);
  if(lastnode == lastnode->parent->right){
    lastnode=lastnode->parent->left;
    delete lastnode->parent->right;
    lastnode->parent->right = nullptr;
  }
  else{
    lastnode=lastnode->parent;
    delete lastnode->left;
    lastnode->left=nullptr;
    TreeNode<T> *p = lastnode->parent;
    while(p!=nullptr){
      if(p->right == lastnode){
        p=p->left;
        break;
      }
      p=p->parent;
      lastnode=lastnode->parent;
    }
    if(p==nullptr){
      p=root;
    }
    while(p->right !=nullptr){
      p=p->right;
    }
    lastnode=p;
  }
  totalnodes--;
  heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft)
{
  if( root != nullptr ){
      cout << prefix;
      cout << (isLeft ? "|--" : "|__" );
      // print the value of the node
      cout << root->object << endl;
      TreeNode<T> *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printHeap( prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printHeap( prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
  }
}

  
